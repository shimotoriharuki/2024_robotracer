/*
 *
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: servoStateFeedback.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024/07/23 23:14:20
 */

/* Include Files */
#include "servoStateFeedback.h"

/* Function Definitions */
/*
 * 状態フィードバック
 *
 * Arguments    : double dt
 *                double target_omega
 *                const double Ab[25]
 *                const double Bb[5]
 *                double pre_target_theta
 *                const double pre_xb[4]
 *                double pre_z
 *                double pre_input
 *                const double disturbance[4]
 *                const double f[4]
 *                double k
 *                double *input
 *                double *target_theta
 *                double xb[4]
 *                double *z
 * Return Type  : void
 */
void servoStateFeedback(double dt, double target_omega, const double Ab[25],
                        const double Bb[5], double pre_target_theta,
                        const double pre_xb[4], double pre_z, double pre_input,
                        const double disturbance[4], const double f[4],
                        double k, double *input, double *target_theta,
                        double xb[4], double *z)
{
  double b_pre_xb[5];
  double dxb[5];
  double d;
  int i;
  int i1;
  *target_theta = pre_target_theta + target_omega * dt;
  b_pre_xb[0] = pre_xb[0];
  b_pre_xb[1] = pre_xb[1];
  b_pre_xb[2] = pre_xb[2];
  b_pre_xb[3] = pre_xb[3];
  b_pre_xb[4] = pre_z;
  for (i = 0; i < 5; i++) {
    d = 0.0;
    for (i1 = 0; i1 < 5; i1++) {
      d += Ab[i + 5 * i1] * b_pre_xb[i1];
    }
    dxb[i] = d + Bb[i] * pre_input;
  }
  b_pre_xb[0] = disturbance[0];
  b_pre_xb[1] = disturbance[1];
  b_pre_xb[2] = disturbance[2];
  b_pre_xb[3] = disturbance[3];
  b_pre_xb[4] = *target_theta;
  for (i = 0; i < 5; i++) {
    dxb[i] += b_pre_xb[i];
  }
  double b_f;
  *z = pre_z + dxb[4] * dt;
  d = pre_xb[0] + dxb[0] * dt;
  xb[0] = d;
  b_f = -f[0] * d;
  d = pre_xb[1] + dxb[1] * dt;
  xb[1] = d;
  b_f += -f[1] * d;
  d = pre_xb[2] + dxb[2] * dt;
  xb[2] = d;
  b_f += -f[2] * d;
  d = pre_xb[3] + dxb[3] * dt;
  xb[3] = d;
  b_f += -f[3] * d;
  *input = b_f + k * *z;
}

/*
 * File trailer for servoStateFeedback.c
 *
 * [EOF]
 */
