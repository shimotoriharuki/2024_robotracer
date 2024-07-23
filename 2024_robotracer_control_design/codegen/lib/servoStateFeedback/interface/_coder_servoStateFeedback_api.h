/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: _coder_servoStateFeedback_api.h
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024/07/23 23:14:20
 */

#ifndef _CODER_SERVOSTATEFEEDBACK_API_H
#define _CODER_SERVOSTATEFEEDBACK_API_H

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
void servoStateFeedback(real_T dt, real_T target_omega, real_T Ab[25],
                        real_T Bb[5], real_T pre_target_theta, real_T pre_xb[4],
                        real_T pre_z, real_T pre_input, real_T disturbance[4],
                        real_T f[4], real_T k, real_T *input,
                        real_T *target_theta, real_T xb[4], real_T *z);

void servoStateFeedback_api(const mxArray *const prhs[11], int32_T nlhs,
                            const mxArray *plhs[4]);

void servoStateFeedback_atexit(void);

void servoStateFeedback_initialize(void);

void servoStateFeedback_terminate(void);

void servoStateFeedback_xil_shutdown(void);

void servoStateFeedback_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_servoStateFeedback_api.h
 *
 * [EOF]
 */
