#ifndef CONFIG_VARS_H_
#define CONFIG_VARS_H_

#include "lcdll.h"
#include "config.h"

struct map_s map_lcd_mini_modes[5] = {
	{ "VIS_LEFT", LCD_MODE_MINI_LEFT },
	{ "VIS_MID", LCD_MODE_MINI_MID },
	{ "VIS_RIGHT", LCD_MODE_MINI_RIGHT },
	{ "X-SCALE", LCD_MODE_MINI_SCALE },
	{ 0, 0 }
};

struct map_s map_lcd_modes[5] = {
	{ "VIS_TOP", LCD_MODE_VIS_TOP },
	{ "VIS_MID", LCD_MODE_VIS_MID },
	{ "VIS_BOT", LCD_MODE_VIS_BOT },
	{ "SCALE", LCD_MODE_SCALE },
	{ 0, 0 }
};

struct map_s map_gb_keys[14] = {
	{ "IGNORE", 0 },
	{ "PAD_RIGHT", 1 },
	{ "PAD_LEFT", 2 },
	{ "PAD_UP", 4 },
	{ "PAD_DOWN", 8 },
	{ "PAD_A", 16 },
	{ "PAD_B", 32 },
	{ "PAD_SELECT", 64 },
	{ "PAD_START", 128 },
	{ "PAD_RIGHT_UP", 5 },
	{ "PAD_RIGHT_DOWN", 9 },
	{ "PAD_LEFT_UP", 6 },
	{ "PAD_LEFT_DOWN", 10 },
	{ 0, 0 }
} ;

struct map_s map_oss_speed[12] = {
	{ "50%", 50 },
	{ "70%", 70 },
	{ "80%", 80 },
	{ "90%", 90 },
	{ "95%", 95 },
	{ "100%", 100 },
	{ "105%", 105 },
	{ "110%", 110 },
	{ "120%", 120 },
	{ "150%", 150 },
	{ "200%", 200 },
	{ 0, 0 }
};

/*	notice that the index of pushmap
 * 	refers to the bitnr of 4g state
 */
 
extern int oss_enabled;
extern int oss_speed;
extern int oss_volume;

extern int backlight;
extern int contrast;
extern int *lcd_modep;

extern char *romdir;
extern char *savedir;
extern char *romfile;


extern int push_map[5];
extern int touch_map[8];
extern int spec_combo[32];



struct config_var variables[] = {
	{ &romdir, "romdir", STR_T, 0 ,0,0,0},
	{ &savedir, "savedir", STR_T, 0 ,0,0,0 },
	{ (void*) LCD_MODE_P, "lcd_mode", MAP_T, map_lcd_modes ,0,3,700},
	{ (void*) LCD_MINI_MODE_P, "mini_h_mode", MAP_T, map_lcd_mini_modes ,0,3,700},
	{ &oss_enabled, "oss_enabled", INT_T, 0 ,0,1,700},
	{ &oss_volume, "oss_volume", INT_T, 0 ,0,100,4},
	{ &oss_speed, "oss_speed", MAP_T, map_oss_speed ,0, 10,400},
	{ &backlight, "backlight", INT_T, 0 ,0,1,0},
	{ &contrast, "contrast", INT_T, 0 ,47,127,16},

	{ &push_map[0], "kb_center", MAP_T, map_gb_keys ,0,13,500},
	{ &push_map[1], "kb_right", MAP_T, map_gb_keys ,0,13,500},
	{ &push_map[2], "kb_left", MAP_T, map_gb_keys ,0,13,500},
	{ &push_map[3], "kb_down", MAP_T, map_gb_keys ,0,13,500},
	{ &push_map[4], "kb_up", MAP_T, map_gb_keys ,0,13,500},
	
	{ &spec_combo[0x06], "kb_left_right", MAP_T, map_gb_keys ,0,13,500},
	{ &spec_combo[0x18], "kb_up_down", MAP_T, map_gb_keys ,0,13,500},

	{ &touch_map[0], "kb_t0", MAP_T, map_gb_keys ,0,13,500},
	{ &touch_map[1], "kb_t1", MAP_T, map_gb_keys ,0,13,500},
	{ &touch_map[2], "kb_t2", MAP_T, map_gb_keys ,0,13,500},
	{ &touch_map[3], "kb_t3", MAP_T, map_gb_keys ,0,13,500},
	{ &touch_map[4], "kb_t4", MAP_T, map_gb_keys ,0,13,500},
	{ &touch_map[5], "kb_t5", MAP_T, map_gb_keys ,0,13,500},
	{ &touch_map[6], "kb_t6", MAP_T, map_gb_keys ,0,13,500},
	{ &touch_map[7], "kb_t7", MAP_T, map_gb_keys ,0,13,500},
	
	{ &romfile, "romfile", STR_T, 0 ,0,0,0},
	
	{ 0, 0, 0, 0, 0, 0 ,0 } 
} ;



#endif /*CONFIG_VARS_H_*/
