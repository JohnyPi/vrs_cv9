/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include <lps25hb.h>
#include <hts221.h>
#include "main.h"
#include "i2c.h"
#include "gpio.h"
#include "tim.h"
#include "display.h"
#include "math.h"

void SystemClock_Config(void);


uint8_t button=0;

int main(void) {

	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	SystemClock_Config();

	MX_GPIO_Init();

	setSegments();
	setDigits();

	LL_mDelay(2000);

	resetDigits();
	resetSegments();

	MX_TIM3_Init();

	MX_I2C1_Init();

	lps25hb_init();
	hts221_init();

	char cislo[20];
	float temp = 0;
	float press =0;
	float humi =0;
	float altitude=0;

	while (1) {
		switch (button) {
			case 0:
				//temp = lps25hb_get_temp();
				temp = hts221_get_temperature();
				sprintf(cislo, "TEMP_%.1f", temp);
				break;
			case 1:
				press = lps25hb_get_pressure();
				sprintf(cislo, "BAR_%.2f", press);
				break;
			case 2:
				press = lps25hb_get_pressure();
				altitude =(44330 * ( 1 - (   pow(((press*100)/ 101325),(1 / 5.255)))));
				sprintf(cislo, "ALT_%d", (uint16_t)altitude);
				break;
			case 3:
				humi = hts221_get_humidity();
				sprintf(cislo, "HUM_%d", (uint8_t)humi);
				break;
		}
		display_show(cislo);

	}




}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);

	if (LL_FLASH_GetLatency() != LL_FLASH_LATENCY_0) {
		Error_Handler();
	}
	LL_RCC_HSI_Enable();

	/* Wait till HSI is ready */
	while (LL_RCC_HSI_IsReady() != 1) {

	}
	LL_RCC_HSI_SetCalibTrimming(16);
	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
	LL_RCC_SetAPB2Prescaler(LL_RCC_APB1_DIV_1);
	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

	/* Wait till System clock is ready */
	while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI) {

	}
	LL_Init1msTick(8000000);
	LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
	LL_SYSTICK_EnableIT();
	LL_SetSystemCoreClock(8000000);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	  __disable_irq();
	  while (1)
	  {
	  }
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
