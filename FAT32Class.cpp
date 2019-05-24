//---------------------------------------------------------------------------

#pragma hdrstop

#include "FAT32Class.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#include "FAT32Class.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
FAT32_FileSystemClass::FAT32_FileSystemClass()
{
	   FileHandle = NULL;
	   OemId = "";
	   BytesPerSector = 0;
	   SectorsPerCluster = 0;
	   NumberOfSectors = 0;
	   BytesPerCluster = 0;
	   NumberOfSectors = 0;
	   //FileSystemStatus="";
	   //StartSector = 0;
}

std::string FAT32_FileSystemClass::GetOemId()
{
	   return OemId;
}



bool FAT32_FileSystemClass::SetAtributes()
{
	   if(FileHandle == 0)
	   {
			   return false;
	   }
	   BYTE dataBuffer[512];
	   ULONGLONG startOffset = 0;
	   DWORD bytesToRead = 512;
	   DWORD bytesRead;

	   LARGE_INTEGER sectorOffset;
	   sectorOffset.QuadPart = startOffset;

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
			   dataBuffer,
			   bytesToRead,
			   &bytesRead,
			   NULL
			   );
	   if(!readResult || bytesRead != bytesToRead)
	   {
			   return false;
	   }
	   FAT32_BootRecord *pBootRecord;

	   pBootRecord = (FAT32_BootRecord*)dataBuffer;
	   if(strcmp((pBootRecord->OemId),"MSDOS5.0") == 0)
	   {

			   OemId = *pBootRecord->OemId;
			   BytesPerSector = pBootRecord->BytesPerSector;
			   SectorsPerCluster = pBootRecord->SectorsPerCluster;
			   NumberOfSectors = pBootRecord->NumberOfSectors32;
			   BytesPerCluster = BytesPerSector*SectorsPerCluster;
			   NumberOfClusters = ((pBootRecord->NumberOfSectors32)/(pBootRecord->SectorsPerCluster));
			   StartSector = (pBootRecord->Reserved+pBootRecord->FATCopies*pBootRecord->NumOfSecFat)*BytesPerSector - 2 * BytesPerCluster;
			   return true;
	   }
	   else
	   {
				FileSystemStatus = "Данная файловая система не FAT32";
				return false;
	   }
}

IteratorOfClusters *FAT32_FileSystemClass::GetIteratorOfClusters()
{
	   return new IteratorOfClustersFAT32(this);
}

FAT32_FileSystemClass::~FAT32_FileSystemClass()
{
	   Close();
}
