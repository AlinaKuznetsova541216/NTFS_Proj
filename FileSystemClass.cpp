//---------------------------------------------------------------------------

#pragma hdrstop

#include "FileSystemClass.h"
#include "NTFSClass.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
FileSystemClass::FileSystemClass()
{
	FileHandle = NULL;
	BytesPerSector = 0;
	SectorsPerCluster = 0;
	NumberOfSectors = 0;
	BytesPerCluster = 0;
	NumberOfSectors = 0;
	StartSector = 0;

}

FileSystemClass *FileSystemClass::ChooseFileSystem(FileSystems FSname)
{
	switch(FSname)
	{
		 case NTFS: return new NTFS_FileSystemClass();
	}

}
FileSystemClass::~FileSystemClass()
{

}


bool FileSystemClass::Open(WCHAR *fileName)
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
					FileSystemStatus = "Ошибка в открытии диска";
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
WORD FileSystemClass::GetBytesPerSector()
{
		 return BytesPerSector;
}

BYTE FileSystemClass::GetSectorsPerCluster()
{
	return SectorsPerCluster;
}

ULONGLONG FileSystemClass::GetNumberOfSectors()
{
	return NumberOfSectors;
}

ULONGLONG FileSystemClass::GetNumberOfClusters()
{
	return NumberOfClusters;
}

DWORD FileSystemClass::GetBytesPerCluster()
{
	return BytesPerCluster;
}

void FileSystemClass::Close()
{
	CloseHandle(FileHandle);
}

bool FileSystemClass::ReadClusters(ULONGLONG startCluster, DWORD BytesPerCluster,   BYTE *outBuffer)
{
	if(FileHandle == 0)
	{
		return false;
	}
	ULONGLONG startOffset = startCluster *BytesPerCluster;
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
//---------------------------------------------------------------------------

