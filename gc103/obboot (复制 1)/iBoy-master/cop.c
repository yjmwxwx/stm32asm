

#include "cop.h"
#include "lcd.h"
#include "hw.h"

#include "sys/nix.h"
#include "sys/lcdll.h"
#include "sys/graphics.h"


int cop_execute(void (*function)())
{
	hw_info info;

	outl((unsigned int)function, IBOY_COP_HANDLER);

	sys_ipod_hw_info(&info);

	if(info.version==0x03)
		outs(0xce, 0xcf004058);
	else
		outl(0x0, 0x60007004);  //COP WAKEUP

	return 1;
}


void cop_lcd_handler()
{
#ifdef USE_COP
	while (!COP_STOPPED)
		lcd_refreshline();
#endif
}

#ifndef OLD_KERNEL
	void cop_lcd_gbc_handler()
	{
	#ifdef USE_COP
		while (!COP_STOPPED)
			lcd_gbc_refreshline();
	#endif
	}
#endif // OLD_KERNEL

void cop_init()
{
#ifdef USE_COP
	outl(0, IBOY_COP_STATUS);  	// Not sure the dogs understand
#endif							// We assume cop to be free here
}

void cop_begin()
{
#ifdef USE_COP

	//err_msg("cop startup", 0);

	COP_SETSTOP(0);

#ifndef OLD_KERNEL
	if(hw.cgb /*&& sys_ipod_is_color()*/)
		cop_execute(cop_lcd_gbc_handler);
	else
#endif
		cop_execute(cop_lcd_handler);

	while(!(inl(IBOY_COP_STATUS) & IBOY_COP_RUNNING))
		;

#endif
}


void cop_end()
{
#ifdef USE_COP
	COP_SETSTOP(1);

	while((inl(IBOY_COP_STATUS) & IBOY_COP_RUNNING))
		;

	//err_msg("cop stopped", 0);
#endif
}
