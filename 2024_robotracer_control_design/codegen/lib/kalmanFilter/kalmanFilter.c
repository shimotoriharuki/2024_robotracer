/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: kalmanFilter.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024/07/21 21:32:40
 */

/* Include Files */
#include "kalmanFilter.h"

/* Function Definitions */
/*
 * Arguments    : double dt
 *                double omega_offset
 *                const double pre_P[4]
 *                double pre_theta
 *                double U
 *                double W
 *                double omega
 *                double theta
 *                double *estimated_robot_theta
 *                double P[4]
 * Return Type  : void
 */
void kalmanFilter(double dt, double omega_offset, const double pre_P[4],
                  double pre_theta, double U, double W, double omega,
                  double theta, double *estimated_robot_theta, double P[4])
{
  double A_theta[4];
  double P_dash[4];
  double theta_tilde[2];
  double B_theta_idx_0;
  double B_theta_idx_1;
  double d;
  double d1;
  double d2;
  double d3;
  double d4;
  int i;
  A_theta[0] = 1.0;
  A_theta[2] = -dt;
  A_theta[1] = 0.0;
  A_theta[3] = 1.0;
  /* 予測ステップ */
  B_theta_idx_1 = pre_P[0];
  d = pre_P[1];
  d1 = pre_P[2];
  d2 = pre_P[3];
  for (i = 0; i < 2; i++) {
    int i1;
    d3 = A_theta[i + 2];
    i1 = (int)A_theta[i];
    d4 = (double)i1 * B_theta_idx_1 + d3 * d;
    d3 = (double)i1 * d1 + d3 * d2;
    P_dash[i] = d4 + d3 * -dt;
    P_dash[i + 2] = d4 * 0.0 + d3;
  }
  B_theta_idx_1 = dt * U;
  P_dash[0] += B_theta_idx_1 * dt;
  P_dash[1] += 0.0 * U * dt;
  P_dash[2] += B_theta_idx_1 * 0.0;
  P_dash[3] += 0.0 * U * 0.0;
  /* 更新ステップ */
  theta_tilde[0] = (pre_theta + -dt * omega_offset) + dt * omega;
  theta_tilde[1] = (0.0 * pre_theta + omega_offset) + 0.0 * omega;
  B_theta_idx_1 = 1.0 / (W + ((P_dash[0] + 0.0 * P_dash[1]) +
                              (P_dash[2] + 0.0 * P_dash[3]) * 0.0));
  B_theta_idx_0 = (P_dash[0] + P_dash[2] * 0.0) * B_theta_idx_1;
  B_theta_idx_1 *= P_dash[1] + P_dash[3] * 0.0;
  A_theta[0] = 1.0 - B_theta_idx_0;
  A_theta[1] = 0.0 - B_theta_idx_1;
  A_theta[2] = 0.0 - B_theta_idx_0 * 0.0;
  A_theta[3] = 1.0 - B_theta_idx_1 * 0.0;
  B_theta_idx_1 = 0.0;
  d = P_dash[0];
  d1 = P_dash[1];
  d2 = P_dash[2];
  d3 = P_dash[3];
  for (i = 0; i < 2; i++) {
    double d5;
    d4 = A_theta[i + 2];
    d5 = A_theta[i];
    P[i] = d5 * d + d4 * d1;
    P[i + 2] = d5 * d2 + d4 * d3;
    B_theta_idx_1 += (1.0 - (double)i) * theta_tilde[i];
  }
  *estimated_robot_theta =
      theta_tilde[0] + B_theta_idx_0 * (theta - B_theta_idx_1);
}

/*
 * File trailer for kalmanFilter.c
 *
 * [EOF]
 */
