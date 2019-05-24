//---------------------------------------------------------------------------

#ifndef FSClassH
#define FSClassH
//---------------------------------------------------------------------------
#include <string>
#include <windows.h>
#include "IteratorOfClusters.h"
//class IteratorOfClusters;
//---------------------------------------------------------------------------
typedef enum{NTFS, exFAT, FAT32}FileSystems;
class FSClass
{
protected:
	   HANDLE FileHandle;
	   WORD BytesPerSector;
	   BYTE SectorsPerCluster;
	   ULONGLONG NumberOfSectors;
	   DWORD BytesPerCluster;
	   ULONGLONG NumberOfClusters; 
	   FSClass();
	   DWORD StartSector;
public:
	   virtual ~FSClass();
	   virtual bool Open(WCHAR *fileName);
	   virtual WORD GetBytesPerSector();
	   virtual BYTE GetSectorsPerCluster();
	   virtual ULONGLONG GetNumberOfSectors();
	   virtual ULONGLONG GetNumberOfClusters();
	   virtual DWORD GetBytesPerCluster();
	   virtual bool SetAtributes() = 0;
	   virtual bool ReadClusters(ULONGLONG StartCluster, DWORD numberOfCluste, BYTE *outBuffer);
	   virtual void Close();
	   virtual IteratorOfClusters * GetIteratorOfClusters()=0;
	   static FSClass *ChooseFS(FileSystems FSname);
	   std::string FileSystemStatus;
};

#endif
