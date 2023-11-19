#include "struct.h"
#include "funct.h"
#include "def.h"

vect	movement(char c, vect pos, char **cllsnmap){
switch(c) {
case K_UP:
	if (map->cllsn[pos.y-1][pos.x]!='X')
		pos.y--; break;
case K_DOWN:
	if (map->cllsn[pos.y+1][pos.x]!='X')
		pos.y++; break;
case K_LEFT:
	if (map->cllsn[pos.y][pos.x-1]!='X')
		pos.x--; break;
case K_RIGHT:
	if (map->cllsn[pos.y][pos.x+1]!='X')
		pos.x++; break;
case K_UP_LEFT:
	if (map->cllsn[pos.y-1][pos.x-1]!='X'){
		pos.y--; pos.x--;} break;
case K_UP_RIGHT:
	if (map->cllsn[pos.y-1][pos.x+1]!='X'){
		pos.y--; pos.x++;} break;
case K_DOWN_LEFT:
	if (map->cllsn[pos.y+1][pos.x-1]!='X'){
		pos.y++; pos.x--;} break;
case K_DOWN_RIGHT:
	if (map->cllsn[pos.y+1][pos.x+1]!='X'){
		pos.y++; pos.x++;} break;
default:break;} return;}

ROOM	*teleportation(vect *pos, ROOM *map){
ROOM	*nextmap = NULL;
if (map->map[pos.y][pos.x] == '>' ||
	map->map[pos.y][pos.x] == '<' ||
	map->map[pos.y][pos.x] == 'Z')
	for (int i=0;i<map->tele_n;i++)
		if (pos.y == map->tele[i].y && pos.x == map->tele[i].x){
			//teleport
			printw("%s", map->tele[i].dstpath); getch();
			nextmap = loadroom(map->tele[i].dstpath);
			pos.y = map->tele[i].dsty;
			pos.x = map->tele[i].dstx;
			//erasemap(pos, map);
			delroom(map);}
return (nextmap?nextmap:map);}
