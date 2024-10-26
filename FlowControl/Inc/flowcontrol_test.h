#ifndef FLOWCONTROL_INC_FLOWCONTROL_TEST_H_
#define FLOWCONTROL_INC_FLOWCONTROL_TEST_H_

#include "stm32f4xx_hal.h"
#include "flowcontrol.h"

class EdgeCounterTest {
public:
	/**
	 * @param pwm_timer Address of the corresponding htim
	 * @param frequency The desired frequency of the PWM signal in Hz
	 * @param duty_cycle The duty cycle of the PWM signal as a percentage (0-100)
	 */
	EdgeCounterTest(TIM_HandleTypeDef* pwm_timer, uint32_t frequency, uint8_t duty_cycle);

	/**
	 * @brief Configures the specified timer to generate a PWM signal
	 *
	 * @param frequency The desired frequency of the PWM signal in Hz
	 * @param duty_cycle The duty cycle of the PWM signal as a percentage (0-100)
	 */
    void setupPWM(uint32_t frequency, uint8_t duty_cycle);

private:
    TIM_HandleTypeDef* pwm_timer;
};

#endif /* FLOWCONTROL_INC_FLOWCONTROL_TEST_H_ */
