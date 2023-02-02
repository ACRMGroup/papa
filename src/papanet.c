/*********************************************************
  papanet.c
  --------------------------------------------------------
  generated at Thu Feb  2 18:13:51 2023
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

#include <math.h>

#define Act_Logistic(sum, bias)  ( (sum+bias<10000.0) ? ( 1.0/(1.0 + exp(-sum-bias) ) ) : 0.0 )
#ifndef NULL
#define NULL (void *)0
#endif

typedef struct UT {
          float act;         /* Activation       */
          float Bias;        /* Bias of the Unit */
          int   NoOfSources; /* Number of predecessor units */
   struct UT   **sources; /* predecessor units */
          float *weights; /* weights from predecessor units */
        } UnitType, *pUnit;

  /* Forward Declaration for all unit types */
  static UnitType Units[64];
  /* Sources definition section */
  static pUnit Sources[] =  {
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, 
Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, 
Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, Units + 49, Units + 50, 
Units + 51, Units + 52, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, 
Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, 
Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, Units + 49, Units + 50, 
Units + 51, Units + 52, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, 
Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, 
Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, Units + 49, Units + 50, 
Units + 51, Units + 52, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, 
Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, 
Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, Units + 49, Units + 50, 
Units + 51, Units + 52, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, 
Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, 
Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, Units + 49, Units + 50, 
Units + 51, Units + 52, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, 
Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, 
Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, Units + 49, Units + 50, 
Units + 51, Units + 52, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, 
Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, 
Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, Units + 49, Units + 50, 
Units + 51, Units + 52, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, 
Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, 
Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, Units + 49, Units + 50, 
Units + 51, Units + 52, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, 
Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, 
Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, Units + 49, Units + 50, 
Units + 51, Units + 52, 
Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, 
Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, 
Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, 
Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, 
Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, Units + 49, Units + 50, 
Units + 51, Units + 52, 
Units + 53, Units + 54, Units + 55, Units + 56, Units + 57, Units + 58, Units + 59, Units + 60, Units + 61, Units + 62, 


  };

  /* Weigths definition section */
  static float Weights[] =  {
0.569890, 0.850530, 0.173350, -0.076050, 0.037490, -0.964850, -0.537850, -0.805380, -0.037220, -0.942250, 
-0.167680, 1.120250, 0.876290, 0.459370, 0.890600, 0.962400, -1.285040, 7.555810, -0.127070, 0.672110, 
0.251940, -2.615200, -0.693890, 0.903160, -0.860810, -24.445721, 0.278800, -2.030510, 0.418390, 0.878890, 
-0.529600, -3.620380, 0.261200, 2.944100, -0.227890, -0.368330, 0.442190, 0.047720, -0.525390, 1.267910, 
0.256430, 0.946430, 0.077920, 6.067400, 0.032710, 3.671330, -0.732970, 0.315960, -0.949390, 2.510200, 
-0.600720, -1.417200, 
-0.086550, 2.978440, -0.991060, -0.947950, -0.085930, -0.988560, 1.507850, 1.814690, 3.082970, 0.490560, 
-1.578310, 4.749040, 0.650530, -0.220920, -0.879590, -2.661430, 0.391150, -2.521450, -0.814560, -1.997600, 
0.087970, 7.689530, -0.034460, -1.806700, -0.283580, 7.165300, 0.569410, -0.470970, -0.960890, 3.456960, 
-0.948440, -0.324410, -0.660880, 4.110900, 0.240200, 4.573410, -0.047690, 3.944990, -1.324250, -9.074750, 
0.671170, -0.707930, 0.565060, 1.366500, -0.160590, 7.469530, 0.115360, 3.093450, 0.657530, -1.056990, 
0.334780, 3.031980, 
1.802320, 2.759970, -0.010480, 0.200320, 0.064600, 5.494160, 0.061730, -1.819040, 0.311270, 4.885580, 
0.111670, -3.036380, -0.126070, 0.860150, -0.618460, 0.077220, -1.007380, -8.738130, -0.668840, -10.916240, 
1.258950, 3.138720, 0.845420, -5.073430, -1.363090, 1.469600, -0.351440, 3.427660, -0.046440, -4.282360, 
-0.910210, 1.834460, 0.093180, 15.174920, 0.159630, 5.001020, 0.397610, 1.286970, 1.180180, 3.442410, 
0.169340, -0.260430, 1.345930, 2.205480, 0.048080, 2.188410, -0.423560, -0.885820, -0.161250, -11.880780, 
-0.631300, -0.208940, 
1.145940, 4.284970, -0.785860, -2.020190, 0.887100, -1.033270, 0.023810, 0.946780, -1.046920, 0.485150, 
-0.519860, -7.868630, 0.458770, 0.568400, 0.754500, -5.544500, 0.580260, -2.603950, 0.199030, -3.047440, 
-0.141300, -1.708880, 0.069500, 0.944820, 0.202770, -95.662643, -0.436070, 8.528730, -0.992280, 6.464060, 
-0.873510, 5.702690, -1.001160, -2.063980, 0.594080, -4.674400, -0.613480, 8.498820, 0.717890, -1.585310, 
-1.005810, -0.773440, -0.474690, -41.339581, 0.095060, 6.442460, 0.816180, -0.369700, -0.896270, -5.322410, 
-0.420190, -1.762540, 
5.044310, 24.499069, 0.875170, -8.149770, -0.371090, 32.427879, -0.332550, -9.955280, 0.187750, 5.747120, 
-0.886150, -3.260190, 0.286520, 0.873840, 0.985070, 0.611050, 0.266870, 15.368380, -1.190130, 6.697210, 
-0.343770, 21.271589, -0.003550, -10.566280, 0.201190, 91.710983, -0.459990, 10.723850, 0.776450, 30.015261, 
-0.492230, 0.532030, -0.166370, -39.187351, 0.942650, -2.941680, 100.177887, -98.373787, 99.409462, 0.030120, 
-0.013800, -0.961050, -0.225660, 5.168080, -0.493010, -0.307740, -0.943800, -1.874570, 0.336700, 9.973880, 
0.780580, -1.212370, 
-0.433640, 1.910040, 0.773420, 5.738520, 1.087140, 6.322430, 3.504890, 7.442330, 0.277080, -6.778780, 
-1.936670, -0.228150, -0.868490, -0.524720, -1.827820, -5.366800, 0.438330, 12.235510, -1.293610, 0.650320, 
-1.630980, -2.772050, -0.986410, 4.125840, 0.150150, 1.181920, 0.474300, 9.883800, 1.413130, 5.269010, 
-0.305800, -1.245470, -1.068190, 0.332650, 0.524830, 24.815760, -2.932920, 0.986700, -0.050770, 1.069630, 
0.068940, -0.795320, -0.381800, -2.765800, 1.141450, -4.501750, -0.256480, 0.176160, -0.810120, -5.281330, 
0.874950, 8.569850, 
-1.332550, 6.890580, 0.808510, 0.955740, -0.037190, 5.976090, 1.969210, -0.531900, 0.401270, 5.326220, 
1.364450, -0.212620, -0.291280, -0.785830, -0.238560, 5.638320, 0.293580, -1.891830, -0.857680, -2.597340, 
-0.673690, -2.101680, -0.183620, -8.553240, -0.034260, 3.190170, -0.484590, 10.572540, 0.966820, 2.642070, 
0.802580, -0.334660, 0.869020, 7.072400, -0.806150, 6.525740, -0.402260, 0.000340, -0.004260, 5.646550, 
0.247940, 0.886990, 0.023570, 11.128830, -0.982970, -8.761690, -1.427910, 1.338420, -0.736630, 16.647619, 
-0.885760, 12.192090, 
1.087970, -2.225130, -0.794630, -0.933160, 2.011110, -38.442139, 2.151310, -12.255720, -1.546180, 0.974130, 
3.899990, 0.222870, -1.095110, -0.009860, -0.986090, 12.527990, -0.521110, -9.587220, 0.234210, -14.648420, 
-0.281670, -13.716630, 3.974720, -10.631640, -0.216760, -2.044760, -0.570820, -3.827800, 0.644310, -12.219810, 
-0.036990, -2.457320, -2.062070, 16.562929, -0.750200, -13.890120, 0.128780, 5.057410, -2.185780, -12.061300, 
0.994800, 0.417310, -0.287380, -5.407210, 0.793960, -24.779280, 0.728210, -11.882780, 0.772670, -8.621020, 
-0.658390, -0.436850, 
1.294010, -4.273800, 0.353640, -1.534240, 0.672390, 4.921410, 0.053330, -0.919740, 1.483860, 5.829690, 
-0.906960, -2.343630, -0.317760, 0.652480, 0.017870, 5.341270, -1.675760, -5.524410, 0.741160, 5.708490, 
-0.913120, -1.581940, -0.382630, 3.978440, 0.446430, 5.106730, -0.296990, 12.341020, 1.055640, -1.297740, 
0.333700, -0.751860, 0.036440, 2.691000, -0.077970, 0.210930, 1.445610, -1.443940, -2.140640, -0.210400, 
0.563320, -0.048560, 0.663870, -16.171209, -0.555030, -21.189159, 0.325490, -9.502160, -0.319290, -1.553280, 
1.104130, 3.738650, 
0.560010, 4.894230, 0.319430, -14.167540, -0.221630, 20.961321, 0.608930, -6.294680, -0.155920, -7.333080, 
-0.286940, 0.696730, 0.202470, -0.425740, 0.848360, 0.694350, 0.317160, 14.831380, -0.820170, -3.331300, 
-0.299860, -0.643160, -0.770500, 3.375040, -0.444250, -32.004410, -0.595880, -1.510280, 0.370190, 12.126330, 
0.630580, 2.660300, 1.461350, 8.478930, 0.766050, 16.121840, 0.886980, -3.235110, -0.701790, 1.057580, 
0.478570, -0.545540, 0.719070, 3.955880, 0.471570, 2.920470, 1.473330, 2.670960, 0.705230, 3.295440, 
-0.896260, 17.954161, 
-1.509370, -0.661630, 0.665750, -0.779810, 0.568700, 0.552250, -0.428400, 0.533450, 0.395420, -0.713360, 


  };

  /* unit definition section (see also UnitType) */
  static UnitType Units[64] = 
  {
    { 0.0, 0.0, 0, NULL , NULL },
    { /* unit 1 (unit) */
      0.0, 1.000000, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 2 (unit) */
      0.0, 0.998030, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 3 (unit) */
      0.0, 0.916740, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 4 (unit) */
      0.0, 0.646710, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 5 (unit) */
      0.0, 0.270800, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 6 (unit) */
      0.0, 0.817340, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 7 (unit) */
      0.0, 0.815400, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 8 (unit) */
      0.0, 0.025570, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 9 (unit) */
      0.0, -0.053500, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 10 (unit) */
      0.0, 0.091130, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 11 (unit) */
      0.0, 0.533640, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 12 (unit) */
      0.0, -0.662580, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 13 (unit) */
      0.0, -0.863460, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 14 (unit) */
      0.0, -0.136120, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 15 (unit) */
      0.0, -0.112190, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 16 (unit) */
      0.0, 0.898340, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 17 (unit) */
      0.0, -0.534100, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 18 (unit) */
      0.0, 0.962170, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 19 (unit) */
      0.0, 0.495280, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 20 (unit) */
      0.0, 0.403610, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 21 (unit) */
      0.0, -0.751960, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 22 (unit) */
      0.0, -0.063110, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 23 (unit) */
      0.0, -0.840520, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 24 (unit) */
      0.0, -0.030860, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 25 (unit) */
      0.0, -0.620860, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 26 (unit) */
      0.0, 0.623160, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 27 (unit) */
      0.0, -0.772630, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 28 (unit) */
      0.0, -0.141230, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 29 (unit) */
      0.0, 0.846450, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 30 (unit) */
      0.0, -0.630550, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 31 (unit) */
      0.0, -0.969780, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 32 (unit) */
      0.0, 0.763300, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 33 (unit) */
      0.0, -0.787810, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 34 (unit) */
      0.0, -0.568970, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 35 (unit) */
      0.0, 0.798170, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 36 (unit) */
      0.0, 0.493380, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 37 (unit) */
      0.0, 0.960320, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 38 (unit) */
      0.0, 0.243250, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 39 (unit) */
      0.0, -0.357750, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 40 (unit) */
      0.0, -0.361850, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 41 (unit) */
      0.0, -0.505410, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 42 (unit) */
      0.0, 0.987540, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 43 (unit) */
      0.0, -0.248810, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 44 (unit) */
      0.0, 0.747080, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 45 (unit) */
      0.0, -0.235100, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 46 (unit) */
      0.0, -0.541860, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 47 (unit) */
      0.0, 0.626930, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 48 (unit) */
      0.0, 0.006560, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 49 (unit) */
      0.0, -0.019000, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 50 (unit) */
      0.0, 0.368120, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 51 (unit) */
      0.0, -0.403410, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 52 (unit) */
      0.0, 0.265510, 0,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 53 (unit) */
      0.0, -0.727440, 52,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 54 (unit) */
      0.0, 0.542990, 52,
       &Sources[52] , 
       &Weights[52] , 
      },
    { /* unit 55 (unit) */
      0.0, 0.586960, 52,
       &Sources[104] , 
       &Weights[104] , 
      },
    { /* unit 56 (unit) */
      0.0, 0.227610, 52,
       &Sources[156] , 
       &Weights[156] , 
      },
    { /* unit 57 (unit) */
      0.0, -0.463910, 52,
       &Sources[208] , 
       &Weights[208] , 
      },
    { /* unit 58 (unit) */
      0.0, 0.842880, 52,
       &Sources[260] , 
       &Weights[260] , 
      },
    { /* unit 59 (unit) */
      0.0, 0.836350, 52,
       &Sources[312] , 
       &Weights[312] , 
      },
    { /* unit 60 (unit) */
      0.0, 0.149630, 52,
       &Sources[364] , 
       &Weights[364] , 
      },
    { /* unit 61 (unit) */
      0.0, 0.850290, 52,
       &Sources[416] , 
       &Weights[416] , 
      },
    { /* unit 62 (unit) */
      0.0, 0.596300, 52,
       &Sources[468] , 
       &Weights[468] , 
      },
    { /* unit 63 (unit) */
      0.0, -0.271770, 10,
       &Sources[520] , 
       &Weights[520] , 
      }

  };



int papanet(float *in, float *out, int init)
{
  int member, source;
  float sum;
  enum{OK, Error, Not_Valid};
  pUnit unit;


  /* layer definition section (names & member units) */

  static pUnit Input[52] = {Units + 1, Units + 2, Units + 3, Units + 4, Units + 5, Units + 6, Units + 7, Units + 8, Units + 9, Units + 10, Units + 11, Units + 12, Units + 13, Units + 14, Units + 15, Units + 16, Units + 17, Units + 18, Units + 19, Units + 20, Units + 21, Units + 22, Units + 23, Units + 24, Units + 25, Units + 26, Units + 27, Units + 28, Units + 29, Units + 30, Units + 31, Units + 32, Units + 33, Units + 34, Units + 35, Units + 36, Units + 37, Units + 38, Units + 39, Units + 40, Units + 41, Units + 42, Units + 43, Units + 44, Units + 45, Units + 46, Units + 47, Units + 48, Units + 49, Units + 50, Units + 51, Units + 52}; /* members */

  static pUnit Hidden1[10] = {Units + 53, Units + 54, Units + 55, Units + 56, Units + 57, Units + 58, Units + 59, Units + 60, Units + 61, Units + 62}; /* members */

  static pUnit Output1[1] = {Units + 63}; /* members */

  static int Output[1] = {63};

  for(member = 0; member < 52; member++) {
    Input[member]->act = in[member];
  }

  for (member = 0; member < 10; member++) {
    unit = Hidden1[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_Logistic(sum, unit->Bias);
  };

  for (member = 0; member < 1; member++) {
    unit = Output1[member];
    sum = 0.0;
    for (source = 0; source < unit->NoOfSources; source++) {
      sum += unit->sources[source]->act
             * unit->weights[source];
    }
    unit->act = Act_Logistic(sum, unit->Bias);
  };

  for(member = 0; member < 1; member++) {
    out[member] = Units[Output[member]].act;
  }

  return(OK);
}
