/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h" 
/*name rule 
 * 
 * function 
 * 	USARTInit(); 
 * 	ADCIint(); 
 * 
 * variable 
 *	flag isStart or isEnd 
 * 
 * define 
 *  SPEED 
 *  CLOCK() 
 * struct and enum 
 * 
 * typedef struct or enum 
 * { 
 * 	HOGE; 
 * 	uint32_t hoge; 
 * 	** 
 * 	} hoge_t; 
 * 
 */ 
 
/* Private function prototypes -----------------------------------------------*/ 
void SystemClock_Config(void); 
extern void MW_TIM1Hadler(void); 
extern void MW_TIM2Hadler(void); 
void MW_wait(uint32_t wait); 
 
int main(void){ 
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */ 
  HAL_Init(); 
  
  /* Configure the system clock */ 
  SystemClock_Config(); 
   
  /*Initialize printf*/ 
  flush(); 
   
   
  /* Initialize all configured peripherals */ 
  MW_USARTInit(USART2ID); 
  xdev_out(MW_USART2Transmit); 
   
  /*Configure GPIO pin : PC13 */ 
  MW_SetGPIOPin(GPIO_PIN_13); 
  MW_SetGPIOMode(GPIO_MODE_INPUT); 
  MW_SetGPIOPull(GPIO_NOPULL); 
  MW_GPIOInit(GPIOCID); 
 
  /*Configure GPIO pin : PA5 */ 
  MW_SetGPIOPin(GPIO_PIN_5); 
  MW_SetGPIOMode(GPIO_MODE_OUTPUT_PP); 
  MW_SetGPIOSpeed(GPIO_SPEED_FREQ_LOW); 
  MW_GPIOInit(GPIOAID); 
  /*Configure GPIO pin : PC4 */ 
  MW_SetGPIOPin(GPIO_PIN_4); 
  MW_SetGPIOMode(GPIO_MODE_IT_RISING); 
  MW_SetGPIOPull(GPIO_NOPULL); 
  MW_GPIOInit(GPIOCID); 
 
  /*Configure GPIO pin Output Level */ 
  MW_GPIOWrite(GPIOAID,GPIO_PIN_5,0); 
 
  while (1) {
  } 
} 
 
void MW_TIM1Hadler(void){ 
} 
void MW_TIM2Hadler(void){ 
} 
 
void MW_wait(uint32_t wait){ 
  uint32_t i,i2; 
  for(i2=0;i2<wait;i2++){ 
      for(i=0;i<1000;i++){ 
	  asm("nop"); 
	  asm("nop"); 
	  asm("nop"); 
	  asm("nop"); 
	  asm("nop"); 
	  asm("nop"); 
	  asm("nop"); 
	  asm("nop"); 
	  asm("nop"); 
	  asm("nop"); 
	  asm("nop"); 
	} 
    } 
} 
/** System Clock Configuration 
 */ 
void SystemClock_Config(void){ 
 
  RCC_OscInitTypeDef RCC_OscInitStruct; 
  RCC_ClkInitTypeDef RCC_ClkInitStruct; 
  RCC_PeriphCLKInitTypeDef PeriphClkInit; 
 
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE; 
  RCC_OscInitStruct.HSEState = RCC_HSE_ON; 
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1; 
  RCC_OscInitStruct.LSIState = RCC_LSI_ON; 
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON; 
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE; 
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9; 
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK){ 
      //    Error_Handler(); 
    } 
 
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK 
    |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2; 
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK; 
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1; 
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2; 
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1; 
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK){ 
      //    Error_Handler(); 
    } 
 
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC; 
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6; 
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK){ 
      //    Error_Handler(); 
    } 
 
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000); 
 
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK); 
 
  /* SysTick_IRQn interrupt configuration */ 
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0); 
} 
 
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
