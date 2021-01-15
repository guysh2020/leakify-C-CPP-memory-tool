

cflags = -std=c++11

objects =  main.cpp Astar.cpp bfs.cpp cell.cpp cli.cpp command.cpp controler.cpp Demo.cpp generator.cpp heuristic.cpp maze.cpp model.cpp searchable.cpp state.cpp view.cpp zip.cpp

all: $(objects)
	g++ $(objects) -o main.exe

%.o: %.cpp
	g++ $(cflags) -c $< -o $@

clean:
	rm -rf *.o *.exe

rebuild: clean all