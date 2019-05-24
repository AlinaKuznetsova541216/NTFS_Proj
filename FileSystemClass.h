//---------------------------------------------------------------------------

#ifndef FileSystemClassH
#define FileSystemClassH
//---------------------------------------------------------------------------
#include <string>
#include <windows.h>
#include "IteratorOfClusters.h"
//class IteratorOfClusters;
//---------------------------------------------------------------------------
typedef enum{NTFS}FileSystems;
class FyleSystemClass
{
protected:
	   HANDLE FileHandle;
	   WORD BytesPerSector;
	   BYTE SectorsPerCluster;
	   ULONGLONG NumberOfSectors;
	   DWORD BytesPerCluster;
	   ULONGLONG NumberOfClusters;
	   FyleSystemClass();
	   DWORD StartSector;
public:
	   virtual ~FyleSystemClass();
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
	   static FileSystemClass *ChooseFileSystem(FileSystems FSname);
	   std::string FileSystemStatus;
};

#endif//---------------------------------------------------------------------------
