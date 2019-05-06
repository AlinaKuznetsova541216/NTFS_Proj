//---------------------------------------------------------------------------

#ifndef ScanThreadH
#define ScanThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <vector>
#include <string>
#include <windows.h>
//---------------------------------------------------------------------------
// Критическая секция добавления результатов поиска
	//TCriticalSection *BufferAccessCS;
//---------------------------------------------------------------------------
const int WaitDelayMs = 2000;
//---------------------------------------------------------------------------
class ScanThread : public TThread
{
private:
	__int64 NumCluster;
	int Id;
	int ClusterSize;
	BYTE *OutBufferPtr;
	BYTE *DataBuffer;
	void CopyData();
	void __fastcall CompleteSearch();
   //	std::vector<std::string> signatures;

protected:
	void __fastcall Execute();
public:
	__fastcall ScanThread(BYTE *dataBufferPtr, int clusterSize, bool CreateSuspended, int startcluster);
	//std::string SignatureType;

	// События, используемые для синхронизации
	TEvent *BufferReadyEvent;
	TEvent *BufferCopiedEvent;
};
//---------------------------------------------------------------------------
#endif
