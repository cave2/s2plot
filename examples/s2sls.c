/* s2sls.c
 *
 * Copyright 2006-2012 David G. Barnes, Paul Bourke, Christopher Fluke
 *
 * This file is part of S2PLOT.
 *
 * S2PLOT is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * S2PLOT is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with S2PLOT.  If not, see <http://www.gnu.org/licenses/>. 
 *
 * We would appreciate it if research outcomes using S2PLOT would
 * provide the following acknowledgement:
 *
 * "Three-dimensional visualisation was conducted with the S2PLOT
 * progamming library"
 *
 * and a reference to
 *
 * D.G.Barnes, C.J.Fluke, P.D.Bourke & O.T.Parry, 2006, Publications
 * of the Astronomical Society of Australia, 23(2), 82-93.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "s2plot.h"

/* Global variables - needed in dynamic callback */
int N = 10;			/* Number of points */
float x[10], y[10], z[10];	/* Arrays of coordinate points */

void cb(double *t, int *kc)
{
   int qls;			/* Current line-style */
   static int ls = 0;		/* Keep track of last press */
   if (*kc != ls) {
      qls = s2qls();		/* Query line-style */
      s2sls((qls%5)+1);		/* Set a new line-style */
   }
   s2line(N, x, y, z);   	/* Draw the poly-line */
   ls = *kc;			/* Update key press count */
}

int main(int argc, char *argv[])
{
   int i;				/* Loop variable */

   fprintf(stderr,"Press <spacebar> to change line style\n");

   srand48((long)time(NULL));		/* Seed random numbers */
   s2opend("/?",argc, argv);		/* Open the display */
   s2swin(-1.,1., -1.,1., -1.,1.);	/* Set the window coordinates */
   s2box("BCDET",0,0,"BCDET",0,0,"BCDET",0,0);	/* Draw coordinate box */

   for (i=0;i<N;i++) {
      x[i] = drand48()*2.0 - 1.0;	/* Random (x,y,z) coordinates */
      y[i] = drand48()*2.0 - 1.0;
      z[i] = drand48()*2.0 - 1.0;
   }

   s2sci(S2_PG_YELLOW);			/* Set colour */
   s2slw(4);				/* Set line width */

   cs2scb(cb);				/* Install a dynamic callback */

   s2show(1);				/* Open the s2plot window */
   
   return 1;
}
