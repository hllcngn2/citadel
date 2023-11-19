#include "struct.h"
#include <stdlib.h>//malloc free
char	*fgetstr(FILE *f, char delim){
int	i=0; while(fgetc(f)!=delim) i++;
char	*str = (char*)malloc(i+1);
fseek(f, -i-1, SEEK_CUR);
fread(str, 1, i, f); str[i]='\0';
return str;}

LINK	*loadlinks(char *path);
void	freelinks(LINK *links);


int	main(int ac, char **av){
puts("testing link structure and array...\n");
puts("- loading ---");
LINK	*links = loadlinks("links1"), *links2;
puts("- loading successful--\n");

puts(" - cycling through links array ---");
int	i=0;
for (LINK *l=links;l->y;l+=sizeof(LINK)){
	printf("- link no%02d:\n", i); i++;
	printf("%03d %03d %s %02d %d %d\n",
		l->y, l->x, l->dstpath, l->dstid, l->dsty, l->dstx);
}
puts("- finished cyclig --\n");

puts("- travelling through 1 link to links2 ---");
puts("finding the right link...");
vect	pos ={7,35};	i=0;
for (LINK *l=links; l->y; l+=sizeof(LINK)){
	if (pos.y ==l->y && pos.x ==l->x){
		printf("match found: link no%02d\n", i);
		printf("dstid = %02d\n", l->dstid);

		links2 = loadlinks(l->dstpath);
		pos.y = links2[l->dstid-1].y;
		pos.x = links2[l->dstid-1].x;
		printf("dst link pos = %03d %03d\n", pos.y, pos.x);

		pos.y += l->dsty;
		pos.x += l->dstx;
		printf("+offset pos = %03d %03d\n", pos.y, pos.x);

		puts("freeing links1");
		freelinks(links);
		links = links2;
	}	i++;
}
puts("- travelling successful ?\n");

puts(" - cycling through links2 array ---");
i=0;
for (LINK *l=links;l->y;l+=sizeof(LINK)){
	printf("- link no%02d:\n", i); i++;
	printf("%03d %03d %s %02d %d %d\n",
		l->y, l->x, l->dstpath, l->dstid, l->dsty, l->dstx);
}
puts("- finished cyclig --\n");

puts("- freeing link array ---");
freelinks(links);
puts("- freeing successful--");
puts("... end of link tests .");
return 0;}


// = function used =
LINK	*loadlinks(char *path){
printf("loading links from file \"%s\"\n", path);
FILE	*f = fopen(path, "r");

int	link_n;
fscanf(f, "%02d", &link_n);
printf("scanned link_n = %02d\n", link_n);
fgetc(f);

LINK	*links = (LINK*)malloc(sizeof(LINK)*(link_n+1));
links[link_n].y = 0;

for (LINK *l=links; link_n-->0; l+=sizeof(LINK)){
	printf("- link no%02d:\n", 4-link_n);
	fscanf(f, "%03d %03d ", &l->y, &l->x);
	printf("scanned: y=%03d x=%03d\n", l->y, l->x);
	l->dstpath = fgetstr(f, ' ');
	printf("scanned: dstpath=\"%s\"\n", l->dstpath);
	fscanf(f, " %02d %d %d", &l->dstid, &l->dsty, &l->dstx);
	printf("scanned: dstid=%02d dsty=%d dstx=%d\n",
		l->dstid, l->dsty, l->dstx);
	fgetc(f);}

fclose(f);
return links;}
void	freelinks(LINK *links){
free(links);
return;}
