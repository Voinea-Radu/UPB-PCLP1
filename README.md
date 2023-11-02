# Tema 1

**Nume**: Voinea Radu-Mihai
**Grupa**: 315 CA

## Table Of Contents

1. [Un Produs Infinit](#un-produs-infinit)
2. [Perfectionarea Punctajelor](#perfectionarea-punctajelor)
3. [Gigel si Tabla de Sah](#gigel-si-tabla-de-sah)
4. [Nanogram Checker](#nanogram-checker)

### Un Produs Infinit

In aceasta problema avem de calculat produsul scalar, al doilea maxim si norma
asociata 2 vectori de dimensiune n. Pentru o eficienta a memoriei utilizate,
vom procesa datele la citire, fara a le retine in memorie.
Astfel:

- Pentru a calcula produsul vectorial vom calcula produsul coordonatelor doua
  cate doua, stocand suma acestora.
- Pentru a calcula al doilea maxim vom retine in memorie maximum si cel de al
  doilea maxim si le vom compara cu fiecare nou element
- Pentru a calcula norma vom calcula patratelor coordonatelor, stocand suma
  acestora. La final vom calcula radicalul din suma.

### Perfectionarea Punctajelor

In aceasta problema trebuie sa determinam numarul minim de materii la care
media trebuie sa devina 10 pentru indeplinirea unui prag de punctaj.
Pentru a rezolva aceasta problema trebuie sa calculam numarul de puncte
dobandite curent urma de determinarea celor mai mari diferente dintre punctajul
obtinut curent si punctajul posibil (il vom nota delta). Pentru fiecare iteratie
vom calcula delta maxim si marca materia ca fiind perfectionata. Vom repeta
pana cand punctajul total trece de pragul mentionat.

### Gigel si Tabla de Sah

In aceasta problema fiind data o tabla de dimensiune n*n si n*n bilete pentru
fiecare pozitie, trebuie determinata pozitia in care procesarea tablii se
opreste. Pentru a rezolva aceasta problema vom itera confirm regulilor si vom
marca pozitiile pe care ne-am deplasat deja ca atare. Vom repeta pana cand
se indeplineste conditia de temrinare sau revizitam aceasi casuta

### Nanogram Checker

In aceasta problema trebuie sa determinam daca o rezolvare a unei nanograme este
valida. Pentru a rezolva aceasta problema vom verifica daca fiecare linie si
fiecare coloana are exact numarul de reguli asociate fiecareia iar fiecare
subsectiune de linie sau coloana are dimensiuna corelata din din regulile
acesteia


