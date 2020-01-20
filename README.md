# dwmblocks

Modular status bar for dwm written in c.

# installation & usage

	# sudo make clean install

# To remove

	# sudo rm /usr/local/dwmblocks
	# sudo rm /usr/local/internetav

In your init script i.e, .xinitrc or .xprofile
put,
	# echo "internetav &" >> ~/.xprofile
	# echo "dwmblocks &" >> ~/.xprofile

OR do it manually by vim in '~/.xprofile' add:
	#################
	internetav &
	dwmblocks &
	################	


# Description (Read this there are few things that need setting up)

To add blocks edit "blocks.h" file. Blocks can be added two ways
bash script, command or a c program function. Be aware more blocks
more resources so c function might me a better choice. Please use
*NOTE: Install "Hack Nerd Font" for glyphs if glyphs not shown.
	https://github.com/ryanoasis/nerd-fonts/releases/download/v2.0.0/Hack.zip
A simple example for adding date blocks would be,

Scrpit(in "blocks.h"):

	##########################################################################################
	icon	isFunc	command						interval	signal
	{ "$",	0,	"date | awk '{ print $1" "$2" "$3" "$4 }'",	0,		0 },
	##########################################################################################

C function(in "comp.c" and "blocks.h"):

	add a new case in "comp.c",
	#################################################################################################################
	case 'd':
		time(&t);
		struct tm *date = localtime(&t);
		sprintf(value+i, "{%02d-%02d(%d)-%02d} ", date->tm_mon+1, date->tm_mday, date->tm_wday+1, date->tm_year-100);
	break;
	#################################################################################################################

	then add in "blocks.h"
	############################################################################################
	icon		isFunc		command		interval	signal
	{ "$",		1,		"d",		0,		0 },
	############################################################################################

	While adding a function remember the first letter in command is used to switch in every case
	it must be diffrent than other values so instead of d you can write date in "blocks.h" but in
	the "comp.c" file the first letter 'd' is used in switch case.

Included Functions are all on the blocks.h edit them as your need. comment them if not needed

Setting up USB and ANDROID via udev.
looping constantly in search for plugged devices can crank up cpu usage
so udev rules are a better way just send a pkill singal command to update
dwmblocks i will give example for usb and android however you can do same 
for any number of external devices you add or any block you wish to add.
To add a udev rule first add a signal value to usb and android in "blocks.h"
by default signal 14 and 15 is used you can change if you like.
	
	# cd /etc/udev/rules.d
	# sudo touch 40-android.rules
	# sudo vim 40-android.rules

	paste the following in android rules: (!wq for save in vim)
	########################################################################################################
	ACTION=="add", SUBSYSTEMS=="usb", SUBSYSTEM=="usb", RUN{program}+="/bin/pkill -SIGRTMIN+15 dwmblocks"
	ACTION=="remove", SUBSYSTEMS=="usb", SUBSYSTEM=="usb", RUN{program}+="/bin/pkill -SIGRTMIN+15 dwmblocks"
	########################################################################################################

	# sudo touch 40-usb.rules
	# sudo vim 40-usb.rules

	paste the following in usb rules:
	##################################################################################################################
	ACTION=="add", SUBSYSTEMS=="usb", SUBSYSTEM=="block", ATTR{removable}=="1", RUN{program}+="/bin/pkill -SIGRTMIN+14 dwmblocks"
	ACTION=="remove", SUBSYSTEMS=="usb", SUBSYSTEM=="block", RUN{program}+="/bin/pkill -SIGRTMIN+14 dwmblocks"
	##################################################################################################################

	# sudo udevadm control --reload

Now, if you plug any usb drives or android devices statusbar should show them.

There are few things this is not complete so battery and network should be added 
i will add them soon. Wifi works lan must be added.

# Happy Hacking. 
