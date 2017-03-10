CLANG=clang++

OBJECTS = main.o Field.o Script.o Simulation.o

StartFleetMineClearing: $(OBJECTS)
	$(CLANG) -o StarFleetMineClearing.out $(OBJECTS) -I ./

main.o : source/main.cpp
	$(CLANG) -c source/main.cpp
Field.o : source/Field.cpp source/Field.h
	$(CLANG) -c source/Field.cpp
Script.o : source/Script.cpp source/Script.h
	$(CLANG) -c source/Script.cpp
Simulation.o : source/Simulation.cpp source/Simulation.h
	$(CLANG) -c source/Simulation.cpp
.PHONY: clean
clean :
	rm StarFleetMineClearing.out $(OBJECTS)
