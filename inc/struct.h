#ifndef STRUCT_H
#define STRUCT_H
#include "obj.h"
#include <ncurses.h>

typedef struct{
	int	y;
	int	x;} vect;
typedef struct{
	int	h;
	int	w;} size;


typedef struct{
	WINDOW	*w_title;
	WINDOW	*w_room;
	WINDOW	*w_dialog;

	WINDOW	*w_menu;
	WINDOW	*w_alert;} Ui;
//menus
//WINDOW	*menu_hist;
//alerts
//WINDOW	*alert_exit;
//terminal window should be at least h13 w78
//or h16 w63 to fit all of the base ui windows
//(when bottom width was 64)


typedef struct{
	vect	pos;
	char	char_symbol;
	char	*nick;

	ROOM	*room;} Gamestate;

#endif
