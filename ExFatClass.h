//---------------------------------------------------------------------------

#ifndef ExFatClassH
#define ExFatClassH
//---------------------------------------------------------------------------
#include <string>
#include <windows.h>
#include "FSClass.h"
#include "IteratorOfClusters.h"
#include "IteratorOfClustersExFat.h"
//---------------------------------------------------------------------------
#pragma pack(push, 1)
typedef struct
{
/*0x00*/BYTE jump[3];
/*0x03*/char OemId[8];
			   BYTE Reserved1[61];
/*0x48*/ULONGLONG NumberOfSectors;
/*0x50*/DWORD FatStartSector;
/*0x54*/DWORD FatSizeInSectors;
/*0x58*/DWORD BitmapStartSector;
/*0x5C*/DWORD NumberOfClusters;
/*0x60*/DWORD RootCluster;
/*0x64*/DWORD PartSerial;
			   BYTE Reserved2[4];
/*0x6C*/BYTE BytesPerSector;
/*0x6D*/BYTE SectorsPerCluster;
			   BYTE Reserved3[400];
			   BYTE Signature[2];
} exFat_BootRecord;
#pragma pack(pop)
class ExFat_FileSystemClass : public FSClass
{
private:
	   std::string OemId;
public:
	   ExFat_FileSystemClass();
	   virtual ~ExFat_FileSystemClass();
	   std::string GetOemId();
	   bool SetAtributes();
	   IteratorOfClusters *GetIteratorOfClusters();
};

#endif
