
// Modify the given location of files as per your system
const char *cpu_hwmon_name = "hwmon0";				// Found in /sys/class/hwmon/hw.....
const char *network_wifi_name = "wlan0";			// Found in /sys/class/net/wl....
const char *network_lan_name = "enp1s0";			// Found in /sys/class/net/en....
const char *backlight_driver_name = "intel_backlight";		// Found in /sys/class/backlight/.......
const char *power_adapter_name = "ADP0";			// Found in /sys/class/power_supply/ADP.....
const char *power_battery_name = "BAT0";			// Found in /sys/class/power_supply/BAT.....

//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Isfunc*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
	{ "",		1,		"netlan",		1,			0 },	// n -> Lan network
	{ "",		1,		"wifistat",		1,			0 },	// w -> for wifi
	{ "﬙",		1,		"cpustat",		1,			0 },	// c -> for cpu
//	{ "",		1,		"memstat",		1,			0 },	// m -> for memory
	{ "",		1,		"xbacklight",		0,			13 },	// x -> for backlight
	{ "",		1,		"volume",		0,			11 },	// v -> for volume
	{ "",		1,		"datet",		3600,			0 },	// d -> date
	{ "",		1,		"ltime",		1,			0 },	// l -> time
	{ "",		1,		"power",		1,			0 },	// p ->	power / battery
	{ "ﮮ",		1,		"updatestat",		0,			12 },	// u -> updates
	{ "",		1,		"busb",			0,			14 },	// b -> usb / pen drives plugged
	{ "",		1,		"android",		0,			15 },	// a -> android plugged
//	{ "",		1,		"transmission",		60,			0 },	// t -> torrent status transmission
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim = ' ';
