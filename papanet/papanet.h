/*********************************************************
  papanet.h
  --------------------------------------------------------
  generated at Thu Oct 13 16:43:32 2016
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

extern int papanet(float *in, float *out, int init);

static struct {
  int NoOfInput;    /* Number of Input Units  */
  int NoOfOutput;   /* Number of Output Units */
  int(* propFunc)(float *, float*, int);
} papanetREC = {52,1,papanet};
