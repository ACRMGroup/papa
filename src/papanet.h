/*********************************************************
  papanet.h
  --------------------------------------------------------
  generated at Tue Oct 15 10:03:20 2019
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

extern int papanet(float *in, float *out, int init);

static struct {
  int NoOfInput;    /* Number of Input Units  */
  int NoOfOutput;   /* Number of Output Units */
  int(* propFunc)(float *, float*, int);
} papanetREC = {52,1,papanet};
