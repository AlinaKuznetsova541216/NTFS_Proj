//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <string>
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
		// �����, ���� �� ����� ����������� ����� ��� �����������
		if(BufferReadyEvent->WaitFor(WaitDelayMs) == wrSignaled)
		{
			//if(BufferAccessCS->TryEnter())
			if(true)
			{
				// ����������� ������
				CopyData();

				// ��������� �����
				BufferReadyEvent->ResetEvent();
				BufferCopiedEvent->SetEvent();
			}
		}
		if(Terminated) break;
	}
	Synchronize(&CompleteSearch);
	// ������� �������
	delete BufferReadyEvent;
	delete BufferCopiedEvent;
	//delete BufferAccessCS;
	//UnicodeString s;
	//

	// ������� �����
	delete[] DataBuffer;
}
//---------------------------------------------------------------------------
void ScanThread::CopyData()
{
	memcpy(DataBuffer, OutBufferPtr, ClusterSize);
	//size_t len;
	//UnicodeString s( reinterpret_cast<char const*>(DataBuffer), len ) ;
     UnicodeString s;
	s=(UnicodeString)(char*)DataBuffer;
	Form1->Memo1->Lines->Add(s) ;
}
//---------------------------------------------------------------------------

void __fastcall ScanThread::CompleteSearch()
{
	Form1->InformationLabel4->Caption = "�������� �������� ����������� � ������!";
}
