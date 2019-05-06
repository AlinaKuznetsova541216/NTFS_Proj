//---------------------------------------------------------------------------

#ifndef IteratorOfClustersH
#define IteratorOfClustersH
#include "NTFSClass.h"
#include "Iterator.h"
//---------------------------------------------------------------------------
class IteratorOfClusters : public Iterator<BYTE *>
{
private:
	NTFS_FileSystemClass * myFsClassPtr;
	DWORD ClusterSize;
	ULONGLONG NumCurrentCluster;
	ULONGLONG NumberOfClusters;
	BYTE * BufferCluster;
public:
	IteratorOfClusters(NTFS_FileSystemClass * myPtr);
	virtual ~IteratorOfClusters();
	virtual void First();
	virtual void Next();
	virtual bool IsDone() const;
	virtual BYTE * GetCurrent();
	virtual void GetCurrent(BYTE **dataBuffer);
	virtual ULONGLONG GetNumCurrentCluster();
};
#endif
