CC=g++ # compilador, troque para gcc se preferir utilizar C
CFLAGS=-Wall -g #-Wextra # compiler flags, troque o que quiser, exceto bibliotecas externas
EXEC=./tp2 # nome do executavel que sera gerado, nao troque
TMPOUT=tp2.testresult
BUILD=./build/
SRC=./src/
INCLUDE=./include/
JOGODIM=JogoDiamantes/

$(EXEC):	$(BUILD)main.o $(BUILD)$(JOGODIM)Ourives.o 
	$(CC) $(CFLAGS) -o $(EXEC) $(BUILD)main.o $(BUILD)$(JOGODIM)*.o 

$(BUILD)main.o:	$(SRC)main.cpp $(BUILD)$(JOGODIM)Ourives.o  
	$(CC) $(CFLAGS) -I $(INCLUDE)$(JOGODIM) -c $(SRC)main.cpp -o $(BUILD)main.o

$(BUILD)$(JOGODIM)Ourives.o: $(SRC)$(JOGODIM)Ourives.cpp $(INCLUDE)$(JOGODIM)Ourives.hpp $(BUILD)$(JOGODIM)Diamante.o
	$(CC) $(CFLAGS) -I $(INCLUDE)$(JOGODIM) -c $(SRC)$(JOGODIM)Ourives.cpp -o $(BUILD)$(JOGODIM)Ourives.o

$(BUILD)$(JOGODIM)Diamante.o: $(SRC)$(JOGODIM)Diamante.cpp $(INCLUDE)$(JOGODIM)Diamante.hpp 
	$(CC) $(CFLAGS) -I $(INCLUDE)$(JOGODIM) -c $(SRC)$(JOGODIM)Diamante.cpp -o $(BUILD)$(JOGODIM)Diamante.o

test:	$(EXEC)
	@bash run_tests.sh $(EXEC) $(TMPOUT)

clean:
	rm -f $(BUILD)*/*.o

mem:
	valgrind --leak-check=full --show-leak-kinds=all $(EXEC) ./testcases/EX0