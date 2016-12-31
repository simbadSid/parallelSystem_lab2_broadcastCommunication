
all: $(EXEC)
CC=smpicc
RUN=smpirun
BINDIR=bin/
SRCDIR=src/
INPUT_FILE_PATH=data/input/
CFLAGS  = -g -Wall -Werror -MP -MMD -DCONFIG_DEBUG
LDFLAGS  = -lm

HOST_FILE_NAME=hostfile_$(NBR_PROCESS).txt
HOST_FILE=$(INPUT_FILE_PATH)$(HOST_FILE_NAME)
PLATFORM_FILE_NAME=ring_$(NBR_PROCESS).xml
PLATFORM_FILE=$(INPUT_FILE_PATH)PLATFORM_FILE_NAME




NBR_PROCESS=50




#-----------------------------------------------------------------------------------------------------------
# ----------------------------------------------- Executions -----------------------------------------------
#-----------------------------------------------------------------------------------------------------------
exec_naive_bcast:		$(BINDIR)bcast_skeleton exec_prepareData
						$(RUN) --cfg=smpi/bcast:mpich -np $(NBR_PROCESS) -hostfile $(HOST_FILE) -platform $(PLATFORM_FILE) $(BINDIR)bcast_skeleton naive_bcast


exec_ring_bcast:		$(BINDIR)bcast_skeleton exec_prepareData
						$(RUN) --cfg=smpi/bcast:mpich -np $(NBR_PROCESS) -hostfile $(HOST_FILE) -platform $(PLATFORM_FILE) $(BINDIR)bcast_skeleton ring_bcast


exec_default_bcast:		$(BINDIR)bcast_skeleton exec_prepareData
						$(RUN) --cfg=smpi/bcast:mpich -np $(NBR_PROCESS) -hostfile $(HOST_FILE) -platform $(PLATFORM_FILE) $(BINDIR)bcast_skeleton default_bcast


exec_prepareData:
						python $(SRCDIR)generate_xml_ring_and_hostfile.py $(NBR_PROCESS); \
						mv $(HOST_FILE_NAME) $(HOST_FILE); \
						mv $(PLATFORM_FILE_NAME) $(PLATFORM_FILE)


#-----------------------------------------------------------------------------------------------------------
# ----------------------------------------------- Executable -----------------------------------------------
#-----------------------------------------------------------------------------------------------------------
$(BINDIR)bcast_skeleton:$(BINDIR)bcast_skeleton.o $(BINDIR)bcast_solution.o $(BINDIR)tools.o
						$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)


#-----------------------------------------------------------------------------------------------------------
# ----------------------------------------------- Modules  -------------------------------------------------
#-----------------------------------------------------------------------------------------------------------
$(BINDIR)%.o:			$(SRCDIR)%.c
						$(CC) -O3 -c -o $@ $^



#-----------------------------------------------------------------------------------------------------------
# ------------------------------------------ General Methods -----------------------------------------------
#-----------------------------------------------------------------------------------------------------------
.PHONY	: clean mrproper
clean:
	rm -f $(BINDIR)*
mrproper: clean
	rm -rf $(HOST_FILE) $(PLATFORM)
