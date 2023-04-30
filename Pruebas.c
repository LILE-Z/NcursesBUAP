#include <ncurses.h>
#include <string.h>

void StartM(WINDOW *menu_win,char *mesg,char *art);    
void MenuG(WINDOW *menu_win);
int main() {
   char mesg[]="Just a string";            /* message to be appeared on the screen */
  // Inicializar ncurses
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  // Obtener tamaño de la pantalla
  int screen_width, screen_height;
  getmaxyx(stdscr, screen_height, screen_width);

  // Calcular tamaño de las cajas
  int box_width = screen_width / 2;
  int box_height = screen_height;

  // Crear la primera caja
  WINDOW *box1 = newwin(box_height, box_width, 0, 0);
  keypad(box1, TRUE);
  refresh();
  box(box1, 0, 0);
  wrefresh(box1);

  // Crear la segunda caja
  WINDOW *box2 = newwin(box_height, box_width, 0, box_width);
  refresh();
  box(box2, 0, 0);
  StartM(box2,mesg,"");
  wrefresh(box2);
  MenuG(stdscr);
  // Esperar por input del usuario
  getch();

  // Limpiar y salir
  delwin(box1);
  delwin(box2);
  endwin();
  return 0; }
void MenuG(WINDOW *menu_win){
    int choice=0;
    int c;
    choice=1;
    wprintw(menu_win,"fjf %d",choice);
    while (1)
    { c=wgetch(menu_win);
      switch (c){
       case KEY_RIGHT:
        if (choice==2)
        {
          choice=0;
        }
        else{
            ++choice;
        }
        wprintw(menu_win,"Welcome to the game %i\n",choice);
        break;
       case KEY_LEFT:
        if (choice==0)
        {
          choice=2;
        }else{
            --choice;
        }
        wprintw(menu_win,"Welcome to the game %i\n",choice);
        break;
         case 10:   
          wprintw(menu_win,"Bye %i\n",choice);
        break;
      }
       
    }
    
    printw("Welcome to the game %i\n",choice);
    
}
void StartM( WINDOW *menu_win,char *mesg,char *art){
  
  mvwprintw(menu_win, 1,2,"%s\n", mesg); //parametros: ventana, y, x, string
  mvwprintw(menu_win,2,2,"  /\\_/\\\n");
   mvwprintw(menu_win,3,2," ( o.o )\n");
    mvwprintw(menu_win,4,2,"  > ^ <\n");
}