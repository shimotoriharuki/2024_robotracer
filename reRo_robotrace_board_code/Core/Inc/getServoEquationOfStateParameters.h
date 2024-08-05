/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: getServoEquationOfStateParameters.h
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024/08/05 21:11:32
 */

#ifndef GETSERVOEQUATIONOFSTATEPARAMETERS_H
#define GETSERVOEQUATIONOFSTATEPARAMETERS_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void getServoEquationOfStateParameters(
    double m_w, double m_p, double r_w, double r_p, double J_w, double J_p,
    double J_m, double g, double n, double kt, double kn, double R,
    double Ab[25], double Bb[5], double C[4]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for getServoEquationOfStateParameters.h
 *
 * [EOF]
 */
