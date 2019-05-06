//---------------------------------------------------------------------------
#ifndef NTFSClassH
#define NTFSClassH
#include <string>
#include <windows.h>
//---------------------------------------------------------------------------
#pragma pack(push, 1)
typedef struct
{
/*0x00*/BYTE  jump[3];			        /* Команда перехода на загрузочный код */
/*0x03*/char OemId[8];	         	/* сигнатура "NTFS    " */
/*0x0b*/WORD BytesPerSector;	     	/* Размер сектора в байтах */
/*0x0d*/BYTE SectorsPerCluster;	        /* Количество секторов в кластере*/
/*0x0e*/WORD ReservedSectors;	     	/* Должно равняться нулю */
/*0x10*/BYTE Fats;			         	/* Должно равняться нулю*/
/*0x11*/WORD RootEntries;		     	/* Должно равняться нулю */
/*0x13*/WORD Sectors;			        /* Должно равняться нулю */
/*0x15*/BYTE MediaType;		            /* Тип носителя, 0xf8 = hard disk */
/*0x16*/WORD SectorsPerFat;		        /* Должно равняться нулю */
/*0x18*/WORD SectorsPerTrack;	     	/* Не используются*/
/*0x1a*/WORD Heads;			         	/* Не используются */
/*0x1c*/DWORD HiddenSectors;		    /* Не используются */
/*0x20*/DWORD LargeSectors;		        /* Должно равняться нулю */
/*0x24*/BYTE PhysicalDrive;		        /* Не используется */
/*0x25*/BYTE CurrentHead;		        /* Не используется*/
/*0x26*/BYTE ExtendedBootSignature;     /* Не используется */
/*0x27*/BYTE Reserved2;			        /* Не используется */
/*0x28*/ULONGLONG NumberOfSectors;      /* Число секторов в томе. */
/*0x30*/ULONGLONG MftLcn;	            /* стартовый кластер MFT. */
/*0x38*/ULONGLONG MftMirrLcn;           /* Стартовый кластер копии MFT */
/*0x40*/BYTE ClustersPerMftRecord;	    /* размер MFT записи в кластерах. */
/*0x41*/BYTE Reserved0[3];		        /* зарезервировано */
/*0x44*/BYTE ClustersPerIndexRecord;    /* Размер индексной записи в кластерах. */
/*0x45*/BYTE Reserved1[3];		        /* зарезервировано */
/*0x48*/ULONGLONG VolumeSerialNumber;   /* уникальный серийный номер тома */
/*0x50*/DWORD Checksum;			        /* не используется */
/*0x54*/BYTE Bootstrap[426];		    /* загрузочный код */
/*0x1fe*/WORD EndOfSectorMarker;	    /* конец загрузочного сектора, сигнатура 0xaa55 */
} NTFS_BootRecord;
#pragma pack(pop)
class NTFS_FileSystemClass
{
protected:
	HANDLE FileHandle;
	std::string OemId;
	WORD BytesPerSector;
	BYTE SectorsPerCluster;
	ULONGLONG NumberOfSectors;
	DWORD BytesPerCluster;  //Число байт в кластере (рассчитаем)
	WORD EndOfSectorMarker;
	ULONGLONG NumberOfClusters; //Общее количество кластеров (рассчитаем)
public:
	NTFS_FileSystemClass();
	bool Open(WCHAR *fileName);
	std::string GetOemId();
	WORD GetBytesPerSector();
	BYTE GetSectorsPerCluster();
	ULONGLONG GetNumberOfSectors();
	ULONGLONG GetNumberOfClusters();
	DWORD GetBytesPerCluster();
	WORD GetEndOfSectorMarker();
	bool SetNTFSAtributes();  //Устанавливаем все атрибуты
	bool ReadClusters(ULONGLONG StartCluster, DWORD numberOfClusters, BYTE *outBuffer);
	void Close();
	std::string FileSystemStatus;
};
#endif
