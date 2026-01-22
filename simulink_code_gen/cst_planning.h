/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: cst_planning.h
 *
 * Code generated for Simulink model 'cst_planning'.
 *
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 * Validation result: Not run
 */

#ifndef RTW_HEADER_cst_planning_h_
#define RTW_HEADER_cst_planning_h_
#ifndef cst_planning_COMMON_INCLUDES_
#define cst_planning_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* cst_planning_COMMON_INCLUDES_ */

#include "zero_crossing_types.h"

/* Block signals and states (default storage) for model 'cst_planning' */
typedef struct
{
    real32_T pp_coefs[12];
    real32_T Product[4];               /* '<S1>/Product' */
    real32_T x0_now;                   /* '<S4>/Delay6' */
    real32_T delta_0;
    real32_T delta_m1;
    real32_T delta_n;
    boolean_T x0_init_flag;            /* '<S4>/Delay' */
}
cst_planning_DW_f;

/* Zero-crossing (trigger) state for model 'cst_planning' */
typedef struct
{
    real_T Delay6_Reset_ZC;            /* '<S4>/Delay6' */
}
cst_planning_ZCV_g;

/* Zero-crossing (trigger) state for model 'cst_planning' */
typedef struct
{
    ZCSigState Delay6_Reset_ZCE;       /* '<S4>/Delay6' */
}
cst_planning_ZCE;

typedef struct
{
    cst_planning_DW_f rtdw;
    cst_planning_ZCE rtzce;
}
cst_planning_MdlrefDW;

/* Model reference registration function */
extern void cst_planning_initialize(cst_planning_ZCE *localZCE);
extern void cst_planning_Init(cst_planning_DW_f *localDW);
extern void cst_planning(const real32_T rtu_iq_target_ip_buff[4], const real32_T
    *rtu_ip_dt, const real32_T *rtu_dt_p, real32_T *rty_iq_cmd,
    cst_planning_DW_f *localDW, cst_planning_ZCE *localZCE);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'cst_planning'
 * '<S1>'   : 'cst_planning/Subsystem'
 * '<S2>'   : 'cst_planning/Subsystem/Initialize Function'
 * '<S3>'   : 'cst_planning/Subsystem/MATLAB Function'
 * '<S4>'   : 'cst_planning/Subsystem/x0'
 */

/*-
 * Requirements for '<Root>': cst_planning

 */
#endif                                 /* RTW_HEADER_cst_planning_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
