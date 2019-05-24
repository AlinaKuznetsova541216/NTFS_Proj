//---------------------------------------------------------------------------

#ifndef IteratorDecoratorOfClustersH
#define IteratorDecoratorOfClustersH
//---------------------------------------------------------------------------
 #include "IteratorDecorator.h"
//#include "IteratorOfClusters.h"
//#include "Iterator.h"
//---------------------------------------------------------------------------
class IteratorDecoratorOfClusters : public IteratorDecorator
{
protected:
	   IteratorOfClusters *IteratorOf;
	   int StartCluster;
	   int EndCluster;
public:
	   IteratorDecoratorOfClusters(IteratorOfClusters *It,int Start,int End);
	   virtual ~IteratorDecoratorOfClusters();
	   virtual void First();
	   virtual void Next();
	   virtual bool IsDone() const;
	   virtual ClusterDisk GetCurrent();
	   virtual void GetCurrent(ClusterDisk *outBuffer);
};

#endif
