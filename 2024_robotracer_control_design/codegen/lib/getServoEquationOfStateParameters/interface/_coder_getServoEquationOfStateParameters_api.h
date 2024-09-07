/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: _coder_getServoEquationOfStateParameters_api.h
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024/08/05 21:11:32
 */

#ifndef _CODER_GETSERVOEQUATIONOFSTATEPARAMETERS_API_H
#define _CODER_GETSERVOEQUATIONOFSTATEPARAMETERS_API_H

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
void c_getServoEquationOfStateParame(const mxArray *const prhs[12],
                                     int32_T nlhs, const mxArray *plhs[3]);

void getServoEquationOfStateParameters(real_T m_w, real_T m_p, real_T r_w,
                                       real_T r_p, real_T J_w, real_T J_p,
                                       real_T J_m, real_T g, real_T n,
                                       real_T kt, real_T kn, real_T R,
                                       real_T Ab[25], real_T Bb[5],
                                       real_T C[4]);

void getServoEquationOfStateParameters_atexit(void);

void getServoEquationOfStateParameters_initialize(void);

void getServoEquationOfStateParameters_terminate(void);

void getServoEquationOfStateParameters_xil_shutdown(void);

void getServoEquationOfStateParameters_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_getServoEquationOfStateParameters_api.h
 *
 * [EOF]
 */
