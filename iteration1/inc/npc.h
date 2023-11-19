#ifndef NPC_H
#define NPC_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
	char	*map;
	int	pos[2];
	int	spot[2];
	int	range[2];
	char	*name;
} Npc;

Npc	**loadnpc();
void	freenpc();

#endif
