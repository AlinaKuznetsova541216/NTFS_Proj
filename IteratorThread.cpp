//---------------------------------------------------------------------------

#pragma hdrstop

#include "IteratorThread.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
__fastcall IteratorThread::IteratorThread(WCHAR *filePath, bool CreateSuspended, int StartClusterFromEdit, int EndClusterFromEdit, bool FullOrRange, bool NTFSRadioButton1, bool exFatRadioButton2, bool FAT32RadioButton3)
	   : TThread(CreateSuspended)
{
	   FreeOnTerminate = true;
	   StartCluster = StartClusterFromEdit;
	   EndCluster = EndClusterFromEdit;
	   Full = FullOrRange;
	   RadioButtonNTFS=NTFSRadioButton1;
	   RadioButtonExFat=exFatRadioButton2;
	   RadioButtonFAT32=FAT32RadioButton3;
	   //myClassPtr = new NTFS_FileSystemClass();
	   //myClassPtr = FSClass::ChooseFS(NTFS);
	   ////////////
	   if (RadioButtonNTFS)
	   {
			   myClassPtr = FSClass::ChooseFS(NTFS);
	   }
	   if (RadioButtonExFat)
	   {
			   myClassPtr = FSClass::ChooseFS(exFAT);
			   StartCluster = 2;
	   }
	   if (RadioButtonFAT32)
	   {
			   myClassPtr = FSClass::ChooseFS(FAT32);
			   StartCluster = 2;
	   }

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
			   Form2->InformationLabel4->Caption = "Выполняется поиск...";
			   Form2->BytesPerSecLabel1->Caption = myClassPtr->GetBytesPerSector();
			   Form2->SecPerClustLabel2->Caption = myClassPtr->GetSectorsPerCluster();
			   Form2->BytesPerClustLabel3->Caption = myClassPtr->GetBytesPerCluster();
			   Form2->NumSecLabel5->Caption = myClassPtr->GetNumberOfSectors();
			   Form2->NumClustLabel6->Caption = myClassPtr->GetNumberOfClusters();
	   }
	   else
	   {
			   //Form1->InformationLabel4->Caption = myClassPtr->GetFileSystetatus().c_str();
			   Form2->InformationLabel4->Caption = myClassPtr->FileSystemStatus.c_str();
	   }
}
//---------------------------------------------------------------------------
void __fastcall IteratorThread::Execute()
{
	   int clusterSize = myClassPtr->GetBytesPerCluster();
	   ClusterDisk dataBuffer;
	   dataBuffer.cluster = new BYTE[clusterSize];
	   dataBuffer.num_of_cluster = 0;
	   MySearchThread = new SearchThread(&dataBuffer,clusterSize,false);
	   IteratorOfClusters * it;
	   //Iterator<ClusterDisk> * it;
	   if (!Full){
			   it = new IteratorDecoratorOfClusters((myClassPtr->GetIteratorOfClusters()), StartCluster, EndCluster);
	   }
	   else {
			   it = myClassPtr->GetIteratorOfClusters();
	   }
	   for(it->First();!it->IsDone();it->Next())
	   {
			   it->GetCurrent(&dataBuffer);
			   MySearchThread->BufferReadyEvent->SetEvent();

			   while(MySearchThread->BufferCopiedEvent->WaitFor(WaitDelayMs) == wrSignaled)
			   {
			   }
			   MySearchThread->BufferCopiedEvent->ResetEvent();
			   if(Terminated) break;
	   }
	   delete it;

	   MySearchThread->Terminate();
	   delete myClassPtr;
	   delete[] dataBuffer.cluster;

}

