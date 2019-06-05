#include <stdio.h>
#include <ncurses.h>
#include "vkb.h"

#define WIDTH 30
#define HEIGHT 10
WINDOW *mainwin;
int startx = 0;
int starty = 0;

void vkb_init(){
  initscr();
  clear();
  noecho();
  cbreak();
  startx = (80 - WIDTH) / 2;
  starty = (24 - HEIGHT ) / 2;
  mainwin = newwin(WIDTH,HEIGHT,startx,starty);
  keypad(mainwin,TRUE);
  refresh();
}

void *vkb_runthread( void *arg ){ 

  int curkey = -1;
  while(1){
    curkey = wgetch(mainwin);
    if( curkey < 130 && keyfreq[curkey] != 0 ){
      mvprintw(24, 0, "'%c' => %fHz", curkey, keyfreq[curkey]);  
      refresh();
    }
  }

}

int main(int argc, char *argv[]){
  vkb_init();
  vkb_runthread(NULL);
}
