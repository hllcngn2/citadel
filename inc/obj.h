#ifndef OBJ_H
#define OBJ_H

typedef struct{
	int	id,dstid;
	int	y,x;
	int	offy,offx;
	char	*dstpath;
}DOOR;

typedef struct{
	int	h,w;
	char	*path;
	char	*title;
	char	**map;
	char	**cllsn;
	DOOR	*door;
}ROOM;

//character:
// position -> vect
// (symbol) -> cursor appearance
//?nick -> player -> str
//color -> cp1 defined on launch
//effect -> buff/modifiers
//movement buff

#endif
