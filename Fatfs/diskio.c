/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types ����ȡ�������ͣ�*/
#include "diskio.h"		/* Declarations of disk functions �����̺���������*/
#include "sd_sdio.h"
#include "flash.h"
#include "malloc.h"	
#include "usart.h"

/* Definitions of physical drive number for each drive */
/* ÿ����������������������Ŷ��� */
#define DEV_SD_CARD		   0	 //SD��,���Ϊ0
#define DEV_EX_FLASH		 1	 //�ⲿflash,���Ϊ1

//����W25Q128
//ǰ12M�ֽڸ�fatfs��,12M�ֽں�,���ڴ���ֿ�,�ֿ�ռ��3.09M.
u16	    FLASH_SECTOR_COUNT=2048*12;	//W25Q1218,ǰ12M�ֽڸ�FATFSռ��
#define FLASH_SECTOR_SIZE 	512			//���С(KB)
#define FLASH_BLOCK_SIZE   	16     	//ÿ��BLOCK��16������



/*-----------------------------------------------------------------------*/
/* Get Drive Status ��ȡ������״̬                                       */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive ������ʶ���������������������ţ� */
)
{
	return RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive ��ʼ��������                                       */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	uint8_t result;

	switch (pdrv) {
	case DEV_SD_CARD :   //SD��
		result = SD_Init();//SD����ʼ��
		break;
	
	case DEV_EX_FLASH :		//�ⲿFLASH
		EN25QXX_Init();     //�ⲿFLASH��ʼ��
		FLASH_SECTOR_COUNT=2048*12;
		result=0;
		break;
	
	default:
		result=1;
		break;
	}
	if(result==0)
		return  STA_NOINIT;
	else
		return 0; //��ʼ���ɹ� 
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s) ��ȡ����																							 */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* ����ʶ���������������������� */
	BYTE *buff,		/* ���ڴ洢��ȡ���ݵ����ݻ����� */
	LBA_t sector,	/* Start sector in LBA ��������ַ�� */
	UINT count		/* ��Ҫ��ȡ�������� */
)
{
	uint8_t result=0; 
  if (!count)
		return RES_PARERR;//count���ܵ���0�����򷵻ز�������		 	 
	switch(pdrv)
	{
		case DEV_SD_CARD://SD��
			result=SD_ReadDisk(buff,sector,count);	 
			while(result)//������
			{
				SD_Init();	//���³�ʼ��SD��
				result=SD_ReadDisk(buff,sector,count);	
				printf("Read Sector Error:%d\r\n",result);
			}
			break;
		case DEV_EX_FLASH://�ⲿflash
			for(;count>0;count--)
			{
				EN25QXX_Read(buff,sector*FLASH_SECTOR_SIZE,FLASH_SECTOR_SIZE);
				sector++;
				buff+=FLASH_SECTOR_SIZE;
			}
			result=0;
			break;
		default:
			result=1; 
	}
   //������ֵ����SPI_SD_driver.c�ķ���ֵת��ff.c�ķ���ֵ
    if(result==0x00)return RES_OK;	 
    else return RES_ERROR;	 
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s) д������																							 */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	uint8_t result;

	if (!count)return RES_PARERR;//count���ܵ���0�����򷵻ز�������	
	
	switch (pdrv) {
	case DEV_SD_CARD :
		result=SD_WriteDisk((u8*)buff,sector,count);
		if(result!=0)
		printf("sd wr error:%d\r\n",result);
		break;
		
	case DEV_EX_FLASH :
		for(;count>0;count--)
		{										    
			EN25QXX_Write((u8*)buff,sector*FLASH_SECTOR_SIZE,FLASH_SECTOR_SIZE);
			sector++;
			buff+=FLASH_SECTOR_SIZE;
		}
		result=0;
		break;
		
	default:
		result=1;
		break;
		
	}
	//������ֵ����SPI_SD_driver.c�ķ���ֵת��ff.c�ķ���ֵ
	if(result == 0x00)
		return RES_OK;	 
	else 
		return RES_ERROR;	
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions   ����������Ļ��                            */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code (���ƴ���)*/
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT result=RES_OK;

	switch (pdrv) {
		case DEV_SD_CARD :
		switch(cmd)
		{
			case CTRL_SYNC:
				result = RES_OK; 
				break;	 
			case GET_SECTOR_SIZE:
				*(DWORD*)buff = 512; 
				result = RES_OK;
				break;	 
			case GET_BLOCK_SIZE:
				*(WORD*)buff = SDCardInfo.CardBlockSize;
				result = RES_OK;
				break;	 
			case GET_SECTOR_COUNT:
				*(DWORD*)buff = SDCardInfo.CardCapacity/512;
				result = RES_OK;
				break;
			default:
				result = RES_PARERR;
				break;
		}
		break;
		
		case DEV_EX_FLASH :
		switch(cmd)
		{
			case CTRL_SYNC:
				result = RES_OK; 
				break;	 
			case GET_SECTOR_SIZE:
				*(WORD*)buff = FLASH_SECTOR_SIZE;
				result = RES_OK;
				break;	 
			case GET_BLOCK_SIZE:
				*(WORD*)buff = FLASH_BLOCK_SIZE;
				result = RES_OK;
				break;	 
			case GET_SECTOR_COUNT:
				*(DWORD*)buff = FLASH_SECTOR_COUNT;
				result = RES_OK;
				break;
			default:
				result = RES_PARERR;
				break;
		}
		break;
	default:
		result = RES_ERROR;
		break;
	}
	
	return result;
}

