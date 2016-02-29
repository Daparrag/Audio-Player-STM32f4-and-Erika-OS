/*
 * File: SW_wrapper.h
 *
 * Code generated for Simulink model 'SW_wrapper'.
 *
 * Model version                  : 1.39
 * Simulink Coder version         : 8.3 (R2012b) 20-Jul-2012
 * TLC version                    : 8.3 (Jul 21 2012)
 * C/C++ source code generated on : Mon Oct 13 18:59:05 2014
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_SW_wrapper_h_
#define RTW_HEADER_SW_wrapper_h_
#ifndef SW_wrapper_COMMON_INCLUDES_
# define SW_wrapper_COMMON_INCLUDES_
#include <string.h>
#include "rtwtypes.h"
#endif                                 /* SW_wrapper_COMMON_INCLUDES_ */

#include "SW_wrapper_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((void*) 0)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((void) 0)
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((void*) 0)
#endif

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  int32_T sfEvent;                     /* '<S1>/Stopwatch' */
  uint8_T is_active_c1_SW_wrapper;     /* '<S1>/Stopwatch' */
  uint8_T is_control;                  /* '<S1>/Stopwatch' */
  uint8_T is_active_control;           /* '<S1>/Stopwatch' */
  uint8_T is_stopwatch;                /* '<S1>/Stopwatch' */
  uint8_T is_buzzer;                   /* '<S1>/Stopwatch' */
  uint8_T is_active_buzzer;            /* '<S1>/Stopwatch' */
  uint8_T is_timeset;                  /* '<S1>/Stopwatch' */
  uint8_T is_alarmset;                 /* '<S1>/Stopwatch' */
  uint8_T is_time;                     /* '<S1>/Stopwatch' */
  uint8_T is_active_time;              /* '<S1>/Stopwatch' */
  uint8_T Thours;                      /* '<S1>/Stopwatch' */
  uint8_T Tminutes;                    /* '<S1>/Stopwatch' */
  uint8_T Tseconds;                    /* '<S1>/Stopwatch' */
  uint8_T Ahours;                      /* '<S1>/Stopwatch' */
  uint8_T Aminutes;                    /* '<S1>/Stopwatch' */
  uint8_T Chours;                      /* '<S1>/Stopwatch' */
  uint8_T Cminutes;                    /* '<S1>/Stopwatch' */
  uint8_T Cseconds;                    /* '<S1>/Stopwatch' */
  uint8_T Ttens;                       /* '<S1>/Stopwatch' */
} D_Work_SW_wrapper;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState Stopwatch_Trig_ZCE[6];    /* '<S1>/Stopwatch' */
} PrevZCSigStates_SW_wrapper;

/* Model entry point functions */
extern void SW_wrapper_initialize(D_Work_SW_wrapper *SW_wrapper_DWork,
  PrevZCSigStates_SW_wrapper *SW_wrapper_PrevZCSigState, boolean_T
  *SW_wrapper_U_tick, boolean_T *SW_wrapper_U_button1, boolean_T
  *SW_wrapper_U_button2, boolean_T *SW_wrapper_U_button3, boolean_T
  *SW_wrapper_U_button4, boolean_T *SW_wrapper_Y_buzzer, uint8_T
  *SW_wrapper_Y_hours, uint8_T *SW_wrapper_Y_minutes, uint8_T
  *SW_wrapper_Y_seconds, uint8_T *SW_wrapper_Y_mode, uint8_T
  *SW_wrapper_Y_tenths);
extern void SW_wrapper_step(D_Work_SW_wrapper *SW_wrapper_DWork,
  PrevZCSigStates_SW_wrapper *SW_wrapper_PrevZCSigState, boolean_T
  SW_wrapper_U_tick, boolean_T SW_wrapper_U_button1, boolean_T
  SW_wrapper_U_button2, boolean_T SW_wrapper_U_button3, boolean_T
  SW_wrapper_U_button4, boolean_T *SW_wrapper_Y_buzzer, uint8_T
  *SW_wrapper_Y_hours, uint8_T *SW_wrapper_Y_minutes, uint8_T
  *SW_wrapper_Y_seconds, uint8_T *SW_wrapper_Y_mode, uint8_T
  *SW_wrapper_Y_tenths);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('Stage3/SW_wrapper')    - opens subsystem Stage3/SW_wrapper
 * hilite_system('Stage3/SW_wrapper/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Stage3'
 * '<S1>'   : 'Stage3/SW_wrapper'
 * '<S2>'   : 'Stage3/SW_wrapper/Stopwatch'
 */
#endif                                 /* RTW_HEADER_SW_wrapper_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
