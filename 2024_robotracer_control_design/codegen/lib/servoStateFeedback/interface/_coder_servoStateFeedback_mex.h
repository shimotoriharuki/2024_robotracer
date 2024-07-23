/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: _coder_servoStateFeedback_mex.h
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024/07/23 23:14:20
 */

#ifndef _CODER_SERVOSTATEFEEDBACK_MEX_H
#define _CODER_SERVOSTATEFEEDBACK_MEX_H

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

void unsafe_servoStateFeedback_mexFunction(int32_T nlhs, mxArray *plhs[4],
                                           int32_T nrhs,
                                           const mxArray *prhs[11]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_servoStateFeedback_mex.h
 *
 * [EOF]
 */
