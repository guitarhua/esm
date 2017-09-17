#ifndef APPS_DCF77_BOARD_BLUEPILL_INC_BOARD_H_
#define APPS_DCF77_BOARD_BLUEPILL_INC_BOARD_H_

#include "stm32f1xx_hal.h"

#define DCF77_BIN_EVERY	(10UL)
#define DCF77_BIN_SIZE	(ESM_TICKS_PER_SEC/DCF77_BIN_EVERY)

#define BOARD_TICK do { \
		static uint8_t count; \
		static uint8_t bin; \
		GPIO_PinState s = HAL_GPIO_ReadPin(DCF77_Input_GPIO_Port, DCF77_Input_Pin); \
		HAL_GPIO_WritePin(DCF77_RawLED_GPIO_Port, DCF77_RawLED_Pin, s); \
		bin += s; \
		if(++count == DCF77_BIN_EVERY) \
		{ \
			sig.receiver = debug_esm; \
			sig.params.bin = bin; \
			esm_send_signal(&sig); \
			count = bin = 0; \
		} \
} while(0)

extern UART_HandleTypeDef huart2;

#endif /* APPS_DCF77_BOARD_BLUEPILL_INC_BOARD_H_ */