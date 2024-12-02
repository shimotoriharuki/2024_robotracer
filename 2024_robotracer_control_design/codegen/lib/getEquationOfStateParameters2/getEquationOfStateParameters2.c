/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: getEquationOfStateParameters2.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024/12/02 20:49:10
 */

/* Include Files */
#include "getEquationOfStateParameters2.h"

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
 *                double kn
 *                double R
 *                double A[4]
 *                double B[2]
 *                double C[2]
 * Return Type  : void
 */
void getEquationOfStateParameters2(double m_w, double m_p, double r_w,
                                   double r_p, double J_w, double J_p,
                                   double J_m, double g, double n, double kt,
                                   double kn, double R, double A[4],
                                   double B[2], double C[2])
{
  double a12;
  double delta;
  (void)J_m;
  (void)kn;
  /* 起電力定数 [V/rpm] */
  delta = (m_w + m_p) * (r_w * r_w);
  a12 = (delta + m_p * r_w * r_p) + J_w;
  delta =
      ((((delta + 2.0 * m_p * r_w * r_p) + m_p * (r_p * r_p)) + J_p) + J_w) -
      a12;
  A[1] = m_p * g * r_p / delta;
  A[3] = 0.0;
  B[0] = 0.0;
  B[1] = -a12 * n * kt / R / delta;
  A[0] = 0.0;
  C[0] = 1.0;
  A[2] = 1.0;
  C[1] = 1.0;
}

/*
 * File trailer for getEquationOfStateParameters2.c
 *
 * [EOF]
 */
