CPPFLAGS = -g -std=c++17 -O3 -fpermissive -Wall -Wextra 
COMPILE = g++ $(CPPFLAGS) -lcrypto

secret:	secret.o client.o prog_parse.o server.o protocol.o
	$(COMPILE) $^ -o $@

secret.o: secret.cpp prog_parse.h protocol.h
	$(COMPILE) -c $<

client.o: client.cpp client.h
	$(COMPILE) -c $<

server.o: server.cpp server.h
	$(COMPILE) -c $<

protocol.o: protocol.cpp protocol.h
	$(COMPILE) -c $<	 

prog_parse.o: prog_parse.cpp prog_parse.h
	$(COMPILE) -c $<

clean:
	rm -f *.o