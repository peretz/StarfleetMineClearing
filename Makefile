make: source/main.cpp source/Field.cpp source/Script.cpp source/Simulation.cpp
	clang++ -o smc.out source/main.cpp source/Field.cpp source/Script.cpp source/Simulation.cpp -I ./
