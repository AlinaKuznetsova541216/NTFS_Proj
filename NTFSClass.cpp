//---------------------------------------------------------------------------
#pragma hdrstop
#include <string>
#include <windows.h>
#include "NTFSClass.h"
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
}
bool NTFS_FileSystemClass::Open(WCHAR *fileName)
{
   FileHandle = CreateFileW(
		fileName, // Имя файла (WCHAR*)
		GENERIC_READ,	  // Режим доступа
		FILE_SHARE_READ | FILE_SHARE_WRITE, // Режим совместной работы
		NULL, // Атрибуты безопасности
		OPEN_EXISTING, // Способ открытия
		FILE_ATTRIBUTE_NORMAL, // Флаги и атрибуты
		NULL // Описатель (идентификатор) файла шаблона с правами доступа GENERIC_READ.
		);

	if(FileHandle == INVALID_HANDLE_VALUE)
	{
		FileSystemStatus = "Ошибка в открытии диска";
		return false;
	}
	if(SetNTFSAtributes())
	{
		return true;
	}
}

std::string NTFS_FileSystemClass::GetOemId()
{
	return OemId;
}

WORD NTFS_FileSystemClass::GetBytesPerSector()
{
	return BytesPerSector;
}

BYTE NTFS_FileSystemClass::GetSectorsPerCluster()
{
	return SectorsPerCluster;
}

ULONGLONG NTFS_FileSystemClass::GetNumberOfSectors()
{
	return NumberOfSectors;
}

ULONGLONG NTFS_FileSystemClass::GetNumberOfClusters()
{
	return NumberOfClusters;
}

DWORD NTFS_FileSystemClass::GetBytesPerCluster()
{
	return BytesPerCluster;
}

WORD NTFS_FileSystemClass::GetEndOfSectorMarker()
{
	return EndOfSectorMarker;
}

bool NTFS_FileSystemClass::ReadClusters(ULONGLONG startCluster, DWORD BytesPerCluster, BYTE *outBuffer)
{
	if(FileHandle == 0)
	{
		return false;
	}
	ULONGLONG startOffset = startCluster*BytesPerCluster;
	DWORD bytesToRead = BytesPerCluster;
	DWORD bytesRead;
	// При чтении данных с физического устройства смещение должно соответствовать границе сектора!
	LARGE_INTEGER sectorOffset;
	sectorOffset.QuadPart = startOffset;
	// Задать позицию
	unsigned long currentPosition = SetFilePointer(
		FileHandle,
		sectorOffset.LowPart,
		&sectorOffset.HighPart,
		FILE_BEGIN // Точка в файле, относительно которой необходимо позиционироваться (FILE_BEGIN, FILE_CURRENT, FILE_END)
		);
	if(currentPosition != sectorOffset.LowPart)
	{
		return false;
	}
	// Чтение данных
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

bool NTFS_FileSystemClass::SetNTFSAtributes()
{
	if(FileHandle == 0)
	{
		return false;
	}
	BYTE dataBuffer[512]; // Для небольших объемов (до нескольких КБ)
	ULONGLONG startOffset = 0;
	DWORD bytesToRead = 512;
	DWORD bytesRead;
	// При чтении данных с физического устройства смещение должно соответствовать границе сектора!
	LARGE_INTEGER sectorOffset;
	sectorOffset.QuadPart = startOffset;
	// Задать позицию
	unsigned long currentPosition = SetFilePointer(
		FileHandle,
		sectorOffset.LowPart,
		&sectorOffset.HighPart,
		FILE_BEGIN // Точка в файле, относительно которой необходимо позиционироваться (FILE_BEGIN, FILE_CURRENT, FILE_END)
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
		return true;
	}
	else
	{
		 FileSystemStatus = "Файловая система не NTFS";
		 return false;
	}
}

void NTFS_FileSystemClass::Close()
{
	CloseHandle(FileHandle);
}
