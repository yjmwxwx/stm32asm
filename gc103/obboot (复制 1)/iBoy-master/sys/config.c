
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "config.h"
#include "config_vars.h"
#include "nix.h"
#include "kb.h"
#include "graphics.h"
#include "../pcm.h"
#include "../dyntrans/compiler_defs.h"

char *config_file;

int config_load(char *filename)
{
	FILE *fconfig;
	char line[260];
	char *p;
	
//	if(config_file) free(config_file);
//	config_file = strdup(file);

	if(!filename || !*filename)	
		filename = config_file;
	
//	err_msg(filename, 200);
	
	fconfig = fopen(filename, "r");
	
	if(!fconfig){
		//err_msg("fail", 200);	
		return 0;
	}
	//err_msg("loaded", 200);
	
	kb_combo_reset(); 
	
	while(fgets(line, 256, fconfig)) {
		remove_space(line);
		if((p = strchr(line, '='))) {
			*p++ = 0; //make two strings out of one	
					
			switch(gettype(line)) {
				case INT_T: config_set_i(line, atoi(p)); break;
				case STR_T: config_set_s(line, p); break;
				case MAP_T: config_set_mapped(line, p); break;
			}
		}
	}

	fclose(fconfig);
	config_apply(1);
	return 1;
}

int config_save(char *filename)
{
	int i=0;
	struct config_var *p;
	FILE * f;
	char s[256];
	
	//err_msg("Saving...", 0);
	
	if(!filename || !*filename)	
		filename = config_file;
	
	err_msg(filename, 1000);
	f = fopen(filename, "w+");
	
	if(!f) {
		err_msg("fail", 1000);
		return 1;
	}
	err_msg("saved", 1000);

	p = &(variables[i++]);
	
	while(p->name) {
		switch(p->typ) {
			case INT_T: sprintf(s, "%s=%i\n", p->name, *(int*)(p->p)); break;
			case STR_T: 
				if(*(char**)(p->p)) sprintf(s, "%s=%s\n", p->name, *(char**)(p->p)); 
				else sprintf(s, "%s=\n", p->name);
			break;
			case MAP_T: 
				sprintf(s, "%s=%s\n", p->name, config_get_mapname(p)); 
			break;
		}
		
		fputs(s, f);
		p = &(variables[i++]);
	}	
	
	fclose(f);
	return 0;
}



struct config_var *getvar(char *name) 
{
	int i=0;
	char *p;
	
	while((p = variables[i].name)) {
		if(!strcmp(name, variables[i].name))
			return 	&variables[i];
		i++;
	}
	
	return NULL;
}

char * config_get_mapname(struct config_var *p)
{
	int n = 0;
	while(p->map[n++].str) 
		if(p->map[n-1].val == *(int *)(p->p)) {		
			return p->map[n-1].str; 
		}
	return NULL;
}

int config_get_mapindex(struct config_var *p)
{
	int n = 0;
	while(p->map[n++].str) 
		if(p->map[n-1].val == *(int *)(p->p)) {		
			return n-1; 
		}
	return 0;
}

extern void pcm_close();
extern void pcm_init();
extern void kb_init();


void config_apply(char silently)
{
	int i,j;
	
	sys_set_backlight(backlight);
	sys_set_contrast(contrast);	
	pcm_init();

	if(oss_enabled && !silently)
		for(j=0;j<200;j++) {
			for(i=0;i<256;i++)
			 	pcm.buf[i] = (short) cycles_table[i] << 10;
			pcm.pos = 256;
			pcm_submit();
		}
		
	kb_setup(1);

}


int gettype(char *name) {
	struct config_var *p = getvar(name);
	if(p) return p->typ;
	return NOT_T;
}

void *getp(char *name) {
	struct config_var *p = getvar(name);
	if(p) return p->p;
	return NULL;
}	

void config_set_i(char *name, int val) 
{ 
	int *p = (int *) getp(name);
	if(p) *p = val; 
}	

int config_get_i(char *name) 
{ 
	int *p = (int *) getp(name);
	if(p) return *p;
	return 0; 
}

void config_set_s(char *name, char *dupme) 
{ 
	char **p = (char **) getp(name);
	if(p) {
		if(*p) free(*p);
		*p = strdup(dupme);
	}
}	

char *config_get_s(char *name) 
{ 
	char **p = (char **) getp(name);
	if(p) return *p;
	return NULL; 
}

int config_isempty_s(char *name)
{
	char **p = (char **) getp(name);
	
	return !(p && *p && **p);  // name correct, string allocated and not empty
}


void config_set_mapped(char *name, char *findme) 
{ 
	int *val = (int *) getp(name);
	char *p;
	struct map_s *map;
	int i;
	
	if(val) {
		map = getvar(name)->map;
		i = 0;
		while((p = map[i++].str)) 
			if(!strcmp(p, findme)) *val = map[i-1].val;
	}
}



int remove_space(char *s)
{
	char *p1 = s, *p2 = s;
	char *p;	
	int cnt=0;

	if(!s && !*s) return 0;

	if((p = strchr(s, '#'))) *p = 0; // remove comments
	
	while(*p1) {
		if(!isspace(*p1)) {
			*p2 = *p1;
			p2++;
		} else cnt++;
		p1++;
	}
	
	*p2 = 0;	
	
	return cnt;
}
