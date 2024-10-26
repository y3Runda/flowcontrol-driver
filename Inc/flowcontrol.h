#ifndef SRC_FLOWCONTROL_H_
#define SRC_FLOWCONTROL_H_

#include "stm32f4xx_hal.h"
#include "main.h"
#include <cstdio>

#define DEBUG_ENABLED

class EdgeCounter {
private:
	TIM_HandleTypeDef* htim;    // Pointer to the timer instance
	uint32_t channel;			// Timer channel (e.g.: TIM_CHANNEL_1)
	uint32_t polarity;			// Edge polarity (e.g.: TIM_INPUTCHANNELPOLARITY_RISING)

	uint16_t edge_count;

	static EdgeCounter* currentInstance;

public:
	EdgeCounter(TIM_HandleTypeDef *htim, uint32_t channel, uint32_t polarity);

	void init();

	void start();

	void reset();

	uint16_t getCount();

	static void setCurrentInstance(EdgeCounter* instance);

	static void captureCallback(TIM_HandleTypeDef* htim);
};

#endif /* SRC_FLOWCONTROL_H_ */
