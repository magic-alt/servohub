/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: tq_fc_id.c
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

#include "tq_fc_id.h"
#include "servo_hub_database_type.h"
#include "rtwtypes.h"

/* Named constants for Chart: '<S10>/Chart' */
#define tq_fc_id_IN_add                ((uint8_T)1U)
#define tq_fc_id_IN_wait               ((uint8_T)2U)

/* Named constants for Chart: '<S2>/Chart' */
#define tq_fc_id_IN_error              ((uint8_T)1U)
#define tq_fc_id_IN_fc_id_state        ((uint8_T)2U)
#define tq_fc_id_IN_idle               ((uint8_T)3U)
#define tq_fc_id_IN_success            ((uint8_T)4U)
#define tq_fc_id_IN_tq_id_state        ((uint8_T)5U)

/* System initialize for referenced model: 'tq_fc_id' */
void tq_fc_id_Init(TqFcIdOutput *rty_output, tq_fc_id_DW_f *localDW)
{
    /* SystemInitialize for Chart: '<S2>/Chart' incorporates:
     *  SubSystem: '<S3>/tq_id_fun'
     */
    /* InitializeConditions for Delay: '<S10>/Delay' */
    localDW->icLoad_i = true;

    /* SystemInitialize for Chart: '<S2>/Chart' incorporates:
     *  SubSystem: '<S3>/fc_id_fun'
     */
    /* InitializeConditions for Delay: '<S7>/Delay' */
    localDW->icLoad = true;

    /* SystemInitialize for BusCreator: '<S1>/Bus Creator' */
    rty_output->pos_cmd_p = localDW->pos_cmd_p;
    rty_output->iq_com_enable = 0U;
    rty_output->tq_com_enable = 0U;
    rty_output->fc_com_enable = 0U;
    rty_output->state_now = 0;
}

/* Output and update for referenced model: 'tq_fc_id' */
void tq_fc_id(const TqFcIdInput *rtu_input, const TqFcIdConfig *rtu_config,
              TqFcIdOutput *rty_output, tq_fc_id_DW_f *localDW)
{
    int32_T i;

    /* Chart: '<S2>/Chart' incorporates:
     *  DataTypeConversion: '<S4>/Data Type Conversion2'
     *  DataTypeConversion: '<S6>/Data Type Conversion2'
     *  Product: '<S4>/Divide'
     *  Product: '<S9>/Divide'
     *  RelationalOperator: '<S4>/Relational Operator'
     *  RelationalOperator: '<S6>/Relational Operator'
     *  Sum: '<S10>/Add'
     *  Sum: '<S4>/Add'
     *  Sum: '<S6>/Add'
     *  Sum: '<S7>/Add'
     *  Sum: '<S9>/Add1'
     */
    /* Gateway: tq_fc_id/tq_fc_id/Chart */
    /* During: tq_fc_id/tq_fc_id/Chart */
    if (localDW->is_active_c3_tq_fc_id == 0U)
    {
        /* Entry: tq_fc_id/tq_fc_id/Chart */
        localDW->is_active_c3_tq_fc_id = 1U;

        /* Entry Internal: tq_fc_id/tq_fc_id/Chart */
        /* Transition: '<S3>:2' */
        localDW->is_c3_tq_fc_id = tq_fc_id_IN_idle;

        /* Entry 'idle': '<S3>:1' */
    }
    else
    {
        switch (localDW->is_c3_tq_fc_id)
        {
          case tq_fc_id_IN_error:
            /* During 'error': '<S3>:6' */
            /* '<S3>:17:1' sf_internal_predicateOutput = error==0; */
            if (localDW->error == 0)
            {
                /* Transition: '<S3>:17' */
                localDW->is_c3_tq_fc_id = tq_fc_id_IN_idle;

                /* Entry 'idle': '<S3>:1' */
            }
            else
            {
                /* '<S3>:6:3' iq_com_enable = uint8(1); */
                localDW->iq_com_enable = 1U;

                /* '<S3>:6:4' state_now = int8(-1); */
                localDW->state_now = -1;

                /* '<S3>:6:5' pos_cmd_p = pos_init_p; */
                localDW->pos_cmd_p = rtu_input->pos_init_p;
            }
            break;

          case tq_fc_id_IN_fc_id_state:
            {
                /* During 'fc_id_state': '<S3>:7' */
                /* '<S3>:15:1' sf_internal_predicateOutput = id_state == true; */
                if (localDW->id_state)
                {
                    real32_T rtb_Divide1;

                    /* Transition: '<S3>:15' */
                    localDW->is_c3_tq_fc_id = tq_fc_id_IN_success;

                    /* Entry 'success': '<S3>:13' */
                    /* '<S3>:13:3' id_state = false; */
                    localDW->id_state = false;

                    /* '<S3>:13:4' iq_com_enable = uint8(1); */
                    localDW->iq_com_enable = 1U;

                    /* '<S3>:13:5' state_now = int8(3); */
                    localDW->state_now = 3;

                    /* '<S3>:13:6' tq_com_enable = uint8(0); */
                    localDW->tq_com_enable = 0U;

                    /* '<S3>:13:7' fc_com_enable = uint8(0); */
                    localDW->fc_com_enable = 0U;

                    /* Outputs for Function Call SubSystem: '<S3>/tq_fc_id_fun' */
                    /* Product: '<S5>/Divide1' incorporates:
                     *  Constant: '<S5>/Constant'
                     *  DataStoreRead: '<S5>/Data Store Read1'
                     */
                    /* '<S3>:13:8' pos_cmd_p = tq_fc_id_fun(pos_init_p,enc_line); */
                    /* Simulink Function 'tq_fc_id_fun': '<S3>:60' */
                    rtb_Divide1 = localDW->fc_n_com / 200000.0F;

                    /* DataStoreWrite: '<S5>/Data Store Write' */
                    localDW->fc_n_com = rtb_Divide1;

                    /* DataStoreWrite: '<S5>/Data Store Write2' incorporates:
                     *  DataStoreRead: '<S5>/Data Store Read'
                     *  Sum: '<S5>/Add'
                     */
                    for (i = 0; i < 360; i++)
                    {
                        localDW->com_table[i] -= rtb_Divide1;
                    }

                    /* End of DataStoreWrite: '<S5>/Data Store Write2' */

                    /* DataStoreWrite: '<S5>/Data Store Write1' incorporates:
                     *  DataStoreRead: '<S5>/Data Store Read2'
                     */
                    localDW->fc_p_com = localDW->fc_n_com;
                    localDW->pos_cmd_p = (rtu_config->enc_line_p_n >> 1) +
                        rtu_input->pos_init_p;

                    /* End of Outputs for SubSystem: '<S3>/tq_fc_id_fun' */

                    /* '<S3>:16:1' sf_internal_predicateOutput = error~=0; */
                }
                else if (localDW->error != 0)
                {
                    /* Transition: '<S3>:16' */
                    localDW->is_c3_tq_fc_id = tq_fc_id_IN_error;

                    /* Entry 'error': '<S3>:6' */
                }
                else
                {
                    int64_T Add_d;

                    /* '<S3>:7:5' iq_com_enable = uint8(0); */
                    localDW->iq_com_enable = 0U;

                    /* '<S3>:7:6' state_now = int8(2); */
                    localDW->state_now = 2;

                    /* Outputs for Function Call SubSystem: '<S3>/fc_id_fun' */
                    /* DiscreteIntegrator: '<S4>/Discrete-Time Integrator' incorporates:
                     *  DataStoreWrite: '<S4>/Data Store Write'
                     */
                    /* '<S3>:7:7' [pos_cmd_p,id_state] = fc_id_fun(iq_com_A,pos_abs_p,pos_init_p,enc_line); */
                    /* Simulink Function 'fc_id_fun': '<S3>:41' */
                    localDW->fc_n_com = localDW->DiscreteTimeIntegrator_DSTATE;

                    /* Chart: '<S7>/Chart' */
                    /* Gateway: tq_fc_id/tq_fc_id/Chart/fc_id_fun/Subsystem/Chart */
                    /* During: tq_fc_id/tq_fc_id/Chart/fc_id_fun/Subsystem/Chart */
                    if (localDW->is_active_c2_tq_fc_id == 0U)
                    {
                        /* Entry: tq_fc_id/tq_fc_id/Chart/fc_id_fun/Subsystem/Chart */
                        localDW->is_active_c2_tq_fc_id = 1U;

                        /* Entry Internal: tq_fc_id/tq_fc_id/Chart/fc_id_fun/Subsystem/Chart */
                        /* Transition: '<S8>:2' */
                        localDW->is_c2_tq_fc_id = tq_fc_id_IN_wait;

                        /* Entry 'wait': '<S8>:1' */
                    }
                    else if (localDW->is_c2_tq_fc_id == tq_fc_id_IN_add)
                    {
                        /* During 'add': '<S8>:3' */
                        /* '<S8>:7:1' sf_internal_predicateOutput = counts == 0; */
                        if (localDW->counts == 0)
                        {
                            /* Transition: '<S8>:7' */
                            localDW->is_c2_tq_fc_id = tq_fc_id_IN_wait;

                            /* Entry 'wait': '<S8>:1' */
                        }

                        /* During 'wait': '<S8>:1' */
                        /* '<S8>:4:1' sf_internal_predicateOutput = counts >= 100; */
                    }
                    else if (localDW->counts >= 100)
                    {
                        /* Transition: '<S8>:4' */
                        localDW->is_c2_tq_fc_id = tq_fc_id_IN_add;

                        /* Entry 'add': '<S8>:3' */
                        /* '<S8>:3:3' counts = 0; */
                        localDW->counts = 0U;

                        /* '<S8>:3:4' out_add = -1; */
                        localDW->out_add = -1;
                    }
                    else
                    {
                        /* '<S8>:1:3' counts = counts + 1; */
                        localDW->counts++;

                        /* '<S8>:1:4' out_add = 0; */
                        localDW->out_add = 0;
                    }

                    /* End of Chart: '<S7>/Chart' */

                    /* Delay: '<S7>/Delay' incorporates:
                     *  Sum: '<S7>/Add1'
                     */
                    if (localDW->icLoad)
                    {
                        localDW->Delay_DSTATE = rtu_input->pos_init_p +
                            rtu_config->enc_line_p_n;
                    }

                    /* Sum: '<S7>/Add' incorporates:
                     *  DataTypeConversion: '<S7>/Data Type Conversion'
                     *  Delay: '<S7>/Delay'
                     */
                    Add_d = localDW->out_add + localDW->Delay_DSTATE;

                    /* Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator' */
                    localDW->DiscreteTimeIntegrator_DSTATE +=
                        rtu_input->iq_com_A;

                    /* Update for Delay: '<S7>/Delay' incorporates:
                     *  Sum: '<S7>/Add'
                     */
                    localDW->icLoad = false;
                    localDW->Delay_DSTATE = Add_d;

                    /* End of Outputs for SubSystem: '<S3>/fc_id_fun' */
                    localDW->pos_cmd_p = Add_d;

                    /* Outputs for Function Call SubSystem: '<S3>/fc_id_fun' */
                    localDW->id_state = (Add_d - rtu_input->pos_init_p <=
                                         (rtu_config->enc_line_p_n >> 1));

                    /* End of Outputs for SubSystem: '<S3>/fc_id_fun' */
                    /* '<S3>:7:8' tq_com_enable = uint8(1); */
                    localDW->tq_com_enable = 1U;

                    /* '<S3>:7:9' fc_com_enable = uint8(0); */
                    localDW->fc_com_enable = 0U;
                }
            }
            break;

          case tq_fc_id_IN_idle:
            /* During 'idle': '<S3>:1' */
            /* '<S3>:5:1' sf_internal_predicateOutput = start == 1; */
            if (rtu_input->start == 1)
            {
                /* Transition: '<S3>:5' */
                localDW->is_c3_tq_fc_id = tq_fc_id_IN_tq_id_state;

                /* Entry 'tq_id_state': '<S3>:4' */
            }
            else
            {
                /* '<S3>:1:3' id_state = false; */
                localDW->id_state = false;

                /* '<S3>:1:4' iq_com_enable = uint8(1); */
                localDW->iq_com_enable = 1U;

                /* '<S3>:1:5' state_now = int8(0); */
                localDW->state_now = 0;

                /* '<S3>:1:6' pos_cmd_p = pos_init_p; */
                localDW->pos_cmd_p = rtu_input->pos_init_p;

                /* '<S3>:1:7' tq_com_enable = uint8(0); */
                localDW->tq_com_enable = 0U;

                /* '<S3>:1:8' fc_com_enable = uint8(0); */
                localDW->fc_com_enable = 0U;
            }
            break;

          case tq_fc_id_IN_success:
            /* During 'success': '<S3>:13' */
            /* '<S3>:18:1' sf_internal_predicateOutput = true; */
            /* Transition: '<S3>:18' */
            localDW->is_c3_tq_fc_id = tq_fc_id_IN_idle;

            /* Entry 'idle': '<S3>:1' */
            break;

          default:
            {
                /* During 'tq_id_state': '<S3>:4' */
                /* '<S3>:8:1' sf_internal_predicateOutput = id_state == true; */
                if (localDW->id_state)
                {
                    /* Transition: '<S3>:8' */
                    localDW->is_c3_tq_fc_id = tq_fc_id_IN_fc_id_state;

                    /* Entry 'fc_id_state': '<S3>:7' */
                    /* '<S3>:7:3' id_state = false; */
                    localDW->id_state = false;

                    /* '<S3>:10:1' sf_internal_predicateOutput = error~=0; */
                }
                else if (localDW->error != 0)
                {
                    /* Transition: '<S3>:10' */
                    localDW->is_c3_tq_fc_id = tq_fc_id_IN_error;

                    /* Entry 'error': '<S3>:6' */
                }
                else
                {
                    int64_T Add_d;

                    /* '<S3>:4:3' iq_com_enable = uint8(0); */
                    localDW->iq_com_enable = 0U;

                    /* '<S3>:4:4' state_now = int8(1); */
                    localDW->state_now = 1;

                    /* Outputs for Function Call SubSystem: '<S3>/tq_id_fun' */
                    /* DataStoreWrite: '<S6>/Data Store Write' incorporates:
                     *  Constant: '<S6>/Constant1'
                     *  DataTypeConversion: '<S6>/Data Type Conversion'
                     *  DataTypeConversion: '<S6>/Data Type Conversion1'
                     *  Gain: '<S6>/Gain'
                     *  Product: '<S6>/Divide'
                     *  Sum: '<S6>/Add1'
                     */
                    /* '<S3>:4:5' [pos_cmd_p,id_state] = tq_id_fun(iq_com_A,pos_abs_p,pos_init_p,enc_line); */
                    /* Simulink Function 'tq_id_fun': '<S3>:26' */
                    localDW->com_table[(uint16_T)((uint16_T)(360.0F * ((real32_T)
                        rtu_input->pos_abs_p / (real32_T)
                        rtu_config->enc_line_p_n)) + 1U) - 1] =
                        rtu_input->iq_com_A;

                    /* Chart: '<S10>/Chart' */
                    /* Gateway: tq_fc_id/tq_fc_id/Chart/tq_id_fun/Subsystem/Chart */
                    /* During: tq_fc_id/tq_fc_id/Chart/tq_id_fun/Subsystem/Chart */
                    if (localDW->is_active_c1_tq_fc_id == 0U)
                    {
                        /* Entry: tq_fc_id/tq_fc_id/Chart/tq_id_fun/Subsystem/Chart */
                        localDW->is_active_c1_tq_fc_id = 1U;

                        /* Entry Internal: tq_fc_id/tq_fc_id/Chart/tq_id_fun/Subsystem/Chart */
                        /* Transition: '<S11>:2' */
                        localDW->is_c1_tq_fc_id = tq_fc_id_IN_wait;

                        /* Entry 'wait': '<S11>:1' */
                    }
                    else if (localDW->is_c1_tq_fc_id == tq_fc_id_IN_add)
                    {
                        /* During 'add': '<S11>:3' */
                        /* '<S11>:7:1' sf_internal_predicateOutput = counts == 0; */
                        if (localDW->counts_m == 0)
                        {
                            /* Transition: '<S11>:7' */
                            localDW->is_c1_tq_fc_id = tq_fc_id_IN_wait;

                            /* Entry 'wait': '<S11>:1' */
                        }

                        /* During 'wait': '<S11>:1' */
                        /* '<S11>:4:1' sf_internal_predicateOutput = counts >= 100; */
                    }
                    else if (localDW->counts_m >= 100)
                    {
                        /* Transition: '<S11>:4' */
                        localDW->is_c1_tq_fc_id = tq_fc_id_IN_add;

                        /* Entry 'add': '<S11>:3' */
                        /* '<S11>:3:3' counts = 0; */
                        localDW->counts_m = 0U;

                        /* '<S11>:3:4' out_add = 1; */
                        localDW->out_add_e = 1;
                    }
                    else
                    {
                        /* '<S11>:1:3' counts = counts + 1; */
                        localDW->counts_m++;

                        /* '<S11>:1:4' out_add = 0; */
                        localDW->out_add_e = 0;
                    }

                    /* End of Chart: '<S10>/Chart' */

                    /* Delay: '<S10>/Delay' */
                    if (localDW->icLoad_i)
                    {
                        localDW->Delay_DSTATE_j = rtu_input->pos_init_p;
                    }

                    /* Sum: '<S10>/Add' incorporates:
                     *  DataTypeConversion: '<S10>/Data Type Conversion'
                     *  Delay: '<S10>/Delay'
                     */
                    Add_d = localDW->out_add_e + localDW->Delay_DSTATE_j;

                    /* Update for Delay: '<S10>/Delay' incorporates:
                     *  Sum: '<S10>/Add'
                     */
                    localDW->icLoad_i = false;
                    localDW->Delay_DSTATE_j = Add_d;

                    /* End of Outputs for SubSystem: '<S3>/tq_id_fun' */
                    localDW->pos_cmd_p = Add_d;

                    /* Outputs for Function Call SubSystem: '<S3>/tq_id_fun' */
                    localDW->id_state = (Add_d - rtu_input->pos_init_p >=
                                         rtu_config->enc_line_p_n);

                    /* End of Outputs for SubSystem: '<S3>/tq_id_fun' */
                    /* '<S3>:4:6' tq_com_enable = uint8(0); */
                    localDW->tq_com_enable = 0U;

                    /* '<S3>:4:7' fc_com_enable = uint8(0); */
                    localDW->fc_com_enable = 0U;
                }
            }
            break;
        }
    }

    /* End of Chart: '<S2>/Chart' */

    /* BusCreator: '<S1>/Bus Creator' */
    rty_output->pos_cmd_p = localDW->pos_cmd_p;
    rty_output->iq_com_enable = localDW->iq_com_enable;
    rty_output->tq_com_enable = localDW->tq_com_enable;
    rty_output->fc_com_enable = localDW->fc_com_enable;
    rty_output->state_now = localDW->state_now;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
