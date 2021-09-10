objects = hellomain.o hellosub1.o \
	  hellosub2.o

hello: $(objects)
	gcc -o hello $(objects)
hellomain.o: hellomain.c
	gcc -c hellomain.c
hellosub1.o: hellosub1.c hello1.h
	gcc -c hellosub1.c
hellosub2.o: hellosub2.c
	gcc -c hellosub2.c

clean: 
	rm hello $(objects)
