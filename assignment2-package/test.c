/* Show structure declarations and use.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PLANETSTRLEN 20

typedef char pstr_t[PLANETSTRLEN+1];

typedef struct {
	pstr_t  name, orbits;
	double  distance;        /* million km */
	double  mass;            /* kilograms */
	double  radius;          /* kilometers */
} planet_t;

planet_t the_earth =
	{"Earth", "Sun", 149.6, 5.9736e+24, 6738.1};
planet_t the_moon =
	{"Moon", "Earth", 0.3844, 7.349e+22, 1738.1};
planet_t another_planet;

#define PLANETPROMPT \
	"name, orbits, distance, mass, radius"


void print_planet(planet_t one_planet);
planet_t read_planet(void);
int read_planet_ptr(planet_t *one_planet);

int
main(int argc, char *argv[]) {
	planet_t planet;
	planet = read_planet();
	print_planet(planet);
	if (read_planet_ptr(&planet) != EOF) {
		print_planet(planet);
	}
	return 0;
}

void
print_planet(planet_t one_planet) {
	printf("%s orbits %s\n", one_planet.name,
		one_planet.orbits);
	printf("\torbital distance is %.2e million km\n",
		one_planet.distance);
	printf("\tmass is %.2e kg\n", one_planet.mass);
	printf("\tradius is %.2e km\n", one_planet.radius);
}

planet_t
read_planet(void) {
	planet_t new_planet;
	printf("Enter %s:\n", PLANETPROMPT);
	scanf("%s %s %lf %lf %lf",
		new_planet.name,
		new_planet.orbits,
		&new_planet.distance,
		&new_planet.mass,
		&new_planet.radius);
	return new_planet;
}

int
read_planet_ptr(planet_t *planet) {
	int nvals_read;
	printf("Enter %s:\n", PLANETPROMPT);
	nvals_read = scanf("%s %s %lf %lf %lf",
		planet->name,
		planet->orbits,
		&planet->distance,
		&planet->mass,
		&planet->radius);
	if (nvals_read != 5) {
		return EOF;
	} else {
		return 0;
	}
}

/* =====================================================================
   Program written by Alistair Moffat, as an example for the book
   "Programming, Problem Solving, and Abstraction with C", Pearson
   Custom Books, Sydney, Australia, 2002; revised edition 2012,
   ISBN 9781486010974.

   See http://people.eng.unimelb.edu.au/ammoffat/ppsaa/ for further
   information.

   Prepared December 2012 for the Revised Edition.
   ================================================================== */