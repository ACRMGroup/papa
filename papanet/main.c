#include <stdio.h>
#include <math.h>

#include "papanet.h"

#define TERMINATE(x) do {                       \
   int _terminate_macro_j;                      \
                       \
   for(_terminate_macro_j=0;                    \
                        \
   (x)[_terminate_macro_j];                     \
                     \
       _terminate_macro_j++)                     \
   {                                             \
   if((x)[_terminate_macro_j] == '\n')        \
   {                                          \
   (x)[_terminate_macro_j] = '\0';            \
            \
   break;   \
                                     \
   }                                 \
   }                                 \
   }                                 \
   while(0)


int main(int argc, char **argv)
{
   float in[80];
   float out[8];
   
   if(ReadData(argv[1], in))
   {
      papanet(in, out, 0);
   }
   
   else
   {
   }
   
   
   

   return(0);
}

int ReadData(char *filename, float *in)
{
   FILE *fp;
   char buffer[80];
   
   
   if((fp=fopen(filename, "r"))!=NULL)
   {
      int numOfCount = 0;
      int valCount   = 0;
      
      while(fgets(buffer, fp))
      {
         TERMINATE(buffer);
         if(!strncmp(buffer, "# Dummy", 7))
            break;
         
         if(numOfCount == 3)
         {
            if(strlen(buffer))
            {
               int i;
               
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
   }
   else
   {
      return(0);
   }
   return(1);
}
