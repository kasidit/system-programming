objects = hellomain.o hellosub1.o \
	  hellosub2.o

hello: $(objects)
	gcc -o hello $(objects)
hellomain.o: 
hellosub1.o: hello1.h
hellosub2.o: 

.PHONY: clean
clean: 
	rm hello $(objects)
