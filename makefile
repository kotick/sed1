FILE=lab1_max_monty.cpp 
EXE=l1  

all: relase
	
relase:
	@echo 'Compilando $@'
	g++ $(FILE) -o $(EXE) -lm -std=c++0x
	@echo 'listo'

run:	
	@echo 'Ejecutando con banderas -i, -o y -l $@'
	./$(EXE) -i in.txt -o out.txt -l log.txt

