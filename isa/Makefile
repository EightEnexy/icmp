CPPFLAGS = -g -std=c++17 -fpermissive -Wall -Wextra
COMPILE = g++ $(CPPFLAGS)

secret:	secret.o client.o prog_parse.o
	$(COMPILE) $^ -o $@

secret.o: secret.cpp prog_parse.h
	$(COMPILE) -c $<

client.o: client.cpp client.h
	$(COMPILE) -c $<

prog_parse.o: prog_parse.cpp prog_parse.h
	$(COMPILE) -c $<


clean:
	rm -f *.o