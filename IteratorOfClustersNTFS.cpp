//---------------------------------------------------------------------------

#pragma hdrstop

#include "IteratorOfClustersNTFS.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

IteratorOfClustersNTFS::IteratorOfClustersNTFS(NTFS_FileSystemClass * myPtr)
{
	   myFsClassPtr = myPtr;
	   ClusterSize = myFsClassPtr->GetBytesPerCluster();
	   NumberOfClusters = myFsClassPtr->GetNumberOfClusters();
	   BufferCluster.cluster = new BYTE [ClusterSize];
	   BufferCluster.num_of_cluster = 0;
}
IteratorOfClustersNTFS::~IteratorOfClustersNTFS()
{
	   delete BufferCluster.cluster;
}
void IteratorOfClustersNTFS::First(){
		NumCurrentCluster = 0;
}
void IteratorOfClustersNTFS::Next(){
		NumCurrentCluster++;
}
bool IteratorOfClustersNTFS::IsDone() const{
	   return (NumCurrentCluster >= NumberOfClusters);
}
ClusterDisk IteratorOfClustersNTFS::GetCurrent()
{
	   myFsClassPtr->ReadClusters(NumCurrentCluster,ClusterSize,BufferCluster.cluster);
	   BufferCluster.num_of_cluster = NumCurrentCluster;
	   return BufferCluster;
}
ULONGLONG IteratorOfClustersNTFS::GetNumCurrentCluster()
{
	   return NumCurrentCluster;
}
void IteratorOfClustersNTFS::GetCurrent(ClusterDisk *dataBuffer){
	   myFsClassPtr->ReadClusters(NumCurrentCluster,ClusterSize,dataBuffer->cluster);
	   dataBuffer->num_of_cluster =  NumCurrentCluster;
}
