lab6: obj/main.o obj/cmp_funcs.o obj/sort_funcs.o
	gcc obj/main.o obj/cmp_funcs.o obj/sort_funcs.o -o lab6 -g

obj/%.o: src/%.c
	gcc -g -c $< -o $@

draw:
	python3 graphs/create_dots.py
	python3 graphs/create_graph.py

clean:
	rm -f obj/*.o lab6
