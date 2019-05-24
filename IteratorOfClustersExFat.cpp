//---------------------------------------------------------------------------

#pragma hdrstop

#include "IteratorOfClustersExFat.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
IteratorOfClustersExFat::IteratorOfClustersExFat(ExFat_FileSystemClass * myPtr)
{
	   myFsClassPtr = myPtr;
	   ClusterSize = myFsClassPtr->GetBytesPerCluster();
	   NumberOfClusters = myFsClassPtr->GetNumberOfClusters();
	   BufferCluster.cluster = new BYTE [ClusterSize];
	   BufferCluster.num_of_cluster = 2;
}
IteratorOfClustersExFat::~IteratorOfClustersExFat()
{
	   delete BufferCluster.cluster;
}
void IteratorOfClustersExFat::First(){
		NumCurrentCluster = 2;
}
void IteratorOfClustersExFat::Next(){
		NumCurrentCluster++;
}
bool IteratorOfClustersExFat::IsDone() const{
	   return (NumCurrentCluster >= NumberOfClusters);
}
ClusterDisk IteratorOfClustersExFat::GetCurrent()
{
	   myFsClassPtr->ReadClusters(NumCurrentCluster,ClusterSize,BufferCluster.cluster);
	   BufferCluster.num_of_cluster = NumCurrentCluster;
	   return BufferCluster;
}
ULONGLONG IteratorOfClustersExFat::GetNumCurrentCluster()
{
	   return NumCurrentCluster;
}
void IteratorOfClustersExFat::GetCurrent(ClusterDisk *dataBuffer){
	   myFsClassPtr->ReadClusters(NumCurrentCluster,ClusterSize,dataBuffer->cluster);
	   dataBuffer->num_of_cluster =  NumCurrentCluster;
}

