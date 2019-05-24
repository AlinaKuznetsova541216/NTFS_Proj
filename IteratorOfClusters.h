//---------------------------------------------------------------------------

#ifndef IteratorOfClustersH
#define IteratorOfClustersH
//---------------------------------------------------------------------------
#include "Iterator.h"
#include <windows.h>
class FSClass;
//---------------------------------------------------------------------------
typedef struct
{
	   BYTE *cluster;
	   ULONGLONG num_of_cluster;
} ClusterDisk;
//---------------------------------------------------------------------------
class IteratorOfClusters : public Iterator<ClusterDisk>
{
private:
	   FSClass * myFsClassPtr;
	   DWORD ClusterSize;
	   ULONGLONG NumCurrentCluster;
	   ULONGLONG NumberOfClusters;
	   ClusterDisk BufferCluster;
public:
	   IteratorOfClusters(FSClass * myPtr);
	   IteratorOfClusters();
	   virtual ~IteratorOfClusters();
	   virtual void First()=0;
	   virtual void Next()=0;
	   virtual bool IsDone() const=0;
	   virtual ClusterDisk GetCurrent()=0;
	   virtual void GetCurrent(ClusterDisk *dataBuffer)=0;
	   virtual ULONGLONG GetNumCurrentCluster()=0;
};

#endif
