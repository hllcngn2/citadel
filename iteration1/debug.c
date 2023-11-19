#include <ncurses.h>

#include "maps.h"

int	main(int ac, char **av) {
Map	*map = loadmap("debug_map");
int	cpos[2];
cpos[0] = 10; cpos[1] = 18;

initscr(); noecho(); cbreak();
nodelay(stdscr, TRUE); refresh();
WINDOW	*mapw = newwin(LINES, COLS, 0, 0);

werase(mapw);
for(int i=0; i<map->siz[0]; i++)
	mvwaddnstr(mapw, LINES/2-cpos[0] + i, (COLS/2-cpos[1]>=0?COLS/2-cpos[1]:0),
		map->s + i*(map->siz[1]+1) -(COLS/2-cpos[1]<0?COLS/2-cpos[1]:0),
		(COLS/2-cpos[1]+map->siz[1]<COLS?map->siz[1]:map->siz[1]+(COLS-(COLS/2-cpos[1]+map->siz[1]))));
wrefresh(mapw);

while(getch()==ERR);

delmap(map);
delwin(mapw);
endwin();
return 0;}
