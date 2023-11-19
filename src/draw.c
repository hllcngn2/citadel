#include "obj.h"
#include "struct.h"
#include "def.h"
#include "macro.h"
#include <string.h>//strlen
#include <stdlib.h>//malloc

void	space(int y,int x, int n){
move(y,x);
for (; n-->0;) addch(' ');
return;}
void	to_be_spaced(int y,int x, const char *s, int n){
//->mvprintw
//->struct x y n
//->add to list
//->spaced call to space all of the lines in the list
return;}
int	print_centered(vect offset, char *s){
int	offx =MID_X +offset.x -strlen(s)/2;
mvprintw(MID_Y +offset.y,offx, s);
return offx;}


vect	drawmenu(const char *fname){
char	*path =(char*)malloc(PATH_MAX_L+1);
strcpy(path, PATH_MENU);
strcat(path, fname);
FILE	*f =fopen(path, "r"); free(path);
vect	offset;
fscanf(f, "%i %i ", &offset.y,&offset.x);
vect	toclr; toclr.y =offset.y;
char *line =NULL; size_t l;
for (; getline(&line, &l, f)!=-1; offset.y++)
	if (offset.y!=toclr.y)
		print_centered(offset, line);
	else {	toclr.y +=MID_Y;
		toclr.x =print_centered(offset, line);}
free(line); fclose(f); return toclr;}

void	getoffsets(vect pos, size map, vect *m_o, vect *p_a, vect *m_c){
vect	map_offset; //in the map buffer
vect	print_area; //  "   offsets
vect	map_corner; //on the screen
if (pos.y > LINES/2){		//player being centered
	map_offset.y = pos.y-LINES/2; //this means
	map_corner.y = 0;}	//the map exceeds the screen
else {	map_offset.y = 0;	//towards the top or left
	map_corner.y = LINES/2-pos.y;}
if (pos.x > COLS/2){
	map_offset.x = pos.x-COLS/2;
	map_corner.x = 0;}
else {	map_offset.x = 0;
	map_corner.x = COLS/2-pos.x;}
//how much can we print without exceeding bottom/right boundaries
if (map.h-map_offset.y > LINES-map_corner.y)
	print_area.y = LINES-map_corner.y;
else print_area.y = map.h-map_offset.y;
if (map.w-map_offset.x > COLS-map_corner.x)
	print_area.x = COLS-map_corner.x;
else print_area.x = map.w-map_offset.x;
*m_o = map_offset;
*p_a = print_area;
*m_c = map_corner; return;}

void	drawmap(vect pos, ROOM *map){
vect	map_offset, print_area, map_corner;
getoffsets(pos, (size){map->h,map->w}, &map_offset, &print_area, &map_corner);
for (int i=0; i<print_area.y; i++)
	mvaddnstr(map_corner.y+i, map_corner.x,
		map->map[i+map_offset.y]+map_offset.x, print_area.x);
refresh(); return;}

void	erasemap(vect pos, ROOM *map){
vect	map_offset, print_area, map_corner;
getoffsets(pos, (size){map->h,map->w}, &map_offset, &print_area, &map_corner);
for (int i=0; i<print_area.y; i++)
	space(map_corner.y+i,map_corner.x, print_area.x);
refresh(); return;}

void	refreshui(Ui *ui){
wrefresh(ui->w_title);
wrefresh(ui->w_room);
wrefresh(ui->w_dialog);
//wrefresh(ui->w_menu);
//wrefresh(ui->w_alert);
return;}
