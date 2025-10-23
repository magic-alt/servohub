/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: pos_speed_ctl_pip.c
 *
 * Code generated for Simulink model 'pos_speed_ctl_pip'.
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

#include "pos_speed_ctl_pip.h"
#include "servo_hub_database_type.h"
#include <math.h>
#include "rtwtypes.h"

/* System initialize for referenced model: 'pos_speed_ctl_pip' */
void pos_speed_ctl_pip_Init(pos_speed_ctl_pip_DW_f *localDW)
{
    /* Outputs for Atomic SubSystem: '<S2>/Initialize Function' */
    /* StateWriter: '<S3>/State Writer' incorporates:
     *  Constant: '<S3>/Constant'
     */
    localDW->speed_ki_int = 0.0F;

    /* StateWriter: '<S3>/State Writer1' incorporates:
     *  Constant: '<S3>/Constant1'
     */
    localDW->iq_tar_last = 0.0F;

    /* StateWriter: '<S3>/State Writer2' incorporates:
     *  Constant: '<S3>/Constant2'
     */
    localDW->ev_last = 0.0F;

    /* StateWriter: '<S3>/State Writer3' incorporates:
     *  Constant: '<S3>/Constant3'
     */
    localDW->pos_now_pulse_last = 0LL;

    /* StateWriter: '<S3>/State Writer4' incorporates:
     *  Constant: '<S3>/Constant4'
     */
    localDW->x2_ev_rad_s = 0.0F;

    /* StateWriter: '<S3>/State Writer5' incorporates:
     *  Constant: '<S3>/Constant5'
     */
    localDW->x3 = 0.0F;

    /* StateWriter: '<S3>/State Writer6' incorporates:
     *  Constant: '<S3>/Constant6'
     */
    localDW->x_err_last = 0.0F;

    /* End of Outputs for SubSystem: '<S2>/Initialize Function' */
}

/* Output and update for referenced model: 'pos_speed_ctl_pip' */
void pos_speed_ctl_pip(const PosSpeedCtlInput *rtu_input, const
                       PosSpeedCtlConfig *rtu_config, PosSpeedCtlOutput
                       *rty_output, pos_speed_ctl_pip_DW_f *localDW)
{
    int64_T rtb_Add1;
    real32_T rtb_Add;
    real32_T rtb_Add2;
    real32_T rtb_Add4;
    real32_T rtb_Add4_tmp;
    real32_T rtb_Add_a;
    real32_T rtb_Gain1;
    real32_T rtb_Gain1_l;
    real32_T rtb_Product7;
    real32_T rtb_Reciprocal;

    /* Sum: '<S2>/Add1' */
    rtb_Add1 = rtu_input->pos_tar_p - rtu_input->pos_now_p;

    /* Sum: '<S2>/Add' incorporates:
     *  DataTypeConversion: '<S2>/Data Type Conversion1'
     *  Gain: '<S6>/Gain1'
     *  Gain: '<S7>/Gain1'
     *  Product: '<S2>/Product1'
     *  Product: '<S2>/Product2'
     *  Product: '<S6>/Product'
     *  Product: '<S7>/Product'
     *  Sum: '<S2>/Add1'
     */
    rtb_Add = (6.28318548F * (real32_T)rtb_Add1 * rtu_config->enc_line_inv_p_n *
               rtu_config->kp_p * rtu_config->mode + 6.28318548F *
               rtu_input->speed_tar_p_s * rtu_config->enc_line_inv_p_n *
               rtu_config->vff) - rtu_input->speed_now_rad_s;

    /* Switch: '<S5>/Switch2' incorporates:
     *  Gain: '<S2>/Gain1'
     *  RelationalOperator: '<S5>/LowerRelop1'
     *  RelationalOperator: '<S5>/UpperRelop'
     *  Switch: '<S5>/Switch'
     */
    if (rtb_Add > rtu_config->speed_max_rad_s)
    {
        rtb_Add = rtu_config->speed_max_rad_s;
    }
    else if (rtb_Add < -rtu_config->speed_max_rad_s)
    {
        /* Switch: '<S5>/Switch' incorporates:
         *  Gain: '<S2>/Gain1'
         */
        rtb_Add = -rtu_config->speed_max_rad_s;
    }

    /* End of Switch: '<S5>/Switch2' */

    /* Product: '<S10>/Product' */
    rtb_Add *= rtu_config->kp_s;

    /* Switch: '<S10>/Switch' incorporates:
     *  Constant: '<S10>/Constant'
     *  Delay: '<S10>/Delay1'
     *  MinMax: '<S10>/Max'
     *  Sum: '<S10>/Add1'
     */
    if (rtu_config->dynamic_integration_enable > 0)
    {
        rtb_Gain1_l = fmaxf(rtu_input->iq_max_A - localDW->iq_tar_last, 0.0F);
    }
    else
    {
        rtb_Gain1_l = rtu_input->iq_max_A;
    }

    /* End of Switch: '<S10>/Switch' */

    /* Sum: '<S10>/Add' incorporates:
     *  Delay: '<S10>/Delay'
     *  Product: '<S10>/Product1'
     */
    rtb_Add_a = rtu_config->ki_s * rtu_config->tp_s * rtb_Add +
        localDW->speed_ki_int;

    /* Gain: '<S10>/Gain1' */
    rtb_Gain1 = -rtu_input->iq_max_A;

    /* Switch: '<S16>/Switch2' incorporates:
     *  RelationalOperator: '<S16>/LowerRelop1'
     *  Switch: '<S10>/Switch1'
     */
    if (rtb_Add_a > rtb_Gain1_l)
    {
        rtb_Add_a = rtb_Gain1_l;
    }
    else
    {
        if (rtu_config->dynamic_integration_enable > 0)
        {
            /* Switch: '<S10>/Switch1' incorporates:
             *  Constant: '<S10>/Constant1'
             *  Delay: '<S10>/Delay1'
             *  Gain: '<S10>/Gain1'
             *  MinMax: '<S10>/Max1'
             *  Sum: '<S10>/Add2'
             */
            rtb_Gain1_l = fminf(-rtu_input->iq_max_A - localDW->iq_tar_last,
                                0.0F);
        }
        else
        {
            /* Switch: '<S10>/Switch1' incorporates:
             *  Gain: '<S10>/Gain1'
             */
            rtb_Gain1_l = -rtu_input->iq_max_A;
        }

        /* Switch: '<S16>/Switch' incorporates:
         *  RelationalOperator: '<S16>/UpperRelop'
         */
        if (rtb_Add_a < rtb_Gain1_l)
        {
            rtb_Add_a = rtb_Gain1_l;
        }

        /* End of Switch: '<S16>/Switch' */
    }

    /* End of Switch: '<S16>/Switch2' */

    /* Sum: '<S10>/Add3' */
    rtb_Add += rtb_Add_a;

    /* Switch: '<S17>/Switch2' incorporates:
     *  Gain: '<S10>/Gain1'
     *  RelationalOperator: '<S17>/LowerRelop1'
     *  RelationalOperator: '<S17>/UpperRelop'
     *  Switch: '<S17>/Switch'
     */
    if (rtb_Add > rtu_input->iq_max_A)
    {
        rtb_Gain1 = rtu_input->iq_max_A;
    }
    else if (rtb_Add >= -rtu_input->iq_max_A)
    {
        rtb_Gain1 = rtb_Add;
    }

    /* End of Switch: '<S17>/Switch2' */

    /* Product: '<S2>/Reciprocal' */
    rtb_Reciprocal = 1.0F / rtu_config->j_kt;

    /* Product: '<S9>/Product7' */
    rtb_Product7 = rtu_input->iq_max_A * rtb_Reciprocal;

    /* Gain: '<S9>/Gain2' */
    rtb_Add = 6.28318548F * rtu_config->dob_wn_Hz;

    /* Sum: '<S9>/Add3' incorporates:
     *  DataTypeConversion: '<S9>/Data Type Conversion'
     *  Delay: '<S9>/Delay1'
     *  Delay: '<S9>/Delay2'
     *  Gain: '<S13>/Gain1'
     *  Product: '<S13>/Product'
     *  Sum: '<S9>/Add'
     */
    rtb_Gain1_l = (real32_T)(rtu_input->pos_now_p - localDW->pos_now_pulse_last)
        * 6.28318548F * rtu_config->enc_line_inv_p_n - localDW->x_err_last;

    /* Product: '<S9>/Product1' incorporates:
     *  Product: '<S9>/Product'
     */
    rtb_Add4_tmp = rtb_Add * rtb_Add;

    /* Sum: '<S12>/Add4' incorporates:
     *  Delay: '<S12>/Delay3'
     *  Product: '<S12>/Product7'
     *  Product: '<S9>/Product1'
     *  Product: '<S9>/Product4'
     */
    rtb_Add4 = rtb_Add4_tmp * rtb_Add * rtb_Gain1_l * rtu_config->tp_s +
        localDW->x3;

    /* Switch: '<S15>/Switch2' incorporates:
     *  RelationalOperator: '<S15>/LowerRelop1'
     */
    if (rtb_Add4 <= rtb_Product7)
    {
        /* Gain: '<S12>/Gain' */
        rtb_Product7 = -rtb_Product7;

        /* Switch: '<S15>/Switch' incorporates:
         *  RelationalOperator: '<S15>/UpperRelop'
         */
        if (rtb_Add4 >= rtb_Product7)
        {
            rtb_Product7 = rtb_Add4;
        }

        /* End of Switch: '<S15>/Switch' */
    }

    /* End of Switch: '<S15>/Switch2' */

    /* Product: '<S9>/Divide' */
    rtb_Add4 = rtb_Product7 / rtb_Reciprocal;

    /* Switch: '<S2>/Switch' incorporates:
     *  Constant: '<S2>/Constant'
     */
    if (rtu_config->dob_enable > 0)
    {
        rtb_Add2 = rtb_Add4;
    }
    else
    {
        rtb_Add2 = 0.0F;
    }

    /* Sum: '<S2>/Add2' incorporates:
     *  Gain: '<S8>/Gain1'
     *  Product: '<S2>/Product'
     *  Product: '<S8>/Product'
     *  Switch: '<S2>/Switch'
     */
    rtb_Add2 = (6.28318548F * rtu_input->acc_tar_p_ss *
                rtu_config->enc_line_inv_p_n * (rtu_config->j_kt *
                 rtu_config->aff) + rtb_Gain1) - rtb_Add2;

    /* Switch: '<S4>/Switch2' incorporates:
     *  Gain: '<S2>/Gain'
     *  RelationalOperator: '<S4>/LowerRelop1'
     *  RelationalOperator: '<S4>/UpperRelop'
     *  Switch: '<S4>/Switch'
     */
    if (rtb_Add2 > rtu_input->iq_max_A)
    {
        rtb_Add2 = rtu_input->iq_max_A;
    }
    else if (rtb_Add2 < -rtu_input->iq_max_A)
    {
        /* Switch: '<S4>/Switch' incorporates:
         *  Gain: '<S10>/Gain1'
         */
        rtb_Add2 = -rtu_input->iq_max_A;
    }

    /* End of Switch: '<S4>/Switch2' */

    /* DataTypeConversion: '<S2>/Data Type Conversion' incorporates:
     *  Sum: '<S2>/Add1'
     */
    rty_output->pos_ctl_error_p = (int32_T)rtb_Add1;

    /* BusCreator: '<S1>/Bus Creator' */
    rty_output->iq_tar_A = rtb_Add2;
    rty_output->dob_iq_com_A = rtb_Add4;

    /* Sum: '<S11>/Add4' incorporates:
     *  Delay: '<S11>/Delay3'
     *  Gain: '<S9>/l2'
     *  Product: '<S11>/Product7'
     *  Product: '<S9>/Product3'
     *  Product: '<S9>/Product5'
     *  Sum: '<S9>/Add1'
     */
    rtb_Reciprocal = (rtb_Add4_tmp * 3.0F * rtb_Gain1_l + (rtb_Reciprocal *
                       rtb_Add2 + rtb_Product7)) * rtu_config->tp_s +
        localDW->x2_ev_rad_s;

    /* Switch: '<S14>/Switch2' incorporates:
     *  Gain: '<S11>/Gain'
     *  RelationalOperator: '<S14>/LowerRelop1'
     *  RelationalOperator: '<S14>/UpperRelop'
     *  Switch: '<S14>/Switch'
     */
    if (rtb_Reciprocal > rtu_config->speed_max_rad_s)
    {
        rtb_Reciprocal = rtu_config->speed_max_rad_s;
    }
    else if (rtb_Reciprocal < -rtu_config->speed_max_rad_s)
    {
        /* Switch: '<S14>/Switch' incorporates:
         *  Gain: '<S11>/Gain'
         */
        rtb_Reciprocal = -rtu_config->speed_max_rad_s;
    }

    /* End of Switch: '<S14>/Switch2' */

    /* Update for Delay: '<S10>/Delay1' */
    localDW->iq_tar_last = rtb_Gain1;

    /* Update for Delay: '<S10>/Delay' */
    localDW->speed_ki_int = rtb_Add_a;

    /* Update for Delay: '<S9>/Delay1' */
    localDW->pos_now_pulse_last = rtu_input->pos_now_p;

    /* Product: '<S9>/Product6' incorporates:
     *  Delay: '<S9>/Delay'
     *  Gain: '<S9>/l1'
     *  Product: '<S9>/Product2'
     *  Sum: '<S9>/Add2'
     */
    rtb_Add = (3.0F * rtb_Add * rtb_Gain1_l + localDW->ev_last) *
        rtu_config->tp_s;

    /* Saturate: '<S9>/Saturation' */
    if (rtb_Add > 3.14159274F)
    {
        /* Update for Delay: '<S9>/Delay2' */
        localDW->x_err_last = 3.14159274F;
    }
    else if (rtb_Add < -3.14159274F)
    {
        /* Update for Delay: '<S9>/Delay2' */
        localDW->x_err_last = -3.14159274F;
    }
    else
    {
        /* Update for Delay: '<S9>/Delay2' */
        localDW->x_err_last = rtb_Add;
    }

    /* End of Saturate: '<S9>/Saturation' */

    /* Update for Delay: '<S12>/Delay3' */
    localDW->x3 = rtb_Product7;

    /* Update for Delay: '<S11>/Delay3' */
    localDW->x2_ev_rad_s = rtb_Reciprocal;

    /* Update for Delay: '<S9>/Delay' */
    localDW->ev_last = rtb_Reciprocal;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
