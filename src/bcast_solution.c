#include "bcast_solution.h"






void naive_bcast(char *message, unsigned int messageSize, int num_procs, int rank)
{
	int i;

	if (rank == 0)
	{
		for (i=1; i<num_procs; i++)
		{
			MPI_Send(message, messageSize, MPI_CHAR, i, 0, MPI_COMM_WORLD);
		}
	}
	else
	{
		MPI_Recv(message, messageSize, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
}


void ring_bcast(char *message, unsigned int messageSize, int num_procs, int rank)
{
	if (rank != 0)
		MPI_Recv(message, messageSize, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	if (rank != num_procs-1)
		MPI_Send(message, messageSize, MPI_CHAR, rank+1, 0, MPI_COMM_WORLD);
}


void default_bcast(char *message, unsigned int messageSize, int num_procs, int rank)
{
	MPI_Bcast(message, messageSize, MPI_CHAR, 0, MPI_COMM_WORLD);
}


void broadcast(char *bcast_implementation_name, char *message, unsigned int messageSize, int num_procs, int rank)
{
	if		(!strcmp(bcast_implementation_name, "naive_bcast"))								naive_bcast	(message, messageSize, num_procs, rank);
	else if	(!strcmp(bcast_implementation_name, "ring_bcast"))								ring_bcast	(message, messageSize, num_procs, rank);
	else if	(!strcmp(bcast_implementation_name, "default_bcast"))							default_bcast(message,messageSize, num_procs, rank);
/*	else if	(!strcmp(bcast_implementation_name, "pipelined_ring_bcast"))
	else if	(!strcmp(bcast_implementation_name, "asynchronous_pipelined_ring_bcast"))
	else if	(!strcmp(bcast_implementation_name, "asynchronous_pipelined_bintree_bcast"))
*/

}

