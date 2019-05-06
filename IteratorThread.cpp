//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "IteratorThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

__fastcall IteratorThread::IteratorThread(WCHAR *filePath, bool CreateSuspended, int StartClusterFromEdit, int EndClusterFromEdit)
	: TThread(CreateSuspended)
{
	FreeOnTerminate = true;
	StartCluster = StartClusterFromEdit;
	EndCluster = EndClusterFromEdit;
	myClassPtr = new NTFS_FileSystemClass();
	// Открыть файловую систему
	if(myClassPtr->Open(filePath))
	{
		if (EndCluster > (myClassPtr->GetNumberOfClusters()))
		{
			EndCluster = int(myClassPtr->GetNumberOfClusters());
		}
		if (StartCluster > (myClassPtr->GetNumberOfClusters()))
		{
			StartCluster = int(myClassPtr->GetNumberOfClusters());
		}
		if (StartCluster > EndCluster)
		{
			int tmp;
			tmp = StartCluster;
			StartCluster = EndCluster;
			EndCluster = tmp;
		}
		Form1->InformationLabel4->Caption = "Идет поиск...";
		Form1->BytesPerSecLabel1->Caption = myClassPtr->GetBytesPerSector();
		Form1->SecPerClustLabel2->Caption = myClassPtr->GetSectorsPerCluster();
		Form1->BytesPerClustLabel3->Caption = myClassPtr->GetBytesPerCluster();
		Form1->NumSecLabel5->Caption = myClassPtr->GetNumberOfSectors();
		Form1->NumClustLabel6->Caption = myClassPtr->GetNumberOfClusters();
	}
	else
	{
		Form1->InformationLabel4->Caption = UnicodeString(myClassPtr->FileSystemStatus.c_str());
	}
	if(!myClassPtr->SetNTFSAtributes())
	{
		delete myClassPtr;
	}
}
//---------------------------------------------------------------------------
void __fastcall IteratorThread::Execute()
{
	// Определить размер кластера
	int clusterSize = myClassPtr->GetBytesPerCluster();
	BYTE *dataBuffer = new BYTE[clusterSize];
	MyScanThread = new ScanThread(dataBuffer,clusterSize,false, StartCluster);

	// Перебор кластеров диска
	//__int64 i;
	//__int64 getnumclust = myClassPtr->GetNumberOfClusters();
	//int bytespercluster = myClassPtr->GetBytesPerCluster();
	Iterator <BYTE *> * it = new IteratorDecoratorOfClusters((new IteratorOfClusters(myClassPtr)), StartCluster, EndCluster);
	for(it->First();!it->IsDone();it->Next())
	{
		it->GetCurrent(&dataBuffer);
		MyScanThread->BufferReadyEvent->SetEvent();
		// Ожидать окончания копирования буфера
		while(MyScanThread->BufferCopiedEvent->WaitFor(WaitDelayMs) != wrSignaled)
		{
		}
		MyScanThread->BufferCopiedEvent->ResetEvent();
		if(Terminated) break;
	}

	// Завершить поиск
	MyScanThread->Terminate();
	delete myClassPtr;
	delete[] dataBuffer;
}
//---------------------------------------------------------------------------
