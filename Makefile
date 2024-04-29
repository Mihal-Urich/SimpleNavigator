all: install test run
	
style:
	clang-format -style=Google -n src/*.cc

test: clean install
	cd build && ./G_Test
	cd build && ./GA_Test

install:
	mkdir build
	cd build && cmake .. && cmake --build .

s21_graph.a: install
	cp build/libs21_graph.a src/

s21_graph_algorithms.a: install
	cp build/libs21_graph_algorithms.a src/

uninstall:
	rm -rf build

rebuild: uninstall install

clean:
	rm -rf build
	rm -rf src/libs21_graph_algorithms.a src/libs21_graph.a

run:
	cd build && ./main

