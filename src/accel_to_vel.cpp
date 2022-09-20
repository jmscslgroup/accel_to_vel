/*
 * accel_to_vel.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "accel_to_vel".
 *
 * Model version              : 4.0
 * Simulink Coder version : 9.8 (R2022b) 13-May-2022
 * C++ source code generated on : Tue Sep 20 15:30:48 2022
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "accel_to_vel.h"
#include "rtwtypes.h"
#include "accel_to_vel_types.h"
#include "accel_to_vel_private.h"
#include <cstring>

/* Block signals (default storage) */
B_accel_to_vel_T accel_to_vel_B;

/* Continuous states */
X_accel_to_vel_T accel_to_vel_X;

/* Block states (default storage) */
DW_accel_to_vel_T accel_to_vel_DW;

/* Real-time model */
RT_MODEL_accel_to_vel_T accel_to_vel_M_ = RT_MODEL_accel_to_vel_T();
RT_MODEL_accel_to_vel_T *const accel_to_vel_M = &accel_to_vel_M_;

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = static_cast<ODE3_IntgData *>(rtsiGetSolverData(si));
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 5;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                static_cast<uint_T>(nXc)*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  accel_to_vel_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  accel_to_vel_step();
  accel_to_vel_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  accel_to_vel_step();
  accel_to_vel_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void accel_to_vel_step(void)
{
  SL_Bus_accel_to_vel_std_msgs_Float64 b_varargout_2;
  real_T rtb_uthorder;
  if (rtmIsMajorTimeStep(accel_to_vel_M)) {
    /* set solver stop time */
    if (!(accel_to_vel_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&accel_to_vel_M->solverInfo,
                            ((accel_to_vel_M->Timing.clockTickH0 + 1) *
        accel_to_vel_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&accel_to_vel_M->solverInfo,
                            ((accel_to_vel_M->Timing.clockTick0 + 1) *
        accel_to_vel_M->Timing.stepSize0 + accel_to_vel_M->Timing.clockTickH0 *
        accel_to_vel_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(accel_to_vel_M)) {
    accel_to_vel_M->Timing.t[0] = rtsiGetT(&accel_to_vel_M->solverInfo);
  }

  /* TransferFcn: '<Root>/Transfer Fcn3' */
  rtb_uthorder = 0.0;
  for (int_T ci = 0; ci < 5; ci++) {
    rtb_uthorder += accel_to_vel_P.TransferFcn3_C[ci] *
      accel_to_vel_X.TransferFcn3_CSTATE[ci];
  }

  /* End of TransferFcn: '<Root>/Transfer Fcn3' */

  /* BusAssignment: '<Root>/Bus Assignment' incorporates:
   *  Constant: '<S1>/Constant'
   */
  accel_to_vel_B.BusAssignment = accel_to_vel_P.Constant_Value;
  accel_to_vel_B.BusAssignment.Linear.X = rtb_uthorder;

  /* Outputs for Atomic SubSystem: '<Root>/Publish' */
  /* MATLABSystem: '<S2>/SinkBlock' */
  Pub_accel_to_vel_33.publish(&accel_to_vel_B.BusAssignment);

  /* End of Outputs for SubSystem: '<Root>/Publish' */
  if (rtmIsMajorTimeStep(accel_to_vel_M)) {
    boolean_T b_varargout_1;

    /* Outputs for Atomic SubSystem: '<Root>/Subscribe' */
    /* MATLABSystem: '<S3>/SourceBlock' */
    b_varargout_1 = Sub_accel_to_vel_27.getLatestMessage(&b_varargout_2);

    /* Outputs for Enabled SubSystem: '<S3>/Enabled Subsystem' incorporates:
     *  EnablePort: '<S4>/Enable'
     */
    if (b_varargout_1) {
      /* SignalConversion generated from: '<S4>/In1' */
      accel_to_vel_B.In1 = b_varargout_2;
    }

    /* End of MATLABSystem: '<S3>/SourceBlock' */
    /* End of Outputs for SubSystem: '<S3>/Enabled Subsystem' */
    /* End of Outputs for SubSystem: '<Root>/Subscribe' */

    /* Saturate: '<Root>/Saturation' */
    if (accel_to_vel_B.In1.Data > accel_to_vel_P.Saturation_UpperSat) {
      /* Saturate: '<Root>/Saturation' */
      accel_to_vel_B.Saturation = accel_to_vel_P.Saturation_UpperSat;
    } else if (accel_to_vel_B.In1.Data < accel_to_vel_P.Saturation_LowerSat) {
      /* Saturate: '<Root>/Saturation' */
      accel_to_vel_B.Saturation = accel_to_vel_P.Saturation_LowerSat;
    } else {
      /* Saturate: '<Root>/Saturation' */
      accel_to_vel_B.Saturation = accel_to_vel_B.In1.Data;
    }

    /* End of Saturate: '<Root>/Saturation' */
  }

  if (rtmIsMajorTimeStep(accel_to_vel_M)) {
    rt_ertODEUpdateContinuousStates(&accel_to_vel_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++accel_to_vel_M->Timing.clockTick0)) {
      ++accel_to_vel_M->Timing.clockTickH0;
    }

    accel_to_vel_M->Timing.t[0] = rtsiGetSolverStopTime
      (&accel_to_vel_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.05s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.05, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      accel_to_vel_M->Timing.clockTick1++;
      if (!accel_to_vel_M->Timing.clockTick1) {
        accel_to_vel_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void accel_to_vel_derivatives(void)
{
  XDot_accel_to_vel_T *_rtXdot;
  _rtXdot = ((XDot_accel_to_vel_T *) accel_to_vel_M->derivs);

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn3' */
  for (int_T is = 0; is < 5; is++) {
    _rtXdot->TransferFcn3_CSTATE[is] = 0.0;
    _rtXdot->TransferFcn3_CSTATE[0] += accel_to_vel_P.TransferFcn3_A[is] *
      accel_to_vel_X.TransferFcn3_CSTATE[is];
  }

  _rtXdot->TransferFcn3_CSTATE[1] += accel_to_vel_X.TransferFcn3_CSTATE[0];
  _rtXdot->TransferFcn3_CSTATE[2] += accel_to_vel_X.TransferFcn3_CSTATE[1];
  _rtXdot->TransferFcn3_CSTATE[3] += accel_to_vel_X.TransferFcn3_CSTATE[2];
  _rtXdot->TransferFcn3_CSTATE[4] += accel_to_vel_X.TransferFcn3_CSTATE[3];
  _rtXdot->TransferFcn3_CSTATE[0] += accel_to_vel_B.Saturation;

  /* End of Derivatives for TransferFcn: '<Root>/Transfer Fcn3' */
}

/* Model initialize function */
void accel_to_vel_initialize(void)
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&accel_to_vel_M->solverInfo,
                          &accel_to_vel_M->Timing.simTimeStep);
    rtsiSetTPtr(&accel_to_vel_M->solverInfo, &rtmGetTPtr(accel_to_vel_M));
    rtsiSetStepSizePtr(&accel_to_vel_M->solverInfo,
                       &accel_to_vel_M->Timing.stepSize0);
    rtsiSetdXPtr(&accel_to_vel_M->solverInfo, &accel_to_vel_M->derivs);
    rtsiSetContStatesPtr(&accel_to_vel_M->solverInfo, (real_T **)
                         &accel_to_vel_M->contStates);
    rtsiSetNumContStatesPtr(&accel_to_vel_M->solverInfo,
      &accel_to_vel_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&accel_to_vel_M->solverInfo,
      &accel_to_vel_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&accel_to_vel_M->solverInfo,
      &accel_to_vel_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&accel_to_vel_M->solverInfo,
      &accel_to_vel_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&accel_to_vel_M->solverInfo, (&rtmGetErrorStatus
      (accel_to_vel_M)));
    rtsiSetRTModelPtr(&accel_to_vel_M->solverInfo, accel_to_vel_M);
  }

  rtsiSetSimTimeStep(&accel_to_vel_M->solverInfo, MAJOR_TIME_STEP);
  accel_to_vel_M->intgData.y = accel_to_vel_M->odeY;
  accel_to_vel_M->intgData.f[0] = accel_to_vel_M->odeF[0];
  accel_to_vel_M->intgData.f[1] = accel_to_vel_M->odeF[1];
  accel_to_vel_M->intgData.f[2] = accel_to_vel_M->odeF[2];
  accel_to_vel_M->contStates = ((X_accel_to_vel_T *) &accel_to_vel_X);
  rtsiSetSolverData(&accel_to_vel_M->solverInfo, static_cast<void *>
                    (&accel_to_vel_M->intgData));
  rtsiSetIsMinorTimeStepWithModeChange(&accel_to_vel_M->solverInfo, false);
  rtsiSetSolverName(&accel_to_vel_M->solverInfo,"ode3");
  rtmSetTPtr(accel_to_vel_M, &accel_to_vel_M->Timing.tArray[0]);
  accel_to_vel_M->Timing.stepSize0 = 0.05;

  /* block I/O */
  (void) memset((static_cast<void *>(&accel_to_vel_B)), 0,
                sizeof(B_accel_to_vel_T));

  /* states (continuous) */
  {
    (void) memset(static_cast<void *>(&accel_to_vel_X), 0,
                  sizeof(X_accel_to_vel_T));
  }

  /* states (dwork) */
  (void) memset(static_cast<void *>(&accel_to_vel_DW), 0,
                sizeof(DW_accel_to_vel_T));

  {
    char_T b_zeroDelimTopic_0[10];
    char_T b_zeroDelimTopic[6];
    static const char_T tmp[5] = { 'v', '_', 'a', 'c', 't' };

    static const char_T tmp_0[9] = { 'c', 'm', 'd', '_', 'a', 'c', 'c', 'e', 'l'
    };

    /* Start for Atomic SubSystem: '<Root>/Publish' */
    /* Start for MATLABSystem: '<S2>/SinkBlock' */
    accel_to_vel_DW.obj.matlabCodegenIsDeleted = false;
    accel_to_vel_DW.objisempty_c = true;
    accel_to_vel_DW.obj.isInitialized = 1;
    for (int32_T i = 0; i < 5; i++) {
      b_zeroDelimTopic[i] = tmp[i];
    }

    b_zeroDelimTopic[5] = '\x00';
    Pub_accel_to_vel_33.createPublisher(&b_zeroDelimTopic[0], 1);
    accel_to_vel_DW.obj.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S2>/SinkBlock' */
    /* End of Start for SubSystem: '<Root>/Publish' */

    /* Start for Atomic SubSystem: '<Root>/Subscribe' */
    /* Start for MATLABSystem: '<S3>/SourceBlock' */
    accel_to_vel_DW.obj_i.matlabCodegenIsDeleted = false;
    accel_to_vel_DW.objisempty = true;
    accel_to_vel_DW.obj_i.isInitialized = 1;
    for (int32_T i = 0; i < 9; i++) {
      b_zeroDelimTopic_0[i] = tmp_0[i];
    }

    b_zeroDelimTopic_0[9] = '\x00';
    Sub_accel_to_vel_27.createSubscriber(&b_zeroDelimTopic_0[0], 1);
    accel_to_vel_DW.obj_i.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S3>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Subscribe' */
  }

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn3' */
  for (int_T is = 0; is < 5; is++) {
    accel_to_vel_X.TransferFcn3_CSTATE[is] = 0.0;
  }

  /* End of InitializeConditions for TransferFcn: '<Root>/Transfer Fcn3' */

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subscribe' */
  /* SystemInitialize for Enabled SubSystem: '<S3>/Enabled Subsystem' */
  /* SystemInitialize for SignalConversion generated from: '<S4>/In1' incorporates:
   *  Outport: '<S4>/Out1'
   */
  accel_to_vel_B.In1 = accel_to_vel_P.Out1_Y0;

  /* End of SystemInitialize for SubSystem: '<S3>/Enabled Subsystem' */
  /* End of SystemInitialize for SubSystem: '<Root>/Subscribe' */
}

/* Model terminate function */
void accel_to_vel_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<Root>/Publish' */
  /* Terminate for MATLABSystem: '<S2>/SinkBlock' */
  if (!accel_to_vel_DW.obj.matlabCodegenIsDeleted) {
    accel_to_vel_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S2>/SinkBlock' */
  /* End of Terminate for SubSystem: '<Root>/Publish' */

  /* Terminate for Atomic SubSystem: '<Root>/Subscribe' */
  /* Terminate for MATLABSystem: '<S3>/SourceBlock' */
  if (!accel_to_vel_DW.obj_i.matlabCodegenIsDeleted) {
    accel_to_vel_DW.obj_i.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S3>/SourceBlock' */
  /* End of Terminate for SubSystem: '<Root>/Subscribe' */
}
