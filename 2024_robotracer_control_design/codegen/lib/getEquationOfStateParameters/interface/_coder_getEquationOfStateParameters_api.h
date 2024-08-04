/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: _coder_getEquationOfStateParameters_api.h
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024/08/04 17:01:01
 */

#ifndef _CODER_GETEQUATIONOFSTATEPARAMETERS_API_H
#define _CODER_GETEQUATIONOFSTATEPARAMETERS_API_H

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
void c_getEquationOfStateParameters_(const mxArray *const prhs[12],
                                     int32_T nlhs, const mxArray *plhs[3]);

void getEquationOfStateParameters(real_T m_w, real_T m_p, real_T r_w,
                                  real_T r_p, real_T J_w, real_T J_p,
                                  real_T J_m, real_T g, real_T n, real_T kt,
                                  real_T kn, real_T R, real_T A[16],
                                  real_T B[4], real_T C[4]);

void getEquationOfStateParameters_atexit(void);

void getEquationOfStateParameters_initialize(void);

void getEquationOfStateParameters_terminate(void);

void getEquationOfStateParameters_xil_shutdown(void);

void getEquationOfStateParameters_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_getEquationOfStateParameters_api.h
 *
 * [EOF]
 */
