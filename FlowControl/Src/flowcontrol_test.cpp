#include "../Inc/flowcontrol_test.h"

#include <stdio.h>


EdgeCounterTest::EdgeCounterTest(TIM_HandleTypeDef* pwm_timer, uint32_t frequency, uint8_t duty_cycle) {
	this->pwm_timer = pwm_timer;

	setupPWM(frequency, duty_cycle);
}


void EdgeCounterTest::setupPWM(uint32_t frequency, uint8_t duty_cycle) {
    // Calculate the prescaler and period based on timer clock and desired frequency
    uint32_t timer_clock = HAL_RCC_GetPCLK1Freq();
    uint32_t prescaler = (timer_clock / (frequency * 1000)) - 1;
    uint32_t period = 1000 - 1;

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
}
