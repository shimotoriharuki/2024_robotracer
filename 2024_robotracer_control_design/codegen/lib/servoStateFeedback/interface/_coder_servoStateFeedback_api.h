/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: _coder_servoStateFeedback_api.h
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024/08/05 21:13:25
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
real_T servoStateFeedback(real_T xb[4], real_T z, real_T f[4], real_T k);

void servoStateFeedback_api(const mxArray *const prhs[4], const mxArray **plhs);

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
