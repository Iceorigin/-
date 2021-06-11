#ifndef _spi_H
#define _spi_H

#include "system.h"

/* �û����� */
#define SPI_SC      					GPIO_Pin_12
#define SPI_SCK  							GPIO_Pin_13
#define SPI_MISO 							GPIO_Pin_14
#define SPI_MOSI  			  		GPIO_Pin_15
#define SPIx									SPI2
#define SPI_GPIOx			        GPIOB
#define SPI_RCC_GPIO_SCK			RCC_APB2Periph_GPIOB				
#define SPI_RCC_SPIx_SCK			RCC_APB1Periph_SPI2	



void SPIx_Init(void);						 //��ʼ��SPIx��
void SPIx_SetSpeed(u8 SpeedSet); //����SPIx�ٶ�   
u8 SPIx_ReadWriteByte(u8 TxData);//SPIx���߶�/дһ���ֽ�

#endif
