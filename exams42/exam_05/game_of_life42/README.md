must work: echo "wasdx" | ./life width height iteration

w: up
a: left
s: down
d: right
x: start/stop writing (at the beginning of the writing pen is not writing)

life: 'O'
dead: ' '

default situation must be written by reading the command from stdin
next generation's situatiation:
	life cell has < 2 live neighbors ---> die
	life cell has 2 or 3 live neighbors ---> live
	life cell has > 3 live neighbors ---> die

	dead cell has 3 live neighbors ---> live

ex.:

echo "dxss" | ./life 3 3 0 | cat -e
 O $
 O $
 O $


echo "dxss" | ./life 3 3 1 | cat -e
   $
OOO$
   $

allowed functions: read putchar malloc calloc free
