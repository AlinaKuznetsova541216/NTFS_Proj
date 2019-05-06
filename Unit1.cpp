//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "IteratorThread.h"
#include "NTFSClass.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
bool StopAndTerminate;
IteratorThread *NewIteratorThread;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ScanButton1Click(TObject *Sender)
{
	Form1->BytesPerSecLabel1->Caption =  " ";
	Form1->SecPerClustLabel2->Caption =  " ";
	Form1->BytesPerClustLabel3->Caption =  " ";
	Form1->NumSecLabel5->Caption =  " ";
	Form1->NumClustLabel6->Caption =  " ";
	NewIteratorThread = new IteratorThread(PathEdit1->Text.c_str(), false, StartClusterEdit1->Text.ToInt(), EndClusterEdit2->Text.ToInt());
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

