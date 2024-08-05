/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: servoStateFeedback.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024/08/05 21:13:25
 */

/* Include Files */
#include "servoStateFeedback.h"

/* Function Definitions */
/*
 * 状態フィードバック
 *
 * Arguments    : const double xb[4]
 *                double z
 *                const double f[4]
 *                double k
 * Return Type  : double
 */
double servoStateFeedback(const double xb[4], double z, const double f[4],
                          double k)
{
  return (((-f[0] * xb[0] + -f[1] * xb[1]) + -f[2] * xb[2]) + -f[3] * xb[3]) +
         k * z;
}

/*
 * File trailer for servoStateFeedback.c
 *
 * [EOF]
 */
