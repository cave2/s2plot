/* ss2sl.c
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

int main(int argc, char *argv[])
{
   COLOUR ambient = { 0.1, 0.0, 0.1 };		/* Ambient colour */
   int nlights = 1;				/* 1 light */
   XYZ *light;					/* Positions of lights */
   COLOUR *lcol;				/* Colours of lights */
   int wc = 1;					/* Use world coordinates */
   int i;					/* Loop variable */

   srand48((long)time(NULL));			/* Seed random numbers */
   s2opend("/?",argc, argv);			/* Open the display */
   s2swin(-1.,1., -1.,1., -1.,1.);		/* Set the window coordinates */
   s2box("BCDET",0,0,"BCDET",0,0,"BCDET",0,0);	/* Draw coordinate box */

   light = (XYZ *)   calloc(nlights, sizeof(XYZ));	/* Allocate memory */
   lcol  = (COLOUR *)calloc(nlights, sizeof(COLOUR));	/* Allocate memory */

   for (i=0;i<nlights;i++) {
      light[i].x = drand48()*2.0 - 1.0;	/* Random light position */
      light[i].y = drand48()*2.0 - 1.0;	
      light[i].z = drand48()*2.0 - 1.0;	
      lcol[i].r  = drand48();			/* Random colour */
      lcol[i].g  = 1.0;
      lcol[i].b  = drand48();			
      ns2vthpoint(light[i], lcol[i], 4);	/* Draw point where light is */
   }

   ns2sphere(0.0,0.0,0.0, 0.3, 1.0,1.0,1.0);	/* Draw a "white" sphere */

   ss2sl(ambient, nlights, light, lcol, wc); 	/* Turn on the lights */

   s2show(1);					/* Open the s2plot window */
   
   return 1;
}
