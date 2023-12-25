#make clean; make build; cat tasks/my_octave/tests/00-my_octave/00-my_octave.in | valgrind --log-file=mem.dump --leak-check=full --track-origins=yes --show-reachable=no --show-leak-kinds=all ./my_octave
make clean; make build;
mv pgm cmake-build-debug
cd cmake-build-debug
valgrind --log-file=../mem.dump --leak-check=full --track-origins=yes --show-reachable=no --show-leak-kinds=all ./image_editor
