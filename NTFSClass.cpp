//---------------------------------------------------------------------------

#pragma hdrstop

#include "NTFSClass.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#include <string>
#include <windows.h>
#include "NTFSClass.h"
//class IteratorOfClusters;
//---------------------------------------------------------------------------
#pragma package(smart_init)
NTFS_FileSystemClass::NTFS_FileSystemClass()
{
	   FileHandle = NULL;
	   OemId = "";
	   BytesPerSector = 0;
	   SectorsPerCluster = 0;
	   NumberOfSectors = 0;
	   BytesPerCluster = 0;
	   NumberOfSectors = 0;
	   EndOfSectorMarker = 0;
	   //FileSystemStatus="";
}

std::string NTFS_FileSystemClass::GetOemId()
{
	   return OemId;
}

WORD NTFS_FileSystemClass::GetEndOfSectorMarker()
{
	   return EndOfSectorMarker;
}

bool NTFS_FileSystemClass::SetAtributes()
{
	   if(FileHandle == 0)
	   {
			   return false;
	   }
	   BYTE dataBuffer[512]; // Для небольших объемов (до нескольких КБ)
	   ULONGLONG startOffset = 0;
	   DWORD bytesToRead = 512;
	   DWORD bytesRead;
	   // При чтении данных с физического устройства смещение должно соответсовать границе сектора!
	   LARGE_INTEGER sectorOffset;
	   sectorOffset.QuadPart = startOffset;
	   // Задать позицию
	   unsigned long currentPosition = SetFilePointer(
			   FileHandle,
			   sectorOffset.LowPart,
			   &sectorOffset.HighPart,
			   FILE_BEGIN // Точка в файле, относительно которой необходимо пиционироваться (FILE_BEGIN, FILE_CURRENT, FILE_END)
			   );
	   if(currentPosition != sectorOffset.LowPart)
	   {
			   return false;
	   }
	   // Чтение данных
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
	   NTFS_BootRecord *pBootRecord;
	   // Инициализируем указатель
	   pBootRecord = (NTFS_BootRecord*)dataBuffer;
	   //Проверка на том NTFS
	   //std::string signNTFS = "NTFS    ";
	   if(strcmp((pBootRecord->OemId),"NTFS    ") == 0)
	   {
			   // Инициализируем атрибуты
			   OemId = *pBootRecord->OemId;
			   BytesPerSector = pBootRecord->BytesPerSector;
			   SectorsPerCluster = pBootRecord->SectorsPerCluster;
			   NumberOfSectors = pBootRecord->NumberOfSectors;
			   BytesPerCluster = ((pBootRecord->BytesPerSector)*(pBootRecord->SectorsPerCluster));
			   EndOfSectorMarker = pBootRecord->EndOfSectorMarker;
			   NumberOfClusters = ((pBootRecord->NumberOfSectors)/(pBootRecord->SectorsPerCluster));
			   StartSector = 0;
			   return true;
	   }
	   else
	   {
				FileSystemStatus = "Файловая система не NTFS";
				return false;
	   }
}

IteratorOfClusters *NTFS_FileSystemClass::GetIteratorOfClusters()
{
	   return new IteratorOfClustersNTFS(this);
}

NTFS_FileSystemClass::~NTFS_FileSystemClass()
{
	   Close();
}
