#ifndef BCAST_SOLUTION_H
#define BCAST_SOLUTION_H


#include <mpi.h>
#include <string.h>



void broadcast(char *bcast_implementation_name, char *message, unsigned int messageSize, int num_procs, int rank);




#endif
