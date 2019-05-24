//---------------------------------------------------------------------------

#pragma hdrstop

#include "IteratorOfClusters.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
IteratorOfClusters::IteratorOfClusters()
{
	   ClusterSize = 0;
	   NumberOfClusters = 0;
	   BufferCluster.cluster = NULL;
	   BufferCluster.num_of_cluster = 0;
}
IteratorOfClusters::~IteratorOfClusters()
{
	   delete[] BufferCluster.cluster;
}

