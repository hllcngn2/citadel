#include "obj.h"
#include "struct.h"
#include "funct.h"
#include "def.h"
#include "macro.h"
#include <stdlib.h>//malloc free
#include <string.h>//strdup strcpy/strcat
#include <stdio.h>
#include <ncurses.h>

char	*fgetstr(FILE *f, char delim){
int	i=0; while(fgetc(f)!=delim) i++;
char	*str = (char*)malloc(i+1);
fseek(f, -i-1, SEEK_CUR);
fread(str, 1, i, f); str[i]='\0';
return str;}


ROOM	*loadroom(char *path){		/*ROOM:loadroom*/
char	*full_path =(char*)malloc(PATH_MAX_L+1);
strcpy(full_path, PATH_MAP);
strcat(full_path, path);
FILE	*f = fopen(full_path, "r");
free(full_path);
ROOM	*room = (ROOM*)malloc(sizeof(ROOM));
room->path = strdup(path);
room->title = fgetstr(f, '\n'); fgetc(f);
fscanf(f, "%03d %03d", &room->h, &room->w); fgetc(f);
room->map = (char**)malloc(sizeof(char*)*room->h);
for (int i=0;i<room->h;i++)
	room->map[i] = (char*)malloc(room->w);
for (int i=0;i<room->h;i++){
	fread(room->map[i], 1, room->w, f); fgetc(f);}
room->cllsn = (char**)malloc(sizeof(char*)*room->h);
for (int i=0;i<room->h;i++)
	room->cllsn[i] = (char*)malloc(room->w);
for (int i=0;i<room->h;i++){
	fread(room->cllsn[i], 1, room->w, f); fgetc(f);}
//teleports
int	link_n; fscanf(f, "%02d", &link_n); fgetc(f);
room->door =(DOOR*)malloc(sizeof(DOOR)*(link_n+1));
room->door[link_n].y =0;
for (DOOR *l =room->door; link_n-->0; l+=sizeof(DOOR)){
	fscanf(f, "%02d %03d %03d %d %d ", &l->id,
		&l->y, &l->x, &l->offy, &l->offx);
	l->dstpath =fgetstr(f, ' ');
	fscanf(f, " %02d ", &l->dstid);
//printw("\nscanning tele#%02d: dstid=%02d", l->id, l->dstid);
//printw("\ndstpath=\"%s\"", l->dstpath);
//printw("\ny=%03d,x=%03d,offy=%d,offx=%d", l->y, l->x, l->offy, l->offx);
}
fclose(f); return room;}

void	delroom(ROOM *room){		/*ROOM:delroom*/
free(room->path);
free(room->title);
for(int i=0;i<room->h;i++)free(room->map[i]); free(room->map);  //todo: iterator
for(int i=0;i<room->h;i++)free(room->cllsn[i]); free(room->cllsn);
free(room->door);
free(room); return;}

void	delgs(Gamestate *gs){		/*GS:delgs*/
free(gs->nick);
delroom(gs->room);
free(gs); return;}

void	save(Gamestate *gs){		/*SAVE:save*/
FILE	*f = fopen("save", "w");
//player nick
fputs(gs->nick,f); fputc('\n',f);
//room path
fputs(gs->room->path,f); fputc('\n',f);
//player position
fprintf(f, "%03d %03d", gs->pos.y,gs->pos.x);
fclose(f); return;}

Gamestate	*newgame(void){
vect	toclr =drawmenu("001");
move(MID_Y,MID_X-4); curs_set(1);
char	*buf =(char*)malloc(10);
int i =0; char c;
while(i <10 && ((c =getch())!='\n'||i ==0)){	//todo: backspace
if (c ==27){ free(buf); return NULL;}
if ((c>='0'&&c<='9')||(c>='A'&&c<='Z')||(c>='a'&&c<='z')
   ||c=='^'||c=='~' ||c=='!' ||c=='?' ||c=='@' ||c=='&'){
	buf[i] =c; addch(c); i++;}}
char	*nick =(char*)malloc(i+1); nick[i] ='\0';
for (; i-->0; nick[i] =buf[i]); free(buf);
move(toclr.y,toclr.x); clrtobot(); curs_set(0);
//loading new game settings
Gamestate	*gs = (Gamestate*)malloc(sizeof(Gamestate));
gs->nick = nick;
gs->char_symbol =nick[0];
gs->room = loadroom("000");
gs->pos.y =10; gs->pos.x =8; return gs;}

Gamestate	*loadsave(void){	/*SAVE:load*/
FILE	*f =fopen("save", "r");
if (!f) return NULL;
Gamestate	*gs =(Gamestate*)malloc(sizeof(Gamestate));
gs->nick =fgetstr(f, '\n'); fgetc(f);
char	*roompath =fgetstr(f, '\n');
fscanf(f, " %03d %03d", &gs->pos.y, &gs->pos.x);
fclose(f);
//loading corresponding stuff
gs->char_symbol =gs->nick[0];
gs->room =loadroom(roompath);
free(roompath); return gs;}

Ui	*createui(void){		/*UI:create*/
Ui	*ui =(Ui*)malloc(sizeof(Ui));
ui->w_title =newwin(3,42, 0,0);
ui->w_room =newwin(12,16, 2,0);
ui->w_dialog =newwin(4,70, LINES-3,(LINES<16?15:(COLS-70)/2));

ui->w_menu =newwin(LINES+1,//(LINES-6>30?30:LINES-6),	//example menus
		70,//(COLS-20>80?80:COLS-20),		//history scrollup
		0,//LINES/2-(LINES-6>30?30:LINES-6)/2,	//centered big menu
		(COLS-70)/2);//COLS/2-(COLS-20>80?80:COLS-20)/2);
ui->w_alert =newwin(3,40, LINES/2-3,COLS/2-20);	//simple alert
box(ui->w_title, 0, 0);
box(ui->w_room, 0, 0);
box(ui->w_dialog, 0, 0);
box(ui->w_menu, 0, 0);
box(ui->w_alert, 0, 0); return ui;}

void	freeui(Ui *ui){
delwin(ui->w_title);
delwin(ui->w_room);
delwin(ui->w_dialog);
delwin(ui->w_menu);
delwin(ui->w_alert); free(ui); return;}
