#ifndef PWM_H
#define PWM_H

#include <stdint.h>
#include <stdbool.h>

/**
 * Initalizes the PWM timer interfaces
 */
void pwm_init();

/**
 * Sets the duty cycle of the PWM signal for Phase A
 * @param dutyValue the duty cycle value, 0-2^16
 * @param enableOutput true to enable the output, false to disable the half bridge
 */
void setPhaseADuty(uint32_t dutyValue, bool enableOutput);

/**
 * Sets the duty cycle of the PWM signal for Phase A
 * @param dutyValue the duty cycle value, 0-2^16
 * @param enableOutput true to enable the output, false to disable the half bridge
 */
void setPhaseBDuty(uint32_t dutyValue, bool enableOutput);

/**
 * Sets the duty cycle of the PWM signal for Phase A
 * @param dutyValue the duty cycle value, 0-2^16
 * @param enableOutput true to enable the output, false to disable the half bridge
 */
void setPhaseCDuty(uint32_t dutyValue, bool enableOutput);

#endif
