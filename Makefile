all:   server.o main.o
	gcc  server.o main.o -o app

server.o: 
	gcc  -c server.c   

main.o:
	gcc -c main.c

clean: 
	rm -rf *.o app 
