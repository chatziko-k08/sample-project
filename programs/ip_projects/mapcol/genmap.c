#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char *colorstr[] = {"red", "green", "blue", "yellow", "orange",
                    "violet", "cyan", "pink", "brown", "grey"};

int main(int argc, char *argv[])
{
   int i, j, ncountries, uncolperc = 100, density = 30, colornum = 4;
   long seed;
   char *color, **neighb;
   seed = time(NULL);
   if (argc == 1) {
      printf("Wrong usage\n");
      return 1;
   }
   ncountries = atoi(argv[1]);                     /* Number of countries */
   if (argc > 2)                                   /* Percentage of uncolored */
      uncolperc = atoi(argv[2]);                   /* countries in the output */
   if (argc > 3)
      density = atoi(argv[3]);                     /* Percentage of borders among countries */
   if (argc > 4)
      seed = atoi(argv[4]);                        /* Seed for the random number generator */
   if (argc > 5)
      colornum = atoi(argv[5]);                    /* Number of colors */
   if (colornum > (int) sizeof(colorstr)) {
      printf("Too many colors\n");
      return 1;
   }
   srand((unsigned int) seed);
   color = malloc(ncountries * sizeof(char));      /* Color matrix for the countries */
   neighb = malloc(ncountries * sizeof(char *));   /* Reserve space for the 2-D triangular */
   for (i = 0 ; i < ncountries - 1 ; i++)          /* matrix to hold countries' borders */
      neighb[i] = malloc((ncountries-i-1) * sizeof(char));
   for (i = 0 ; i < ncountries ; i++)
      color[i] = rand() % colornum + 1;            /* Select random color for each country */
   for (i = 0 ; i < ncountries-1 ; i++)
      for (j = i+1 ; j < ncountries ; j++) {
         neighb[i][j-i-1] = 0;
         if (color[i] != color[j])
            if ((100.0 * rand()) / ((double) RAND_MAX + 1.0) < (double) density)
               neighb[i][j-i-1] = 1;               /* Decide randomly about borders */
      }
   for (i = 0 ; i < (uncolperc * ncountries) / 100.0 ; i++) {
      j = rand() % ncountries;                     /* Uncolor some countries */
      while (color[j] == 0)                        /* according to the given percentage */
         j = (j + 1) % ncountries;
      color[j] = 0;
   }
   for (i = 0 ; i < ncountries ; i++) {            /* Print out the map */
      printf("%s C%05d", (color[i] == 0 ? "nocolor" : colorstr[color[i]-1]), i+1);
      for (j = 0 ; j < ncountries ; j++) {
         if (i < j)                                /* Express borders in both directions */
            if (neighb[i][j-i-1] == 1)
               printf(" C%05d", j+1);
         if (i > j)
            if (neighb[j][i-j-1] == 1)
               printf(" C%05d", j+1);
      }
      printf("\n");
   }
   return 0;
}
