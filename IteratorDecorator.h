//---------------------------------------------------------------------------

#ifndef IteratorDecoratorH
#define IteratorDecoratorH
//---------------------------------------------------------------------------
#include <string>
#include <windows.h>
#include "IteratorOfClusters.h"
//---------------------------------------------------------------------------
class IteratorDecorator : public IteratorOfClusters
{
protected:
	   IteratorOfClusters * Iterat;
	   IteratorDecorator() {}
public:
	   IteratorDecorator(IteratorOfClusters * it) {Iterat = it;}
	   virtual ~IteratorDecorator(){delete Iterat;}
	   virtual void First(){Iterat->First();}
	   virtual void Next(){Iterat->Next();}
	   virtual bool IsDone(){return Iterat->IsDone();}
	   virtual ClusterDisk GetCurrent(){return Iterat->GetCurrent();}
	   virtual void GetCurrent(ClusterDisk *dataBuffer){Iterat->GetCurrent(dataBuffer);}
	   virtual ULONGLONG GetNumCurrentCluster(){return Iterat->GetNumCurrentCluster();}

};
#endif
