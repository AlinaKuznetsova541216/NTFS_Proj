//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "IteratorThread.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
TForm2 *Form2;
bool StopAndTerminate;
IteratorThread *NewIteratorThread;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{           VirtualStringTree2->NodeDataSize = sizeof(NodeOfStringTree);

}
//---------------------------------------------------------------------------
void __fastcall TForm2::ScanButton1Click(TObject *Sender)
{
       VirtualStringTree2->Clear();
	   Form2->BytesPerSecLabel1->Caption =  " ";
	   Form2->SecPerClustLabel2->Caption =  " ";
	   Form2->BytesPerClustLabel3->Caption =  " ";
	   Form2->NumSecLabel5->Caption =  " ";
	   Form2->NumClustLabel6->Caption =  " ";
	   NewIteratorThread = new IteratorThread(PathEdit1->Text.c_str(), false, StartClusterEdit1->Text.ToInt(), EndClusterEdit2->Text.ToInt(), FullClustersCheckBox1->Checked,  NTFSRadioButton1->Checked, exFatRadioButton2->Checked, FAT32RadioButton3->Checked);
	   StopAndTerminate = true;

}
//---------------------------------------------------------------------------
void __fastcall TForm2::StopButton2Click(TObject *Sender)
{
   if (StopAndTerminate)
       {
			   NewIteratorThread->Terminate();
	   }

}
//---------------------------------------------------------------------------

void __fastcall TForm2::VirtualStringTree2GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)

{
  if(!Node)       return;
	 NodeOfStringTree *nodeData = (NodeOfStringTree*)Sender->GetNodeData(Node);
	   switch(Column)
	   {
			   case 0: CellText = nodeData->Id; break;
			   case 1: CellText = nodeData->NumCluster; break;
			   case 2: CellText = nodeData->Type.c_str(); break;
       }

}
//---------------------------------------------------------------------------

