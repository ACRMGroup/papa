/*********************************************************
  papanet.c
  --------------------------------------------------------
  generated at Tue Oct 15 10:03:20 2019
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
0.265410, -0.043130, 0.137310, 11.371420, -0.328460, 0.664460, -6.862190, -0.723810, 10.678740, 12.112030, 
-1.062090, -10.900750, 0.841150, 0.466820, 0.366790, -0.352450, -0.720990, -0.045330, 1.507600, -2.841280, 
-0.144980, -0.409250, -1.505060, -5.458420, -0.896120, -0.216840, 8.119510, 0.318630, 0.583570, -0.867310, 
3.626290, -0.149240, -0.801170, 0.729560, -0.364950, 0.746030, 0.899830, 0.992920, -6.932480, -6.480620, 
0.127050, 0.821140, 1.556100, -1.688060, 0.173590, 0.482250, -4.507140, 0.041890, -0.449460, 0.475290, 
-1.181640, -7.742250, 
0.038370, -0.524160, -0.861140, -3.671760, 0.095350, -0.841910, 3.134170, -0.692110, 0.090730, -1.754120, 
2.602710, -0.833710, 0.627260, -0.291000, -1.250510, -0.548830, 0.343410, -0.670800, -0.168860, -2.031310, 
0.603050, 0.078170, 3.504750, 4.364100, -0.577470, -3.730020, -9.234260, 1.723950, -0.559340, 0.892290, 
-0.776450, 0.113940, -0.928390, -0.889860, -0.034420, -0.065620, 0.187600, -0.297260, -7.396130, -6.021880, 
0.612330, -0.962260, 2.286660, 3.926070, 0.001700, 0.247150, 2.448560, -0.519730, 0.652940, 0.171620, 
1.234420, 8.636300, 
4.760370, 4.392480, -1.433870, -10.738260, 0.617960, 3.286940, -0.501010, 0.760400, 7.441230, 7.853000, 
5.465980, -7.713070, 3.664300, 2.243140, -7.856650, 0.193680, 1.212030, 2.000670, 0.598450, 5.851330, 
1.967590, 2.151500, 4.516760, -0.929290, 3.471450, 3.211000, 3.550170, 15.341340, -0.352110, -0.523970, 
0.745480, -0.438960, 4.117040, 3.613870, 4.004590, -0.629910, 0.835070, 1.834370, -0.472480, -0.277080, 
3.806410, 3.574170, -10.110990, 11.192210, 1.478020, 1.097030, 2.972090, 9.222690, 3.598490, 3.598020, 
-4.543470, -7.652910, 
0.826370, 0.860120, -0.491830, 3.796710, 0.454520, -0.508630, -9.285900, -0.119130, 0.361470, 0.827140, 
1.522890, 2.645160, 0.469540, 0.444510, -0.841640, 0.580880, -0.406060, -1.058570, -3.597120, 2.817530, 
0.155610, -0.305010, -4.404910, 8.212560, 0.221920, 1.802410, 2.180570, -5.436560, -0.874120, -0.152190, 
0.152360, 1.079450, -0.476400, -0.797070, 0.619180, 0.880690, 0.983310, 0.208520, -2.706780, -5.449400, 
-0.975420, -0.876980, -0.475690, -0.158030, 0.331380, 0.547510, 8.923930, 3.834140, -0.705760, -0.435700, 
0.003540, -6.948210, 
0.466040, 0.463390, 0.715650, -1.783160, 0.115790, 1.190290, 5.290540, -0.716790, 0.357400, -1.161290, 
-3.693400, -0.328480, -0.794540, 0.846360, 4.684130, 0.619490, 0.381750, 0.483490, 0.195400, 5.895330, 
-0.002500, -0.327520, 2.642990, -5.005140, -0.091020, -0.803420, -0.305790, 1.823840, 0.856630, -0.728170, 
-1.811050, 0.158990, -0.328790, 0.237060, 0.921490, -0.698520, 0.917490, 0.887760, -2.827060, 0.237470, 
0.073890, -0.953640, 0.087210, -0.747650, -0.528200, -0.455120, 0.084340, 2.906010, 0.310380, 0.802180, 
3.063880, 1.022260, 
-0.379070, -0.742490, 0.608480, 6.383170, 0.889010, 0.013890, 0.733880, 0.487950, 0.351310, -0.643110, 
0.548310, 0.868040, -0.812840, -0.390700, -0.935600, 0.189740, -0.601610, 1.060600, 0.795300, -7.466940, 
-0.835640, 0.016280, -0.374550, -0.209140, 0.320020, -0.273890, 0.556790, 1.001940, 1.015200, 0.938560, 
-0.530280, 0.228070, -0.652140, -0.327750, 0.529430, 0.717560, -0.487760, 0.431760, 2.017340, -2.192210, 
0.157550, -0.631270, -0.688310, 4.768830, 0.223840, 0.610100, 2.779560, 0.872310, -0.710830, -0.639650, 
-0.218120, 9.380760, 
-0.676240, -0.822810, 0.896650, -5.683520, 0.837680, 0.510340, 4.427200, -0.288460, -1.111610, 0.550520, 
0.240920, -0.576750, -0.403870, -0.870920, -1.097040, -0.378500, -0.727370, 0.406230, -0.552860, -1.934040, 
-0.165900, -0.041100, -8.646460, -1.478620, -0.094060, -0.017830, 5.735480, -3.638600, 1.554640, -0.386840, 
0.923530, -0.861110, 0.695190, 0.642910, -0.882200, -0.490490, 0.596420, 0.014330, 0.016830, -0.741140, 
0.077920, 0.795080, -0.612830, -0.054860, -0.828570, 0.449920, -4.913920, -0.048680, -0.772860, 0.500780, 
-1.008920, -0.393200, 
0.892360, 0.789680, -0.059560, -0.145910, 0.771010, 0.914860, -0.001800, -0.449500, 0.011540, 0.307830, 
0.929850, 0.266990, -0.831200, -0.009860, -0.723540, -0.847080, 0.969310, 0.420080, 0.521280, -0.432920, 
0.796850, -0.554760, 0.510680, 0.136670, -0.183200, -0.029030, -0.537270, -0.443170, -0.607160, -0.481040, 
-0.012360, -0.636630, 0.881470, -0.151740, -0.723500, -0.102350, -0.657310, 0.751880, -0.420350, 0.996860, 
0.936410, 0.417310, -0.342870, 0.399530, 0.132330, 0.453410, 0.751420, 0.731340, 0.790110, 0.167930, 
-0.641170, 0.479760, 
0.985030, 0.570240, 0.279410, -5.040720, 0.288410, 0.025830, -1.232660, 0.340240, 13.968490, 12.399930, 
-0.534150, -13.191240, -0.448660, 0.665270, 5.782750, -0.371030, -0.712220, -0.095240, -1.950700, -6.374400, 
-0.911690, -0.833460, -2.770290, 4.928560, 0.127850, -0.152550, 9.779830, 4.328280, -0.132040, 0.623990, 
-1.981180, -0.517940, 0.614100, 0.820850, -0.149340, 0.961640, 0.910830, 0.678150, -4.180030, 5.778650, 
0.439620, -0.008050, -0.912980, 1.648390, -0.444290, -0.392580, -4.184320, 0.660080, -0.317630, 0.675550, 
-0.674920, -2.988930, 
0.642510, -0.074620, 0.389980, 9.875410, 0.083100, 0.785000, -3.600070, -0.070580, -0.281820, -0.572770, 
-2.702250, -0.333270, 0.160360, -0.464580, 5.197280, 0.750450, 0.473060, -0.914510, -0.464030, 0.362660, 
-0.392660, -0.632800, -5.435190, -11.574760, -0.359860, 0.087550, -2.152210, -0.473780, 7.928630, 9.112600, 
0.690690, 0.247400, 0.512650, -0.899470, 0.323010, 0.478110, 0.892610, -0.641570, -3.207380, 3.968240, 
0.638140, -0.413710, 0.669280, 3.531950, 0.526100, 0.654350, -0.233150, 3.677910, 0.305770, 0.031440, 
1.702410, 2.687600, 
-0.610950, -0.749760, 0.341840, -0.364880, 0.900590, 1.122160, -0.783630, 0.223570, 0.433730, -0.479340, 


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
      0.0, -0.745250, 52,
       &Sources[0] , 
       &Weights[0] , 
      },
    { /* unit 54 (unit) */
      0.0, 0.538730, 52,
       &Sources[52] , 
       &Weights[52] , 
      },
    { /* unit 55 (unit) */
      0.0, 4.356990, 52,
       &Sources[104] , 
       &Weights[104] , 
      },
    { /* unit 56 (unit) */
      0.0, 0.262620, 52,
       &Sources[156] , 
       &Weights[156] , 
      },
    { /* unit 57 (unit) */
      0.0, -0.479670, 52,
       &Sources[208] , 
       &Weights[208] , 
      },
    { /* unit 58 (unit) */
      0.0, 0.905310, 52,
       &Sources[260] , 
       &Weights[260] , 
      },
    { /* unit 59 (unit) */
      0.0, 0.745610, 52,
       &Sources[312] , 
       &Weights[312] , 
      },
    { /* unit 60 (unit) */
      0.0, 0.183220, 52,
       &Sources[364] , 
       &Weights[364] , 
      },
    { /* unit 61 (unit) */
      0.0, 0.716130, 52,
       &Sources[416] , 
       &Weights[416] , 
      },
    { /* unit 62 (unit) */
      0.0, 0.641080, 52,
       &Sources[468] , 
       &Weights[468] , 
      },
    { /* unit 63 (unit) */
      0.0, -0.296420, 10,
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
