#
rp:ppt
	./ppt
rn:Menu
	./Menu
ra:animacion
	./animacion
ppt: ppt.c
	gcc -o ppt  ppt.c -l ncurses
Menu: Menu.c
	gcc -o Menu Menu.c -l ncurses
animacion: animacion.c
	gcc -o animacion animacion.c -l ncurses
clean:
	rm -f ppt 