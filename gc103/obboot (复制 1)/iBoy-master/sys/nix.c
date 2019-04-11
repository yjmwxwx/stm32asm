/*
 * nix.c
 *
 * System interface for *nix systems.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <linux/kd.h>
#include <sys/signal.h>
#include <sys/fcntl.h>
#include <termios.h>


#include "nix.h"
#include "lcdll.h"

#define FBIOGET_CONTRAST	_IOR('F', 0x22, int)
#define FBIOSET_CONTRAST	_IOW('F', 0x23, int)

#define FBIOGET_BACKLIGHT	_IOR('F', 0x24, int)
#define FBIOSET_BACKLIGHT	_IOW('F', 0x25, int)


#ifndef HAVE_USLEEP
static void my_usleep(unsigned int us)
{
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = us;
	select(0, NULL, NULL, NULL, &tv);
}
#endif

void *sys_timer()
{
	struct timeval *tv;

	tv = malloc(sizeof(struct timeval));
	gettimeofday(tv, NULL);
	return tv;
}

int sys_elapsed(struct timeval *prev)
{
	struct timeval tv;
	int secs, usecs;

	gettimeofday(&tv, NULL);
	secs = tv.tv_sec - prev->tv_sec;
	usecs = tv.tv_usec - prev->tv_usec;
	*prev = tv;
	if (!secs) return usecs;
	return secs*1000000 + usecs;
}

void sys_sleep(int us)
{
	if (us <= 0) return;
#ifdef HAVE_USLEEP
	usleep(us);
#else
	my_usleep(us);
#endif
}


void sys_fb_ioctl(int request, int *val)
{
	int f;

	f = open("/dev/fb0", O_NONBLOCK);
	if(f<0) f = open("/dev/fb/0", O_NONBLOCK);
	if(f<0) return;

	ioctl(f, request, val);
	close(f);
}


int backlight = 0;

int sys_get_backlight()
{
	int h;

	sys_fb_ioctl(FBIOGET_BACKLIGHT, &h);

	return h;
}


void sys_set_backlight(int on)
{
	backlight = on;
	sys_fb_ioctl(FBIOSET_BACKLIGHT, (int*)(long)on);  //sic
}


int contrast = -1;

int sys_get_contrast()
{
	int h;

	sys_fb_ioctl(FBIOGET_CONTRAST, &h);
	return h;
}


void sys_set_contrast(int cont)
{
	if(cont < 0) return;
	contrast = cont;
	sys_fb_ioctl(FBIOSET_CONTRAST, (int*)(long)cont); //sic
}


/* allocs a new string containing dir+file*/
FILE * fopen2(char *dir, char *file, char *mode)
{
	char *h;
	FILE *f;

	if(!dir || !*dir || !file || !*file) return NULL;

	h = malloc(strlen(dir) + strlen(file) + 2);
	if(!h) die("out of mem for fopen2");

	strcpy(h, dir);
	if(h[strlen(h)-1] != '/') strcat(h, "/");
	strcat(h, file);
	f = fopen(h, mode);
	free(h);
	return f;
}



int orig_backlight;
int orig_contrast;
struct termio savetty, settty;


int consoleFd = -1;
struct termios old;

int startKeyHandler(void)
{
	struct termios new;

	if ((consoleFd = open("/dev/console", O_NONBLOCK)) < 0)
		fprintf(stderr, "Could not open /dev/console");

	if (tcgetattr(consoleFd, &old) < 0)
		fprintf(stderr, "Could not save old termios");

	new = old;

	new.c_lflag    &= ~(ICANON | ECHO  | ISIG);
	new.c_iflag    &= ~(ISTRIP | IGNCR | ICRNL | INLCR | IXOFF | IXON | BRKINT);
	new.c_cc[VMIN]  = 0;
	new.c_cc[VTIME] = 0;

	if (tcsetattr(consoleFd, TCSAFLUSH, &new) < 0)
		die( "Could not set new termios");

//	if (ioctl(consoleFd, KDSKBMODE, K_MEDIUMRAW) < 0)
//		die( "Could not set keyboardmode");

	ioctl(consoleFd, KDSETMODE, KD_GRAPHICS);
	return 0;
}


void closeKeyHandler(void)
{
	if (tcsetattr(consoleFd, TCSAFLUSH, &old) < 0)
	fprintf(stderr, "Could not reset old termios");

	if (consoleFd > 2)
		if (close(consoleFd) < 0)
			fprintf(stderr, "Could not close console");
}


int sys_getkey(void)
{
	int c = -1;

	while (read(consoleFd, &c, 1) == 1);


	if(c!=-1) return c & 0xff;
	else return -1;
}



void sys_ipod_init()
{

	startKeyHandler();

	/*int flags = fcntl(0, F_GETFL, 0);
	int fd = open("/dev/console", O_NONBLOCK);

	if (fd < 0)
	{
		printf("attention: console still active!\n");
		sleep(20);
		// not _deadly_ if we can't set graphics mode
		return;
	}
	fcntl(0, F_SETFL, flags | O_NONBLOCK);
        ioctl(0, TCGETA, &savetty);
        ioctl(0, TCGETA, &settty);
        settty.c_lflag &= ~ICANON;
        settty.c_lflag &= ~ECHO;
        ioctl(0, TCSETAF, &settty);


	orig_contrast = sys_get_contrast();
	if(contrast < 80 || contrast > 120) contrast = orig_contrast;
	else sys_set_contrast(contrast);
	orig_backlight = sys_get_backlight();
	sys_set_backlight(backlight);
	//ipod_hw_version = sys_get_hw_version();

	ioctl(fd, KDSETMODE, KD_GRAPHICS);
	close(fd);*/
}


void sys_ipod_cleanup()
{
	/*
	int fd = open("/dev/console", O_NONBLOCK);

	sys_set_contrast(orig_contrast);
	sys_set_backlight(orig_backlight);

	if (fd >= 0) {
		ioctl(fd, KDSETMODE, KD_TEXT);
		close(fd);
	}
	ioctl(0, TCSETAF, &savetty);
	*/

	ioctl(consoleFd, KDSETMODE, KD_TEXT);
	closeKeyHandler();
}


/**
 * Finds the hw-ID for the current iPod.
 *
 * 10000: iPod 1G
 * 20000: iPod 2G
 * 30000: iPod 3G
 * 40000: iPod Mini 1G
 * 50000: iPod 4G
 * 50013: iPod 4G
 * 60000: iPod Photo / Color
 * 60005: iPod Photo / Color Rev.2
 * 70000: iPod Mini 2G
 * c0005: iPod Nano
 * ?????: iPod Video
 *
 * NOTE: These numbers are subject to change. This is not a complete list.
 */
 int version = -1;

int sys_ipod_hw_type(void)
{
	int i;
	char cpuinfo[512];
	char * ptr;
	FILE * file;

	if(version<0) {
		if ((file = fopen("/proc/cpuinfo", "r")) != NULL)
		{
			while (fgets(cpuinfo, sizeof(cpuinfo), file) != NULL)
				if (strncmp(cpuinfo, "Revision", 8) == 0)
					break;

			fclose(file);
		}
		else
		{
			return 0;
		}

		for (i = 0; !isspace(cpuinfo[i]); i++);
		for (; isspace(cpuinfo[i]); i++);

		ptr     = cpuinfo + i + 2;
		version = strtol(ptr, NULL, 16);
	}

	return version;
}



int sys_ipod_is_color()
{
	byte v =  (sys_ipod_hw_type() >> 16);

	return (v >= 6) && (v != 7);
}



/**
 * Finds out the hardware specs. of the current iPod.
 */
void sys_ipod_hw_info(hw_info * info)
{
	info->flags = 0;
	switch (info->version = (sys_ipod_hw_type() >> 16))
	{
		case 0xb: /* iPod Video */
			info->lcd_base      = IPOD_VIDEO_LCD_BASE;
			info->lcd_busy_mask = IPOD_VIDEO_LCD_BUSY_MASK;
			info->lcd_width     = IPOD_VIDEO_LCD_WIDTH;
			info->lcd_height    = IPOD_VIDEO_LCD_HEIGHT;
			info->ipod_rtc      = IPOD_PP5020_RTC;
			info->ipod_type     = "iPod Video";
			info->lcd_type	    = 5;
			info->flags        |= LCD_COLOR | LCD_VIDEO;

			break;

		case 0xc: /* iPod Nano */
			info->lcd_base      = IPOD_NANO_LCD_BASE;
			info->lcd_busy_mask = IPOD_NANO_LCD_BUSY_MASK;
			info->lcd_width     = IPOD_NANO_LCD_WIDTH;
			info->lcd_height    = IPOD_NANO_LCD_HEIGHT;
			info->ipod_rtc      = IPOD_PP5020_RTC;
			info->ipod_type     = "iPod Nano";
			info->lcd_type	    = 1;
			info->flags        |= LCD_COLOR;


			break;

		case 0x6: /* iPod Photo / Color */
			info->lcd_base      = IPOD_COLOR_LCD_BASE;
			info->lcd_busy_mask = IPOD_COL_LCD_BUSY_MASK;
			info->lcd_width     = IPOD_COL_LCD_WIDTH;
			info->lcd_height    = IPOD_COL_LCD_HEIGHT;
			info->ipod_rtc      = IPOD_PP5020_RTC;
			info->ipod_type     = "iPod Color";
			info->flags        |= LCD_COLOR;

			if(sys_ipod_hw_type() == 0x60000) {
				info->lcd_type = 0; //photo
			}
			else
			{
				int gpio_a01 = (inl(0x6000D030) & 0x02) >> 1;
				int gpio_a04 = (inl(0x6000D030) & 0x10) >> 4;

				if (((gpio_a01 << 1) | gpio_a04) == 0 ||
				    ((gpio_a01 << 1) | gpio_a04) == 2)
				{ 
					info->lcd_type = 0;
				} else {
					info->lcd_type = 1;
				}
			}

			break;

		case 0x5: /* iPod 4G (gray)*/
			info->lcd_base      = IPOD_PP5020_LCD_BASE;
			info->lcd_busy_mask = IPOD_STD_LCD_BUSY_MASK;
			info->lcd_width     = IPOD_STD_LCD_WIDTH;
			info->lcd_height    = IPOD_STD_LCD_HEIGHT;
			info->ipod_rtc      = IPOD_PP5020_RTC;
			info->ipod_type     = "iPod 4G";
			info->flags        &= ~LCD_COLOR;
			info->lcd_type	    = 2;

			break;

		case 0x7: /* iPod Mini 2G */
			info->lcd_width     = IPOD_MINI_LCD_WIDTH;
			info->lcd_height    = IPOD_MINI_LCD_HEIGHT;
			info->lcd_base      = IPOD_PP5020_LCD_BASE;
			info->lcd_busy_mask = IPOD_STD_LCD_BUSY_MASK;
			info->ipod_rtc      = IPOD_PP5020_RTC;
			info->ipod_type     = "iPod Mini";
			info->lcd_type	    = 3;
			info->flags        &= ~LCD_COLOR;
			break;

		case 0x4: /* iPod Mini 1G */
			info->lcd_width     = IPOD_MINI_LCD_WIDTH;
			info->lcd_height    = IPOD_MINI_LCD_HEIGHT;
			info->lcd_base      = IPOD_PP5020_LCD_BASE;
			info->lcd_busy_mask = IPOD_STD_LCD_BUSY_MASK;
			info->ipod_rtc      = IPOD_PP5020_RTC;
			info->ipod_type     = "iPod Mini";
			info->lcd_type	    = 2;
			info->flags        &= ~LCD_COLOR;
			break;

		case 0x3: /* iPod 3G */

		case 0x2: /* iPod 2G */

		case 0x1: /* iPod 1G */
			info->lcd_width     = IPOD_STD_LCD_WIDTH;
			info->lcd_height    = IPOD_STD_LCD_HEIGHT;
			info->lcd_base      = IPOD_PP5002_LCD_BASE;
			info->ipod_rtc      = IPOD_PP5002_RTC;
			info->lcd_busy_mask = IPOD_STD_LCD_BUSY_MASK;
			info->ipod_type     = "iPod";
			info->lcd_type	    = 2;
			info->flags        &= ~LCD_COLOR;
		break;
	}
}



/*
 * disgusting !!!!
*/



#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <features.h>
#include <alloca.h>
#include <assert.h>
#include <errno.h>
#include <dirent.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/syscall.h>


/* Directory stream type.  */
struct __dirstream {
  /* file descriptor */
  int dd_fd;

  /* offset of the next dir entry in buffer */
  size_t dd_nextloc;

  /* bytes of valid entries in buffer */
  size_t dd_size;

  /* -> directory buffer */
  void *dd_buf;

  /* offset of the next dir entry in directory. */
  off_t dd_nextoff;

  /* total size of buffer */
  size_t dd_max;

  /* lock */
#ifdef __UCLIBC_HAS_THREADS__
  pthread_mutex_t dd_lock;
#else
  void *dd_lock;
#endif
} ;/* stream data from opendir() */

struct dirent64 {
	unsigned long	d_ino;
	long 			d_off;
	unsigned short	d_reclen;
	unsigned char	d_type;
	char		d_name[256];
};



struct kernel_dirent64 {
	unsigned long long		d_ino;
	long long		d_off;
	unsigned short	d_reclen;
	unsigned char	d_type;
	char		d_name[256];
};


#ifndef __NR_getdents64 /*CYGWIN workaround !?*/
#define __NR_getdents64 9437401
#endif

#define __NR___syscall_getdents64 __NR_getdents64
static inline _syscall3(int, __syscall_getdents64, int, fd, unsigned char *, dirp, size_t, count);


ssize_t __getdents64 (int fd, char *buf, size_t nbytes)
{
    struct dirent64 *dp;
    long long last_offset = -1;
    ssize_t retval;
    size_t red_nbytes;
    struct kernel_dirent64 *skdp, *kdp;
    const int size_diff = 0;

    red_nbytes = MIN (nbytes - ((nbytes /
    (offsetof (struct dirent64, d_name) + 14)) * size_diff),
    nbytes - size_diff);

    dp = (struct dirent64 *) buf;
    skdp = kdp = alloca (red_nbytes);

    retval = __syscall_getdents64(fd, (char *)kdp, red_nbytes);
    if (retval == -1)
		return -1;

    while ((char *) kdp < (char *) skdp + retval) {
		const size_t alignment = __alignof__ (struct dirent64);
		/* Since kdp->d_reclen is already aligned for the kernel structure
		   this may compute a value that is bigger than necessary.  */
		size_t new_reclen = ((kdp->d_reclen + size_diff + alignment - 1) & ~(alignment - 1));
		if ((char *) dp + new_reclen > buf + nbytes) {
		    /* Our heuristic failed.  We read too many entries.  Reset
		       the stream.  */
		    assert (last_offset != -1);
		    lseek(fd, last_offset, SEEK_SET);

		    if ((char *) dp == buf) {
			/* The buffer the user passed in is too small to hold even
			   one entry.  */
				__set_errno (EINVAL);
				return -1;
			}
		 	break;
		}

		last_offset = kdp->d_off;
		dp->d_ino = kdp->d_ino;
		dp->d_off = kdp->d_off;
		dp->d_reclen = new_reclen;
		dp->d_type = kdp->d_type;
		memcpy (dp->d_name, kdp->d_name,
		kdp->d_reclen - offsetof (struct kernel_dirent64, d_name));
		dp = (struct dirent64 *) ((char *) dp + new_reclen);
		kdp = (struct kernel_dirent64 *) (((char *) kdp) + kdp->d_reclen);
    }
    return (char *) dp - buf;
}

struct dirent64 *readdir64(struct __dirstream * dir)
{
	ssize_t bytes;
	struct dirent64 *de;

	if (!dir) return NULL;

	//err_msg("dents: %d", 2000, __NR_getdents64);

	do {
	    if (dir->dd_size <= dir->dd_nextloc) {
			/* read dir->dd_max bytes of directory entries. */
			bytes = __getdents64(dir->dd_fd, dir->dd_buf, dir->dd_max);
			if (bytes <= 0) return NULL;

			dir->dd_size = bytes;
			dir->dd_nextloc = 0;
	    }

	    de = (struct dirent64 *) (((char *) dir->dd_buf) + dir->dd_nextloc);

	    /* Am I right? H.J. */
	    dir->dd_nextloc += de->d_reclen;

	    /* We have to save the next offset here. */
	    dir->dd_nextoff = de->d_off;

	    /* Skip deleted files.  */
	} while (de->d_ino == 0);

	return de;
}

/*
 * hate this!!!
 * use scandir64 instead if available !
*/

 int sys_scandir(const char *dir, struct dirent ***namelist,
              int(*filter)(const struct dirent *),
              int(*compar)(const struct dirent **, const struct dirent **))
{
	DIR *d = opendir(dir);
	//struct stat stat_result;
	struct dirent64 *ent;
	int n = 0;

	if(!d) return 0;

	*namelist = malloc(1 * sizeof(struct dirent *));

	while ((ent = readdir64(d))) {
		/*if(strcmp(ent->d_name, ".") || strcmp(ent->d_name, "..")) {
			lstat(ent->d_name, &stat_result);
			ent->d_type = S_ISDIR(stat_result.st_mode)?DT_DIR:0;
		} else ent->d_type = DT_DIR; */

		if(!filter( (struct dirent *) ent)) continue;

		n++;
		*namelist = realloc(*namelist, n * sizeof(struct dirent *));
		(*namelist)[n-1] = malloc(sizeof(struct dirent));

		strcpy((*namelist)[n-1]->d_name, ent->d_name);
		(*namelist)[n-1]->d_type = ent->d_type;
	}

	qsort(*namelist, n, sizeof(struct dirent*), (int(*)(const void *, const void *)) compar);
	return n;
}
















