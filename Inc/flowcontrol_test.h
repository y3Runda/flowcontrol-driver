#ifndef FLOWCONTROL_INC_FLOWCONTROL_TEST_H_
#define FLOWCONTROL_INC_FLOWCONTROL_TEST_H_

#include "stm32f4xx_hal.h"
#include "main.h"
#include "flowcontrol.h"
#include <cstdio>

class EdgeCounterTest {
public:
	EdgeCounterTest(TIM_HandleTypeDef* pwm_timer);

	/**
	 * @brief Configures the specified timer to generate a PWM signal
	 *
	 * @param frequency The desired frequency of the PWM signal in Hz
	 * @param duty_cycle The duty cycle of the PWM signal as a percentage (0-100)
	 * @param period
	 */
    uint32_t setupPWM(uint32_t frequency, uint8_t duty_cycle, uint32_t period);

    /**
	 * @param htim_counter Address of the corresponding htim for the input capture (EdgeCounter itself)
	 * @param frequency The desired frequency of the PWM signal in Hz
	 * @param duty_cycle The duty cycle of the PWM signal as a percentage (0-100)
	 * @param period
	 */
    void testSecond(TIM_HandleTypeDef* htim_counter, uint32_t frequency, uint8_t duty_cycle, uint32_t period);

private:
    TIM_HandleTypeDef* pwm_timer;
};

void edgeCounterTest(TIM_HandleTypeDef *htim_pwm, TIM_HandleTypeDef *htim_counter);

#endif /* FLOWCONTROL_INC_FLOWCONTROL_TEST_H_ */
