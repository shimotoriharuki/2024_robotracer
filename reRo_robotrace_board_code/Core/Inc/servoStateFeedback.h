/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: servoStateFeedback.h
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024/07/23 23:14:20
 */

#ifndef SERVOSTATEFEEDBACK_H
#define SERVOSTATEFEEDBACK_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void servoStateFeedback(double dt, double target_omega,
                               const double Ab[25], const double Bb[5],
                               double pre_target_theta, const double pre_xb[4],
                               double pre_z, double pre_input,
                               const double disturbance[4], const double f[4],
                               double k, double theta_p, double dtheta_p, double theta_w, double dtheta_w,
							   double *input, double *target_theta, double xb[4], double *z);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for servoStateFeedback.h
 *
 * [EOF]
 */
