#ifndef __KB_H__
#define __KB_H_


typedef void (*pSense_kb)(byte *press, byte *touch);  

// these values are for 4g and newer other gens simulate these values

#define IPOD_LEFT	0x04
#define IPOD_RIGHT	0x02
#define IPOD_UP		0x10
#define IPOD_DOWN	0x08
#define IPOD_CENTER	0x01

#define IPOD_HOLD	0x80


void kb_setup(int reset);
void kb_init();
int kb_getch();
void kb_close();
void kb_poll();
int kb_gethold();
void kb_combo_reset();

void sense_kb_3g(byte *press, byte *touch); 
void sense_kb_mini(byte *press, byte *touch);
void sense_kb_std(byte *press, byte *touch); 


#endif
