/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: _coder_getServoEquationOfStateParameters_api.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024/08/05 21:11:32
 */

/* Include Files */
#include "_coder_getServoEquationOfStateParameters_api.h"
#include "_coder_getServoEquationOfStateParameters_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;

emlrtContext emlrtContextGlobal = {
    true,                                                 /* bFirstTime */
    false,                                                /* bInitialized */
    131643U,                                              /* fVersionInfo */
    NULL,                                                 /* fErrorFunction */
    "getServoEquationOfStateParameters",                  /* fFunctionName */
    NULL,                                                 /* fRTCallStack */
    false,                                                /* bDebugMode */
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, /* fSigWrd */
    NULL                                                  /* fSigMem */
};

/* Function Declarations */
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId);

static const mxArray *b_emlrt_marshallOut(const real_T u[5]);

static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId);

static const mxArray *c_emlrt_marshallOut(const real_T u[4]);

static void emlrtExitTimeCleanupDtorFcn(const void *r);

static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *nullptr,
                               const char_T *identifier);

static const mxArray *emlrt_marshallOut(const real_T u[25]);

/* Function Definitions */
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T
 */
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = c_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const real_T u[5]
 * Return Type  : const mxArray *
 */
static const mxArray *b_emlrt_marshallOut(const real_T u[5])
{
  static const int32_T i = 0;
  static const int32_T i1 = 5;
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateNumericArray(1, (const void *)&i, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m, &i1, 1);
  emlrtAssign(&y, m);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T
 */
static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims = 0;
  real_T ret;
  emlrtCheckBuiltInR2012b((emlrtConstCTX)sp, msgId, src, "double", false, 0U,
                          (const void *)&dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const real_T u[4]
 * Return Type  : const mxArray *
 */
static const mxArray *c_emlrt_marshallOut(const real_T u[4])
{
  static const int32_T iv[2] = {0, 0};
  static const int32_T iv1[2] = {1, 4};
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateNumericArray(2, (const void *)&iv[0], mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m, &iv1[0], 2);
  emlrtAssign(&y, m);
  return y;
}

/*
 * Arguments    : const void *r
 * Return Type  : void
 */
static void emlrtExitTimeCleanupDtorFcn(const void *r)
{
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *nullptr
 *                const char_T *identifier
 * Return Type  : real_T
 */
static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *nullptr,
                               const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  real_T y;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(nullptr), &thisId);
  emlrtDestroyArray(&nullptr);
  return y;
}

/*
 * Arguments    : const real_T u[25]
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const real_T u[25])
{
  static const int32_T iv[2] = {0, 0};
  static const int32_T iv1[2] = {5, 5};
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateNumericArray(2, (const void *)&iv[0], mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m, &iv1[0], 2);
  emlrtAssign(&y, m);
  return y;
}

/*
 * Arguments    : const mxArray * const prhs[12]
 *                int32_T nlhs
 *                const mxArray *plhs[3]
 * Return Type  : void
 */
void c_getServoEquationOfStateParame(const mxArray *const prhs[12],
                                     int32_T nlhs, const mxArray *plhs[3])
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  real_T(*Ab)[25];
  real_T(*Bb)[5];
  real_T(*C)[4];
  real_T J_m;
  real_T J_p;
  real_T J_w;
  real_T R;
  real_T g;
  real_T kn;
  real_T kt;
  real_T m_p;
  real_T m_w;
  real_T n;
  real_T r_p;
  real_T r_w;
  st.tls = emlrtRootTLSGlobal;
  Ab = (real_T(*)[25])mxMalloc(sizeof(real_T[25]));
  Bb = (real_T(*)[5])mxMalloc(sizeof(real_T[5]));
  C = (real_T(*)[4])mxMalloc(sizeof(real_T[4]));
  /* Marshall function inputs */
  m_w = emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "m_w");
  m_p = emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "m_p");
  r_w = emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "r_w");
  r_p = emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "r_p");
  J_w = emlrt_marshallIn(&st, emlrtAliasP(prhs[4]), "J_w");
  J_p = emlrt_marshallIn(&st, emlrtAliasP(prhs[5]), "J_p");
  J_m = emlrt_marshallIn(&st, emlrtAliasP(prhs[6]), "J_m");
  g = emlrt_marshallIn(&st, emlrtAliasP(prhs[7]), "g");
  n = emlrt_marshallIn(&st, emlrtAliasP(prhs[8]), "n");
  kt = emlrt_marshallIn(&st, emlrtAliasP(prhs[9]), "kt");
  kn = emlrt_marshallIn(&st, emlrtAliasP(prhs[10]), "kn");
  R = emlrt_marshallIn(&st, emlrtAliasP(prhs[11]), "R");
  /* Invoke the target function */
  getServoEquationOfStateParameters(m_w, m_p, r_w, r_p, J_w, J_p, J_m, g, n, kt,
                                    kn, R, *Ab, *Bb, *C);
  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(*Ab);
  if (nlhs > 1) {
    plhs[1] = b_emlrt_marshallOut(*Bb);
  }
  if (nlhs > 2) {
    plhs[2] = c_emlrt_marshallOut(*C);
  }
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void getServoEquationOfStateParameters_atexit(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtPushHeapReferenceStackR2021a(
      &st, false, NULL, (void *)&emlrtExitTimeCleanupDtorFcn, NULL, NULL, NULL);
  emlrtEnterRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  getServoEquationOfStateParameters_xil_terminate();
  getServoEquationOfStateParameters_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void getServoEquationOfStateParameters_initialize(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, NULL);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void getServoEquationOfStateParameters_terminate(void)
{
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * File trailer for _coder_getServoEquationOfStateParameters_api.c
 *
 * [EOF]
 */
