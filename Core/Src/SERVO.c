/*
 * SERVO.c
 *
 *  Created on: Sep 13, 2022
 *      Author: yunus
 */


#include "stm32f4xx_hal.h"
#include "SERVO.h"

#define SERVO_OFFSET 90
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim2;

uint16_t PotValue; //0-4096 ANALOG VALUE
uint16_t ANGLE;
float Mapping = 4096 / 360;


	void ADC_SERVO_CONTROL(){
		HAL_ADC_Start(&hadc1);

		  if (HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK){
			  PotValue = HAL_ADC_GetValue(&hadc1);
		  }

		  HAL_ADC_Stop(&hadc1);

		  ANGLE = (PotValue/Mapping)+SERVO_OFFSET;
		  htim2.Instance->CCR1 = ANGLE;
		  HAL_Delay(5);
	}
