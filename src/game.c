#include "obj.h"
#include "struct.h"
#include "funct.h"
#include "def.h"

ROOM	*movement(char k, vect *p, ROOM *map){
vect	pos =*p, mv;
switch(k) {
case K_UP:		mv =(vect){-1, 0};	break;
case K_DOWN:		mv =(vect){ 1, 0};	break;
case K_LEFT:		mv =(vect){ 0,-1};	break;
case K_RIGHT:		mv =(vect){ 0, 1};	break;
case K_UP_LEFT:		mv =(vect){-1,-1};	break;
case K_UP_RIGHT:	mv =(vect){-1, 1};	break;
case K_DOWN_LEFT:	mv =(vect){ 1,-1};	break;
case K_DOWN_RIGHT:	mv =(vect){ 1, 1};	break;
default:				return map;}
if (map->cllsn[pos.y +mv.y][pos.x +mv.x] !='X'){
	if (map->cllsn[pos.y +mv.y][pos.x +mv.x] =='D'){
//printw("\nteleport detected");
	for (DOOR *d =map->door; d->y; d+=sizeof(DOOR))
	if (pos.y +mv.y ==d->y && pos.x +mv.x ==d->x){
		map =teleport(&pos, map, d); break;}}
	else{ pos.y +=mv.y; pos.x +=mv.x;}}
*p = pos; return map;}

ROOM	*teleport(vect *pos, ROOM *room, DOOR *d){
int	dstid =d->dstid;//" for some reason this line has to go first
ROOM	*nextroom =loadroom(d->dstpath);
for (d =nextroom->door; d->y && d->id!=dstid; d+=sizeof(DOOR));
if (!d->y){delroom(nextroom); return room;}
erasemap(*pos, room);
pos->y =d->y +d->offy;
pos->x =d->x +d->offx;
delroom(room); return nextroom;}
