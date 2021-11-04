#ifndef PWM_H
#define PWM_H

#include <stdint.h>
#include <stdbool.h>

extern uint8_t PHASE_A_INDEX;
extern uint8_t PHASE_B_INDEX;
extern uint8_t PHASE_C_INDEX;

/**
 * Initalizes the PWM timer interfaces
 */
void pwm_init();

/**
 * Inverts the phases of the BLDC motor.
 */
void invert_phases(bool inverted);

/**
 * Sets the duty cycle of the PWM signal for Phase A
 * @param dutyValue the duty cycle value
 * @param enableOutput true to enable the output, false to disable the half bridge
 */
void setPhaseADuty(uint32_t dutyValue, bool enableOutput);

/**
 * Sets the duty cycle of the PWM signal for Phase A
 * @param dutyValue the duty cycle value
 * @param enableOutput true to enable the output, false to disable the half bridge
 */
void setPhaseBDuty(uint32_t dutyValue, bool enableOutput);

/**
 * Sets the duty cycle of the PWM signal for Phase A
 * @param dutyValue the duty cycle value
 * @param enableOutput true to enable the output, false to disable the half bridge
 */
void setPhaseCDuty(uint32_t dutyValue, bool enableOutput);

#endif
