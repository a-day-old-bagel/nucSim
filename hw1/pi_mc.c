
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Marsaglia RNG
#include "random_number.h"

void printProgressUpdate(unsigned long progress, unsigned long expected, unsigned long frequency) {
  if (1 == (progress % frequency)) {
    printf("\r\t%.0F%%", (progress / (double)expected) * 100.);
    fflush(stdout);
  }
}

int main(int argc, char *argv[]) {

  unsigned long nShots = 3; // default number of random numbers to generate
  unsigned long nCircleHits = 0;
  unsigned long nSquareHits = 0;
  FILE *dataFile = NULL;
  int writeToFile = 1; // whether or not the shots will be written to a data file (always true unless too many shots)

  start_random_number(101, 202); // supply the seeds to begin the RNG
  printf("Generating random numbers using the Marsaglia method...\n");

  if (argc > 1) { // if user provided number of shots to take, get that value, otherwise inform of that option
    nShots = strtoul(argv[1], NULL, 0);
    if ( ! nShots) {
      fprintf(stderr, "Invalid number of shots given!\n");
      exit(1);
    } else if (nShots > 1000000) { // try not to produce text files larger than 2 MB
      fprintf(stderr, "%lu is too many shots to be written to a file, but the answer will still be given.\n", nShots);
      writeToFile = 0;
    } else {
      printf("Shots (x, y) will be recorded in shots.dat as two columns of text.\n");
    }
  } else {
    printf("Number of shots taken may be provided as a program argument. Default value will be used this time.\n");
  }
  printf("Generating %lu random numbers...\n", nShots);

  if (writeToFile) {
    dataFile = fopen("shots.dat", "w"); // Open a file to which to write shot data
    if (dataFile == NULL) {
      fprintf(stderr, "Error opening shots.dat file to write!\n");
      exit(1);
    }
  }

  for (; nSquareHits < nShots; ++nSquareHits) { // take the shots, record in data file
    double x = next_random_number();
    double y = next_random_number();
    nCircleHits += sqrt(x * x + y * y) <= 1.0;
    if (writeToFile) { fprintf(dataFile, "%F %F\n", x, y); }
    printProgressUpdate(nSquareHits, nShots, 1000000); // update user to show progress
  }
  printProgressUpdate(3, 3, 2); // set progress report to 100%

  if (writeToFile) { fclose(dataFile); } // close data file (if necessary) and report results
  printf("\nPi = 4 * %lu / %lu = %g\n", nCircleHits, nSquareHits, 4. * nCircleHits / (double)nSquareHits);

  return 0;
}

