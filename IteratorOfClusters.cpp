//---------------------------------------------------------------------------

#pragma hdrstop

#include "IteratorOfClusters.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
IteratorOfClusters::IteratorOfClusters(NTFS_FileSystemClass * myPtr)
{
	myFsClassPtr = myPtr;
	ClusterSize = myFsClassPtr->GetBytesPerCluster();
	NumberOfClusters = myFsClassPtr->GetNumberOfClusters();
	NumCurrentCluster = 0;
	BufferCluster = new BYTE[ClusterSize];
}
IteratorOfClusters::~IteratorOfClusters()
{
	delete BufferCluster;
}
void IteratorOfClusters::First(){
	 NumCurrentCluster = 0;
}
void IteratorOfClusters::Next(){
	 NumCurrentCluster++;
}
bool IteratorOfClusters::IsDone() const{
	return (NumCurrentCluster >= NumberOfClusters);
}
BYTE * IteratorOfClusters::GetCurrent()
{
	myFsClassPtr->ReadClusters(NumCurrentCluster,ClusterSize,BufferCluster);
	return BufferCluster;
}
ULONGLONG IteratorOfClusters::GetNumCurrentCluster()
{
	return NumCurrentCluster;
}
void IteratorOfClusters::GetCurrent(BYTE **dataBuffer){
	myFsClassPtr->ReadClusters(NumCurrentCluster,ClusterSize,*dataBuffer);
}