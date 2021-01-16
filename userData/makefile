

cflags = -std=c++11

objects =  test.cpp t_main.cpp t_Astar.cpp t_bfs.cpp t_cell.cpp t_cli.cpp t_command.cpp t_controler.cpp t_Demo.cpp t_generator.cpp t_heuristic.cpp t_maze.cpp t_model.cpp t_searchable.cpp t_state.cpp t_view.cpp t_zip.cpp

all: $(objects)
	g++ $(objects) -o main.exe

%.o: %.cpp
	g++ $(cflags) -c $< -o $@

clean:
	rm -rf *.o *.exe

rebuild: clean all