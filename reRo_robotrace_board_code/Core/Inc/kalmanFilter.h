/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: kalmanFilter.h
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024/07/21 21:32:40
 */

#ifndef KALMANFILTER_H
#define KALMANFILTER_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void kalmanFilter(double dt, double omega_offset, const double pre_P[4],
                         double pre_theta, double U, double W, double omega,
                         double theta, double *estimated_robot_theta,
                         double P[4]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for kalmanFilter.h
 *
 * [EOF]
 */
