//---------------------------------------------------------------------------

#pragma hdrstop

#include "FSClass.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#include "NTFSClass.h"
#include "ExFatClass.h"
#include "FAT32Class.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
FSClass::FSClass()
{
	   FileHandle = NULL;
	   BytesPerSector = 0;
	   SectorsPerCluster = 0;
	   NumberOfSectors = 0;
	   BytesPerCluster = 0;
	   NumberOfSectors = 0;
	   StartSector = 0;
}
FSClass *FSClass::ChooseFS(FileSystems FSname)
{
	   switch(FSname)
	   {
			   case NTFS: return new NTFS_FileSystemClass();
			   case exFAT: return new ExFat_FileSystemClass();
			   case FAT32: return new FAT32_FileSystemClass();
	   }
}
FSClass::~FSClass()
{

}

bool FSClass::Open(WCHAR *fileName)
{
   FileHandle = CreateFileW(
			   fileName,
			   GENERIC_READ,
			   FILE_SHARE_READ | FILE_SHARE_WRITE,
			   NULL,
			   OPEN_EXISTING,
			   FILE_ATTRIBUTE_NORMAL,
			   NULL
			   );

	   if(FileHandle == INVALID_HANDLE_VALUE)
	   {
			   FileSystemStatus = "Ошибка, не удается открыть ФС!";
			   return false;
	   }
	   if(SetAtributes())
	   {
			   return true;
	   }
	   else
	   {
		return false;
	}
}

WORD FSClass::GetBytesPerSector()
{
	   return BytesPerSector;
}

BYTE FSClass::GetSectorsPerCluster()
{
	   return SectorsPerCluster;
}

ULONGLONG FSClass::GetNumberOfSectors()
{
	   return NumberOfSectors;
}

ULONGLONG FSClass::GetNumberOfClusters()
{
	   return NumberOfClusters;
}

DWORD FSClass::GetBytesPerCluster()
{
	   return BytesPerCluster;
}

void FSClass::Close()
{
	   CloseHandle(FileHandle);
}

bool FSClass::ReadClusters(ULONGLONG startCluster, DWORD BytesPerCluster, BYTE*outBuffer)
{
	   if(FileHandle == 0)
	   {
			   return false;
	   }
	   ULONGLONG startOffset = startCluster*BytesPerCluster;
	   DWORD bytesToRead = BytesPerCluster;
	   DWORD bytesRead;

	   LARGE_INTEGER sectorOffset;
	   sectorOffset.QuadPart = startOffset + StartSector;

	   unsigned long currentPosition = SetFilePointer(
			   FileHandle,
			   sectorOffset.LowPart,
			   &sectorOffset.HighPart,
			   FILE_BEGIN
			   );
	   if(currentPosition != sectorOffset.LowPart)
	   {
			   return false;
	   }

	   bool readResult = ReadFile(
			   FileHandle,
			   outBuffer,
			   bytesToRead,
			   &bytesRead,
			   NULL
			   );
	   if(!readResult || bytesRead != bytesToRead)
	   {
			   return false;
	   }
}

