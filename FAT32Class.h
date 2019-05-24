//---------------------------------------------------------------------------

#ifndef FAT32ClassH
#define FAT32ClassH
//---------------------------------------------------------------------------
#include <string>
#include <windows.h>
#include "FSClass.h"
#include "IteratorOfClusters.h"
#include "IteratorOfClustersFAT32.h"
//---------------------------------------------------------------------------
#pragma pack(push, 1)
typedef struct
{
			   BYTE jump[3];
/*0x03*/char OemId[8];
/*0x0B*/WORD BytesPerSector;
/*0x0D*/BYTE SectorsPerCluster;
/*0x0E*/WORD Reserved;
/*0x10*/BYTE FATCopies;
			   WORD Reserved1;
/*0x13*/WORD NumberOfSectors16;
			   BYTE Reserved2[11];
/*0x16*/DWORD NumberOfSectors32;
/*0x18*/DWORD NumOfSecFat;
			   BYTE Reserved3[470];
			   BYTE Signature[2];
} FAT32_BootRecord;
#pragma pack(pop)
class FAT32_FileSystemClass : public FSClass
{
private:
	   std::string OemId;
public:
	   FAT32_FileSystemClass();
	   virtual ~FAT32_FileSystemClass();
	   std::string GetOemId();
	   bool SetAtributes();
	   IteratorOfClusters *GetIteratorOfClusters();
};

#endif
