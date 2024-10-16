/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: _coder_stateFeedback_api.h
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024/08/04 16:57:41
 */

#ifndef _CODER_STATEFEEDBACK_API_H
#define _CODER_STATEFEEDBACK_API_H

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
real_T stateFeedback(real_T x[4], real_T f[4]);

void stateFeedback_api(const mxArray *const prhs[2], const mxArray **plhs);

void stateFeedback_atexit(void);

void stateFeedback_initialize(void);

void stateFeedback_terminate(void);

void stateFeedback_xil_shutdown(void);

void stateFeedback_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_stateFeedback_api.h
 *
 * [EOF]
 */
