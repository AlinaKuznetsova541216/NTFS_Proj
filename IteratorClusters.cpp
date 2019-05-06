//---------------------------------------------------------------------------

#pragma hdrstop

#include "IteratorClusters.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
IteratorDecoratorOfClusters::IteratorDecoratorOfClusters(IteratorOfClusters *It,int Start,int End)
{
	IteratorOf = It;
	StartCluster = Start;
	EndCluster = End;
}
IteratorDecoratorOfClusters::~IteratorDecoratorOfClusters()
{
	delete IteratorOf;
};
void IteratorDecoratorOfClusters::First()
{
	for (IteratorOf->First(); !IteratorOf->IsDone();IteratorOf->Next())
	{
		if (IteratorOf->GetNumCurrentCluster() == StartCluster)
		{
			break;
		}
	}
}
void IteratorDecoratorOfClusters::Next()
{
	IteratorOf->Next();
}
bool IteratorDecoratorOfClusters::IsDone() const
{
	return (IteratorOf->GetNumCurrentCluster() >= EndCluster);
}
BYTE * IteratorDecoratorOfClusters::GetCurrent()
{
	return IteratorOf-> GetCurrent();
}
void IteratorDecoratorOfClusters::GetCurrent(BYTE **outBuffer)
{
   IteratorOf->GetCurrent(outBuffer);
}
