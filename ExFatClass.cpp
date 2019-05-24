//---------------------------------------------------------------------------

#pragma hdrstop

#include "ExFatClass.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
ExFat_FileSystemClass::ExFat_FileSystemClass()
{
	   FileHandle = NULL;
	   OemId = "";
	   BytesPerSector = 0;
	   SectorsPerCluster = 0;
	   NumberOfSectors = 0;
	   BytesPerCluster = 0;
	   NumberOfSectors = 0;
}

std::string ExFat_FileSystemClass::GetOemId()
{
	   return OemId;
}

bool ExFat_FileSystemClass::SetAtributes()
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
	   exFat_BootRecord *pBootRecord;

	   pBootRecord = (exFat_BootRecord*)dataBuffer;
	   if(strcmp((pBootRecord->OemId),"EXFAT   ") == 0)
	   {

			   OemId = *pBootRecord->OemId;
			   BytesPerSector = 1 << pBootRecord->BytesPerSector;
			   SectorsPerCluster = 1 << pBootRecord->SectorsPerCluster;
			   NumberOfSectors = pBootRecord->NumberOfSectors;
			   BytesPerCluster = BytesPerSector*SectorsPerCluster;
			   NumberOfClusters = pBootRecord->NumberOfClusters;
			   StartSector = 512 * pBootRecord->BitmapStartSector - 2 * BytesPerCluster;
			   return true;
	   }
	   else
	   {
				FileSystemStatus = "Выбранная ФС не exFAT";
				return false;
	   }
}

IteratorOfClusters *ExFat_FileSystemClass::GetIteratorOfClusters()
{
	   return new IteratorOfClustersExFat(this);
}

ExFat_FileSystemClass::~ExFat_FileSystemClass()
{
	   Close();
}

