#include "../Inc/flowcontrol.h"


EdgeCounter* EdgeCounter::currentInstance = nullptr;


EdgeCounter::EdgeCounter(TIM_HandleTypeDef *htim, uint32_t channel, uint32_t polarity) {
	this->htim = htim;
	this->channel = channel;
	this->polarity = polarity;

	init();
	start();
}


void EdgeCounter::init() {
	TIM_IC_InitTypeDef sConfigIC = {0};

	sConfigIC.ICPolarity = this->polarity;
	sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
	sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
	sConfigIC.ICFilter = 0;

	HAL_StatusTypeDef status_ic_init = HAL_TIM_IC_Init(htim);
	HAL_StatusTypeDef status_config_channel = HAL_TIM_IC_ConfigChannel(htim, &sConfigIC, channel);
	HAL_StatusTypeDef status_start = HAL_TIM_Base_Start(this->htim);

#ifdef DEBUG_ENABLED
	if (status_ic_init != 0) {
		printf("HAL_TIM_IC_Init is not OK. Status = %d\n", status_ic_init);
	}
	if (status_config_channel != 0) {
		printf("HAL_TIM_IC_ConfigChannel is not OK. Status = %d", status_config_channel);
	}
	if (status_start != 0) {
		printf("HAL_TIM_Base_Start is not OK. Status = %d", status_start);
	}
#endif
}


void EdgeCounter::start() {
	EdgeCounter::setCurrentInstance(this);

	HAL_StatusTypeDef status = HAL_TIM_IC_Start_IT(this->htim, this->channel);

#ifdef DEBUG_ENABLED
	if (status != 0) {
		printf("HAL_TIM_IC_Start_IT status = %d\n", status);
	}
#endif
}


void EdgeCounter::reset() {
	this->edge_count = 0;
}


uint16_t EdgeCounter::getCount() {
	return this->edge_count;
}


void EdgeCounter::setCurrentInstance(EdgeCounter *instance) {
	currentInstance = instance;
}


void EdgeCounter::captureCallback(TIM_HandleTypeDef *htim) {
	if (currentInstance && currentInstance->htim->Instance == htim->Instance) {
		currentInstance->edge_count++;
	}
}


extern "C" void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
	EdgeCounter::captureCallback(htim);
}
