/*
 * File: SW_wrapper.c
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

#include "SW_wrapper.h"
#include "SW_wrapper_private.h"

/* Named constants for Chart: '<S1>/Stopwatch' */
#define SW_wrapper_IN_NO_ACTIVE_CHILD  ((uint8_T)0U)
#define SW_wrapper_IN_alarmset         ((uint8_T)1U)
#define SW_wrapper_IN_going            ((uint8_T)1U)
#define SW_wrapper_IN_off              ((uint8_T)1U)
#define SW_wrapper_IN_sethours         ((uint8_T)1U)
#define SW_wrapper_IN_setminutes       ((uint8_T)2U)
#define SW_wrapper_IN_setup            ((uint8_T)1U)
#define SW_wrapper_IN_stop             ((uint8_T)2U)
#define SW_wrapper_IN_stopwatch        ((uint8_T)2U)
#define SW_wrapper_IN_ticking          ((uint8_T)2U)
#define SW_wrapper_IN_time             ((uint8_T)3U)
#define SW_wrapper_IN_timeset          ((uint8_T)4U)
#define SW_wrapper_event_buttonM       (5)
#define SW_wrapper_event_buttonP       (3)
#define SW_wrapper_event_mode          (1)
#define SW_wrapper_event_reset         (2)
#define SW_wrapper_event_submode       (6)
#define SW_wrapper_event_tens          (0)
#define SW_wrapper_event_timeseton     (4)

/* Forward declaration for local functions */
static void SW_wrapper_broadcast_timeseton(boolean_T *SW_wrapper_Y_buzzer,
  uint8_T *SW_wrapper_Y_hours, uint8_T *SW_wrapper_Y_minutes, uint8_T
  *SW_wrapper_Y_seconds, uint8_T *SW_wrapper_Y_mode, uint8_T
  *SW_wrapper_Y_tenths, D_Work_SW_wrapper *SW_wrapper_DWork);
static void SW_wrapper_control(boolean_T *SW_wrapper_Y_buzzer, uint8_T
  *SW_wrapper_Y_hours, uint8_T *SW_wrapper_Y_minutes, uint8_T
  *SW_wrapper_Y_seconds, uint8_T *SW_wrapper_Y_mode, uint8_T
  *SW_wrapper_Y_tenths, D_Work_SW_wrapper *SW_wrapper_DWork);
static void SW_wrapper_c1_SW_wrapper(boolean_T *SW_wrapper_Y_buzzer, uint8_T
  *SW_wrapper_Y_hours, uint8_T *SW_wrapper_Y_minutes, uint8_T
  *SW_wrapper_Y_seconds, uint8_T *SW_wrapper_Y_mode, uint8_T
  *SW_wrapper_Y_tenths, D_Work_SW_wrapper *SW_wrapper_DWork);
static void SW_wrap_chartstep_c1_SW_wrapper(boolean_T *SW_wrapper_Y_buzzer,
  uint8_T *SW_wrapper_Y_hours, uint8_T *SW_wrapper_Y_minutes, uint8_T
  *SW_wrapper_Y_seconds, uint8_T *SW_wrapper_Y_mode, uint8_T
  *SW_wrapper_Y_tenths, D_Work_SW_wrapper *SW_wrapper_DWork);

/* Function for Chart: '<S1>/Stopwatch' */
static void SW_wrapper_broadcast_timeseton(boolean_T *SW_wrapper_Y_buzzer,
  uint8_T *SW_wrapper_Y_hours, uint8_T *SW_wrapper_Y_minutes, uint8_T
  *SW_wrapper_Y_seconds, uint8_T *SW_wrapper_Y_mode, uint8_T
  *SW_wrapper_Y_tenths, D_Work_SW_wrapper *SW_wrapper_DWork)
{
  int32_T b_previousEvent;

  /* Event: '<S2>:90' */
  b_previousEvent = SW_wrapper_DWork->sfEvent;
  SW_wrapper_DWork->sfEvent = SW_wrapper_event_timeseton;
  SW_wrapper_c1_SW_wrapper(SW_wrapper_Y_buzzer, SW_wrapper_Y_hours,
    SW_wrapper_Y_minutes, SW_wrapper_Y_seconds, SW_wrapper_Y_mode,
    SW_wrapper_Y_tenths, SW_wrapper_DWork);
  SW_wrapper_DWork->sfEvent = b_previousEvent;
}

/* Function for Chart: '<S1>/Stopwatch' */
static void SW_wrapper_control(boolean_T *SW_wrapper_Y_buzzer, uint8_T
  *SW_wrapper_Y_hours, uint8_T *SW_wrapper_Y_minutes, uint8_T
  *SW_wrapper_Y_seconds, uint8_T *SW_wrapper_Y_mode, uint8_T
  *SW_wrapper_Y_tenths, D_Work_SW_wrapper *SW_wrapper_DWork)
{
  /* During 'control': '<S2>:43' */
  switch (SW_wrapper_DWork->is_control) {
   case SW_wrapper_IN_alarmset:
    /* During 'alarmset': '<S2>:55' */
    if (SW_wrapper_DWork->sfEvent == SW_wrapper_event_mode) {
      /* Transition: '<S2>:57' */
      /* Exit Internal 'alarmset': '<S2>:55' */
      SW_wrapper_DWork->is_alarmset = SW_wrapper_IN_NO_ACTIVE_CHILD;
      SW_wrapper_DWork->is_control = SW_wrapper_IN_NO_ACTIVE_CHILD;
      SW_wrapper_broadcast_timeseton(SW_wrapper_Y_buzzer, SW_wrapper_Y_hours,
        SW_wrapper_Y_minutes, SW_wrapper_Y_seconds, SW_wrapper_Y_mode,
        SW_wrapper_Y_tenths, SW_wrapper_DWork);
      if ((SW_wrapper_DWork->is_control == SW_wrapper_IN_NO_ACTIVE_CHILD) &&
          (!(SW_wrapper_DWork->is_active_control == 0U))) {
        SW_wrapper_DWork->is_control = SW_wrapper_IN_timeset;

        /* Entry 'timeset': '<S2>:53' */
        *SW_wrapper_Y_mode = 3U;

        /* Entry Internal 'timeset': '<S2>:53' */
        /* Transition: '<S2>:99' */
        *SW_wrapper_Y_hours = SW_wrapper_DWork->Thours;
        *SW_wrapper_Y_minutes = SW_wrapper_DWork->Tminutes;
        *SW_wrapper_Y_seconds = 0U;
        if (SW_wrapper_DWork->is_timeset != SW_wrapper_IN_sethours) {
          SW_wrapper_DWork->is_timeset = SW_wrapper_IN_sethours;

          /* Entry 'sethours': '<S2>:97' */
        }
      }
    } else {
      switch (SW_wrapper_DWork->is_alarmset) {
       case SW_wrapper_IN_sethours:
        /* During 'sethours': '<S2>:74' */
        if ((SW_wrapper_DWork->sfEvent == SW_wrapper_event_buttonM) &&
            (SW_wrapper_DWork->Ahours == 0)) {
          /* Transition: '<S2>:82' */
          SW_wrapper_DWork->Ahours = 23U;
          SW_wrapper_DWork->is_alarmset = SW_wrapper_IN_sethours;

          /* Entry 'sethours': '<S2>:74' */
          *SW_wrapper_Y_hours = SW_wrapper_DWork->Ahours;
        } else if (SW_wrapper_DWork->sfEvent == SW_wrapper_event_buttonP) {
          /* Transition: '<S2>:80' */
          SW_wrapper_DWork->Ahours = (uint8_T)((SW_wrapper_DWork->Ahours + 1) %
            24);
          SW_wrapper_DWork->is_alarmset = SW_wrapper_IN_sethours;

          /* Entry 'sethours': '<S2>:74' */
          *SW_wrapper_Y_hours = SW_wrapper_DWork->Ahours;
        } else if (SW_wrapper_DWork->sfEvent == SW_wrapper_event_buttonM) {
          /* Transition: '<S2>:119' */
          SW_wrapper_DWork->Ahours--;
          SW_wrapper_DWork->is_alarmset = SW_wrapper_IN_sethours;

          /* Entry 'sethours': '<S2>:74' */
          *SW_wrapper_Y_hours = SW_wrapper_DWork->Ahours;
        } else {
          if (SW_wrapper_DWork->sfEvent == SW_wrapper_event_submode) {
            /* Transition: '<S2>:159' */
            SW_wrapper_DWork->is_alarmset = SW_wrapper_IN_setminutes;

            /* Entry 'setminutes': '<S2>:158' */
            *SW_wrapper_Y_minutes = SW_wrapper_DWork->Aminutes;
          }
        }
        break;

       case SW_wrapper_IN_setminutes:
        /* During 'setminutes': '<S2>:158' */
        if (SW_wrapper_DWork->sfEvent == SW_wrapper_event_submode) {
          /* Transition: '<S2>:160' */
          SW_wrapper_DWork->is_alarmset = SW_wrapper_IN_sethours;

          /* Entry 'sethours': '<S2>:74' */
          *SW_wrapper_Y_hours = SW_wrapper_DWork->Ahours;
        } else if (SW_wrapper_DWork->sfEvent == SW_wrapper_event_buttonP) {
          /* Transition: '<S2>:161' */
          SW_wrapper_DWork->Aminutes = (uint8_T)((SW_wrapper_DWork->Aminutes + 1)
            % 60);
          SW_wrapper_DWork->is_alarmset = SW_wrapper_IN_setminutes;

          /* Entry 'setminutes': '<S2>:158' */
          *SW_wrapper_Y_minutes = SW_wrapper_DWork->Aminutes;
        } else if ((SW_wrapper_DWork->sfEvent == SW_wrapper_event_buttonM) &&
                   (SW_wrapper_DWork->Aminutes == 0)) {
          /* Transition: '<S2>:162' */
          SW_wrapper_DWork->Aminutes = 59U;
          SW_wrapper_DWork->is_alarmset = SW_wrapper_IN_setminutes;

          /* Entry 'setminutes': '<S2>:158' */
          *SW_wrapper_Y_minutes = SW_wrapper_DWork->Aminutes;
        } else {
          if (SW_wrapper_DWork->sfEvent == SW_wrapper_event_buttonM) {
            /* Transition: '<S2>:163' */
            SW_wrapper_DWork->Aminutes--;
            SW_wrapper_DWork->is_alarmset = SW_wrapper_IN_setminutes;

            /* Entry 'setminutes': '<S2>:158' */
            *SW_wrapper_Y_minutes = SW_wrapper_DWork->Aminutes;
          }
        }
        break;

       default:
        SW_wrapper_DWork->is_alarmset = SW_wrapper_IN_NO_ACTIVE_CHILD;
        break;
      }
    }
    break;

   case SW_wrapper_IN_stopwatch:
    /* During 'stopwatch': '<S2>:44' */
    if (SW_wrapper_DWork->sfEvent == SW_wrapper_event_mode) {
      /* Transition: '<S2>:59' */
      /* Exit Internal 'stopwatch': '<S2>:44' */
      SW_wrapper_DWork->is_stopwatch = SW_wrapper_IN_NO_ACTIVE_CHILD;
      SW_wrapper_DWork->is_control = SW_wrapper_IN_time;

      /* Entry 'time': '<S2>:54' */
      *SW_wrapper_Y_mode = 1U;
    } else if (SW_wrapper_DWork->sfEvent == SW_wrapper_event_reset) {
      /* Transition: '<S2>:188' */
      /* Transition: '<S2>:174' */
      /* Exit Internal 'stopwatch': '<S2>:44' */
      SW_wrapper_DWork->is_stopwatch = SW_wrapper_IN_NO_ACTIVE_CHILD;
      *SW_wrapper_Y_tenths = 0U;
      SW_wrapper_DWork->Chours = 0U;
      SW_wrapper_DWork->Cminutes = 0U;
      SW_wrapper_DWork->Cseconds = 0U;
      if (SW_wrapper_DWork->is_stopwatch != SW_wrapper_IN_stop) {
        SW_wrapper_DWork->is_stopwatch = SW_wrapper_IN_stop;

        /* Entry 'stop': '<S2>:50' */
        *SW_wrapper_Y_hours = SW_wrapper_DWork->Chours;
        *SW_wrapper_Y_minutes = SW_wrapper_DWork->Cminutes;
        *SW_wrapper_Y_seconds = SW_wrapper_DWork->Cseconds;
      }
    } else {
      switch (SW_wrapper_DWork->is_stopwatch) {
       case SW_wrapper_IN_going:
        /* During 'going': '<S2>:170' */
        if (SW_wrapper_DWork->sfEvent == SW_wrapper_event_buttonP) {
          /* Transition: '<S2>:172' */
          SW_wrapper_DWork->is_stopwatch = SW_wrapper_IN_stop;

          /* Entry 'stop': '<S2>:50' */
          *SW_wrapper_Y_hours = SW_wrapper_DWork->Chours;
          *SW_wrapper_Y_minutes = SW_wrapper_DWork->Cminutes;
          *SW_wrapper_Y_seconds = SW_wrapper_DWork->Cseconds;
        } else {
          if (SW_wrapper_DWork->sfEvent == SW_wrapper_event_tens) {
            /* Transition: '<S2>:182' */
            *SW_wrapper_Y_tenths = (uint8_T)((*SW_wrapper_Y_tenths + 1) % 10);
            if (*SW_wrapper_Y_tenths == 0) {
              /* Transition: '<S2>:180' */
              SW_wrapper_DWork->Cseconds = (uint8_T)((SW_wrapper_DWork->Cseconds
                + 1) % 60);
              if (SW_wrapper_DWork->Cseconds == 0) {
                /* Transition: '<S2>:176' */
                SW_wrapper_DWork->Cminutes = (uint8_T)
                  ((SW_wrapper_DWork->Cminutes + 1) % 60);
                if (SW_wrapper_DWork->Cminutes == 0) {
                  /* Transition: '<S2>:178' */
                  SW_wrapper_DWork->Chours = (uint8_T)((SW_wrapper_DWork->Chours
                    + 1) % 24);
                  SW_wrapper_DWork->is_stopwatch = SW_wrapper_IN_going;

                  /* Entry 'going': '<S2>:170' */
                  *SW_wrapper_Y_hours = SW_wrapper_DWork->Chours;
                  *SW_wrapper_Y_minutes = SW_wrapper_DWork->Cminutes;
                  *SW_wrapper_Y_seconds = SW_wrapper_DWork->Cseconds;
                } else {
                  /* Transition: '<S2>:185' */
                  SW_wrapper_DWork->is_stopwatch = SW_wrapper_IN_going;

                  /* Entry 'going': '<S2>:170' */
                  *SW_wrapper_Y_hours = SW_wrapper_DWork->Chours;
                  *SW_wrapper_Y_minutes = SW_wrapper_DWork->Cminutes;
                  *SW_wrapper_Y_seconds = SW_wrapper_DWork->Cseconds;
                }
              } else {
                /* Transition: '<S2>:184' */
                SW_wrapper_DWork->is_stopwatch = SW_wrapper_IN_going;

                /* Entry 'going': '<S2>:170' */
                *SW_wrapper_Y_hours = SW_wrapper_DWork->Chours;
                *SW_wrapper_Y_minutes = SW_wrapper_DWork->Cminutes;
                *SW_wrapper_Y_seconds = SW_wrapper_DWork->Cseconds;
              }
            } else {
              /* Transition: '<S2>:183' */
              SW_wrapper_DWork->is_stopwatch = SW_wrapper_IN_going;

              /* Entry 'going': '<S2>:170' */
              *SW_wrapper_Y_hours = SW_wrapper_DWork->Chours;
              *SW_wrapper_Y_minutes = SW_wrapper_DWork->Cminutes;
              *SW_wrapper_Y_seconds = SW_wrapper_DWork->Cseconds;
            }
          }
        }
        break;

       case SW_wrapper_IN_stop:
        /* During 'stop': '<S2>:50' */
        if (SW_wrapper_DWork->sfEvent == SW_wrapper_event_buttonP) {
          /* Transition: '<S2>:171' */
          SW_wrapper_DWork->is_stopwatch = SW_wrapper_IN_going;

          /* Entry 'going': '<S2>:170' */
          *SW_wrapper_Y_hours = SW_wrapper_DWork->Chours;
          *SW_wrapper_Y_minutes = SW_wrapper_DWork->Cminutes;
          *SW_wrapper_Y_seconds = SW_wrapper_DWork->Cseconds;
        }
        break;

       default:
        SW_wrapper_DWork->is_stopwatch = SW_wrapper_IN_NO_ACTIVE_CHILD;
        break;
      }
    }
    break;

   case SW_wrapper_IN_time:
    /* During 'time': '<S2>:54' */
    if (SW_wrapper_DWork->sfEvent == SW_wrapper_event_mode) {
      /* Transition: '<S2>:56' */
      SW_wrapper_DWork->is_control = SW_wrapper_IN_alarmset;

      /* Entry 'alarmset': '<S2>:55' */
      *SW_wrapper_Y_mode = 2U;

      /* Entry Internal 'alarmset': '<S2>:55' */
      /* Transition: '<S2>:75' */
      *SW_wrapper_Y_hours = SW_wrapper_DWork->Ahours;
      *SW_wrapper_Y_minutes = SW_wrapper_DWork->Aminutes;
      *SW_wrapper_Y_seconds = 0U;
      if (SW_wrapper_DWork->is_alarmset != SW_wrapper_IN_sethours) {
        SW_wrapper_DWork->is_alarmset = SW_wrapper_IN_sethours;

        /* Entry 'sethours': '<S2>:74' */
      }
    } else {
      if (SW_wrapper_DWork->sfEvent == SW_wrapper_event_tens) {
        /* Transition: '<S2>:72' */
        *SW_wrapper_Y_hours = SW_wrapper_DWork->Thours;
        *SW_wrapper_Y_minutes = SW_wrapper_DWork->Tminutes;
        *SW_wrapper_Y_seconds = SW_wrapper_DWork->Tseconds;
      }
    }
    break;

   case SW_wrapper_IN_timeset:
    /* During 'timeset': '<S2>:53' */
    if (SW_wrapper_DWork->sfEvent == SW_wrapper_event_mode) {
      /* Transition: '<S2>:58' */
      /* Exit Internal 'timeset': '<S2>:53' */
      SW_wrapper_DWork->is_timeset = SW_wrapper_IN_NO_ACTIVE_CHILD;
      SW_wrapper_DWork->is_control = SW_wrapper_IN_NO_ACTIVE_CHILD;
      SW_wrapper_broadcast_timeseton(SW_wrapper_Y_buzzer, SW_wrapper_Y_hours,
        SW_wrapper_Y_minutes, SW_wrapper_Y_seconds, SW_wrapper_Y_mode,
        SW_wrapper_Y_tenths, SW_wrapper_DWork);
      if ((SW_wrapper_DWork->is_control == SW_wrapper_IN_NO_ACTIVE_CHILD) &&
          (!(SW_wrapper_DWork->is_active_control == 0U))) {
        SW_wrapper_DWork->is_control = SW_wrapper_IN_stopwatch;

        /* Entry 'stopwatch': '<S2>:44' */
        *SW_wrapper_Y_mode = 4U;

        /* Entry Internal 'stopwatch': '<S2>:44' */
        /* Transition: '<S2>:143' */
        /* Transition: '<S2>:174' */
        *SW_wrapper_Y_tenths = 0U;
        SW_wrapper_DWork->Chours = 0U;
        SW_wrapper_DWork->Cminutes = 0U;
        SW_wrapper_DWork->Cseconds = 0U;
        if (SW_wrapper_DWork->is_stopwatch != SW_wrapper_IN_stop) {
          SW_wrapper_DWork->is_stopwatch = SW_wrapper_IN_stop;

          /* Entry 'stop': '<S2>:50' */
          *SW_wrapper_Y_hours = SW_wrapper_DWork->Chours;
          *SW_wrapper_Y_minutes = SW_wrapper_DWork->Cminutes;
          *SW_wrapper_Y_seconds = SW_wrapper_DWork->Cseconds;
        }
      }
    } else {
      switch (SW_wrapper_DWork->is_timeset) {
       case SW_wrapper_IN_sethours:
        /* During 'sethours': '<S2>:97' */
        if ((SW_wrapper_DWork->sfEvent == SW_wrapper_event_buttonM) &&
            (SW_wrapper_DWork->Thours == 0)) {
          /* Transition: '<S2>:103' */
          SW_wrapper_DWork->Thours = 23U;
          SW_wrapper_DWork->is_timeset = SW_wrapper_IN_sethours;

          /* Entry 'sethours': '<S2>:97' */
          *SW_wrapper_Y_hours = SW_wrapper_DWork->Thours;
        } else if (SW_wrapper_DWork->sfEvent == SW_wrapper_event_submode) {
          /* Transition: '<S2>:164' */
          SW_wrapper_DWork->is_timeset = SW_wrapper_IN_setminutes;

          /* Entry 'setminutes': '<S2>:165' */
          *SW_wrapper_Y_minutes = SW_wrapper_DWork->Tminutes;
        } else if (SW_wrapper_DWork->sfEvent == SW_wrapper_event_buttonP) {
          /* Transition: '<S2>:102' */
          SW_wrapper_DWork->Thours = (uint8_T)((SW_wrapper_DWork->Thours + 1) %
            24);
          SW_wrapper_DWork->is_timeset = SW_wrapper_IN_sethours;

          /* Entry 'sethours': '<S2>:97' */
          *SW_wrapper_Y_hours = SW_wrapper_DWork->Thours;
        } else {
          if (SW_wrapper_DWork->sfEvent == SW_wrapper_event_buttonM) {
            /* Transition: '<S2>:120' */
            SW_wrapper_DWork->Thours--;
            SW_wrapper_DWork->is_timeset = SW_wrapper_IN_sethours;

            /* Entry 'sethours': '<S2>:97' */
            *SW_wrapper_Y_hours = SW_wrapper_DWork->Thours;
          }
        }
        break;

       case SW_wrapper_IN_setminutes:
        /* During 'setminutes': '<S2>:165' */
        if (SW_wrapper_DWork->sfEvent == SW_wrapper_event_buttonP) {
          /* Transition: '<S2>:166' */
          SW_wrapper_DWork->Tminutes = (uint8_T)((SW_wrapper_DWork->Tminutes + 1)
            % 60);
          SW_wrapper_DWork->is_timeset = SW_wrapper_IN_setminutes;

          /* Entry 'setminutes': '<S2>:165' */
          *SW_wrapper_Y_minutes = SW_wrapper_DWork->Tminutes;
        } else if (SW_wrapper_DWork->sfEvent == SW_wrapper_event_submode) {
          /* Transition: '<S2>:167' */
          SW_wrapper_DWork->is_timeset = SW_wrapper_IN_sethours;

          /* Entry 'sethours': '<S2>:97' */
          *SW_wrapper_Y_hours = SW_wrapper_DWork->Thours;
        } else if ((SW_wrapper_DWork->sfEvent == SW_wrapper_event_buttonM) &&
                   (SW_wrapper_DWork->Tminutes == 0)) {
          /* Transition: '<S2>:168' */
          SW_wrapper_DWork->Tminutes = 59U;
          SW_wrapper_DWork->is_timeset = SW_wrapper_IN_setminutes;

          /* Entry 'setminutes': '<S2>:165' */
          *SW_wrapper_Y_minutes = SW_wrapper_DWork->Tminutes;
        } else {
          if (SW_wrapper_DWork->sfEvent == SW_wrapper_event_buttonM) {
            /* Transition: '<S2>:169' */
            SW_wrapper_DWork->Tminutes--;
            SW_wrapper_DWork->is_timeset = SW_wrapper_IN_setminutes;

            /* Entry 'setminutes': '<S2>:165' */
            *SW_wrapper_Y_minutes = SW_wrapper_DWork->Tminutes;
          }
        }
        break;

       default:
        SW_wrapper_DWork->is_timeset = SW_wrapper_IN_NO_ACTIVE_CHILD;
        break;
      }
    }
    break;

   default:
    SW_wrapper_DWork->is_control = SW_wrapper_IN_NO_ACTIVE_CHILD;
    break;
  }
}

/* Function for Chart: '<S1>/Stopwatch' */
static void SW_wrapper_c1_SW_wrapper(boolean_T *SW_wrapper_Y_buzzer, uint8_T
  *SW_wrapper_Y_hours, uint8_T *SW_wrapper_Y_minutes, uint8_T
  *SW_wrapper_Y_seconds, uint8_T *SW_wrapper_Y_mode, uint8_T
  *SW_wrapper_Y_tenths, D_Work_SW_wrapper *SW_wrapper_DWork)
{
  /* During: SW_wrapper/Stopwatch */
  if (SW_wrapper_DWork->is_active_c1_SW_wrapper == 0U) {
    /* Entry: SW_wrapper/Stopwatch */
    SW_wrapper_DWork->is_active_c1_SW_wrapper = 1U;

    /* Entry Internal: SW_wrapper/Stopwatch */
    SW_wrapper_DWork->is_active_time = 1U;

    /* Entry Internal 'time': '<S2>:62' */
    /* Transition: '<S2>:69' */
    SW_wrapper_DWork->Thours = 0U;
    SW_wrapper_DWork->Tminutes = 0U;
    SW_wrapper_DWork->Tseconds = 0U;
    SW_wrapper_DWork->Ttens = 0U;
    SW_wrapper_DWork->is_time = SW_wrapper_IN_ticking;
    SW_wrapper_DWork->is_active_control = 1U;

    /* Entry Internal 'control': '<S2>:43' */
    /* Transition: '<S2>:60' */
    SW_wrapper_DWork->Ahours = 0U;
    SW_wrapper_DWork->Aminutes = 0U;
    if (SW_wrapper_DWork->is_control != SW_wrapper_IN_time) {
      SW_wrapper_DWork->is_control = SW_wrapper_IN_time;

      /* Entry 'time': '<S2>:54' */
      *SW_wrapper_Y_mode = 1U;
    }

    SW_wrapper_DWork->is_active_buzzer = 1U;

    /* Entry Internal 'buzzer': '<S2>:110' */
    /* Transition: '<S2>:112' */
    if (SW_wrapper_DWork->is_buzzer != SW_wrapper_IN_off) {
      SW_wrapper_DWork->is_buzzer = SW_wrapper_IN_off;

      /* Entry 'off': '<S2>:111' */
      *SW_wrapper_Y_buzzer = FALSE;
    }
  } else {
    if (SW_wrapper_DWork->is_active_time != 0U) {
      /* During 'time': '<S2>:62' */
      switch (SW_wrapper_DWork->is_time) {
       case SW_wrapper_IN_setup:
        /* During 'setup': '<S2>:85' */
        if (SW_wrapper_DWork->sfEvent == SW_wrapper_event_timeseton) {
          /* Transition: '<S2>:94' */
          SW_wrapper_DWork->is_time = SW_wrapper_IN_ticking;
        }
        break;

       case SW_wrapper_IN_ticking:
        /* During 'ticking': '<S2>:68' */
        if (SW_wrapper_DWork->sfEvent == SW_wrapper_event_timeseton) {
          /* Transition: '<S2>:91' */
          SW_wrapper_DWork->is_time = SW_wrapper_IN_setup;
        } else {
          if (SW_wrapper_DWork->sfEvent == SW_wrapper_event_tens) {
            /* Transition: '<S2>:137' */
            SW_wrapper_DWork->Ttens = (uint8_T)((SW_wrapper_DWork->Ttens + 1) %
              10);
            if (SW_wrapper_DWork->Ttens == 0) {
              /* Transition: '<S2>:71' */
              SW_wrapper_DWork->Tseconds = (uint8_T)((SW_wrapper_DWork->Tseconds
                + 1) % 60);
              if (SW_wrapper_DWork->Tseconds == 0) {
                /* Transition: '<S2>:87' */
                SW_wrapper_DWork->Tminutes = (uint8_T)
                  ((SW_wrapper_DWork->Tminutes + 1) % 60);
                if (SW_wrapper_DWork->Tminutes == 0) {
                  /* Transition: '<S2>:139' */
                  SW_wrapper_DWork->Thours = (uint8_T)((SW_wrapper_DWork->Thours
                    + 1) % 24);
                  SW_wrapper_DWork->is_time = SW_wrapper_IN_ticking;
                }
              }
            }
          }
        }
        break;

       default:
        SW_wrapper_DWork->is_time = SW_wrapper_IN_NO_ACTIVE_CHILD;
        break;
      }
    }

    if (SW_wrapper_DWork->is_active_control != 0U) {
      SW_wrapper_control(SW_wrapper_Y_buzzer, SW_wrapper_Y_hours,
                         SW_wrapper_Y_minutes, SW_wrapper_Y_seconds,
                         SW_wrapper_Y_mode, SW_wrapper_Y_tenths,
                         SW_wrapper_DWork);
    }
  }
}

/* Function for Chart: '<S1>/Stopwatch' */
static void SW_wrap_chartstep_c1_SW_wrapper(boolean_T *SW_wrapper_Y_buzzer,
  uint8_T *SW_wrapper_Y_hours, uint8_T *SW_wrapper_Y_minutes, uint8_T
  *SW_wrapper_Y_seconds, uint8_T *SW_wrapper_Y_mode, uint8_T
  *SW_wrapper_Y_tenths, D_Work_SW_wrapper *SW_wrapper_DWork)
{
  SW_wrapper_c1_SW_wrapper(SW_wrapper_Y_buzzer, SW_wrapper_Y_hours,
    SW_wrapper_Y_minutes, SW_wrapper_Y_seconds, SW_wrapper_Y_mode,
    SW_wrapper_Y_tenths, SW_wrapper_DWork);
}

/* Model step function */
void SW_wrapper_step(D_Work_SW_wrapper *SW_wrapper_DWork,
                     PrevZCSigStates_SW_wrapper *SW_wrapper_PrevZCSigState,
                     boolean_T SW_wrapper_U_tick, boolean_T SW_wrapper_U_button1,
                     boolean_T SW_wrapper_U_button2, boolean_T
                     SW_wrapper_U_button3, boolean_T SW_wrapper_U_button4,
                     boolean_T *SW_wrapper_Y_buzzer, uint8_T *SW_wrapper_Y_hours,
                     uint8_T *SW_wrapper_Y_minutes, uint8_T
                     *SW_wrapper_Y_seconds, uint8_T *SW_wrapper_Y_mode, uint8_T *
                     SW_wrapper_Y_tenths)
{
  boolean_T zcEvent[6];
  boolean_T tmp;
  int32_T i;
  int8_T rtb_inputevents_idx;
  int8_T rtb_inputevents_idx_0;
  int8_T rtb_inputevents_idx_1;
  int8_T rtb_inputevents_idx_2;
  int8_T rtb_inputevents_idx_3;

  /* Chart: '<S1>/Stopwatch' incorporates:
   *  TriggerPort: '<S2>/ input events '
   */
  /* Inport: '<Root>/tick' */
  zcEvent[0] = (((SW_wrapper_PrevZCSigState->Stopwatch_Trig_ZCE[0] == POS_ZCSIG)
                 != SW_wrapper_U_tick) &&
                (SW_wrapper_PrevZCSigState->Stopwatch_Trig_ZCE[0] !=
                 UNINITIALIZED_ZCSIG));

  /* Inport: '<Root>/button1' */
  zcEvent[1] = (((SW_wrapper_PrevZCSigState->Stopwatch_Trig_ZCE[1] == POS_ZCSIG)
                 != SW_wrapper_U_button1) &&
                (SW_wrapper_PrevZCSigState->Stopwatch_Trig_ZCE[1] !=
                 UNINITIALIZED_ZCSIG));

  /* Inport: '<Root>/button4' */
  zcEvent[2] = (((SW_wrapper_PrevZCSigState->Stopwatch_Trig_ZCE[2] == POS_ZCSIG)
                 != SW_wrapper_U_button4) &&
                (SW_wrapper_PrevZCSigState->Stopwatch_Trig_ZCE[2] !=
                 UNINITIALIZED_ZCSIG));

  /* Inport: '<Root>/button2' */
  zcEvent[3] = (((SW_wrapper_PrevZCSigState->Stopwatch_Trig_ZCE[3] == POS_ZCSIG)
                 != SW_wrapper_U_button2) &&
                (SW_wrapper_PrevZCSigState->Stopwatch_Trig_ZCE[3] !=
                 UNINITIALIZED_ZCSIG));

  /* Inport: '<Root>/button3' */
  zcEvent[4] = (((SW_wrapper_PrevZCSigState->Stopwatch_Trig_ZCE[4] == POS_ZCSIG)
                 != SW_wrapper_U_button3) &&
                (SW_wrapper_PrevZCSigState->Stopwatch_Trig_ZCE[4] !=
                 UNINITIALIZED_ZCSIG));

  /* Inport: '<Root>/button4' */
  zcEvent[5] = (((SW_wrapper_PrevZCSigState->Stopwatch_Trig_ZCE[5] == POS_ZCSIG)
                 != SW_wrapper_U_button4) &&
                (SW_wrapper_PrevZCSigState->Stopwatch_Trig_ZCE[5] !=
                 UNINITIALIZED_ZCSIG));
  tmp = FALSE;
  for (i = 0; i < 6; i++) {
    tmp = (tmp || zcEvent[i]);
  }

  if (tmp) {
    /* Inport: '<Root>/button1' */
    rtb_inputevents_idx = (int8_T)(int32_T)(zcEvent[1] ? SW_wrapper_U_button1 ?
      RISING_ZCEVENT : FALLING_ZCEVENT : NO_ZCEVENT);

    /* Inport: '<Root>/button4' */
    rtb_inputevents_idx_0 = (int8_T)(int32_T)(zcEvent[2] ? SW_wrapper_U_button4 ?
      RISING_ZCEVENT : FALLING_ZCEVENT : NO_ZCEVENT);

    /* Inport: '<Root>/button2' */
    rtb_inputevents_idx_1 = (int8_T)(int32_T)(zcEvent[3] ? SW_wrapper_U_button2 ?
      RISING_ZCEVENT : FALLING_ZCEVENT : NO_ZCEVENT);

    /* Inport: '<Root>/button3' */
    rtb_inputevents_idx_2 = (int8_T)(int32_T)(zcEvent[4] ? SW_wrapper_U_button3 ?
      RISING_ZCEVENT : FALLING_ZCEVENT : NO_ZCEVENT);

    /* Inport: '<Root>/button4' */
    rtb_inputevents_idx_3 = (int8_T)(int32_T)(zcEvent[5] ? SW_wrapper_U_button4 ?
      RISING_ZCEVENT : FALLING_ZCEVENT : NO_ZCEVENT);

    /* Inport: '<Root>/tick' */
    /* Gateway: SW_wrapper/Stopwatch */
    if ((int8_T)(int32_T)(zcEvent[0] ? SW_wrapper_U_tick ? RISING_ZCEVENT :
                          FALLING_ZCEVENT : NO_ZCEVENT) != 0) {
      /* Event: '<S2>:135' */
      SW_wrapper_DWork->sfEvent = SW_wrapper_event_tens;
      SW_wrap_chartstep_c1_SW_wrapper(SW_wrapper_Y_buzzer, SW_wrapper_Y_hours,
        SW_wrapper_Y_minutes, SW_wrapper_Y_seconds, SW_wrapper_Y_mode,
        SW_wrapper_Y_tenths, SW_wrapper_DWork);
    }

    if (rtb_inputevents_idx == 1) {
      /* Event: '<S2>:11' */
      SW_wrapper_DWork->sfEvent = SW_wrapper_event_mode;
      SW_wrap_chartstep_c1_SW_wrapper(SW_wrapper_Y_buzzer, SW_wrapper_Y_hours,
        SW_wrapper_Y_minutes, SW_wrapper_Y_seconds, SW_wrapper_Y_mode,
        SW_wrapper_Y_tenths, SW_wrapper_DWork);
    }

    if (rtb_inputevents_idx_0 == 1) {
      /* Event: '<S2>:26' */
      SW_wrapper_DWork->sfEvent = SW_wrapper_event_reset;
      SW_wrap_chartstep_c1_SW_wrapper(SW_wrapper_Y_buzzer, SW_wrapper_Y_hours,
        SW_wrapper_Y_minutes, SW_wrapper_Y_seconds, SW_wrapper_Y_mode,
        SW_wrapper_Y_tenths, SW_wrapper_DWork);
    }

    if (rtb_inputevents_idx_1 == 1) {
      /* Event: '<S2>:84' */
      SW_wrapper_DWork->sfEvent = SW_wrapper_event_buttonP;
      SW_wrap_chartstep_c1_SW_wrapper(SW_wrapper_Y_buzzer, SW_wrapper_Y_hours,
        SW_wrapper_Y_minutes, SW_wrapper_Y_seconds, SW_wrapper_Y_mode,
        SW_wrapper_Y_tenths, SW_wrapper_DWork);
    }

    if (rtb_inputevents_idx_2 == 1) {
      /* Event: '<S2>:108' */
      SW_wrapper_DWork->sfEvent = SW_wrapper_event_buttonM;
      SW_wrap_chartstep_c1_SW_wrapper(SW_wrapper_Y_buzzer, SW_wrapper_Y_hours,
        SW_wrapper_Y_minutes, SW_wrapper_Y_seconds, SW_wrapper_Y_mode,
        SW_wrapper_Y_tenths, SW_wrapper_DWork);
    }

    if (rtb_inputevents_idx_3 == 1) {
      /* Event: '<S2>:122' */
      SW_wrapper_DWork->sfEvent = SW_wrapper_event_submode;
      SW_wrap_chartstep_c1_SW_wrapper(SW_wrapper_Y_buzzer, SW_wrapper_Y_hours,
        SW_wrapper_Y_minutes, SW_wrapper_Y_seconds, SW_wrapper_Y_mode,
        SW_wrapper_Y_tenths, SW_wrapper_DWork);
    }
  }

  /* Inport: '<Root>/tick' */
  SW_wrapper_PrevZCSigState->Stopwatch_Trig_ZCE[0] = (uint8_T)(SW_wrapper_U_tick
    ? (int32_T)POS_ZCSIG : (int32_T)ZERO_ZCSIG);

  /* Inport: '<Root>/button1' */
  SW_wrapper_PrevZCSigState->Stopwatch_Trig_ZCE[1] = (uint8_T)
    (SW_wrapper_U_button1 ? (int32_T)POS_ZCSIG : (int32_T)ZERO_ZCSIG);

  /* Inport: '<Root>/button4' */
  SW_wrapper_PrevZCSigState->Stopwatch_Trig_ZCE[2] = (uint8_T)
    (SW_wrapper_U_button4 ? (int32_T)POS_ZCSIG : (int32_T)ZERO_ZCSIG);

  /* Inport: '<Root>/button2' */
  SW_wrapper_PrevZCSigState->Stopwatch_Trig_ZCE[3] = (uint8_T)
    (SW_wrapper_U_button2 ? (int32_T)POS_ZCSIG : (int32_T)ZERO_ZCSIG);

  /* Inport: '<Root>/button3' */
  SW_wrapper_PrevZCSigState->Stopwatch_Trig_ZCE[4] = (uint8_T)
    (SW_wrapper_U_button3 ? (int32_T)POS_ZCSIG : (int32_T)ZERO_ZCSIG);

  /* Inport: '<Root>/button4' */
  SW_wrapper_PrevZCSigState->Stopwatch_Trig_ZCE[5] = (uint8_T)
    (SW_wrapper_U_button4 ? (int32_T)POS_ZCSIG : (int32_T)ZERO_ZCSIG);
}

/* Model initialize function */
void SW_wrapper_initialize(D_Work_SW_wrapper *SW_wrapper_DWork,
  PrevZCSigStates_SW_wrapper *SW_wrapper_PrevZCSigState, boolean_T
  *SW_wrapper_U_tick, boolean_T *SW_wrapper_U_button1, boolean_T
  *SW_wrapper_U_button2, boolean_T *SW_wrapper_U_button3, boolean_T
  *SW_wrapper_U_button4, boolean_T *SW_wrapper_Y_buzzer, uint8_T
  *SW_wrapper_Y_hours, uint8_T *SW_wrapper_Y_minutes, uint8_T
  *SW_wrapper_Y_seconds, uint8_T *SW_wrapper_Y_mode, uint8_T
  *SW_wrapper_Y_tenths)
{
  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)SW_wrapper_DWork, 0,
                sizeof(D_Work_SW_wrapper));

  /* external inputs */
  (*SW_wrapper_U_tick) = FALSE;
  (*SW_wrapper_U_button1) = FALSE;
  (*SW_wrapper_U_button2) = FALSE;
  (*SW_wrapper_U_button3) = FALSE;
  (*SW_wrapper_U_button4) = FALSE;

  /* external outputs */
  (*SW_wrapper_Y_buzzer) = FALSE;
  (*SW_wrapper_Y_hours) = 0U;
  (*SW_wrapper_Y_minutes) = 0U;
  (*SW_wrapper_Y_seconds) = 0U;
  (*SW_wrapper_Y_mode) = 0U;
  (*SW_wrapper_Y_tenths) = 0U;

  {
    int_T idx;
    for (idx = 0; idx < 6; idx ++) {
      SW_wrapper_PrevZCSigState->Stopwatch_Trig_ZCE[idx] = UNINITIALIZED_ZCSIG;
    }
  }

  /* InitializeConditions for Chart: '<S1>/Stopwatch' */
  SW_wrapper_DWork->is_active_buzzer = 0U;
  SW_wrapper_DWork->is_buzzer = SW_wrapper_IN_NO_ACTIVE_CHILD;
  SW_wrapper_DWork->is_active_control = 0U;
  SW_wrapper_DWork->is_control = SW_wrapper_IN_NO_ACTIVE_CHILD;
  SW_wrapper_DWork->is_alarmset = SW_wrapper_IN_NO_ACTIVE_CHILD;
  SW_wrapper_DWork->is_stopwatch = SW_wrapper_IN_NO_ACTIVE_CHILD;
  SW_wrapper_DWork->is_timeset = SW_wrapper_IN_NO_ACTIVE_CHILD;
  SW_wrapper_DWork->is_active_time = 0U;
  SW_wrapper_DWork->is_time = SW_wrapper_IN_NO_ACTIVE_CHILD;
  SW_wrapper_DWork->is_active_c1_SW_wrapper = 0U;
  SW_wrapper_DWork->Thours = 0U;
  SW_wrapper_DWork->Tminutes = 0U;
  SW_wrapper_DWork->Tseconds = 0U;
  SW_wrapper_DWork->Ahours = 0U;
  SW_wrapper_DWork->Aminutes = 0U;
  SW_wrapper_DWork->Chours = 0U;
  SW_wrapper_DWork->Cminutes = 0U;
  SW_wrapper_DWork->Cseconds = 0U;
  SW_wrapper_DWork->Ttens = 0U;

  /* InitializeConditions for Outport: '<Root>/mode' incorporates:
   *  InitializeConditions for Chart: '<S1>/Stopwatch'
   */
  *SW_wrapper_Y_mode = 0U;

  /* InitializeConditions for Outport: '<Root>/hours' incorporates:
   *  InitializeConditions for Chart: '<S1>/Stopwatch'
   */
  *SW_wrapper_Y_hours = 0U;

  /* InitializeConditions for Outport: '<Root>/minutes' incorporates:
   *  InitializeConditions for Chart: '<S1>/Stopwatch'
   */
  *SW_wrapper_Y_minutes = 0U;

  /* InitializeConditions for Outport: '<Root>/seconds' incorporates:
   *  InitializeConditions for Chart: '<S1>/Stopwatch'
   */
  *SW_wrapper_Y_seconds = 0U;

  /* InitializeConditions for Outport: '<Root>/buzzer' incorporates:
   *  InitializeConditions for Chart: '<S1>/Stopwatch'
   */
  *SW_wrapper_Y_buzzer = FALSE;

  /* InitializeConditions for Outport: '<Root>/tenths' incorporates:
   *  InitializeConditions for Chart: '<S1>/Stopwatch'
   */
  *SW_wrapper_Y_tenths = 0U;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
