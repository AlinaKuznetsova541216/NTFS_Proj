//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "IteratorThread.h"
//#include "NTFSClass.h"
#include "Unit1.h"
bool StopAndTerminate;
IteratorThread *NewIteratorThread;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TForm1::ScanButton1Click(TObject *Sender)
{
	   VirtualStringTree2->Clear();
	   Form1->BytesPerSecLabel1->Caption =  " ";
	   Form1->SecPerClustLabel2->Caption =  " ";
	   Form1->BytesPerClustLabel3->Caption =  " ";
	   Form1->NumSecLabel5->Caption =  " ";
	   Form1->NumClustLabel6->Caption =  " ";
	   NewIteratorThread = new IteratorThread(PathEdit1->Text.c_str(), false,tartClusterEdit1->Text.ToInt(), EndClusterEdit2->Text.ToInt(), FullClustersCheBox1->Checked,  NTFSRadioButton1->Checked, exFatRadioButton2->Checked, FAT32RaoButton3->Checked);
	   StopAndTerminate = true;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::StopButton2Click(TObject *Sender)
{
			if (StopAndTerminate)
	   {
			   NewIteratorThread->Terminate();
	   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::VirtualStringTree2GetText(TBaseVirtualTree *Sender, PrtualNode Node,
				 TColumnIndex Column, TVSTTextType TextType, UnicodeString &ClText)

{
	   if(!Node)       return;
	   NodeOfStringTree *nodeData = (NodeOfStringTree*)Sender->GetNodeData(No);
	   switch(Column)
	   {
			   case 0: CellText = nodeData->Id; break;
			   case 1: CellText = nodeData->NumCluster; break;
			   case 2: CellText = nodeData->Type.c_str(); break;
	   }

}
//---------------------------------------------------------------------------
		}



