/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: _coder_kalmanFilter_mex.h
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024/07/21 21:32:40
 */

#ifndef _CODER_KALMANFILTER_MEX_H
#define _CODER_KALMANFILTER_MEX_H

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

void unsafe_kalmanFilter_mexFunction(int32_T nlhs, mxArray *plhs[2],
                                     int32_T nrhs, const mxArray *prhs[8]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_kalmanFilter_mex.h
 *
 * [EOF]
 */
