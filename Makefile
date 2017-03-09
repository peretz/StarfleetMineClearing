make: source/main.cpp source/Field.cpp source/Script.cpp
	clang++ -o smc.out source/main.cpp source/Field.cpp source/Script.cpp -I ./
