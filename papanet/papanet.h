/*********************************************************
  papanet.h
  --------------------------------------------------------
  generated at Mon Oct 17 15:17:17 2016
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

extern int papanet(float *in, float *out, int init);

static struct {
  int NoOfInput;    /* Number of Input Units  */
  int NoOfOutput;   /* Number of Output Units */
  int(* propFunc)(float *, float*, int);
} papanetREC = {52,1,papanet};
