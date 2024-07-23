/*
 * Sponsored License - for use in support of a program or activity
 * sponsored by MathWorks.  Not for government, commercial or other
 * non-sponsored organizational use.
 * File: main.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 2024/07/23 23:14:20
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

/* Include Files */
#include "main.h"
#include "servoStateFeedback.h"
#include "servoStateFeedback_terminate.h"

/* Function Declarations */
static void argInit_4x1_real_T(double result[4]);

static void argInit_5x1_real_T(double result[5]);

static void argInit_5x5_real_T(double result[25]);

static double argInit_real_T(void);

/* Function Definitions */
/*
 * Arguments    : double result[4]
 * Return Type  : void
 */
static void argInit_4x1_real_T(double result[4])
{
  int idx0;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 4; idx0++) {
    /* Set the value of the array element.
Change this value to the value that the application requires. */
    result[idx0] = argInit_real_T();
  }
}

/*
 * Arguments    : double result[5]
 * Return Type  : void
 */
static void argInit_5x1_real_T(double result[5])
{
  int idx0;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 5; idx0++) {
    /* Set the value of the array element.
Change this value to the value that the application requires. */
    result[idx0] = argInit_real_T();
  }
}

/*
 * Arguments    : double result[25]
 * Return Type  : void
 */
static void argInit_5x5_real_T(double result[25])
{
  int i;
  /* Loop over the array to initialize each element. */
  for (i = 0; i < 25; i++) {
    /* Set the value of the array element.
Change this value to the value that the application requires. */
    result[i] = argInit_real_T();
  }
}

/*
 * Arguments    : void
 * Return Type  : double
 */
static double argInit_real_T(void)
{
  return 0.0;
}

/*
 * Arguments    : int argc
 *                char **argv
 * Return Type  : int
 */
int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  /* The initialize function is being called automatically from your entry-point
   * function. So, a call to initialize is not included here. */
  /* Invoke the entry-point functions.
You can call entry-point functions multiple times. */
  main_servoStateFeedback();
  /* Terminate the application.
You do not need to do this more than one time. */
  servoStateFeedback_terminate();
  return 0;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void main_servoStateFeedback(void)
{
  double dv[25];
  double dv1[5];
  double dv2[4];
  double pre_xb_tmp[4];
  double xb[4];
  double dt_tmp;
  double input;
  double target_theta;
  double z;
  /* Initialize function 'servoStateFeedback' input arguments. */
  dt_tmp = argInit_real_T();
  /* Initialize function input argument 'Ab'. */
  /* Initialize function input argument 'Bb'. */
  /* Initialize function input argument 'pre_xb'. */
  argInit_4x1_real_T(pre_xb_tmp);
  /* Initialize function input argument 'disturbance'. */
  /* Initialize function input argument 'f'. */
  /* Call the entry-point 'servoStateFeedback'. */
  argInit_5x5_real_T(dv);
  argInit_5x1_real_T(dv1);
  argInit_4x1_real_T(dv2);
  servoStateFeedback(dt_tmp, dt_tmp, dv, dv1, dt_tmp, pre_xb_tmp, dt_tmp,
                     dt_tmp, pre_xb_tmp, dv2, dt_tmp, &input, &target_theta, xb,
                     &z);
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
