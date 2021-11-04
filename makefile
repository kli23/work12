all: dirinfo.o
	gcc -o dirinfo dirinfo.o
dirinfo.o: dirinfo.c
	gcc -c dirinfo.c
run:
	./dirinfo $(ARGS)
clean:
	rm dirinfo
	rm *.o