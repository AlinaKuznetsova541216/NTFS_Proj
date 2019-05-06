//---------------------------------------------------------------------------

#ifndef IteratorClustersH
#define IteratorClustersH
#include "IteratorDecorator.h"
#include "IteratorOfClusters.h"
//#include "Iterator.h"
//---------------------------------------------------------------------------
class IteratorDecoratorOfClusters : public IteratorDecorator
{
protected:
	IteratorOfClusters *IteratorOf;
	int StartCluster;
	int EndCluster;
	//IteratorDecoratorOfClusters(Iterator<BYTE *> * it){IteratorOf = it};
public:
	IteratorDecoratorOfClusters(IteratorOfClusters *It,int Start,int End);
	virtual ~IteratorDecoratorOfClusters();
	virtual void First();
	virtual void Next();
	virtual bool IsDone() const;
	virtual BYTE * GetCurrent();
	virtual void GetCurrent(BYTE **outBuffer);
};
#endif
