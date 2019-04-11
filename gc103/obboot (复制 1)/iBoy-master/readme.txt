iboy 0.7.5.4
Released January 2007

TABLE OF CONTENTS

* Important Notices
* Intro
* Features
* Gameboy Color Notes
* Usage
* General Installation
* Unix/Mac OS X: Manual Installation
* Windows: Manual Installation for podzilla2
* iBoy Configuration
* Acknowledgements

-------------------
*** Important Notices

1) Please read the iBoy wiki for all of the latest information
http://ipodlinux.org/iBoy

2) To play Gameboy Color games on both color and grayscale ipods you MUST use the newkern version.  It NEEDS the modified Linux 2.4 kernel from SourceForge:
http://sourceforge.net/project/showfiles.php?group_id=144523&package_id=197970

-------------------
*** Intro
	
iBoy is a Gameboy and Gameboy Color emulator for the iPod. iBoy is GPL Software. See LICENSE for more information.

-------------------
*** Features
	
- Compatible with iPod 3G, 4G (Grayscale), 4G (Color, 5G, 5.5G
- Compatible with iPod Mini 2G
- Compatible with iPod Nano 1G
- Can emulate both Gameboy and Gameboy Color games
- Emulation through dynamic translation of gameboy code
- Coprocessor used for graphical routines
- Several display modes (down-scaling, cropping)
- 44.1 kHz Stereo Sound

-------------------
***  Gameboy Color Notes

Starting with version 0.7 of iBoy, iBoy supports GameBoy Color games. Each iBoy release consists of two builds:

1. iboy_oldkern - This build of iBoy is for the standard Linux kernel. It does not support Gameboy Color games.

2. iboy_newkern - This build of iBoy requires a customized Linux kernel (http://downloads.sourceforge.net/iboy/kernel_bin.tar.bz2?modtime=1155292738&big_mirror=0), available on the SourceForge Project Page (http://sourceforge.net/projects/iboy). 

The custom Linux kern was created because the regular kernel eats up a huge amount (80kb) of SRAM for the audio buffer. To solve this, the iBoy developers patched the kernel to allow the user to manually set buffer size through a syscall. It should be fully backward compatible with the old kernel.

After downloading the custom kernel, you can either replace your old one, or give the custom kernel a different name and place it on your iPod's Linux partition. If you are using the Loader2 to load iBoy, you can adjust the path in your loader.cfg file to point to the new kernel. For example, the following line could appear in your loader.cfg file:
iBoy 075 @ (hd0,2)/newkern.bin /bin/iboy 

-------------------
*** Usage

These controls are set by default and can be changed via the iboy.cfg. Please see iBoy Configuration section for more information.

Use the hold switch to access the iBoy Menu.

Controls for all iPod's except the 1G-Mini are used by lightly touching different locations on the scroll wheel.
Touch the left side of the wheel 	Left
Touch the right side of the wheel 	Right
Touch the top of the wheel 	Up
Touch the bottom of the wheel 	Down
Touch the upper right corner of the wheel 	A
Touch the upper left corner of the wheel 	B
Touch the bottom right corner of the wheel 	Start
Touch the bottom left corner of the wheel 	Select

The Mini-1G uses a different type of wheel than the newer iPods, so most of the controlling is done using the buttons.
Previous Button 	Left
Next Button 	Right
Wheel Counter-Clockwise 	Up
Wheel Clockwise 	Down
Select Button 	A
Play / Pause 	B
Menu 	Start
No Default Specified 	Select

-------------------
*** General Installation

PLEASE check the wiki for up-to-date installation information.

General Tips

There are three recommended ways to run iBoy:

1. From the Loader2 menu before Linux boots up
2. From the External Application Launcher in Podzilla2
3. From the File Browser in Floydzilla 

Note: You cannot run iBoy from within podzilla2 without the External Application Launcher.

If you have installed iPodLinux using the official installer, you can have Loader2 automatically installed on your iPod.

-------------------
*** Unix/Mac OS X: Manual Installation

These instructions are not relevant if you have Floydzilla installed. Floydzilla automatically installs iBoy for you.

   1. Download or build a recent version of iBoy that is compatible with your iPod
   2. Mount your iPod on your computer
   3. Copy the binary (named "iboy") to "/bin/"

          cp iboy /mnt/ipodroot/bin/ 

   4. Create the file "iboy.cfg" using your favorite text editor. Here is an example file:

          romdir=/home/roms/
          savedir=/home/saves/ 

   5. Copy the file "iboy.cfg" to "/etc/"

          cp iboy.cfg /mnt/ipodroot/etc/ 

   6. Create a Directory to put your ROMs and Save Files

          mkdir -p /mnt/ipodroot/home/roms 
          mkdir -p /mnt/ipodroot/home/saves 

   7. Copy your ROMs to the Directory "/home/roms/" on the ipod.
   8. If you have Loader2 installed, edit or create a loader.cfg file and add the following line.

          iboy @ (hd0,1)/kernel.bin /bin/iboy 

   9. Unmount, Boot iPL, and Enjoy! iBoy should now be a menu option on Loader2. If you do not have Loader2 but have the External Application Launcher installed, you can use that to run iBoy.
  10. If you want to play Gameboy Color games, you will also need to install the updated kernel. 

-------------------
*** Windows: Manual Installation for podzilla2

These instructions are not relevant if you have Floydzilla installed. Floydzilla automatically installs iBoy for you.

   1. Download or build a recent version of iBoy that is compatible with your iPod
   2. Mount your iPod on your computer
   3. Copy the binary (named "iboy") to the root of your iPod Windows drive. The file should be just "iboy" without anything else.
   4. Create the file "iboy.cfg" using your favorite text editor. Here is an example file:

          romdir=/home/roms/
          savedir=/home/saves/ 

   5. Copy the file "iboy.cfg" to the root of your iPod drive.
   6. Copy all of your ROMs to the root of your iPod drive. Make sure they all have the .gb or .gbc extension.
   7. Create a text file in the root of your iPod drive. Name the file start, making sure that the file name does not contain the extension .txt
   8. Write this text in the start file, using your favourite text editor. This file will be executed upon loading podzilla or podzilla2, and move the appropriate files to your iPod's ext2 Linux partition.

          mkdir -p /home/roms
          mkdir -p /home/saves
          mv /hp/iboy /sbin
          mv /hp/iboy.cfg /etc/
          mv /hp/*.gb /home/roms/
          mv /hp/*.gbc /home/roms/
          rm /hp/start 

   9. Unmount, Boot iPL, and Enjoy! You can use the External Application Launcher to run iBoy.
  10. If you want to play Gameboy Color games, you will also need to install the updated kernel. 

If you would like to run iBoy from Launcher2, you can create or edit your loader.cfg file and add the following line:
iboy @ (hd0,1)/kernel.bin /bin/iboy
You should place this file in the root directory of your iPod Windows partition. Do not do thus unless you understand how Launcher2 works. 

-------------------
*** iBoy Configuration

iBoy is configured via a iboy.cfg file. The main configuration file is iboy.cfg which must be located in 

1) /mnt or
2) /hp or
3) /etc

as seen by iPodLinux. /etc will not be accessible under Windows as it is located in an ext2 or ext3 file system, but /mnt or /hp are normally seen under windows as the
root directory of the fat partition. It should be sufficient to simply put iboy.cfg into the root directory of the fat partition. 

Once iBoy is running, these settings can also be modified through main-menu options.

There are strict format rules for the configuration files, which are:

<variable>=<integer>   or   <variable>=<literal>

Where <variable> is a configurable property of iboy, <integer> is a number, also used for boolean values as 1 for 'true' and 0 for 'false' and <literal> is a sequence of characters standing for their self or representing an integer number (as a symbolic constant).

- One of those two can be used each line
- Each variable=<value> pair must be immediately followed by a newline
- No special characters, other whitespaces or comments allowed

The two most important entries are:

romdir=/abspath/
savedir=/abspath/

They must be set in iboy.cfg. Please notice the closing / which is expected and make sure that savedir is writeable. Roms in romdir must end with .gb or .gbc and should not be longer than 10 chars. 

Additional, optional configuration items are listed below.  Most options can be changed through the menu (although the ROM might need reset after reconfiguration).

Further Configuration

* romfile=somename.gb           start this rom without menu 

* oss_enabled=<0,1>             enable/disable sound

* lcd_mode=			vertical scaling for older iPods with small screens
<
  VIS_TOP                       cut bottom
  VIS_MID                       cut bottom and top (half each)
  VIS_BOT                       cut top
  SCALE                         scale to fit for 3G, 4G, Nano, Mini (160x128)
>

* mini_h_mode			horizontal scaling for iPod Mini.
Do NOT include this option on an iPod other than the mini
<
X-SCALE				scale to fit iPod mini
VIS_LEFT			not supported
VIS_MID				not supported
VIS_RIGHT			not supported
>

* oss_speed=<50%,70%,80%,90%,95%,100%,105%,110%,120%,150%,200%>
                                determines desired game-speed,
                                needs oss_enabled=1 

* backlight=<0,1>

* contrast=<90 to 110>

* kb_center, kb_right, kb_left, kb_down, kb_left_right, kb_up_down=<
IGNORE, PAD_RIGHT, PAD_LEFT, PAD_UP, PAD_DOWN, PAD_A, PAD_B, PAD_SELECT, PAD_START, PAD_LEFT_UP, PAD_LEFT_DOWN, PAD_RIGHT_UP, PAD_RIGHT_DOWN
>
This selects what option to do when pressing down on a button (or multiple buttons)

* kb_t0, kb_t1, kb_t2, ..., kb_t7=<
IGNORE, PAD_RIGHT, PAD_LEFT, PAD_UP, PAD_DOWN, PAD_A, PAD_B, PAD_SELECT, PAD_START, PAD_LEFT_UP, PAD_LEFT_DOWN, PAD_RIGHT_UP, PAD_RIGHT_DOWN
>
This selects what option to do when touching the circle touchpad on recent iPods.  t0 corresponds 12:00 on the touchpad.  t1 corresponds to 1:30, ... t7 corresponds to 10:30.

-------------------
*** Acknowledgements

Ducky and Fellni want to thank...
	
aegray for great support and coding work	
bholland for porting iBoy to other iPod generations

and of course all other supporters, users and especially 
the developers of gnuboy, the piece of gnu software written 
so portable and generic that it was quite easy to adopt it to 
run on Apple iPods. We also appreciate the fantastic work 
of the iPod Linux team.

Thank you!
