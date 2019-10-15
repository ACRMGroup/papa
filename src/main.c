/************************************************************************/
/**

   Program:    papanet
   \file       main.c
   
   \version    V1.0
   \date       13.10.16       
   \brief      C program to run Abhi's packing angle prediction network
   
   \copyright  (c) UCL / Dr. Andrew C. R. Martin 2016
   \author     Dr. Andrew C. R. Martin
   \par
               Institute of Structural & Molecular Biology,
               University College,
               Gower Street,
               London.
               WC1E 6BT.
   \par
               andrew@bioinf.org.uk
               andrew.martin@ucl.ac.uk
               
**************************************************************************

   This program is not in the public domain, but it may be copied
   according to the conditions laid out in the accompanying file
   COPYING.DOC

   The code may be modified as required, but any modifications must be
   documented so that the person responsible can be identified.

   The code may not be sold commercially or included as part of a 
   commercial product except as described in the file COPYING.DOC.

**************************************************************************

   Description:
   ============
   This code uses the snns2c function built from Abhi's packing angle 
   predictor to avoid needing to install SNNS

**************************************************************************

   Usage:
   ======
   papanet file.in

**************************************************************************

   Revision History:
   =================
   V1.0    13.10.16 Original   By: ACRM

*************************************************************************/
/* Includes
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "papanet.h"

/************************************************************************/
/* Defines and macros
*/
#define MAXBUFF 80

#define TERMINATE(x) do {                                               \
      int _terminate_macro_j;                                           \
      for(_terminate_macro_j=0;                                         \
          (x)[_terminate_macro_j];                                      \
          _terminate_macro_j++)                                         \
      {                                                                 \
         if((x)[_terminate_macro_j] == '\n')                            \
         {                                                              \
            (x)[_terminate_macro_j] = '\0';                             \
            break;                                                      \
         }                                                              \
      }                                                                 \
   }                                                                    \
   while(0)
   

/************************************************************************/
/* Globals
*/

/************************************************************************/
/* Prototypes
*/
int ReadData(char *filename, float *in);
int main(int argc, char **argv);
void Usage(void);

/************************************************************************/
int main(int argc, char **argv)
{
   float *in;
   float *out;
   
   in  = (float *)malloc(papanetREC.NoOfInput * sizeof(float));
   out = (float *)malloc(papanetREC.NoOfOutput * sizeof(float));
   

   if((argc != 2) || !strncmp(argv[1], "-h", 2))
   {
      Usage();
      return(0);
   }
   
   
   if(ReadData(argv[1], in))
   {
      papanetREC.propFunc(in, out, 0);
      
      printf("%f\n", out[0]);
   }
   else
   {
      fprintf(stderr, "Error (papanet): Unable to read input file: %s\n",
              argv[1]);
   }

   return(0);
}


/************************************************************************/
void Usage(void)
{
   fprintf(stderr,"\npapanet V1.0 (c) UCL, Dr. Andrew C.R. Martin\n");

   fprintf(stderr,"\nUsage: papanet in.txt \n");

   fprintf(stderr,"\npapanet performs a neural network prediction of \
packing angles using the\n");
   fprintf(stderr,"neural network trained by Abhinandan Raghavan, but \
as a standalone\n");
   fprintf(stderr,"program. This is used in the standalone version of \
the papa (Predict \n");
   fprintf(stderr,"Antibody Packing Angle) software.\n\n");
}


/************************************************************************/
int ReadData(char *filename, float *in)
{
   FILE *fp;
   char buffer[MAXBUFF];
   
   
   if((fp=fopen(filename, "r"))!=NULL)
   {
      int numOfCount = 0;
      int valCount   = 0;
      
      while(fgets(buffer, MAXBUFF, fp))
      {
         TERMINATE(buffer);
         if(!strncmp(buffer, "# Dummy", 7))
            break;
         
         if(numOfCount == 3)
         {
            if(strlen(buffer))
            {
               int i;
               float values[4];
               
               
               sscanf(buffer, "%f %f %f %f",
                      &values[0], &values[1], &values[2], &values[3]);
               for(i=0; i<4; i++)
               {
                  in[valCount++] = values[i];
               }
            }
         }
         else
         {
            if(!strncmp(buffer, "No.", 3))
            {
               numOfCount++;
            }
         }
      }
fclose(fp);

   }
   else
   {
      return(0);
   }
   return(1);
}
