/*********************************************************
  papanet.h
  --------------------------------------------------------
  generated at Thu Feb  2 18:13:51 2023
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

extern int papanet(float *in, float *out, int init);

static struct {
  int NoOfInput;    /* Number of Input Units  */
  int NoOfOutput;   /* Number of Output Units */
  int(* propFunc)(float *, float*, int);
} papanetREC = {52,1,papanet};
