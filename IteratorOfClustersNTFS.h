//---------------------------------------------------------------------------

#ifndef IteratorOfClustersNTFSH
#define IteratorOfClustersNTFSH
//---------------------------------------------------------------------------
#include "NTFSClass.h"
#include "IteratorOfClusters.h"
class NTFS_FileSystemClass;
//---------------------------------------------------------------------------
class IteratorOfClustersNTFS : public IteratorOfClusters
{
private:
	   NTFS_FileSystemClass * myFsClassPtr;
	   DWORD ClusterSize;
	   ULONGLONG NumCurrentCluster;
	   ULONGLONG NumberOfClusters;
	   ClusterDisk BufferCluster;
public:
	   IteratorOfClustersNTFS(NTFS_FileSystemClass * myPtr);
	   virtual ~IteratorOfClustersNTFS();
	   virtual void First();
	   virtual void Next();
	   virtual bool IsDone() const;
	   virtual ClusterDisk GetCurrent();
	   virtual void GetCurrent(ClusterDisk *dataBuffer);
	   virtual ULONGLONG GetNumCurrentCluster();
};

#endif
