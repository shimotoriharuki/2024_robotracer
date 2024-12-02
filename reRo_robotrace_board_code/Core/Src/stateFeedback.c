/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: stateFeedback.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024/08/04 16:57:41
 */

/* Include Files */
#include "stateFeedback.h"

/* Function Definitions */
/*
 * 状態フィードバック
 *
 * Arguments    : const double x[4]
 *                const double f[4]
 * Return Type  : double
 */
double stateFeedback(const double x[2], const double f[2])
{
//  return ((-f[0] * x[0] + -f[1] * x[1]) + -f[2] * x[2]) + -f[3] * x[3];
  return (-f[0] * x[0] + -f[1] * x[1]);
}

/*
 * File trailer for stateFeedback.c
 *
 * [EOF]
 */
