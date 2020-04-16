all: echo-server echo-client echo-client-signal echo-server-concur-fork echo-server-concur-thread echo-UDP-client echo-UDP-server beej-selectserver echo-client-select echo-server-select
echo-server: echo-server.o
	gcc -o echo-server echo-server.o
echo-server.o: echo-server.c
	gcc -c echo-server.c
echo-client: echo-client.o
	gcc -o echo-client echo-client.o
echo-client.o: echo-client.c
	gcc -c echo-client.c
echo-UDP-client: echo-UDP-client.o
	gcc -o echo-UDP-client echo-UDP-client.o
echo-UDP-server: echo-UDP-server.o
	gcc -o echo-UDP-server echo-UDP-server.o
echo-client-signal: echo-client-signal.o
	gcc -o echo-client-signal echo-client-signal.o
echo-client-signal.o: echo-client-signal.c
	gcc -c echo-client-signal.c
echo-server-concur-fork: echo-server-concur-fork.o
	gcc -o echo-server-concur-fork echo-server-concur-fork.o
echo-server-concur-thread: echo-server-concur-thread.o
	gcc -o echo-server-concur-thread echo-server-concur-thread.o -lpthread
beef-selectserver: beef-selectserver.o
	gcc -o beef-selectserver beef-selectserver.o
echo-sever-select: echo-sever-select.o
	gcc -o echo-sever-select echo-sever-select.o
echo-client-select: echo-client-select.o
	gcc -o echo-client-select echo-client-select.o
clean: 
	rm echo-server echo-client echo-client-signal echo-server-concur-fork echo-server-concur-thread echo-UDP-client echo-UDP-server beej-selectserver echo-client-select echo-server-select *.o
