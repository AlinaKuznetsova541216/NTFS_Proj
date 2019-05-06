//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ScanThread.h"
#include "Unit1.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall ScanThread::ScanThread(BYTE *dataBufferPtr, int clusterSize, bool CreateSuspended, int StartCluster)
	: TThread(CreateSuspended)
{
	FreeOnTerminate = true;
	NumCluster = StartCluster;
	Id=1;
	BufferReadyEvent  = new TEvent(NULL, true, false,"",false);
	BufferCopiedEvent = new TEvent(NULL, true, false,"",false);
	//BufferAccessCS = new TCriticalSection;
	ClusterSize = clusterSize;
	OutBufferPtr = dataBufferPtr;
	DataBuffer = new BYTE[clusterSize];
}
//---------------------------------------------------------------------------
void __fastcall ScanThread::Execute()
{
	while(true)
	{
		// Ждать, пока не будет подготовлен буфер для копирования
		if(BufferReadyEvent->WaitFor(WaitDelayMs) == wrSignaled)
		{
			//if(BufferAccessCS->TryEnter())
			if(true)
			{
				// Скопировать данные
				CopyData();

				// Отпустить буфер
				BufferReadyEvent->ResetEvent();
				BufferCopiedEvent->SetEvent();
			}
		}
		if(Terminated) break;
	}
	Synchronize(&CompleteSearch);
	// Удалить события
	delete BufferReadyEvent;
	delete BufferCopiedEvent;
	//delete BufferAccessCS;
	// Удалить буфер
	delete[] DataBuffer;
}
//---------------------------------------------------------------------------
void ScanThread::CopyData()
{
	memcpy(DataBuffer, OutBufferPtr, ClusterSize);
}
//---------------------------------------------------------------------------

void __fastcall ScanThread::CompleteSearch()
{
	Form1->InformationLabel4->Caption = "Заданные кластеры скопированы в буффер!";
}
