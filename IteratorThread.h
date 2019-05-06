//---------------------------------------------------------------------------

#ifndef IteratorThreadH
#define IteratorThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
#include "ScanThread.h"
#include "NTFSClass.h"
#include "Unit1.h"
#include "IteratorDecoratorOfClusters.h"
#include <windows.h>
//---------------------------------------------------------------------------
class IteratorThread : public TThread
{
private:
	HANDLE FileSystemHandle;
	ScanThread *MyScanThread;
	NTFS_FileSystemClass *myClassPtr;
	int StartCluster;
	int EndCluster;
protected:
	void __fastcall Execute();
public:
	__fastcall IteratorThread(WCHAR *filePath, bool CreateSuspended, int StartClusterFromEdit, int EndClusterFromEdit);
};
//---------------------------------------------------------------------------
//typedef vector<BYTE> DiskCluster;
#endif
