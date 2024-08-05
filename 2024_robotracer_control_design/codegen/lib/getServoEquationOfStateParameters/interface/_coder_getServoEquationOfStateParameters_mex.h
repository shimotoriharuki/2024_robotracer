/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: _coder_getServoEquationOfStateParameters_mex.h
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024/08/05 21:11:32
 */

#ifndef _CODER_GETSERVOEQUATIONOFSTATEPARAMETERS_MEX_H
#define _CODER_GETSERVOEQUATIONOFSTATEPARAMETERS_MEX_H

/* Include Files */
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
MEXFUNCTION_LINKAGE void mexFunction(int32_T nlhs, mxArray *plhs[],
                                     int32_T nrhs, const mxArray *prhs[]);

emlrtCTX mexFunctionCreateRootTLS(void);

void unsafe_getServoEquationOfStateParameters_mexFunction(
    int32_T nlhs, mxArray *plhs[3], int32_T nrhs, const mxArray *prhs[12]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_getServoEquationOfStateParameters_mex.h
 *
 * [EOF]
 */
