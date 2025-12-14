lab6: main.o cmp_funcs.o sort_funcs.o
	gcc main.o cmp_funcs.o sort_funcs.o -o lab6 -g

%.o: %.c
	gcc -g -c $< -o $@

clean:
	rm -f *.o lab6
