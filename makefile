_OBJ = dijkstra

_NIM1 = 13517020
_NIM2 = 13517137

make:
	mpicc src/$(_OBJ).c -o $(_OBJ)$/
	scp $(_OBJ) $(_NIM1)@167.205.35.150:~$/
	scp $(_OBJ) $(_NIM1)@167.205.35.151:~$/
	scp $(_OBJ) $(_NIM1)@167.205.35.152:~$/
	scp $(_OBJ) $(_NIM1)@167.205.35.153:~$/
	scp $(_OBJ) $(_NIM1)@167.205.35.154:~$/
	scp $(_OBJ) $(_NIM1)@167.205.35.155:~$/
	scp $(_OBJ) $(_NIM2)@167.205.35.150:~$/
	scp $(_OBJ) $(_NIM2)@167.205.35.151:~$/
	scp $(_OBJ) $(_NIM2)@167.205.35.152:~$/
	scp $(_OBJ) $(_NIM2)@167.205.35.153:~$/
	scp $(_OBJ) $(_NIM2)@167.205.35.154:~$/
	scp $(_OBJ) $(_NIM2)@167.205.35.155:~$/

run:
	mpirun -np 6 --hostfile mpi_hostfile --bind-to core:overload-allowed dijkstra 100