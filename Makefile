liaotianshi: liaotianshi.o
	gcc liaotianshi.o  -o  liaotianshi
liaotianshi.o:liaotianshi.s
	gcc -c liaotianshi.s -o liaotianshi.o
liaotianshi.s:liaotianshi.i
	gcc -S liaotianshi.i -o liaotianshi.s
liaotianshi.i:liaotianshi.c
	gcc -E liaotianshi.c -o liaotianshi.i

.PHONY:clean
clean:
	-rm -f liaotianshi.o liaotianshi liaotianshi.s liaotianshi.i


