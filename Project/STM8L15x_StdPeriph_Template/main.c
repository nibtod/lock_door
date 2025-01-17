/**
  ******************************************************************************
  * @file    USART/USART_HyperTerminal_Interrupts/main.c
  * @author  MCD Application Team
  * @version V1.5.2
  * @date    30-September-2014
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "stm8l15x.h"
#include "fingerVeinProtocol.h"
#include "tim4.h"
#include "usart.h"
#include "stateManager.h"
#include "button.h"
#include "extern_exit_it.h"
#include <string.h>
#include "fingerVeinDemo.h"
#include "motor.h"

#define LED_GPIO_PORT  GPIOG
#define LED_GPIO_PINS  GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7


/** @addtogroup STM8L15x_StdPeriph_Examples
  * @{
  */

/**
  * @addtogroup USART_HyperTerminal_Interrupts
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

void Delay (uint32_t nCount);
void delay_ms(uint32_t nCount);
void send(uint8_t *data);
void printfAct(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */


void main(void)
{
    GPIO_Init(LED_GPIO_PORT, LED_GPIO_PINS, GPIO_Mode_Out_PP_Low_Fast);
  /*High speed internal clock prescaler: 1*/
   CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);      
   //testDemo();
    
    buttonInit();
    tim4config();
    USART1_Config();
    initMotor();
    printf("hello\n");
   while (1)
  {
    //stateMachine();
    motorProcess();

  }
}

/**
  * @brief  Configure USART peripheral  
  * @param  None
  * @retval None
  */

/**
  * @brief  Delay.
  * @param  nCount
  * @retval None
  */
void Delay(uint32_t nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}
void delay_ms(uint32_t nCount)
{
  for(int i=nCount;i>0;i--)
    for(int y=2000;y>0;y--);

}

void send(uint8_t *data)
{

    while(*data)
    {
        USART_SendData8(USART2,*data++);
        while(!USART_GetFlagStatus(USART2,USART_FLAG_TXE));
      
    }

}

int fputc(int ch,FILE *f)
{
        while(!USART_GetFlagStatus(USART1,USART_FLAG_TXE));
        USART_SendData8(USART1,ch);
        return(ch);

}



#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif
/**
  * @}
  */

/**
  * @}
  */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
