motif_example_2:	motif_example_2.o
			cc -L/usr/local/lib -O -o motif_example_2 motif_example_2.o -lXm -lXt -lX11

motif_example_2.o:	motif_example_2.c
			cc -I/usr/local/include -c motif_example_2.c
