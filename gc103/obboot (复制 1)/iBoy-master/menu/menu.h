#ifndef MENU_H_
#define MENU_H_

typedef void (*pFunc)();

struct menu {
	char **strings;
	pFunc *funcs;
	char *attr;
	//struct menu **psubmenu;
	int len;
	int vis;
};

struct menu smainmenu;
struct menu sloadmenu;
struct menu ssavemenu;
struct menu sconfmenu;
struct menu sconfselmenu;


void enter_menu();

void do_return();
void do_exit();
void do_romselect();
void do_saveselect();
void do_loadselect();
void do_romselect_cleanup();

void do_reset();
void do_saveconfig();
void do_saveconfig_rom();

void config_menu();


extern void submenu_cleanup();


// MAIN MENU //
char *main_menu_strings[] = {
	"iBoy-0.7.5.4",

	"Leave Menu",
	"Load Rom\xff",
	"Load\xff",
	"Save\xff",
	"Config\xff",
	"Reset Game",
	"Exit iBoy"
};

pFunc main_menu_funcs[] = {
	do_return,
	do_romselect,
	do_loadselect,
	do_saveselect,
	config_menu,
	do_reset,
	do_exit
};

///////////////


#endif /*MENU_H_*/
