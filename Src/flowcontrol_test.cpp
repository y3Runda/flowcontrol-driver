#include "../Inc/flowcontrol_test.h"

#include <stdio.h>


EdgeCounterTest::EdgeCounterTest(TIM_HandleTypeDef* pwm_timer) {
	this->pwm_timer = pwm_timer;
}


uint32_t EdgeCounterTest::setupPWM(uint32_t frequency, uint8_t duty_cycle, uint32_t period) {
    // Calculate the prescaler and period based on timer clock and desired frequency
    uint32_t timer_clock = HAL_RCC_GetPCLK1Freq();
    uint32_t prescaler = (timer_clock / (frequency * 1000)) - 1;
    period = period - 1;

    pwm_timer->Init.Prescaler = prescaler;
    pwm_timer->Init.CounterMode = TIM_COUNTERMODE_UP;
    pwm_timer->Init.Period = period;
    pwm_timer->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    pwm_timer->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    HAL_TIM_PWM_Init(pwm_timer);

    TIM_OC_InitTypeDef sConfigOC = {0};
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = (period * duty_cycle) / 100;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

    HAL_TIM_PWM_ConfigChannel(pwm_timer, &sConfigOC, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(pwm_timer, TIM_CHANNEL_1);

    return timer_clock / ((prescaler + 1) * (period + 1));
}


void EdgeCounterTest::testSecond(TIM_HandleTypeDef* htim_counter, uint32_t frequency, uint8_t duty_cycle, uint32_t period) {
	EdgeCounter edgeCounter(htim_counter, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
	uint32_t actual_frequency = setupPWM(frequency, duty_cycle, period);
	edgeCounter.reset();
	HAL_Delay(1000);
	uint16_t edge_count = edgeCounter.getCount();
	printf("TEST: frequency = %ld, duty cycle = %d, period = %ld\n", frequency, duty_cycle, period);
	printf("      actual_frequency = %ld\n", actual_frequency);
	printf("      edge_count = %d\n", edge_count);
	if (actual_frequency == edge_count) {
		printf("TEST PASSED\n\n");
	} else {
		printf("TEST FAILED\n\n");
	}
}

void edgeCounterTest(TIM_HandleTypeDef *htim_pwm, TIM_HandleTypeDef *htim_counter) {
	EdgeCounterTest test(htim_pwm);
	test.testSecond(htim_counter, 500, 30, 1000);
	test.testSecond(htim_counter, 1500, 50, 1000);
	test.testSecond(htim_counter, 1500, 50, 2000);
}
