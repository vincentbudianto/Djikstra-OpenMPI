CC=mpicc
# CFLAGS=-I$(IDIR)

ODIR=out

_OBJ = dijkstra
# OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# _NIM = 13517020
_NIM = 13517137

make: $(OBJ)
	$(CC) src/$(_OBJ).c -o out/$(_OBJ) && scp $(_OBJ) $(_NIM)@167.205.35.151:~ && scp $(_OBJ) $(_NIM)@167.205.35.152:~ && scp $(_OBJ) $(_NIM)@167.205.35.153:~ && scp $(_OBJ) $(_NIM)@167.205.35.154:~ && scp $(_OBJ) $(_NIM)@167.205.35.155:~