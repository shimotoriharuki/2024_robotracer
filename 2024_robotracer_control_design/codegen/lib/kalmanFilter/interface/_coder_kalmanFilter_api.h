/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: _coder_kalmanFilter_api.h
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024/07/21 21:32:40
 */

#ifndef _CODER_KALMANFILTER_API_H
#define _CODER_KALMANFILTER_API_H

/* Include Files */
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"
#include <string.h>

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void kalmanFilter(real_T dt, real_T omega_offset, real_T pre_P[4],
                  real_T pre_theta, real_T U, real_T W, real_T omega,
                  real_T theta, real_T *estimated_robot_theta, real_T P[4]);

void kalmanFilter_api(const mxArray *const prhs[8], int32_T nlhs,
                      const mxArray *plhs[2]);

void kalmanFilter_atexit(void);

void kalmanFilter_initialize(void);

void kalmanFilter_terminate(void);

void kalmanFilter_xil_shutdown(void);

void kalmanFilter_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_kalmanFilter_api.h
 *
 * [EOF]
 */
