build:
	g++ -c simulation_code/body.cpp      				-o assemblies/body.o 
	g++ -c simulation_code/differentialEquations.cpp  	-o assemblies/differentialEquations.o
	g++ -c simulation_code/utils.cpp       				-o assemblies/utils.o
	g++ -o sim.exe simulation_code/main.cpp assemblies/differentialEquations.o assemblies/body.o assemblies/utils.o

run: build
	sim.exe "outfile.txt" "infile.txt" 20000 0.01

plot:
	python plotting/plot.py "outfile.txt"

clean:
	rm assemblies/*.o
	rm outfile.txt
	rm sim.exe

runplot: run plot

buildrunplot: build run plot
