#ifndef _sd_sdio_H
#define _sd_sdio_H


#include "system.h"


/*�û�������			  
 *	SDIOʱ�Ӽ��㹫ʽ:SDIO_CKʱ��=SDIOCLK/[clkdiv+2];����,SDIOCLKһ��Ϊ72Mhz
 *	ʹ��DMAģʽ��ʱ��,�������ʿ��Ե�24Mhz,���������Ŀ����Ǹ��ٿ�,����Ҳ�����
 *	������뽵��ʱ��,ʹ�ò�ѯģʽ�Ļ�,�Ƽ�SDIO_TRANSFER_CLK_DIV����Ϊ3���߸���
*/
#define SDIO_INIT_CLK_DIV        0xB2 		//SDIO��ʼ��Ƶ�ʣ����400Kh  
#define SDIO_TRANSFER_CLK_DIV    0x04		  //SDIO����Ƶ��,��ֵ̫С���ܻᵼ�¶�д�ļ����� 
 
//SDIO����ģʽ����,ͨ��SD_SetDeviceMode��������.
#define SD_POLLING_MODE         	0     	//��ѯģʽ,��ģʽ��,�����д������,��������SDIO_TRANSFER_CLK_DIV������.
#define SD_DMA_MODE    	        	1	      //DMAģʽ,��ģʽ��,�����д������,��������SDIO_TRANSFER_CLK_DIV������.  
#define SD_MODE                   SD_POLLING_MODE    //����ģʽ


//����ר�� 0�ر� 1���� 
#define  debug 1


//GPIO�˿�����

#define SD_Pin_D0                GPIO_Pin_8
#define SD_Pin_D1								 GPIO_Pin_9		
#define SD_Pin_D2                GPIO_Pin_10
#define SD_Pin_D3                GPIO_Pin_11
#define SD_Pin_SCK               GPIO_Pin_12
#define SD_Pin_CMD               GPIO_Pin_2

/*=====================================================================================================================*/

/*-=SDIO ���ִ���ö�ٶ���=-*/
typedef enum
{	 
	//��������� 
	SD_CMD_CRC_FAIL                    = (1),  // �յ�������Ӧ���� CRC У��ʧ�ܣ� 
	SD_DATA_CRC_FAIL                   = (2),  // ���ݿ鷢��/���գ�CRC У��ʧ�ܣ� 
	SD_CMD_RSP_TIMEOUT                 = (3),  // ������Ӧ��ʱ 
	SD_DATA_TIMEOUT                    = (4),  // ���ݳ�ʱ 
	SD_TX_UNDERRUN                     = (5),  // ���� FIFO Ƿ�� 
	SD_RX_OVERRUN                      = (6),  // ���� FIFO ��� 
	SD_START_BIT_ERR                   = (7),  // �ڿ�����ģʽ��δ�����������ź��ϼ�⵽��ʼλ 
	SD_CMD_OUT_OF_RANGE                = (8),  // CMD �Ĳ���������Χ��
	SD_ADDR_MISALIGNED                 = (9),  // ��ַ��λ��
	SD_BLOCK_LEN_ERR                   = (10), // ����������Ŀ鳤�Ȼ�����ֽ�����鳤�Ȳ�ƥ�� 
	SD_ERASE_SEQ_ERR                   = (11), // ���������˳����ִ���
	SD_BAD_ERASE_PARAM                 = (12), // ���������Чѡ��
	SD_WRITE_PROT_VIOLATION            = (13), // ���Զ�д��������б�� 
	SD_LOCK_UNLOCK_FAILED              = (14), // �ڽ��������м�⵽���л�������󣬻��߳��Է��������Ŀ� 
	SD_COM_CRC_FAILED                  = (15), // ��һ������� CRC ���ʧ�� 
	SD_ILLEGAL_CMD                     = (16), // ����Կ�״̬���Ϸ� 
	SD_CARD_ECC_FAILED                 = (17), // ��Ӧ�ÿ��ڲ� ECC ��δ�ܸ������� 
	SD_CC_ERROR                        = (18), // �ڲ������������� 
	SD_GENERAL_UNKNOWN_ERROR           = (19), // һ���δ֪���� 
	SD_STREAM_READ_UNDERRUN            = (20), // �ÿ��޷�������ȡ������֧�����ݴ��䡣 
	SD_STREAM_WRITE_OVERRUN            = (21), // �ÿ��޷�֧����ģʽ�µ����ݱ�� 
	SD_CID_CSD_OVERWRITE               = (22), // CID/CSD ���Ǵ��� 
	SD_WP_ERASE_SKIP                   = (23), // �����ֵ�ַ�ռ䱻���� 
	SD_CARD_ECC_DISABLED               = (24), // �������ڲ�ʹ���ڲ� ECC �������ִ�� 
	SD_ERASE_RESET                     = (25), // ���ڽ��յ������������е��������������ִ��ǰ����� 
	SD_AKE_SEQ_ERROR                   = (26), // ��֤˳����� 
	SD_INVALID_VOLTRANGE               = (27), // SD����Ч��ѹ
	SD_ADDR_OUT_OF_RANGE               = (28), 
	SD_SWITCH_ERROR                    = (29), 
	SD_SDIO_DISABLED                   = (30),
	SD_SDIO_FUNCTION_BUSY              = (31),
	SD_SDIO_FUNCTION_FAILED            = (32),
	SD_SDIO_UNKNOWN_FUNCTION           = (33),
	//��׼������
	SD_INTERNAL_ERROR, 
	SD_NOT_CONFIGURED,
	SD_REQUEST_PENDING, 
	SD_REQUEST_NOT_APPLICABLE,                //SD ��������
	SD_INVALID_PARAMETER,                     //��Ч�Ĳ���
	SD_UNSUPPORTED_FEATURE,  
	SD_UNSUPPORTED_HW,  
	SD_ERROR,  
	SD_OK = 0  
} SD_Error;		  


/*-=SD��CSD�Ĵ�������=-*/		  
typedef struct
{
	u8  CSDStruct;            // CSD�ṹ 
	u8  SysSpecVersion;       // ϵͳ���汾 
	u8  Reserved1;            // Reserved 
	u8  TAAC;                 // ���ݶ�����ʱ�� 
	u8  NSAC;                 // ʱ������(NSAC*100)�е����ݶ�����ʱ�䣩 
	u8  MaxBusClkFrec;        // ������ݴ�������
	u16 CardComdClasses;      // �������� 
	u8  RdBlockLen;           // ����ȡ���ݳ���
	u8  PartBlockRead;        // ����ֿ�� 
	u8  WrBlockMisalign;      // д�鲻���� 
	u8  RdBlockMisalign;      // ���鲻���� 
	u8  DSRImpl;              // ִ�е� DSR
	u8  Reserved2;            // Reserved 
	u32 DeviceSize;           // �豸�ߴ�
	
  //1.0/2.0/MMC������ 	
	u8  MaxRdCurrentVDDMin;   // ����޶ȡ� ��ȡ����@ VDD ��Сֵ 
	u8  MaxRdCurrentVDDMax;   // ����޶ȡ� ��ȡ����@ VDD ���ֵ 
	u8  MaxWrCurrentVDDMin;   // ����޶ȡ� д�����@ VDD ��Сֵ 
	u8  MaxWrCurrentVDDMax;   // ����޶ȡ� д�����@ VDD ���ֵ 
	u8  DeviceSizeMul;        // �豸�ߴ���� 
	
	u8  EraseGrSize;          // �������С 
	u8  EraseGrMul;           // �������С���� 
	u8  WrProtectGrSize;      // д�������С 
	u8  WrProtectGrEnable;    // д������ʹ�� 
	u8  ManDeflECC;           // ������Ĭ�� ECC 
	u8  WrSpeedFact;          // д���ٶ�ϵ�� 
	u8  MaxWrBlockLen;        // ����޶�д�����ݿ鳤��/����鲿��д
	u8  WriteBlockPaPartial;  // ����д��Ĳ��ֿ� 
	u8  Reserved3;            // Reserded 
	u8  ContentProtectAppli;  // ���ݱ���Ӧ�� 
	u8  FileFormatGrouop;     // �ļ���ʽ�� 
	u8  CopyFlag;             // ���Ʊ�־ (OTP) 
	u8  PermWrProtect;        // ����д����
	u8  TempWrProtect;        // ��ʱд���� 
	u8  FileFormat;           // �ļ���ʽ 
	u8  ECC;                  // ECC�� 
	u8  CSD_CRC;              // CSD CRC 
	u8  Reserved4;            // always 1
} SD_CSD;   

/*-=SD��CID�Ĵ�������=-*/
typedef struct
{
	u8  ManufacturerID;       // ������ID 
	u16 OEM_AppliID;          // OEM/Ӧ�ó��� ID 
	u32 ProdName1;            // ��Ʒ���Ƶ� 1 ���� 
	u8  ProdName2;            // ��Ʒ���Ƶ� 2 ����
	u8  ProdRev;              // ��Ʒ�汾 
	u32 ProdSN;               // ��Ʒ���к� 
	u8  Reserved1;            // Reserved1 
	u16 ManufactDate;         // �������� 
	u8  CID_CRC;              // CID CRC 
	u8  Reserved2;            // always 1 
} SD_CID;	 

/*-=SD��״̬=-*/
typedef enum
{
	SD_CARD_READY                  = ((uint32_t)0x00000001), //׼��״̬
	SD_CARD_IDENTIFICATION         = ((uint32_t)0x00000002), //ʶ��״̬
	SD_CARD_STANDBY                = ((uint32_t)0x00000003), //����״̬
	SD_CARD_TRANSFER               = ((uint32_t)0x00000004), //����״̬
	SD_CARD_SENDING                = ((uint32_t)0x00000005), //��������״̬
	SD_CARD_RECEIVING              = ((uint32_t)0x00000006), //��������״̬
	SD_CARD_PROGRAMMING            = ((uint32_t)0x00000007), //���״̬
	SD_CARD_DISCONNECTED           = ((uint32_t)0x00000008), //�Ͽ�����״̬
	SD_CARD_ERROR                  = ((uint32_t)0x000000FF)  //����/��Ч״̬
}SDCardState;

/*-=SD����Ϣ,����CSD,CID������=-*/
typedef struct
{
  SD_CSD SD_csd;								//SD�� CSD
  SD_CID SD_cid;								//SD�� CID
  long long CardCapacity;     	//SD������,��λ:�ֽ�,���֧��2^64�ֽڴ�С�Ŀ�.
  u32 CardBlockSize; 	        	//SD�����С	
  u16 RCA;					            //����Ե�ַ
  u8 CardType;		      	    	//������
} SD_CardInfo;
extern SD_CardInfo SDCardInfo;  //SD����Ϣ			



/*-=SDIO ָ�=-*/
#define SD_CMD0                       ((u8)0)  //��λ��������״̬
#define SD_CMD1                       ((u8)1) 
#define SD_CMD2                       ((u8)2) 
#define SD_CMD3                       ((u8)3)  // < SDIO_SEND_REL_ADDR ���� SD �� 
#define SD_CMD4                       ((u8)4  
#define SD_CMD5                       ((u8)5)
#define SD_CMD6                       ((u8)6)
#define SD_CMD7                       ((u8)7)
#define SD_CMD8                       ((u8)8)
#define SD_CMD9                       ((u8)9)
#define SD_CMD10                      ((u8)10)
#define SD_CMD11                      ((u8)11) //SD����֧��
#define SD_CMD12                   		((u8)12) //ֹͣ��stop������
#define SD_CMD13                      ((u8)13)
#define SD_CMD14                      ((u8)14)
#define SD_CMD15                  		((u8)15)
#define SD_CMD16                      ((u8)16)
#define SD_CMD17                   		((u8)17)
#define SD_CMD18                     	((u8)18)
#define SD_CMD19                   		((u8)19)
#define SD_CMD20                			((u8)20) 
#define SD_CMD23                     	((u8)23) 
#define SD_CMD24                 			((u8)24)
#define SD_CMD25                   		((u8)25)
#define SD_CMD26                      ((u8)26)
#define SD_CMD27                      ((u8)27)
#define SD_CMD28                    	((u8)28)
#define SD_CMD29                      ((u8)29)
#define SD_CMD30                    	((u8)30)
#define SD_CMD32                			((u8)32) // ����Ҫ�����ĵ�һ��д��ĵ�ַ�� ���������� SD ���� 
#define SD_CMD33                   		((u8)33) // ����Ҫ������������Χ�����һ��д��ĵ�ַ�� ���������� SD ���� 
#define SD_CMD35                    	((u8)35) // ����Ҫ�����ĵ�һ��д��ĵ�ַ������������ MMC ���淶 3.31��
#define SD_CMD36                      ((u8)36) // ����Ҫ������������Χ�����һ��д��ĵ�ַ�� ���������� MMC ���淶 3.31�� 
#define SD_CMD38                      ((u8)38)
#define SD_CMD39                      ((u8)39) // SD����֧�� 
#define SD_CMD40                      ((u8)40) // SD����֧�� 
#define SD_CMD42                      ((u8)42)
#define SD_CMD55                      ((u8)55)
#define SD_CMD56                      ((u8)56)
#define SD_CMD64                      ((u8)64)


/*	���������� SD ���ض����
 *			�ڷ�����Щ����֮ǰӦ�÷���CMD55��
 */
#define SD_ACMD6               			 ((u8)6)  //�������� SD ��
#define SD_ACMD13                    ((u8)13) //�������� SD �� 
#define SD_ACMD22        						 ((u8)22) //�������� SD �� 
#define SD_ACMD41                    ((u8)41) //�������� SD �� 
#define SD_ACMD42          					 ((u8)42) //�������� SD �� 
#define SD_ACMD51                    ((u8)51) //�������� SD �� 
#define SD_ACMD52                    ((u8)52) //�������� SD I/O ��
#define SD_ACMD53                    ((u8)53) //�������� SD I/O ��

/*	���������� SD ����ȫ���
 *			�ڷ�����Щ����֮ǰӦ�÷���CMD55��
 */
#define SD_ACMD18 									 ((u8)18) //�������� SD �� 
#define SD_ACMD25 									 ((u8)25) //�������� SD �� 
#define SD_ACMD38   		             ((u8)38) //�������� SD �� 
#define SD_ACMD43                    ((u8)43) //�������� SD �� 
#define SD_ACMD44                    ((u8)44) //�������� SD �� 
#define SD_ACMD45      		           ((u8)45) //�������� SD �� 
#define SD_ACMD46           	       ((u8)46) //�������� SD �� 
#define SD_ACMD47             	     ((u8)47) //�������� SD �� 
#define SD_ACMD49           	       ((u8)49) //�������� SD �� 
#define SD_ACMD48_SD_APP_GET_CER_RES1                 ((u8)48) //�������� SD �� 
#define SD_ACMD48_SD_APP_SECURE_WRITE_MKB             ((u8)48) //�������� SD �� 

/*-=֧�ֵ�SD������=-*/
#define SDIO_STD_CAPACITY_SD_CARD_V1_1             ((u32)0x00000000)
#define SDIO_STD_CAPACITY_SD_CARD_V2_0             ((u32)0x00000001)
#define SDIO_HIGH_CAPACITY_SD_CARD                 ((u32)0x00000002)
#define SDIO_MULTIMEDIA_CARD                       ((u32)0x00000003)
#define SDIO_SECURE_DIGITAL_IO_CARD                ((u32)0x00000004)
#define SDIO_HIGH_SPEED_MULTIMEDIA_CARD            ((u32)0x00000005)
#define SDIO_SECURE_DIGITAL_IO_COMBO_CARD          ((u32)0x00000006)
#define SDIO_HIGH_CAPACITY_MMC_CARD                ((u32)0x00000007)

//SDIO��ز�������
#define NULL 0
#define SDIO_STATIC_FLAGS               ((u32)0x000005FF) //��̬��־
#define SDIO_CMD0TIMEOUT                ((u32)0x00010000)	//CMD0��ʱ 
#define SDIO_DATATIMEOUT                ((u32)0xFFFFFFFF)	//���ݳ�ʱ 
#define SDIO_FIFO_Address               ((u32)0x40018080) 

//��״̬ R1��OCR �Ĵ����� 
#define SD_OCR_ADDR_OUT_OF_RANGE        ((u32)0x80000000) //����Ĳ����������Ľ��ܷ�Χ/��ַ������Χ
#define SD_OCR_ADDRESS_ERROR            ((u32)0x40000000) //û����ĵ�ַ��ͬ������ʹ�õĿ鳤�Ȳ�ƥ��
#define SD_OCR_BLOCK_LEN_ERR            ((u32)0x20000000) //�������ܵĿ鳤�ȣ����ߴ���ĳ���ͬ�鳤�Ȳ�ƥ��
#define SD_OCR_ERASE_SEQ_ERR            ((u32)0x10000000) //�������������д�
#define SD_OCR_BAD_ERASE_PARAM          ((u32)0x08000000) //Ҫ�����ġ�дģ�顱��ѡ����Ч
#define SD_OCR_WRITE_PROT_VIOLATION     ((u32)0x04000000) //�Ա���ģ�����д��������д���������в���
//#define SD_OCR_CARD_IS_LOCKED           ((u32)0x02000000) //������������������
#define SD_OCR_LOCK_UNLOCK_FAILED       ((u32)0x01000000) //�����������������
#define SD_OCR_COM_CRC_FAILED           ((u32)0x00800000) //ǰһ������� CRC ������
#define SD_OCR_ILLEGAL_CMD              ((u32)0x00400000) //����ǰ״̬�����ܵ�����
#define SD_OCR_CARD_ECC_FAILED          ((u32)0x00200000) //�ڲ� ECC �յ��������ݲ���
#define SD_OCR_CC_ERROR                 ((u32)0x00100000) //�ڲ��Ŀ�����������
#define SD_OCR_GENERAL_UNKNOWN_ERROR    ((u32)0x00080000) //ͨ�û���δ֪����
#define SD_OCR_STREAM_READ_UNDERRUN     ((u32)0x00040000)
#define SD_OCR_STREAM_WRITE_OVERRUN     ((u32)0x00020000) 
#define SD_OCR_CID_CSD_OVERWRIETE       ((u32)0x00010000) //CSD ��ֻ������ͬ�������ݲ�ƥ�䣬��ͼ���򿽱�����������д����λ
#define SD_OCR_WP_ERASE_SKIP            ((u32)0x00008000) //��Ϊ�����飬������д��������ֻ�����˲���ָ���ĵ�ַ��
#define SD_OCR_CARD_ECC_DISABLED        ((u32)0x00004000) //�����Ѿ�ִ�У�ûʹ���ڲ� ECC
#define SD_OCR_ERASE_RESET              ((u32)0x00002000) //��Ϊ�յ��˳��������������ִ��֮ǰ���������б����

#define SD_OCR_CURRENT_STATE_dis        ((u32)0x00001000) //�Ͽ�����״̬(Disconnect State)
#define SD_OCR_CURRENT_STATE_prg        ((u32)0x00000E00) //���״̬(Programming State)
#define SD_OCR_CURRENT_STATE_rcv        ((u32)0x00000C00) //��������״̬(Receive-data State)
#define SD_OCR_CURRENT_STATE_data       ((u32)0x00000A00) //��������״̬(Sending-data State)
#define SD_OCR_CURRENT_STATE_tran       ((u32)0x00000800) //����״̬(Transfer State)
#define SD_OCR_CURRENT_STATE_stby       ((u32)0x00000600) //����״̬(Stand-by State)
#define SD_OCR_CURRENT_STATE_ident      ((u32)0x00000400) //ʶ��״̬(Identification State)
#define SD_OCR_CURRENT_STATE_ready      ((u32)0x00000200) //׼��״̬(Ready State)
#define SD_OCR_CURRENT_STATE_idle       ((u32)0x00000000) //����״̬(Idle State)
#define SD_OCR_READY_FOR_DATA           ((u32)0x00000100) //�����ϱ�ʾ����յ�״̬�������Խ�������
#define SD_OCR_AKE_SEQ_ERROR            ((u32)0x00000008) //��֤�������з�������
#define SD_OCR_ERRORBITS                ((u32)0xFDFFE008) //����λ

//R6 ��Ӧ����
//�ο�stm32�ֲ�SD R6��Ӧ
#define SD_R6_GENERAL_UNKNOWN_ERROR     ((u32)0x00002000) //ͨ�ñ���
#define SD_R6_ILLEGAL_CMD               ((u32)0x00004000) //�Ƿ�����
#define SD_R6_COM_CRC_FAILED            ((u32)0x00008000) //�˿�CRCʧ��


#define SD_VOLTAGE_WINDOW_SD            ((u32)0x80100000)//stm32 ��������3.6v  ����鿴OCR�Ĵ���˵��
#define SD_HIGH_CAPACITY                ((u32)0x40000000)//[30] CCS:1  ������SD��
#define SD_STD_CAPACITY                 ((u32)0x00000000)//[30] CCS:0  ������SD��
#define SD_CHECK_PATTERN                ((u32)0x000001AA)//[19:16]VHS(֧�ֵ�ѹ):0x1(0001b)
																												 //[15:8]���ģʽ:0xAA(10101010b)
#define SD_VOLTAGE_WINDOW_MMC           ((u32)0x80FF8000) //��ѹ����MMC
#define SD_MAX_VOLT_TRIAL               ((u32)0x0000FFFF) //��ѹ���� ACMD41���� �������ѹ��Ч
#define SD_ALLZERO                      ((u32)0x00000000) //�ޱ���

#define SD_WIDE_BUS_SUPPORT             ((u32)0x00040000) //֧�ֿ�����
#define SD_SINGLE_BUS_SUPPORT           ((u32)0x00010000) //SD������֧��
#define SD_CARD_LOCKED                  ((u32)0x02000000) //SD������״̬
#define SD_CARD_PROGRAMMING             ((u32)0x00000007) //SD�����״̬
#define SD_CARD_RECEIVING               ((u32)0x00000006) //SD������״̬
#define SD_DATATIMEOUT                  ((u32)0xFFFFFFFF) //�������ʱ�� 
#define SD_0TO7BITS                     ((u32)0x000000FF)
#define SD_8TO15BITS                    ((u32)0x0000FF00)
#define SD_16TO23BITS                   ((u32)0x00FF0000)
#define SD_24TO31BITS                   ((u32)0xFF000000)
#define SD_MAX_DATA_LENGTH              ((u32)0x01FFFFFF) //�����ճ���

#define SD_HALFFIFO                     ((u32)0x00000008) //��FIFO
#define SD_HALFFIFOBYTES                ((u32)0x00000020) //��FIFO�ֽ�

//֧�ֵ�������  
#define SD_CCCC_LOCK_UNLOCK             ((u32)0x00000080)
#define SD_CCCC_WRITE_PROT              ((u32)0x00000040)
#define SD_CCCC_ERASE                   ((u32)0x00000020)
																	 
//CMD8ָ��
#define SDIO_SEND_IF_COND               ((u32)0x00000008)

/*=================================================================================*/

SD_Error SD_Init(void);//��ʼ��SD��
u8 SD_ReadDisk(u8*buf,u32 sector,u8 cnt); 	//��SD��,fatfs/usb����
u8 SD_WriteDisk(u8*buf,u32 sector,u8 cnt);	//дSD��,fatfs/usb����


SD_Error SD_PowerON(void);//SD���ϵ�
SD_Error SD_PowerOFF(void);//SD���ص�
SD_Error SD_InitializeCards(void);//��ʼ�����е�SD��
SD_Error SD_GetCardInfo(SD_CardInfo *cardinfo);//��ȡSD����Ϣ
SD_Error SD_SelectDeselect(u32 addr);//ѡ��SD��
SD_Error FindSCR(u16 rca,u32 *pscr);//����SD����SCR�Ĵ���ֵ
SD_Error SD_EnableWideBusOperation(u32 wmode);//�������߿��
SD_Error SD_SetDeviceMode(u32 Mode);//����SD������ģʽ
SD_Error SD_SendStatus(uint32_t *pcardstatus);//��ȡ��ǰ��״̬
SDCardState SD_GetState(void);//����SD����״̬

/*SDIO���*/
void SDIO_Clock_Set(u8 clkdiv);//SDIOʱ������
SD_Error SDEnWideBus(u8 enx);//SDIOʹ�ܿ�����ģʽ
u8 convert_from_bytes_to_power_of_two(u16 NumberOfBytes);
void SD_DMA_Config(u32*mbuf,u32 bufsize,u32 DMA_DIR);//����SDIO DMA


SD_Error SD_ReadBlock(u8 *buf,long long addr,u16 blksize); //SD����ȡһ����  
SD_Error SD_ReadMultiBlocks(u8 *buf,long long  addr,u16 blksize,u32 nblks); //SD����ȡ�����  
SD_Error SD_WriteBlock(u8 *buf,long long addr,  u16 blksize);	//SD��дһ����
SD_Error SD_WriteMultiBlocks(u8 *buf,long long addr,u16 blksize,u32 nblks); //SD��д�����
SD_Error SD_ProcessIRQSrc(void);//SDIO�жϴ�����
SD_Error IsCardProgramming(u8 *pstatus);//��鿨�Ƿ�����ִ��д����



SD_Error Cmd0Error(void);												//���CMD0��ִ��״̬
SD_Error CmdResp1Error(u8 cmd);									//���R1��Ӧ�Ĵ���״̬
SD_Error CmdResp2Error(void);										//���R2��Ӧ�Ĵ���״̬
SD_Error CmdResp3Error(void);										//���R3��Ӧ�Ĵ���״̬
SD_Error CmdResp6Error(u8 cmd,u16*prca);				//���R6��Ӧ�Ĵ���״̬
SD_Error CmdResp7Error(void);										//���R7��Ӧ�Ĵ���״̬







#endif









