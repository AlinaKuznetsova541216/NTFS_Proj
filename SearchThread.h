//---------------------------------------------------------------------------

#ifndef SearchThreadH
#define SearchThreadH
#include <vcl.h>
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <vector>
#include <string>
#include <windows.h>
#include "IteratorOfClusters.h"

//---------------------------------------------------------------------------
const int WaitDelayMs = 2000;
//---------------------------------------------------------------------------
class SearchThread : public TThread
{
private:
	   int Id;
	   int ClusterSize;
	   ClusterDisk *OutBufferPtr;
	   BYTE *DataBuffer;
	   __int64 NumberCluster;
	   void CopyData();
	   void SearchData();
	   void __fastcall AddMatch();
	   void __fastcall CompleteSearch();
	   std::vector<std::string> signatures;

protected:
	   void __fastcall Execute();
public:
	   __fastcall SearchThread(ClusterDisk *dataBufferPtr, int clusterSize, bool CreateSuspended);
	   std::string SignatureType;
	   TEvent *BufferReadyEvent;
	   TEvent *BufferCopiedEvent;
};
#endif
