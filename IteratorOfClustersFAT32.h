//---------------------------------------------------------------------------

#ifndef IteratorOfClustersFAT32H
#define IteratorOfClustersFAT32H
//---------------------------------------------------------------------------
#include "FAT32Class.h"
#include "IteratorOfClusters.h"
class FAT32_FileSystemClass;
//---------------------------------------------------------------------------
class IteratorOfClustersFAT32 : public IteratorOfClusters
{
private:
	   FAT32_FileSystemClass * myFsClassPtr;
	   DWORD ClusterSize;
	   ULONGLONG NumCurrentCluster;
	   ULONGLONG NumberOfClusters;
	   ClusterDisk BufferCluster;
public:
	   IteratorOfClustersFAT32(FAT32_FileSystemClass * myPtr);
	   virtual ~IteratorOfClustersFAT32();
	   virtual void First();
	   virtual void Next();
	   virtual bool IsDone() const;
	   virtual ClusterDisk GetCurrent();
	   virtual void GetCurrent(ClusterDisk *dataBuffer);
	   virtual ULONGLONG GetNumCurrentCluster();
};
#endif
