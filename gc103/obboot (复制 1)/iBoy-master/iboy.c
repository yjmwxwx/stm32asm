/*
 * iBoy - A GameBoy (tm) Emulator for iPod (tm), based on gnuBoy
 * Copyright (C) 2005
 *
 * Fellni, Ducky
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <signal.h>
#include <time.h>
#include <ctype.h>
#include <fcntl.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/soundcard.h>


#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>



#include "loader.h"
#include "emu.h"
#include "input.h"
#include "sound.h"
#include "disas.h"
#include "cop.h"

#include "sys/lcdll.h"
#include "sys/kb.h"
#include "sys/nix.h"
#include "sys/config.h"


extern void enter_menu();

extern int emu_running;


int __CTOR_LIST__;
int __DTOR_LIST__;



static void shutdown()
{
	cop_end();

	pcm_close();
	kb_close();

	#ifndef PORTABLE
		sys_ipod_cleanup();
	#endif

	fflush(stdout);
	fflush(stderr);
}

void die(char *fmt, ...)
{
	va_list ap;

//	shutdown();	  // fixme is exit enough?
	va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
    exit(0);
}

void vdie(char *fmt, va_list ap)
{
//	shutdown();	  // fixme is exit enough?
    vprintf(fmt, ap);
    exit(0);
}

static int bad_signals[] =
{
	/* These are all standard, so no need to #ifdef them... */
	SIGINT, SIGSEGV, SIGTERM, SIGFPE, SIGABRT, SIGILL,
#ifdef SIGQUIT
	SIGQUIT,
#endif
#ifdef SIGPIPE
	SIGPIPE,
#endif
	0
};

static void fatalsignal(int s)
{
	die("Signal %d\n", s);
}

static void catch_signals()
{
	int i;
	for (i = 0; bad_signals[i]; i++)
		signal(bad_signals[i], fatalsignal);
}

FILE *lcd_file = NULL;

extern char *config_file;


void iboy_init(char *rom, char *path)
{
	const char * cp[] = { "./iboy.cfg", "/mnt/iboy.cfg", "/hp/iboy.cfg", "/etc/iboy.cfg"};
	int i;


	atexit(shutdown);
	catch_signals();

	/* iPod Generation specific initialisations */
	kb_init();
#ifndef PORTABLE
#ifndef USE_TEXTMENU
	sys_ipod_init();
#endif
#endif

	if(blitter_init()) die("blitter setup died!");

#ifdef PORTABLE
	printf("open lcd...\n");
	lcd_file = fopen("/roms/1.bmp", "rb+");
	if(!lcd_file) die("no compatibility possible... I better die");
#endif

	i = 0;
	do {
		config_file = (char *)(cp[i++]);
	} while(!config_load(0) && i<4);

	if(!romdir) romdir = get_current_dir_name();
	if(!savedir) savedir = get_current_dir_name();

	if(rom && path) {
		romfile = strdup(rom);
		romdir = strdup(path);
	}


	cop_init();  // FIXME COP
	pcm_init();

	while(1) {

		enter_menu();
		/* where the fun begins */

		while(!loader_init()) {
			emu_running = 1;
			emu_reset();
			cop_begin();
			emu_run();
			cop_end();
			loader_unload();
		}
	}


	/* never reached */
}



int main(int argc, char **argv)
{

	//printf("\n\nloading iboy...\n\npress any key...\n\n");
	//fflush(stdout);
	//getchar();

#ifdef PORTABLE
	#ifdef KB_PORTABLE
	set_input_mode();
	#endif
#endif

//	stdout = fopen("/stdout.txt", "w+");
//	stderr = fopen("/stderr.txt", "w+");

	if(argc==2) {
		iboy_init(argv[1], "/roms/");	// that ain't clever
	}
	else if(argc==3) {
		iboy_init(argv[1], argv[2]);
	}
	else {
		iboy_init(NULL, NULL);
	}

	return 0;
}


void new_iboy_window()
{
		iboy_init(NULL, NULL);
}
