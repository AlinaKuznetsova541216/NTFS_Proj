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
	   BYTE dataBuffer[512]; // ��� ��������� ������� (�� ���������� ��)
	   ULONGLONG startOffset = 0;
	   DWORD bytesToRead = 512;
	   DWORD bytesRead;
	   // ��� ������ ������ � ����������� ���������� �������� ������ ������������� ������� �������!
	   LARGE_INTEGER sectorOffset;
	   sectorOffset.QuadPart = startOffset;
	   // ������ �������
	   unsigned long currentPosition = SetFilePointer(
			   FileHandle,
			   sectorOffset.LowPart,
			   &sectorOffset.HighPart,
			   FILE_BEGIN // ����� � �����, ������������ ������� ���������� ��������������� (FILE_BEGIN, FILE_CURRENT, FILE_END)
			   );
	   if(currentPosition != sectorOffset.LowPart)
	   {
			   return false;
	   }
	   // ������ ������
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
	   // �������������� ���������
	   pBootRecord = (NTFS_BootRecord*)dataBuffer;
	   //�������� �� ��� NTFS
	   //std::string signNTFS = "NTFS    ";
	   if(strcmp((pBootRecord->OemId),"NTFS    ") == 0)
	   {
			   // �������������� ��������
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
				FileSystemStatus = "�������� ������� �� NTFS";
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
