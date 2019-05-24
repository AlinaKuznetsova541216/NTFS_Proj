//---------------------------------------------------------------------------
#include <vcl.h>
#include <string>
#pragma hdrstop
//#include "Unit1.h"
#include "Unit2.h"
#include "SearchThread.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
__fastcall SearchThread::SearchThread(ClusterDisk *dataBufferPtr, int clusterSize, bool CreateSuspended)
		  : TThread(CreateSuspended)
{
	   signatures.resize(2);
	   signatures[0] = "\x25\x50\x44\x46";
	   signatures[1] = "\xff\xd8\xff\xe0";
	   FreeOnTerminate = true;
	   Id=1;
	   BufferReadyEvent  = new TEvent(NULL, true, false,"",false);
	   BufferCopiedEvent = new TEvent(NULL, true, false,"",false);
	   //BufferAccessCS = new TCriticalSection;
	   ClusterSize = clusterSize;
	   OutBufferPtr = dataBufferPtr;
	   DataBuffer = new BYTE[clusterSize];
	   NumberCluster = OutBufferPtr->num_of_cluster;
}
//---------------------------------------------------------------------------
void __fastcall SearchThread::Execute()
{
	   while(true)
	   {
			  if(BufferReadyEvent->WaitFor(WaitDelayMs) == wrSignaled)
			   {
					   //if(BufferAccessCS->TryEnter())
					   if(true)
					   {

							   CopyData();

							   BufferReadyEvent->ResetEvent();
							   BufferCopiedEvent->SetEvent();


							   SearchData();
						  //   NumberCluster++;
							   //BufferAccessCS->Leave();
					   }
			   }
			   if(Terminated) break;
	   }
	   Synchronize(&CompleteSearch);

	   delete BufferReadyEvent;
	   delete BufferCopiedEvent;
	   //delete BufferAccessCS;

	   delete[] DataBuffer;
}
//---------------------------------------------------------------------------
void SearchThread::CopyData()
{
	   memcpy(DataBuffer, OutBufferPtr, ClusterSize);
	   NumberCluster = OutBufferPtr->num_of_cluster;
}
//---------------------------------------------------------------------------
void SearchThread::SearchData()
{

	   /*std::vector<std::string> signatures(2);
	   signatures[0] = "\x25\x50\x44\x46";
	   signatures[1] = "\xff\xd8\xff\xe0";  */
	   for (int j = 0; j < signatures.size(); j++) {
			   if (memcmp(DataBuffer , signatures[j].c_str(), 4) == 0) {
					   if (j==0) {
							   SignatureType = "PDF";
					   }
					   if (j==1) {
							   SignatureType = "JPG";
					   }
					   Synchronize(&AddMatch);
			   }
	   }
}
//---------------------------------------------------------------------------
void __fastcall SearchThread::AddMatch()
{
	   PVirtualNode entryNode = Form2->VirtualStringTree2->AddChild(Form2->VirtualStringTree2->RootNode);
	   NodeOfStringTree *nodeData = (NodeOfStringTree*)Form2->VirtualStringTree2->GetNodeData(entryNode);
	   nodeData->Id  = Id;
	   nodeData->NumCluster = NumberCluster;
	   //wcscpy(nodeData->Type ,SignatureType.c_str());
	   nodeData->Type = SignatureType.c_str();
	   Id++;
}
//---------------------------------------------------------------------------
void __fastcall SearchThread::CompleteSearch()
{
	   Form2->InformationLabel4->Caption = "Поиск завершен!";
}
