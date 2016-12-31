#include "tools.h"









/*
 * Abort, printing the usage information only if the
 * first argument is non-NULL (and hopefully set to argv[0]), and
 * printing the second argument regardless.
 */
void program_abort(char *exec_name, char *message)
{
	int my_rank;
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	if (my_rank == 0)
	{
		if (message)
		{
			fprintf(stderr,"%s",message);
		}
		if (exec_name)
		{
			print_usage(exec_name);
		}
	}
	MPI_Abort(MPI_COMM_WORLD, 1);
	exit(1);
}

/**
 * Print the usage information
 */
void print_usage(char *exec_name)
{
	int my_rank;
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);

	if (my_rank == 0)
	{
		fprintf(stderr,"Usage: smpirun --cfg=smpi/bcast:mpich -np <num processes>\n");
		fprintf(stderr,"              -platform <XML platform file> -hostfile <host file>\n");
		fprintf(stderr,"              %s <bcast implementation name> [-c <chunk size>]\n",exec_name);
		fprintf(stderr,"MPIRUN arguments:\n");
		fprintf(stderr,"\t<num processes>: number of MPI processes\n");
		fprintf(stderr,"\t<XML platform file>: a Simgrid platform description file\n");
		fprintf(stderr,"\t<host file>: MPI host file with host names from the platform file\n");
		fprintf(stderr,"PROGRAM arguments:\n");
		fprintf(stderr,"\t<bcast implementation name>: the name of the broadcast implementaion (e.g., naive_bcast)\n");
		fprintf(stderr,"\t[-c <chunk size>]: chunk size in bytes for message splitting (optional)\n");
		fprintf(stderr,"\n");
	}
	return;
}
