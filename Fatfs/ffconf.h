/*---------------------------------------------------------------------------/
/ FatFs ��������
/---------------------------------------------------------------------------*/

#define FFCONF_DEF	86631	/* Revision ID */

/*---------------------------------------------------------------------------/
/ ��������
/---------------------------------------------------------------------------*/

#define FF_FS_READONLY	0
/* ��ѡ���л�ֻ�����á� (0:Read/Write or 1:Read-only)
/  Read-only(ֻ��)����ȥ��дAPI����: f_write(), f_sync(),
/  f_unlink(), f_mkdir(), f_chmod(), f_rename(), f_truncate(), f_getfree()
/  �Լ���ѡ����д���ܡ� */


#define FF_FS_MINIMIZE	0
/* ��ѡ�����С��������ɾ��һЩ���� API ������
/
/   0: ������������ȫ���á�
/   1: ɾ��: f_stat(), f_getfree(), f_unlink(), f_mkdir(), f_truncate() , f_rename() ���� 
/   2: ��1֮��,��ɾ����: f_opendir(), f_readdir() , f_closedir() ����
/   3: ��2֮��,��ɾ����: f_lseek() ���ܡ� */


#define FF_USE_FIND		0
/* ��ѡ��(ʹ/ʧ��)���˵�Ŀ¼��ȡ����, f_findfirst() �� f_findnext().
/  (0:Disable, 1:Enable 2:Enable with matching altname[] too) */


#define FF_USE_MKFS		1
/* ��ѡ��(ʹ/ʧ��)���� f_mkfs() ���� (0:Disable or 1:Enable) */
/* ���������ϴ���һ���ļ�ϵͳ */


#define FF_USE_FASTSEEK	1
/* ��ѡ��(ʹ/ʧ��)�����������ܡ� (0:Disable or 1:Enable) */
/* �����Ƿ���ٶ�λ */

#define FF_USE_EXPAND	0
/* ��ѡ��(ʹ/ʧ��)���� f_expand ���� (0:Disable or 1:Enable) */


#define FF_USE_CHMOD	0
/* ��ѡ��(ʹ/ʧ��)���Բ������ܣ� f_chmod() �� f_utime().
/  (0:Disable or 1:Enable)  ��Ҫ FF_FS_READONLY Ϊ 0 �������ô�ѡ� */


#define FF_USE_LABEL	1
/* ��ѡ��(ʹ/ʧ��)���깦�ܣ� f_getlabel() �� f_setlabel().
/  (0:Disable or 1:Enable) */
/*  �����Ƿ�֧�ִ����̷���ȡ������ */


#define FF_USE_FORWARD	0
/* ��ѡ��(ʹ/ʧ��) f_forward() function. (0:Disable or 1:Enable) */
/* ֱ������ļ������� */

#define FF_USE_STRFUNC	1
#define FF_PRINT_LLI		0
#define FF_PRINT_FLOAT	0
#define FF_STRF_ENCODE	0
/* FF_USE_STRFUNC (ʹ/ʧ��)�ַ�������, f_gets(), f_putc(), f_puts(), f_printf().
/  �Ƿ�֧���ַ��������
/
/   0: Disable. FF_PRINT_LLI, FF_PRINT_FLOAT, FF_STRF_ENCODE û��Ч����
/   1: Enable �� LF-CRLF ת��
/   2: Enable LF-CRLF ת��
/
/  FF_PRINT_LLI = 1           ʹ f_printf() ֧�� long long ���� 
/  FF_PRINT_FLOAT = 1/2       ʹ f_printf() ֧�� float(������) ����.
/  ��Щ������Ҫ C99 ����߰汾��
/
/  �� FF_LFN_UNICODE >= 1 �� ʹ�� FF_USE_LFN ʱ, �� �ַ�������ת�����е��ַ����롣
/  FF_STRF_ENCODE  ѡ��ͨ����Щ������ȡ/д���ļ��ϵ��ַ������Ԥ�衣
/  
/   0: ANSI/OEM in current CP
/   1: Unicode in UTF-16LE
/   2: Unicode in UTF-16BE
/   3: Unicode in UTF-8
*/


/*---------------------------------------------------------------------------/
/ ���Ի����������ռ�����
/---------------------------------------------------------------------------*/

#define FF_CODE_PAGE	936
/* ��ѡ��ָ��Ҫ��Ŀ��ϵͳ��ʹ�õ� ���� ���͡�
/  ����ȷ�Ĵ���ҳ���ûᵼ���ļ���ʧ�ܡ�
/
/   437 - U.S.
/   720 - Arabic
/   737 - Greek
/   771 - KBL
/   775 - Baltic
/   850 - Latin 1
/   852 - Latin 2
/   855 - Cyrillic
/   857 - Turkish
/   860 - Portuguese
/   861 - Icelandic
/   862 - Hebrew
/   863 - Canadian French
/   864 - Arabic
/   865 - Nordic
/   866 - Russian
/   869 - Greek 2
/   932 - Japanese (DBCS)
/   936 - Simplified Chinese (DBCS)
/   949 - Korean (DBCS)
/   950 - Traditional Chinese (DBCS)
/     0 - Include all code pages above and configured by f_setcp()
*/


#define FF_USE_LFN		3
#define FF_MAX_LFN		255
/* The FF_USE_LFN switches the support for LFN .(long file name)
/  FF_USE_LFN (ʹ/ʧ��)�Ƿ�֧�ֳ��ļ���(����ҪFF_CODE_PAGE��֧��)
/ 
/   0: Disable LFN. FF_MAX_LFN ��Ч��
/   1: Enable LFN �� BSS �����ô���̬������������ LFN�� Always NOT thread-safe.
/   2: Enable LFN �� ��ջ�����þ��ж�̬������������ LFN��
/   3: Enable LFN �� HEAP �����þ��ж�̬������������ LFN��
/
/  To enable the LFN, ffunicode.c needs to be added to the project. The LFN function
/  requiers certain internal working buffer occupies (FF_MAX_LFN + 1) * 2 bytes and
/  additional (FF_MAX_LFN + 44) / 15 * 32 bytes when exFAT is enabled.
/  The FF_MAX_LFN defines size of the working buffer in UTF-16 code unit and it can
/  be in range of 12 to 255. It is recommended to be set it 255 to fully support LFN
/  specification.
/  When use stack for the working buffer, take care on stack overflow. When use heap
/  memory for the working buffer, memory management functions, ff_memalloc() and
/  ff_memfree() exemplified in ffsystem.c, need to be added to the project. */


#define FF_LFN_UNICODE	0
/* This option switches the character encoding on the API when LFN is enabled.
/
/   0: ANSI/OEM in current CP (TCHAR = char)
/   1: Unicode in UTF-16 (TCHAR = WCHAR)
/   2: Unicode in UTF-8 (TCHAR = char)
/   3: Unicode in UTF-32 (TCHAR = DWORD)
/
/  Also behavior of string I/O functions will be affected by this option.
/  When LFN is not enabled, this option has no effect. */


#define FF_LFN_BUF		255
#define FF_SFN_BUF		12
/* This set of options defines size of file name members in the FILINFO structure
/  which is used to read out directory items. These values should be suffcient for
/  the file names to read. The maximum possible length of the read file name depends
/  on character encoding. When LFN is not enabled, these options have no effect. */


#define FF_FS_RPATH		0
/* This option configures support for relative path.
/
/   0: Disable relative path and remove related functions.
/   1: Enable relative path. f_chdir() and f_chdrive() are available.
/   2: f_getcwd() function is available in addition to 1.
*/


/*---------------------------------------------------------------------------/
/ ������/������
/---------------------------------------------------------------------------*/

#define FF_VOLUMES		2
/* Ҫʹ�õľ����߼������������� (1-10) */
/* ����FATFS ֧���߼��豸�� */


#define FF_STR_VOLUME_ID	0
#define FF_VOLUME_STRS		"RAM","NAND","CF","SD","SD2","USB","USB2","USB3"
/* FF_STR_VOLUME_ID switches support for volume ID in arbitrary strings.
/  When FF_STR_VOLUME_ID is set to 1 or 2, arbitrary strings can be used as drive number in the path name. 
/  FF_VOLUME_STRS defines the volume ID strings for each logical drives.
/  Number of items must not be less than FF_VOLUMES. 
/	 Valid characters for the volume ID strings are A-Z, a-z and 0-9, however they arecompared in case-insensitive.  
/  If FF_STR_VOLUME_ID >= 1 and FF_VOLUME_STRS is
/  not defined, a user defined volume string table needs to be defined as:
/  const char* VolumeStr[FF_VOLUMES] = {"ram","flash","sd","usb",...
/
/  FF_STR_VOLUME_ID ���ö������ַ����еľ� ID ��֧�֡�
/  �� FF_STR_VOLUME_ID ����Ϊ 1 �� 2 ʱ������ʹ�������ַ�����Ϊ·�����е��������š�
/  FF_VOLUME_STRS ����ÿ���߼��������ľ� ID �ַ�������Ŀ������������ FF_VOLUMES��
/  �� ID �ַ�������Ч�ַ��� A-Z��a-z �� 0-9���������ǲ����ִ�Сд��
/  ��� FF_STR_VOLUME_ID >= 1 ��δ���� FF_VOLUME_STRS������Ҫ�����û�����ľ��ַ�����Ϊ��
/  const char* VolumeStr[FF_VOLUMES] = {"ram","flash","sd","usb",.. .
*/


#define FF_MULTI_PARTITION	0
/* This option switches support for multiple volumes on the physical drive.
/  By default (0), each logical drive number is bound to the same physical drive
/  number and only an FAT volume found on the physical drive will be mounted.
/  When this function is enabled (1), each logical drive number can be bound to
/  arbitrary physical drive and partition listed in the VolToPart[]. Also f_fdisk()
/  funciton will be available. */
/* ��ѡ�����ö������������϶������֧�֡� */

#define FF_MIN_SS		512
#define FF_MAX_SS		512
/* This set of options configures the range of sector size to be supported. (512,
/  1024, 2048 or 4096) Always set both 512 for most systems, generic memory card and
/  harddisk, but a larger value may be required for on-board flash memory and some
/  type of optical media. When FF_MAX_SS is larger than FF_MIN_SS, FatFs is configured
/  for variable sector size mode and disk_ioctl() function needs to implement
/  GET_SECTOR_SIZE command. */
/* ����ѡ������Ҫ֧�ֵ�������С��Χ��*/

#define FF_LBA64		0
/* This option switches support for 64-bit LBA. (0:Disable or 1:Enable)
/  To enable the 64-bit LBA, also exFAT needs to be enabled. (FF_FS_EXFAT == 1) */
/* ��ѡ�����ö� 64 λ LBA ��֧�֡�*/

#define FF_MIN_GPT		0x10000000
/* Minimum number of sectors to switch GPT as partitioning format in f_mkfs and
/  f_fdisk function. 0x100000000 max. This option has no effect when FF_LBA64 == 0. */


#define FF_USE_TRIM		0
/* This option switches support for ATA-TRIM. (0:Disable or 1:Enable)
/  To enable Trim function, also CTRL_TRIM command should be implemented to the
/  disk_ioctl() function. */
/* ��ѡ�����ö� ATA-TRIM ��֧�֡�*/


/*---------------------------------------------------------------------------/
/ System Configurations ϵͳ����
/---------------------------------------------------------------------------*/

#define FF_FS_TINY		0
/* This option switches tiny buffer configuration. (0:Normal or 1:Tiny)
/  At the tiny configuration, size of file object (FIL) is shrinked FF_MAX_SS bytes.
/  Instead of private sector buffer eliminated from the file object, common sector
/  buffer in the filesystem object (FATFS) is used for the file data transfer. */


#define FF_FS_EXFAT		0
/* This option switches support for exFAT filesystem. (0:Disable or 1:Enable)
/  To enable exFAT, also LFN needs to be enabled. (FF_USE_LFN >= 1)
/  Note that enabling exFAT discards ANSI C (C89) compatibility. */
/* ��ѡ�����ö� exFAT �ļ�ϵͳ��֧�֡� */

#define FF_FS_NORTC		0
#define FF_NORTC_MON	1
#define FF_NORTC_MDAY	1
#define FF_NORTC_YEAR	2020
/* The option FF_FS_NORTC switches timestamp functiton. If the system does not have
/  any RTC function or valid timestamp is not needed, set FF_FS_NORTC = 1 to disable
/  the timestamp function. Every object modified by FatFs will have a fixed timestamp
/  defined by FF_NORTC_MON, FF_NORTC_MDAY and FF_NORTC_YEAR in local time.
/  To enable timestamp function (FF_FS_NORTC = 0), get_fattime() function need to be
/  added to the project to read current time form real-time clock. FF_NORTC_MON,
/  FF_NORTC_MDAY and FF_NORTC_YEAR have no effect.
/  These options have no effect in read-only configuration (FF_FS_READONLY = 1). */


#define FF_FS_NOFSINFO	0
/* If you need to know correct free space on the FAT32 volume, set bit 0 of this
/  option, and f_getfree() function at first time after volume mount will force
/  a full FAT scan. Bit 1 controls the use of last allocated cluster number.
/
/  bit0=0: Use free cluster count in the FSINFO if available.
/  bit0=1: Do not trust free cluster count in the FSINFO.
/  bit1=0: Use last allocated cluster number in the FSINFO if available.
/  bit1=1: Do not trust last allocated cluster number in the FSINFO.
*/


#define FF_FS_LOCK		0
/* The option FF_FS_LOCK switches file lock function to control duplicated file open
/  and illegal operation to open objects. This option must be 0 when FF_FS_READONLY
/  is 1.
/
/  0:  Disable file lock function. To avoid volume corruption, application program
/      should avoid illegal open, remove and rename to the open objects.
/  >0: Enable file lock function. The value defines how many files/sub-directories
/      can be opened simultaneously under file lock control. Note that the file
/      lock control is independent of re-entrancy. */


/* #include <somertos.h>	// O/S definitions */
#define FF_FS_REENTRANT	0
#define FF_FS_TIMEOUT	1000
#define FF_SYNC_t		HANDLE
/* The option FF_FS_REENTRANT switches the re-entrancy (thread safe) of the FatFs
/  module itself. Note that regardless of this option, file access to different
/  volume is always re-entrant and volume control functions, f_mount(), f_mkfs()
/  and f_fdisk() function, are always not re-entrant. Only file/directory access
/  to the same volume is under control of this function.
/
/   0: Disable re-entrancy. FF_FS_TIMEOUT and FF_SYNC_t have no effect.
/   1: Enable re-entrancy. Also user provided synchronization handlers,
/      ff_req_grant(), ff_rel_grant(), ff_del_syncobj() and ff_cre_syncobj()
/      function, must be added to the project. Samples are available in
/      option/syscall.c.
/
/  The FF_FS_TIMEOUT defines timeout period in unit of time tick.
/  The FF_SYNC_t defines O/S dependent sync object type. e.g. HANDLE, ID, OS_EVENT*,
/  SemaphoreHandle_t and etc. A header file for O/S definitions needs to be
/  included somewhere in the scope of ff.h. */



/*--- End of configuration options ---*/