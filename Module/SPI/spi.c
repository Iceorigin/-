#include "spi.h"


/*	SPI�ڳ�ʼ��
 *	�������Ƕ�SPIx�ĳ�ʼ��
 */
void SPIx_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;
	
	/* SPI��IO�ں�SPI�����ʱ�� */
  RCC_APB2PeriphClockCmd(SPI_RCC_GPIO_SCK, ENABLE );
  RCC_APB1PeriphClockCmd(SPI_RCC_SPIx_SCK, ENABLE);
	
	/* SPI��IO������ */
	GPIO_InitStructure.GPIO_Pin = SPI_SCK | SPI_MISO | SPI_MOSI;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //PB13/14/15����������� 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI_GPIOx, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = SPI_SC;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI_GPIOx, &GPIO_InitStructure);
	GPIO_SetBits(SPI_GPIOx,GPIO_Pin_12);

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//����SPI����ģʽ:����Ϊ��SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
	SPI_Init(SPIx, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
	
	SPI_Cmd(SPIx, ENABLE); //ʹ��SPI����
	
	SPIx_ReadWriteByte(0xff);//��������	
}

/*	SPIx�ٶ����ú���
 *	SPI�ٶ�=fAPB1/��Ƶϵ��
 *	@ref SPI_BaudRate_Prescaler:SPI_BaudRatePrescaler_2~SPI_BaudRatePrescaler_256  
 *	fAPB1ʱ��һ��Ϊ36Mhz��
 */
void SPIx_SetSpeed(u8 SPI_BaudRatePrescaler)
{
	SPIx->CR1&=0XFFC7;//λ3-5���㣬�������ò�����
	SPIx->CR1|=SPI_BaudRatePrescaler;	//����SPI�ٶ� 
	SPI_Cmd(SPIx,ENABLE); //ʹ��SPI2
} 

/*	SPIx ��дһ���ֽ�
 *	TxData:Ҫд����ֽ�
 *	����ֵ:��ȡ�����ֽ�
 */
u8 SPIx_ReadWriteByte(u8 TxData)
{		 			 
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);//�ȴ���������  
	SPI_I2S_SendData(SPIx, TxData); //ͨ������SPIx����һ��byte  ����	
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET); //�ȴ�������һ��byte  
	return SPI_I2S_ReceiveData(SPIx); //����ͨ��SPIx������յ�����			    
}

