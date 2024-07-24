/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: getEquationOfStateParameters.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024/07/23 23:10:29
 */

/* Include Files */
#include "getEquationOfStateParameters.h"

/* Function Definitions */
/*
 * Arguments    : double m_w
 *                double m_p
 *                double r_w
 *                double r_p
 *                double J_w
 *                double J_p
 *                double J_m
 *                double g
 *                double n
 *                double kt
 *                double ke
 *                double R
 *                double Ab[25]
 *                double Bb[5]
 *                double C[4]
 * Return Type  : void
 */
void getEquationOfStateParameters(double m_w, double m_p, double r_w,
                                  double r_p, double J_w, double J_p,
                                  double J_m, double g, double n, double kt,
                                  double ke, double R, double Ab[25],
                                  double Bb[5], double C[4])
{
  double a11;
  double a12_tmp;
  double a22;
  double a22_tmp;
  double delta;
  //double ke;
  //ke = 1.0 / (kn * 2.0 * 3.1415926535897931 / 60.0);
  /* 起電力定数 [V/rpm] */
  a22 = (m_w + m_p) * (r_w * r_w);
  a11 = (((a22 + 2.0 * m_p * r_w * r_p) + m_p * (r_p * r_p)) + J_p) + J_w;
  a12_tmp = (a22 + m_p * r_w * r_p) + J_w;
  a22_tmp = n * n;
  a22 = (a22 + J_w) + a22_tmp * J_m;
  delta = a11 * a22 - a12_tmp * a12_tmp;
  /*  拡大系 */
  Ab[1] = a22 * m_p * g * r_p / delta;
  Ab[6] = 0.0;
  Ab[11] = 0.0;
  Ab[16] = a12_tmp * a22_tmp * kt * ke / R / delta;
  Ab[3] = -a12_tmp * m_p * g * r_p / delta;
  Ab[8] = 0.0;
  Ab[13] = 0.0;
  Ab[18] = -a11 * a22_tmp * kt * ke / R / delta;
  C[0] = 1.0;
  Ab[0] = 0.0;
  Ab[2] = 0.0;
  Ab[20] = 0.0;
  Ab[4] = -1.0;
  C[1] = 1.0;
  Ab[5] = 1.0;
  Ab[7] = 0.0;
  Ab[21] = 0.0;
  Ab[9] = -1.0;
  C[2] = 1.0;
  Ab[10] = 0.0;
  Ab[12] = 0.0;
  Ab[22] = 0.0;
  Ab[14] = -1.0;
  C[3] = 1.0;
  Ab[15] = 0.0;
  Ab[17] = 1.0;
  Ab[23] = 0.0;
  Ab[19] = -1.0;
  Ab[24] = 0.0;
  Bb[0] = 0.0;
  Bb[1] = -a12_tmp * n * kt / R / delta;
  Bb[2] = 0.0;
  Bb[3] = a11 * n * kt / R / delta;
  Bb[4] = 0.0;
}

/*
 * File trailer for getEquationOfStateParameters.c
 *
 * [EOF]
 */
