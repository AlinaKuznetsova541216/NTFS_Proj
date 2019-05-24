//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VirtualTrees.hpp"
//---------------------------------------------------------------------------
typedef struct
{
	   int Id;
	   __int64 NumCluster;
	   std::string Type;
} NodeOfStringTree;

class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TLabel *BytesPerSecLabel1;
	TLabel *SecPerClustLabel2;
	TLabel *BytesPerClustLabel3;
	TLabel *InformationLabel4;
	TLabel *NumSecLabel5;
	TLabel *NumClustLabel6;
	TLabel *Label7infoFor1;
	TLabel *Label8infoFor2;
	TLabel *Label9infoFor3;
	TLabel *Label10infoFor5;
	TLabel *Label11infoFor6;
	TLabel *Label12infoFor4;
	TLabel *LabelStartCluster;
	TLabel *LabelEndCluster;
	TEdit *PathEdit1;
	TButton *ScanButton1;
	TButton *StopButton2;
	TVirtualStringTree *VirtualStringTree2;
	TEdit *StartClusterEdit1;
	TEdit *EndClusterEdit2;
	TCheckBox *FullClustersCheckBox1;
	TRadioButton *NTFSRadioButton1;
	TRadioButton *FAT32RadioButton3;
	TRadioButton *exFatRadioButton2;
	void __fastcall ScanButton1Click(TObject *Sender);
	void __fastcall StopButton2Click(TObject *Sender);
	void __fastcall VirtualStringTree2GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText);

private:	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
