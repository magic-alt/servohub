/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: tq_fc_id.h
 *
 * Code generated for Simulink model 'tq_fc_id'.
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

#ifndef RTW_HEADER_tq_fc_id_h_
#define RTW_HEADER_tq_fc_id_h_
#ifndef tq_fc_id_COMMON_INCLUDES_
#define tq_fc_id_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* tq_fc_id_COMMON_INCLUDES_ */

#include "servo_hub_database_type.h"

/* Block signals and states (default storage) for model 'tq_fc_id' */
typedef struct
{
    int64_T pos_cmd_p;                 /* '<S2>/Chart' */
    int64_T Delay_DSTATE;              /* '<S7>/Delay' */
    int64_T Delay_DSTATE_j;            /* '<S10>/Delay' */
    real32_T com_table[360];           /* '<S2>/Data Store Memory' */
    real32_T DiscreteTimeIntegrator_DSTATE;/* '<S4>/Discrete-Time Integrator' */
    real32_T fc_p_com;                 /* '<S2>/Data Store Memory1' */
    real32_T fc_n_com;                 /* '<S2>/Data Store Memory2' */
    int8_T state_now;                  /* '<S2>/Chart' */
    int8_T out_add;                    /* '<S7>/Chart' */
    int8_T out_add_e;                  /* '<S10>/Chart' */
    int8_T error;                      /* '<S2>/Chart' */
    uint8_T iq_com_enable;             /* '<S2>/Chart' */
    uint8_T tq_com_enable;             /* '<S2>/Chart' */
    uint8_T fc_com_enable;             /* '<S2>/Chart' */
    uint8_T is_active_c3_tq_fc_id;     /* '<S2>/Chart' */
    uint8_T is_c3_tq_fc_id;            /* '<S2>/Chart' */
    uint8_T counts;                    /* '<S7>/Chart' */
    uint8_T is_active_c2_tq_fc_id;     /* '<S7>/Chart' */
    uint8_T is_c2_tq_fc_id;            /* '<S7>/Chart' */
    uint8_T counts_m;                  /* '<S10>/Chart' */
    uint8_T is_active_c1_tq_fc_id;     /* '<S10>/Chart' */
    uint8_T is_c1_tq_fc_id;            /* '<S10>/Chart' */
    boolean_T id_state;                /* '<S2>/Chart' */
    boolean_T icLoad;                  /* '<S7>/Delay' */
    boolean_T icLoad_i;                /* '<S10>/Delay' */
}
tq_fc_id_DW_f;

typedef struct
{
    tq_fc_id_DW_f rtdw;
}
tq_fc_id_MdlrefDW;

extern void tq_fc_id_Init(TqFcIdOutput *rty_output, tq_fc_id_DW_f *localDW);
extern void tq_fc_id(const TqFcIdInput *rtu_input, const TqFcIdConfig
                     *rtu_config, TqFcIdOutput *rty_output, tq_fc_id_DW_f
                     *localDW);

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
 * '<Root>' : 'tq_fc_id'
 * '<S1>'   : 'tq_fc_id/tq_fc_id'
 * '<S2>'   : 'tq_fc_id/tq_fc_id/tq_fc_id'
 * '<S3>'   : 'tq_fc_id/tq_fc_id/tq_fc_id/Chart'
 * '<S4>'   : 'tq_fc_id/tq_fc_id/tq_fc_id/Chart/fc_id_fun'
 * '<S5>'   : 'tq_fc_id/tq_fc_id/tq_fc_id/Chart/tq_fc_id_fun'
 * '<S6>'   : 'tq_fc_id/tq_fc_id/tq_fc_id/Chart/tq_id_fun'
 * '<S7>'   : 'tq_fc_id/tq_fc_id/tq_fc_id/Chart/fc_id_fun/Subsystem'
 * '<S8>'   : 'tq_fc_id/tq_fc_id/tq_fc_id/Chart/fc_id_fun/Subsystem/Chart'
 * '<S9>'   : 'tq_fc_id/tq_fc_id/tq_fc_id/Chart/tq_fc_id_fun/Subsystem'
 * '<S10>'  : 'tq_fc_id/tq_fc_id/tq_fc_id/Chart/tq_id_fun/Subsystem'
 * '<S11>'  : 'tq_fc_id/tq_fc_id/tq_fc_id/Chart/tq_id_fun/Subsystem/Chart'
 */

/*-
 * Requirements for '<Root>': tq_fc_id

 */
#endif                                 /* RTW_HEADER_tq_fc_id_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
