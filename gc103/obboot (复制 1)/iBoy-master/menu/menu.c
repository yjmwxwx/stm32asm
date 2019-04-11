

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

#include "menu.h"

#include "../lcd.h"
#include "../loader.h"
#include "../emu.h"
#include "../save.h"
#include "../sys/oss.h"
#include "../sys/config.h"
#include "../cop.h"

#include "../sys/config.h"
#include "../sys/nix.h"
#include "../sys/kb.h"
#include "../sys/graphics.h"
#include "../sys/nix.h"


#define MIN(x, y) (((x)<(y))?(x):(y))


struct menu *curmenu;
int ireturn = 0;
int cur_selected = 0;

struct config_var *cur_var;
int old_cfg_selected = 0;
int old_rom_selected = 0;
char *old_rom_path = 0;


#define MAX_VIS 9


extern void sound_dirty();

void menu_init()
{
	smainmenu.strings = main_menu_strings;
	smainmenu.funcs = main_menu_funcs;
	smainmenu.attr = 0;
	smainmenu.len = sizeof(main_menu_strings)/4-1;
	smainmenu.vis = MAX_VIS;
	curmenu = &smainmenu;
}


void submenu_cleanup()
{
	int i;

	for(i=0;i<=curmenu->len;i++) {
		if(curmenu->strings[i]) free(curmenu->strings[i]);
		curmenu->strings[i] = 0;
	}

	if (curmenu->strings) free(curmenu->strings);
	if (curmenu->funcs) free(curmenu->funcs);
	if (curmenu->attr) free(curmenu->attr);

	curmenu->strings = 0;
	curmenu->funcs = 0;
	curmenu->attr = 0;
	curmenu->len = 0;

	curmenu = &smainmenu;
}

void submenu_init(struct menu *pm, char *title)
{
	pm->strings = malloc(2 * sizeof(char *));  // should be free here
	pm->funcs = malloc(sizeof(pFunc));  // should be free here
	pm->attr = malloc(2);

	pm->strings[0] = strdup(title);
	pm->attr[0] = 0;
	pm->strings[1] = strdup("< Back");
	pm->attr[1] = 0;

	pm->funcs[0] = submenu_cleanup;
	pm->len = 1;
	pm->vis = MAX_VIS;
	cur_selected = 0;
	curmenu = pm;
}


void menu_draw(int selected)
{
	int i, sel, ilen, mod;
	int cursor = selected, offset = 0;
	char p[15], *s;

	draw_rect(16, 16, 144, 120, 0);
	if(selected<0) return;
	draw_string(16, 17, curmenu->strings[0], 1);

	if(cursor >= curmenu->vis) {
		cursor = selected%curmenu->vis;
		offset = selected-cursor;
	}

	for(i=0; (i<curmenu->vis) && (i+offset<curmenu->len); i++) {
		if(i==cursor) sel = 1;
		else sel = 0;
		memset(p, ' ', 14);
		p[14] = 0;
		s = curmenu->strings[offset+i+1];
		ilen = 0;
		mod = 0;
		if(curmenu->attr){
			switch(curmenu->attr[offset+i+1]) {
				case 0:
					break;
				case 2:
					mod = 2;
					ilen = 2;
					p[1] = '\xfe'; // Directory Icon
					break;
				default:
					ilen = 2;
					p[1] = '*'; 		// other Icon
					break;
			}
		}

		memcpy(p+1+ilen, s, MIN(12-ilen, strlen(s)));
		if(strlen(s) > 12-ilen) {
			p[12] = 255;
		}
		draw_string(24, 32+8*i, p, sel | mod);

	}
	draw_refresh();
}


void menu_execute(int selected)
{
	if(curmenu->funcs[selected] != 0)
		curmenu->funcs[selected]();
}


void do_saveconfig() { config_save(NULL); }
void do_saveconfig_rom()
{
	char *d, *r, *c;

	r = config_get_s("romfile");
	d = config_get_s("romdir");
	if(old_rom_path)
		d = old_rom_path;
	c = malloc(strlen(d) + strlen(r) + 2);
	strcpy(c, d);
	strcat(c, r);

	strcpy(c + strlen(c) - (3+(r[strlen(r)-1] == 'c')), ".cfg");
	config_save(c);
	free(c);
}


void do_return()
{
	ireturn = 1;
	cop_begin();
}



void wait_nohold()
{
	usleep(50*1000);				//FIXME ugly debounce
	err_msg("Remove Hold%c", 0, 255);
	while(kb_gethold()) usleep(15*1000);
	usleep(50*1000);
}


void do_exit()
{
	exit(0);
}


void do_romload()
{
	char *p = sloadmenu.strings[cur_selected+1];
	char *d, *c;

	old_rom_selected = cur_selected;

	err_msg("Loading\xff", 0);
	config_load("/etc/iboy.cfg");

	config_set_s("romfile", p);

	d = get_current_dir_name();

	if(old_rom_path) {
		free(old_rom_path);
	}

	old_rom_path = get_current_dir_name();

	//config_get_s("romdir");
	c = malloc(strlen(d) + strlen(p) + 2);
	free(d);
	strcpy(c, d);
	strcat(c, p);
	strcpy(c + strlen(c) - (3+(p[strlen(p)-1] == 'c')), ".cfg");
	config_load(c);
	free(c);
	submenu_cleanup();
	emu_reload();
	ireturn = 1;
}


void do_reset()
{
	if(config_isempty_s("romfile")) return;
	emu_reload();
	ireturn = 1;
}


int myalphasort(const void *a, const void *b)
{
	struct dirent *c = *(struct dirent**) a;
	struct dirent *d = *(struct dirent**) b;

	char e = c->d_type; //c->d_name[strlen(c->d_name)+1];
	char f = d->d_type; //d->d_name[strlen(d->d_name)+1];

	if((e==DT_DIR) && (f!=DT_DIR)) return -1;
	if((e!=DT_DIR) && (f==DT_DIR)) return 1;

	return strcmp(c->d_name, d->d_name);
}

int filter_gb(const struct dirent *p)
{
	//return 1;
	return !strcasecmp(p->d_name+strlen(p->d_name)-3, ".gb") ||
	!strcasecmp(p->d_name+strlen(p->d_name)-4, ".gbc") || p->d_type==DT_DIR;
}

int filter_dir(const struct dirent *p)
{
	return p->d_type==DT_DIR;
}


pFunc select_func=0;

void file_menu(char *path, char *title,  int(*filter)(const struct dirent *), pFunc action)
{
	struct dirent **nl;
	int n;

	submenu_init(&sloadmenu, title);

	chdir(path);

	n = sys_scandir(".", &nl, filter, myalphasort);

	if(n<0) {
		if(!path) err_msg("(null) dir", 4000);
		else if(!*path) err_msg("(zero) dir", 4000);
		else {
			err_msg("inval %s", 4000, path);
		}
		submenu_cleanup();
	} else {
		if(select_func) {
			sloadmenu.funcs[0] = select_func;
			if(sloadmenu.strings[1]) free(sloadmenu.strings[1]);
			sloadmenu.strings[1] = get_current_dir_name();
		}

		sloadmenu.strings = realloc(sloadmenu.strings, (2+n) * sizeof(char *));
		sloadmenu.funcs = realloc(sloadmenu.funcs, (1+n) * sizeof(pFunc));
		sloadmenu.attr = realloc(sloadmenu.attr, 2+n);
		sloadmenu.len = n+1;

		while(n--) {
			sloadmenu.strings[n+2] = strdup(nl[n]->d_name);
			if(nl[n]->d_type==DT_DIR) {
				sloadmenu.attr[n+2] = 2;
			}
			else{
				sloadmenu.attr[n+2] = 0;
			}


			sloadmenu.funcs[n+1] = action;
			free(nl[n]);
		}
		free(nl);
	}
}

void browse()
{
	DIR *d;
	char *p = strdup(sloadmenu.strings[cur_selected+1]);
	char *s;

	if( (d = opendir(p)) ) {
		closedir(d);
		submenu_cleanup();
		file_menu(p, "   Select Rom   ", filter_gb, browse);
	} else {
		s = get_current_dir_name();
		config_set_s("romdir", s);
		free(s);
		do_romload();
	}
	free(p);
}

void browse_dirs()
{
	char *p = strdup(curmenu->strings[cur_selected+1]);
	submenu_cleanup();
	file_menu(p, "   Select Dir   ", filter_dir, browse_dirs);
	free(p);
}

void config_change()
{
	//struct config_var *p = getvar(name);
	int val = cur_var->minval+cur_selected;

	switch(cur_var->typ) {
		case INT_T:
			config_set_i(cur_var->name, val);
		break;
		case STR_T: break;
		case MAP_T:
			*((int *)cur_var->p) = cur_var->map[val].val;
		break;
	}

	config_apply(0);
	submenu_cleanup();  //cleanup sets menu to mainmenu
						//as we have more menu levels
	curmenu = &sconfmenu;	//set curmenu manual (this is needed to clean up
							//the previous menu level!!!!
	cur_selected = old_cfg_selected;
}



void config_dir_set()
{
	select_func = 0;
	config_set_s(cur_var->name, get_current_dir_name());
	submenu_cleanup();
}

void config_dir()
{
	char *s = config_get_s(cur_var->name);
	select_func = config_dir_set;
	file_menu(s, "   Select Dir   ", filter_dir, browse_dirs);
}

void cfg_change()
{
	//config_change(sconfmenu.strings[cur_selected+1]);
	int i,n=0;
	char *name = sconfmenu.strings[cur_selected+1];
	int val=0;
	char s[128];
	old_cfg_selected = cur_selected;
	cur_var = getvar(name);
	char blanks[17] = "                ";

	if(gettype(name) != STR_T) {
		val = cur_var->minval;
		n = cur_var->maxval - cur_var->minval + 1;
	}else{
		n = 1;
	}

	memcpy(blanks+(16-MIN(16, strlen(name)))/2, name, MIN(strlen(name),16));
	submenu_init(&sconfselmenu, blanks);


	sconfselmenu.strings = realloc(sconfselmenu.strings, (1+n) * sizeof(char *));
	sconfselmenu.funcs = realloc(sconfselmenu.funcs, (n) * sizeof(pFunc));
	sconfselmenu.attr = 0;
	sconfselmenu.len = n;

	i=0;
	while(i<n) {
		switch(gettype(name)) {
			case INT_T:
				sprintf(s,"%5d",val+i);
				sconfselmenu.strings[i+1] = strdup(s);
				sconfselmenu.funcs[i] = config_change;
			break;
			case STR_T:
				sconfselmenu.strings[i+1] = strdup(config_get_s(name));
				sconfselmenu.funcs[i] = config_dir;
			break;
			case MAP_T:
				sconfselmenu.strings[i+1] = strdup(cur_var->map[val+i].str);
				sconfselmenu.funcs[i] = config_change;
			break;
		}

		i++;
	}
	switch(gettype(name)) {
			case INT_T:
				cur_selected = config_get_i(name)-val;
			break;
			case STR_T:
			break;
			case MAP_T:
				cur_selected = config_get_mapindex(cur_var);
			break;
	}
}

void config_menu()
{
	int i,n=0;

	submenu_init(&sconfmenu, " Configuration  ");

	while(variables[n++].name);
	n--;

	sconfmenu.strings = realloc(sconfmenu.strings, (2+n+2) * sizeof(char *));
	sconfmenu.funcs = realloc(sconfmenu.funcs, (1+n+2) * sizeof(pFunc));
	sconfmenu.attr = 0;
	sconfmenu.len = n+3;

	sconfmenu.strings[2] = strdup("SaveForRom");
	sconfmenu.funcs[1] = do_saveconfig_rom;
	sconfmenu.strings[3] = strdup("SaveGlobal");
	sconfmenu.funcs[2] = do_saveconfig;

	i=0;
	while(i<n) {
		sconfmenu.strings[i+4] = strdup((variables[i]).name);
		sconfmenu.funcs[i+3] = cfg_change;
		i++;
	}
}


void do_romselect()
{
	char *romdir = config_get_s("romdir");
	if(old_rom_path)
		romdir = old_rom_path;
	file_menu(romdir, "   Select Rom   ", filter_gb, browse);

	cur_selected = old_rom_selected;
}


void do_save()
{
	FILE *f = NULL;

	err_msg("Saving\xff", 0);

	f = fopen2(config_get_s("savedir"), curmenu->strings[cur_selected+1], "w+");
	if(!f) 	err_msg("Could not open file", 4000);
	else {
		savestate(f);
		fclose(f);
		err_msg("Game Saved", 1400);
	}

	submenu_cleanup();
	ireturn = 1;
	cop_begin();
}


void do_saveselect()
{
	int i;
	char *p, *romfile;

	if(config_isempty_s("romfile")) return;
	romfile = config_get_s("romfile");

	submenu_init(&sloadmenu, "   Save Slot    ");
	sloadmenu.strings = realloc(sloadmenu.strings, 12 * sizeof(char *));
	sloadmenu.funcs = realloc(sloadmenu.funcs, 11 * sizeof(pFunc));
	sloadmenu.attr = 0;

	for(i=0; i<10; i++) {
		sloadmenu.strings[i+2] = malloc(strlen(romfile) + 4); //xxx.gb -> xxx_3.sav
		sloadmenu.funcs[i+1] = do_save;
		p = sloadmenu.strings[i+2];
		strcpy(p, romfile);
		sprintf(p+strlen(p)-3, "_%1d.sav", i);
	}

	sloadmenu.len = 11;
	curmenu = &sloadmenu;
}


extern void mem_updatemap();
extern byte patdirty[];

void do_load()
{
	FILE *f = NULL;

	err_msg("Loading\xff", 0);

	f = fopen2(config_get_s("savedir"), curmenu->strings[cur_selected+1], "r");
	if(!f) 	err_msg("Could not open file", 4000);
	else {
		err_msg("Load State...", 100);
		loadstate(f);
		fclose(f);

		lcd_reset();

		sound_dirty();
		mem_updatemap();
		err_msg("ready", 100);
	}

	submenu_cleanup();
	ireturn = 1;
	cop_begin();
}


int filter_sav(const struct dirent *p)
{
	char *romfile = config_get_s("romfile");

	if(!strcasecmp(p->d_name+strlen(p->d_name)-4, ".sav"))
		return !strncasecmp(p->d_name, romfile, strlen(romfile)-3);
	return 0;
}

void do_loadselect()
{
	if(config_isempty_s("romfile")) return;
	file_menu(config_get_s("savedir"), "   Load Slot    ", filter_sav, do_load);
}



void enter_menu()
{
	int c;

	cop_end();

	menu_init();
	wait_nohold();
	ireturn = 0;

	while(!ireturn) {
		menu_draw(cur_selected);
		c = kb_getch();

		switch(c) {
			case 'l': cur_selected-=9; break;
			case 'm': cur_selected--; break;
			case 'r': cur_selected+=9; break;
			case 'd': cur_selected++; break;
			case 'h':
				wait_nohold();
				cur_selected = 0;
			case '\n': menu_execute(cur_selected); break;
		}

		if(cur_selected<0) cur_selected=curmenu->len-1;
		else if(cur_selected>=curmenu->len) cur_selected = 0;
	}

	//cop_begin(); do this somewhere else !  (in do_return and after emu_reload)
}
