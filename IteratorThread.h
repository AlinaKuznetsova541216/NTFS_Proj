//---------------------------------------------------------------------------

#ifndef IteratorThreadH
#define IteratorThreadH
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
#include "SearchThread.h"
#include "FSClass.h"
#include "Unit2.h"
#include "IteratorDecoratorOfClusters.h"
#include "IteratorOfClusters.h"
#include <windows.h>
//---------------------------------------------------------------------------
class IteratorThread : public TThread
{
private:
	   HANDLE FileSystemHandle;
	   SearchThread *MySearchThread;
	   FSClass *myClassPtr;
	   int StartCluster;
	   int EndCluster;
	   bool Full;
	   bool RadioButtonNTFS;
	   bool RadioButtonExFat;
	   bool RadioButtonFAT32;
protected:
	   void __fastcall Execute();
public:
	   __fastcall IteratorThread(WCHAR *filePath, bool CreateSuspended, int StartClusterFromEdit, int EndClusterFromEdit, bool FullOrRange, bool NTFSRadioButn1, bool exFatRadioButton2, bool FAT32RadioButton3);
};
//---------------------------------------------------------------------------
//typedef vector<BYTE> DiskCluster;

#endif
