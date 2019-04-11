#ifndef __COP_H_
#define __COP_H_


#define COP_SETSTOP(s) outb(s, &(hiramcopy->cop_stop))
#define COP_STOPPED inb(&(hiramcopy->cop_stop))	

int cop_execute(void (*function)());

void cop_init();
void cop_begin();
void cop_end();

#define IBOY_DMA_BUFFER		0x40000040

#define IBOY_COP_HANDLER 	0x4001501C
#define IBOY_COP_STATUS 	0x40015020

#define IBOY_COP_RUNNING	(1 << 0)


#endif
