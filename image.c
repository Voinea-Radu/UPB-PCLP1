/*
Nume: Voinea Radu-Mihai
Grupa: 315 CA
*/

#include <string.h>
#include "image.h"
#include "utils.h"
#include <math.h>

image_t new_image(FILE *file)
{
	bool is_comment = false;

	string_t buffer = safe_malloc(MAX_PGM_LINE_SIZE * sizeof(char));
	size_t buffer_size = 0;

	reset_buffer(buffer, &buffer_size);

	image_t image = new_empty_image();

	image.state = IMAGE_READ_PGM_TYPE;
	image.load = image_read_type;

	char data;
	while (1) {
		data = (char)fgetc(file);

		if (data == '#' && !is_binary(&image))
			is_comment = true;

		if (data == '\n') {
			if (is_comment) {
				is_comment = false;
				continue;
			}
			is_comment = false;
		}

		if (is_comment)
			continue;

		// Binary file format
		if (is_reading_binary(&image)) {
			buffer[buffer_size++] = data;
			buffer[buffer_size] = '\0';

			image.load(&image, buffer);
			reset_buffer(buffer, &buffer_size);
		} else {
			// ASCII file format
			if (data == '\n' || data == ' ' || data == '\t') {
				if (buffer_size == 0)
					continue;

				image.load(&image, buffer);
				reset_buffer(buffer, &buffer_size);
			} else {
				buffer[buffer_size++] = data;
				buffer[buffer_size] = '\0';
			}
		}

		if (image.state == IMAGE_LOADED || image.state == IMAGE_NOT_LOADED)
			break;
	}

	free(buffer);
	return image;
}

void image_read_type(image_t *image, string_t buffer)
{
	image->type = buffer[1] - '0';

	image->state = IMAGE_LOADING;
	image->load = image_read_width;
}

void image_read_width(image_t *image, string_t buffer)
{
	image->width = strtol(buffer, NULL, 10);

	image->load = image_read_height;
}

void image_read_height(image_t *image, string_t buffer)
{
	image->height = strtol(buffer, NULL, 10);

	if (image->height == 0 || image->width == 0) {
		image->state = IMAGE_NOT_LOADED;
		return;
	}

	// Create the data matrix
	image->data = malloc(image->height * sizeof(pixel_t *));
	for (size_t i = 0; i < image->height; i++) {
		image->data[i] = malloc(image->width * sizeof(pixel_t));
		for (size_t j = 0; j < image->width; j++)
			image->data[i][j] = new_pixel_color(0, 0, 0);
	}

	// Set the selection to the full image
	__u32 x1 = 0;
	__u32 y1 = 0;
	__u32 x2 = image->width;
	__u32 y2 = image->height;
	set_selection(image, &x1, &y1, &x2, &y2);

	image->load = image_read_max_value;
}

void image_read_max_value(image_t *image, string_t buffer)
{
	image->state = IMAGE_READ_DATA;

	if (image->type == 1 || image->type == 4) {
		if (is_mono(image))
			image_read_mono_data(image, buffer);
		return;
	}

	// Format 2 3 5 6
	if (is_mono(image))
		image->load = image_read_mono_data;
	else
		image->load = image_read_rgb_data;
}

void image_read_mono_data(image_t *image, string_t buffer)
{
	int scalar = 1;

	if (image->type == 1 || image->type == 4)
		scalar = 255;

	image->data[image->read_y][image->read_x] =
			new_pixel_mono_color(is_binary(image) ?
								 (int)buffer[0] :
								 strtol(buffer, NULL, 10) * scalar);

	image->read_x++;
	if (image->read_x == image->width) {
		image->read_x = 0;
		image->read_y++;
	}

	if (image->read_y == image->height)
		image->state = IMAGE_LOADED;
}

void image_read_rgb_data(image_t *image, string_t buffer)
{
	switch (image->state) {
	case IMAGE_READ_DATA:
	case IMAGE_READ_DATA_RED:
		image->data[image->read_y][image->read_x].red = is_binary(image) ?
														(int)buffer[0] :
														strtol(buffer, NULL,
															   10);
		image->state = IMAGE_READ_DATA_GREEN;
		break;
	case IMAGE_READ_DATA_GREEN:
		image->data[image->read_y][image->read_x].green = is_binary(image) ?
														  (int)buffer[0] :
														  strtol(buffer,
																 NULL, 10);
		image->state = IMAGE_READ_DATA_BLUE;
		break;
	case IMAGE_READ_DATA_BLUE:
		image->data[image->read_y][image->read_x].blue = is_binary(image) ?
														 (int)buffer[0] :
														 strtol(buffer,
																NULL, 10);
		image->state = IMAGE_READ_DATA_RED;

		image->read_x++;
		if (image->read_x == image->width) {
			image->read_x = 0;
			image->read_y++;
		}

		if (image->read_y == image->height)
			image->state = IMAGE_LOADED;

		break;
	}
}

bool is_mono(image_t *image)
{
	return image->type == 1 || image->type == 2 || image->type == 4 ||
		   image->type == 5;
}

pixel_t new_pixel_mono_color(u__s8 color)
{
	pixel_t output;

	output.red = color;
	output.green = color;
	output.blue = color;

	return output;
}

pixel_t new_pixel_color(u__s8 red, u__s8 green, u__s8 blue)
{
	pixel_t output;

	output.red = red;
	output.green = green;
	output.blue = blue;

	return output;
}

void free_image_pointer(image_t *image)
{
	free_image(*image);
	free(image);
}

void free_image(image_t image)
{
	free_data(&image.data, image.height);
}

void free_data(pixel_t ***data, __u32 size_y)
{
	for (size_t i = 0; i < size_y; i++)
		free((*data)[i]);

	free(*data);
}

image_t new_empty_image(void)
{
	image_t image;

	image.type = 0;

	image.width = 0;
	image.height = 0;

	image.data = NULL;

	image.selection_start = new_position(0, 0);
	image.selection_end = new_position(0, 0);

	// TODO Maybe remove at some point
	// image.max_data_value = 0;

	image.read_x = 0;
	image.read_y = 0;
	image.state = IMAGE_NOT_LOADED;

	image.load = NULL;

	return image;
}

bool is_reading_binary(image_t *image)
{
	bool flag1 = is_binary(image);
	bool flag2 = image->state == IMAGE_READ_DATA ||
				 image->state == IMAGE_READ_DATA_RED ||
				 image->state == IMAGE_READ_DATA_GREEN ||
				 image->state == IMAGE_READ_DATA_BLUE;

	return flag1 && flag2;
}

bool is_binary(image_t *image)
{
	return image->type == 4 || image->type == 5 || image->type == 6;
}

position_t new_position(__u32 x, __u32 y)
{
	position_t position;

	position.x = x;
	position.y = y;

	return position;
}

int set_selection(image_t *image, __u32 *x1, __u32 *y1, __u32 *x2,
				  __u32 *y2)
{
	// The (-1)s are because the specification stats that the selection is
	// inclusive to the left and top and exclusive to the right
	// [x1, x2) [y1, y2)

	if (*x1 == *x2 || *y1 == *y2)
		return 1;

	__u32 real_x1 = min(*x1, *x2);
	__u32 real_x2 = max(*x1, *x2);
	__u32 real_y1 = min(*y1, *y2);
	__u32 real_y2 = max(*y1, *y2);

	*x1 = real_x1;
	*x2 = real_x2;
	*y1 = real_y1;
	*y2 = real_y2;

	if (*x1 >= image->width || *x2 > image->width || *y1 >= image->height ||
		*y2 > image->height)
		return 1;

	image->selection_start = new_position(*x1, *y1);
	image->selection_end = new_position(*x2 - 1, *y2 - 1);

	return 0;
}

__u32 *generate_histogram(image_t *image)
{
	return generate_histogram_coords(image, image->selection_start.x,
									 image->selection_start.y,
									 image->selection_end.x,
									 image->selection_end.y);
}

__u32 *
generate_histogram_coords(image_t *image, __u32 start_x, __u32 start_y,
						  __u32 end_x, __u32 end_y)
{
	__u32 *histogram = calloc(260, sizeof(__u32));

	for (size_t i = start_y; i <= end_y; i++)
		for (size_t j = start_x; j <= end_x; j++)
			histogram[image->data[i][j].red]++;

	return histogram;
}

void print_histogram(image_t *image, __u32 max_stars, __u32 bins)
{
	if (image->state == IMAGE_NOT_LOADED) {
		printf("No image loaded\n");
		return;
	}

	if (!is_mono(image)) {
		printf("Black and white image needed\n");
		return;
	}

	__u32 *histogram = generate_histogram(image);

	__u32 *binned_histogram = calloc(bins, sizeof(__u32));

	__u32 elements_per_bin = 256 / bins;

	__u32 max_value = 0;

	for (int bin_index = 0; bin_index < bins; bin_index++)
		for (int element_index = 0;
			 element_index < elements_per_bin; element_index++) {
			binned_histogram[bin_index] += histogram
			[bin_index * elements_per_bin + element_index];

			if (binned_histogram[bin_index] > max_value)
				max_value = binned_histogram[bin_index];
		}

	for (int i = 0; i < bins; i++) {
		int stars = (int)(1.0 * binned_histogram[i] * max_stars / max_value);

		printf("%d\t|\t", stars);

		for (int j = 0; j < stars; j++)
			printf("*");

		printf("\n");
	}

	free(histogram);
	free(binned_histogram);
}

void equalize(image_t *image)
{
	if (image->state == IMAGE_NOT_LOADED) {
		printf("No image loaded\n");
		return;
	}

	if (!is_mono(image)) {
		printf("Black and white image needed\n");
		return;
	}

	__u32 *histogram = generate_histogram_coords(image, 0, 0,
												 image->width - 1,
												 image->height - 1);

	double area_reversed = 1.0 / (image->width * image->height);

	for (__u32 y = 0; y < image->height; y++)
		for (__u32 x = 0; x < image->width; x++) {
			__u32 sum = 0;

			for (__u32 i = 0; i <= image->data[y][x].red; i++)
				sum += histogram[i];

			image->data[y][x].red = (u__s8)round(255.0 * area_reversed * sum);
			image->data[y][x].red = clamp(image->data[y][x].red, 0, 255);
		}

	free(histogram);
	printf("Equalize done\n");
}

void save_image_ascii(image_t *image, FILE *file)
{
	if (image->type > 3)
		fprintf(file, "P%d\n", image->type - 3);
	else
		fprintf(file, "P%d\n", image->type);

	fprintf(file, "%zu %zu\n", image->width, image->height);

	if (image->type == 1 || image->type == 4)
		fprintf(file, "1\n");
	else
		fprintf(file, "255\n");

	for (size_t i = 0; i < image->height; i++) {
		for (size_t j = 0; j < image->width; j++)
			if (is_mono(image))
				fprintf(file, "%d ", image->data[i][j].red);
			else
				fprintf(file, "%d %d %d ", image->data[i][j].red,
						image->data[i][j].green, image->data[i][j].blue);

		fprintf(file, "\n");
	}
}

void save_image_binary(image_t *image, FILE *file)
{
	if (image->type <= 3)
		fprintf(file, "P%d\n", image->type + 3);
	else
		fprintf(file, "P%d\n", image->type);

	fprintf(file, "%zu %zu\n", image->width, image->height);

	if (image->type == 1 || image->type == 4)
		fprintf(file, "1\n");
	else
		fprintf(file, "255\n");

	for (size_t i = 0; i < image->height; i++)
		for (size_t j = 0; j < image->width; j++)
			if (is_mono(image))
				fprintf(file, "%c", image->data[i][j].red);
			else
				fprintf(file, "%c%c%c", image->data[i][j].red,
						image->data[i][j].green, image->data[i][j].blue);
}

void rotate(image_t *image, __s16 degrees)
{
	if (image->state == IMAGE_NOT_LOADED) {
		printf("No image loaded\n");
		return;
	}

	if (degrees == 0) {
		printf("Rotated 0\n");
		return;
	}

	if (degrees > 360 || degrees < -360 || degrees % 90 != 0) {
		printf("Unsupported rotation angle\n");
		return;
	}

	u__s8 iterations = abs(degrees) / 90;

	__u32 size_x = image->selection_end.x - image->selection_start.x + 1;
	__u32 size_y = image->selection_end.y - image->selection_start.y + 1;

	if (size_x == image->width && size_y == image->height) {
		rotate_matrix(image, degrees, size_x, size_y, iterations);
		return;
	}

	rotate_sub_matrix(image, degrees, size_x, size_y, iterations);
}

void
rotate_matrix(image_t *image, __s16 degrees, __u32 size_x, __u32 size_y,
			  u__s8 iterations)
{
	pixel_t **new_data;
	init_image_data(&new_data, size_y, size_x);

	for (__u32 y = 0; y < size_y; y++) {
		for (__u32 x = 0; x < size_x; x++) {
			if (degrees > 0) {
				pixel_t pixel = image->data[size_y - y - 1][x];
				new_data[x][y] = pixel;
			} else {
				new_data[x][y] = image->data[y][size_x - x - 1];
			}
		}
	}

	free_image(*image);

	image->width = size_y;
	image->height = size_x;

	image->selection_start = new_position(0, 0);
	image->selection_end = new_position(image->width - 1, image->height - 1);

	image->data = malloc(image->height * sizeof(pixel_t *));
	for (size_t i = 0; i < image->height; i++)
		image->data[i] = malloc(image->width * sizeof(pixel_t));

	free_data(&image->data, image->height);

	image->data = new_data;

	if (iterations != 1) {
		rotate_matrix(image, degrees, size_y, size_x, iterations - 1);
		return;
	}

	printf("Rotated %d\n", degrees);
}

void rotate_sub_matrix(image_t *image, __s16 degrees, __u32 size_x,
					   __u32 size_y, u__s8 iterations)
{
	if (size_x != size_y) {
		printf("The selection must be square\n");
		return;
	}

	pixel_t **new_data;
	init_image_data(&new_data, size_x, size_y);

	for (__u32 y = 0; y < size_y; y++)
		for (__u32 x = 0; x < size_x; x++)
			if (degrees > 0) {
				new_data[x][y] = image->data
				[image->selection_start.y + size_y - y - 1]
				[image->selection_start.x + x];
			} else {
				new_data[x][y] = image->data[image->selection_start.y + y]
				[image->selection_start.x + size_x - x - 1];
			}

	for (__u32 y = 0; y < size_y; y++) {
		for (__u32 x = 0; x < size_x; x++) {
			image->data[image->selection_start.y + y][image->selection_start.x +
													  x] = new_data[y][x];
		}
	}

	free_data(&new_data, size_y);

	if (iterations != 1) {
		rotate_sub_matrix(image, degrees, size_y, size_x, iterations - 1);
		return;
	}

	printf("Rotated %d\n", degrees);
}

void init_image_data(pixel_t ***data_pointer, __u32 size_x, __u32 size_y)
{
	*data_pointer = safe_malloc(size_y * sizeof(__u32 *));
	for (__u32 i = 0; i < size_y; i++)
		(*data_pointer)[i] = safe_malloc(size_x * sizeof(__u32));
}

void crop(image_t *image)
{
	if (image->state == IMAGE_NOT_LOADED) {
		printf("No image loaded\n");
		return;
	}

	__u32 size_x = image->selection_end.x - image->selection_start.x + 1;
	__u32 size_y = image->selection_end.y - image->selection_start.y + 1;

	pixel_t **new_data;
	init_image_data(&new_data, size_x, size_y);

	for (__u32 y = 0; y < size_y; y++)
		for (__u32 x = 0; x < size_x; x++)
			new_data[y][x] = image->data[image->selection_start.y + y]
			[image->selection_start.x + x];

	free_data(&image->data, image->height);

	image->width = size_x;
	image->height = size_y;

	image->selection_start = new_position(0, 0);
	image->selection_end = new_position(image->width - 1, image->height - 1);

	image->data = new_data;

	printf("Image cropped\n");
}

bool apply_filter(image_t *image, __s8 filter[3][3], double factor)
{
	if (image->state == IMAGE_NOT_LOADED) {
		printf("No image loaded\n");
		return false;
	}

	if (is_mono(image)) {
		printf("Easy, Charlie Chaplin\n");
		return false;
	}

	pixel_t **new_data = safe_malloc(image->height * sizeof(__u32 *));
	for (__u32 i = 0; i < image->height; i++)
		new_data[i] = safe_malloc(image->width * sizeof(__u32));

	for (__u32 y = max(image->selection_start.y, 1);
		 y <= min(image->selection_end.y, image->height - 2); y++) {
		for (__u32 x = max(image->selection_start.x, 1);
			 x <= min(image->selection_end.x, image->width - 2); x++) {
			__s16 red = 0;
			__s16 green = 0;
			__s16 blue = 0;

			for (__s8 i = -1; i <= 1; i++) {
				for (__s8 j = -1; j <= 1; j++) {
					red += image->data[y + i][x + j].red * filter[i + 1][j + 1];
					green += image->data[y + i][x + j].green *
							 filter[i + 1][j + 1];
					blue += image->data[y + i][x + j].blue *
							filter[i + 1][j + 1];
				}
			}

			red = (__s16)round(red * factor);
			green = (__s16)round(green * factor);
			blue = (__s16)round(blue * factor);

			red = clamp(red, 0, 255);
			green = clamp(green, 0, 255);
			blue = clamp(blue, 0, 255);

			new_data[y][x] = new_pixel_color((u__s8)red, (u__s8)green,
											 (u__s8)blue);
		}
	}

	for (__u32 y = max(image->selection_start.y, 1);
		 y <= min(image->selection_end.y, image->height - 2); y++) {
		for (__u32 x = max(image->selection_start.x, 1);
			 x <= min(image->selection_end.x, image->width - 2); x++) {
			image->data[y][x] = new_data[y][x];
		}
	}

	free_data(&new_data, image->height);

	return true;
}
