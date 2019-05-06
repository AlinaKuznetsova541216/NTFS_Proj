//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <windows.h>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TLabel *BytesPerSecLabel1;
	TLabel *SecPerClustLabel2;
	TLabel *BytesPerClustLabel3;
	TEdit *PathEdit1;
	TButton *ScanButton1;
	TLabel *InformationLabel4;
	TLabel *NumSecLabel5;
	TLabel *NumClustLabel6;
	TButton *StopButton2;
	TLabel *Label7infoFor1;
	TLabel *Label8infoFor2;
	TLabel *Label9infoFor3;
	TLabel *Label10infoFor5;
	TLabel *Label11infoFor6;
	TEdit *StartClusterEdit1;
	TEdit *EndClusterEdit2;
	TLabel *LabelStartCluster;
	TLabel *LabelEndCluster;
	TMemo *Memo1;
	void __fastcall ScanButton1Click(TObject *Sender);
	void __fastcall StopButton2Click(TObject *Sender);



private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
