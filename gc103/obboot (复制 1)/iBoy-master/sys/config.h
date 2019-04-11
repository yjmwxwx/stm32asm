#ifndef CONFIG_H_
#define CONFIG_H_

#define STR_T 0
#define CHR_T 1
#define INT_T 4
#define MAP_T 64
#define NOT_T 255

extern char * config_file;

typedef unsigned char type_t;

struct config_var {
	void *p;
	char *name;
	type_t typ;
	struct map_s *map;
	int minval;
	int maxval;
	int msgdelay;
};
//extern struct config_var *cur_var;
//extern int cur_selected;	

struct map_s {
	char *str;	
	int val;
} ;

void config_apply(char silently);
int config_load(char *file);
int config_save(char *filename);
void config_set_i(char *name, int val);
int config_get_i(char *name);
char *config_get_s(char *name);
int config_isempty_s(char *name);
void config_set_s(char *name, char *dupme);
void config_set_mapped(char *name, char *findme);
void config_change();
char * config_get_mapname(struct config_var *p);
struct config_var *getvar(char *name);
int gettype(char *name);
void *getp(char *name);
int config_get_mapindex(struct config_var *p);
int remove_space(char *);

extern struct config_var variables[];

#endif /*CONFIG_H_*/
