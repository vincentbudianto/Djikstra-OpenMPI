CC=mpicc
# CFLAGS=-I$(IDIR)

ODIR=out

_OBJ = dijkstra
# OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

hellomake: $(OBJ)
	$(CC) src/$(_OBJ).c -o out/$(_OBJ)
