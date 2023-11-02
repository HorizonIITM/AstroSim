CCFLAGS=-O3

CCFLAGS_DEBUG=-g -Og -fsanitize=address

build:
	g++ $(CCFLAGS) -c simulation_code/body.cpp      				-o assemblies/body.o 
	g++ $(CCFLAGS) -c simulation_code/differentialEquations.cpp  	-o assemblies/differentialEquations.o
	g++ $(CCFLAGS) -c simulation_code/integrators.cpp 				-o assemblies/integrators.o
	g++ $(CCFLAGS) -c simulation_code/utils.cpp       				-o assemblies/utils.o
	g++ $(CCFLAGS) -o sim.exe simulation_code/main.cpp assemblies/differentialEquations.o assemblies/body.o assemblies/integrators.o assemblies/utils.o

debug:
	g++ $(CCFLAGS_DEBUG) -c simulation_code/body.cpp      				-o assemblies/body.o 
	g++ $(CCFLAGS_DEBUG) -c simulation_code/differentialEquations.cpp  	-o assemblies/differentialEquations.o
	g++ $(CCFLAGS_DEBUG) -c simulation_code/integrators.cpp 				-o assemblies/integrators.o
	g++ $(CCFLAGS_DEBUG) -c simulation_code/utils.cpp       				-o assemblies/utils.o
	g++ $(CCFLAGS_DEBUG) -o sim.exe simulation_code/main.cpp assemblies/differentialEquations.o assemblies/body.o assemblies/integrators.o assemblies/utils.o

run: build
	./sim.exe "outfile.txt" "infile.txt" 20000 0.01

plot:
	python3 plotting/plot.py "outfile.txt"

clean:
	rm -f assemblies/*.o
	rm -f outfile.txt
	rm -f sim.exe

runplot: run plot

buildrunplot: build run plot
