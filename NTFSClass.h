//---------------------------------------------------------------------------

#ifndef NTFSClassH
#define NTFSClassH
//---------------------------------------------------------------------------
#include <string>
#include <windows.h>
#include "FSClass.h"
#include "IteratorOfClusters.h"
#include "IteratorOfClustersNTFS.h"
//---------------------------------------------------------------------------
#pragma pack(push, 1)
typedef struct
{
/*0x00*/BYTE  jump[3];                         /* ������� �������� �� ��������� ��� */
/*0x03*/char OemId[8];                 /* ��������� "NTFS    " */
/*0x0b*/WORD BytesPerSector;           /* ������ ������� � ������ */
/*0x0d*/BYTE SectorsPerCluster;                /* ���������� �������� � ������*/
/*0x0e*/WORD ReservedSectors;          /* ������ ��������� ���� */
/*0x10*/BYTE Fats;                                     /* ������ ��������� ��*/
/*0x11*/WORD RootEntries;                      /* ������ ��������� ���� */
/*0x13*/WORD Sectors;                          /* ������ ��������� ���� */
/*0x15*/BYTE MediaType;                            /* ��� ��������, 0xf8 = ha disk */
/*0x16*/WORD SectorsPerFat;                    /* ������ ��������� ���� */
/*0x18*/WORD SectorsPerTrack;          /* �� ������������*/
/*0x1a*/WORD Heads;                                    /* �� ������������ */
/*0x1c*/DWORD HiddenSectors;               /* �� ������������ */
/*0x20*/DWORD LargeSectors;                    /* ������ ��������� ���� */
/*0x24*/BYTE PhysicalDrive;                    /* �� ������������ */
/*0x25*/BYTE CurrentHead;                      /* �� ������������*/
/*0x26*/BYTE ExtendedBootSignature;     /* �� ������������ */
/*0x27*/BYTE Reserved2;                                /* �� ������������ */
/*0x28*/ULONGLONG NumberOfSectors;      /* ����� �������� � ����. */
/*0x30*/ULONGLONG MftLcn;                  /* ��������� ������� MFT. */
/*0x38*/ULONGLONG MftMirrLcn;           /* ��������� ������� ����� MFT */
/*0x40*/BYTE ClustersPerMftRecord;         /* ������ MFT ������ � ���������.
/*0x41*/BYTE Reserved0[3];                     /* ��������������� */
/*0x44*/BYTE ClustersPerIndexRecord;    /* ������ ��������� ������ � �������� */
/*0x45*/BYTE Reserved1[3];                     /* ��������������� */
/*0x48*/ULONGLONG VolumeSerialNumber;   /* ���������� �������� ����� ���� */
/*0x50*/DWORD Checksum;                                /* �� ������������ */
/*0x54*/BYTE Bootstrap[426];               /* ����������� ��� */
/*0x1fe*/WORD EndOfSectorMarker;           /* ����� ������������ �������, ������� 0xaa55 */
} NTFS_BootRecord;
#pragma pack(pop)
class NTFS_FileSystemClass : public FSClass
{
protected:
	   std::string OemId;
	   WORD EndOfSectorMarker;
	   //DWORD StartSector;
public:
	   NTFS_FileSystemClass();
	   virtual ~NTFS_FileSystemClass();
	   std::string GetOemId();
	   WORD GetEndOfSectorMarker();
	   bool SetAtributes();  //������������� ��� ��������
	  IteratorOfClusters *GetIteratorOfClusters();
};

#endif
