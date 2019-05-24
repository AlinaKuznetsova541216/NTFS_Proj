//---------------------------------------------------------------------------

#pragma hdrstop

#include "IteratorOfClustersFAT32.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

IteratorOfClustersFAT32::IteratorOfClustersFAT32(FAT32_FileSystemClass * myPtr)
{
	   myFsClassPtr = myPtr;
	   ClusterSize = myFsClassPtr->GetBytesPerCluster();
	   NumberOfClusters = myFsClassPtr->GetNumberOfClusters();
	   BufferCluster.cluster = new BYTE [ClusterSize];
	   BufferCluster.num_of_cluster = 2;
}
IteratorOfClustersFAT32::~IteratorOfClustersFAT32()
{
	   delete BufferCluster.cluster;
}
void IteratorOfClustersFAT32::First(){
		NumCurrentCluster = 2;
}
void IteratorOfClustersFAT32::Next(){
		NumCurrentCluster++;
}
bool IteratorOfClustersFAT32::IsDone() const{
	   return (NumCurrentCluster >= NumberOfClusters);
}
ClusterDisk IteratorOfClustersFAT32::GetCurrent()
{
	   myFsClassPtr->ReadClusters(NumCurrentCluster,ClusterSize,BufferCluster.cluster);
	   BufferCluster.num_of_cluster = NumCurrentCluster;
	   return BufferCluster;
}
ULONGLONG IteratorOfClustersFAT32::GetNumCurrentCluster()
{
	   return NumCurrentCluster;
}
void IteratorOfClustersFAT32::GetCurrent(ClusterDisk *dataBuffer){
	   myFsClassPtr->ReadClusters(NumCurrentCluster,ClusterSize,dataBuffer->cluster);
	   dataBuffer->num_of_cluster =  NumCurrentCluster;
}


