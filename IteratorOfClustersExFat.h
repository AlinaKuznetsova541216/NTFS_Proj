//---------------------------------------------------------------------------

#ifndef IteratorOfClustersExFatH
#define IteratorOfClustersExFatH
//---------------------------------------------------------------------------
#include "ExFatClass.h"
#include "IteratorOfClusters.h"
class ExFat_FileSystemClass;
//---------------------------------------------------------------------------
class IteratorOfClustersExFat : public IteratorOfClusters
{
private:
	   ExFat_FileSystemClass * myFsClassPtr;
	   DWORD ClusterSize;
	   ULONGLONG NumCurrentCluster;
	   ULONGLONG NumberOfClusters;
	   ClusterDisk BufferCluster;
public:
	   IteratorOfClustersExFat(ExFat_FileSystemClass * myPtr);
	   virtual ~IteratorOfClustersExFat();
	   virtual void First();
	   virtual void Next();
	   virtual bool IsDone() const;
	   virtual ClusterDisk GetCurrent();
	   virtual void GetCurrent(ClusterDisk *dataBuffer);
	   virtual ULONGLONG GetNumCurrentCluster();
};

#endif
