
// Modify the given location of files as per your system
const char *cpu_stat = "/proc/stat";
const char *cpu_temp = "/sys/class/hwmon/hwmon0/temp1_input";

const char *memory_stat = "/proc/meminfo";

const char *wifi_opstate = "/sys/class/net/wlan0/operstate";
const char *wifi_rssilink = "/proc/net/wireless";
const char *wifi_rxbytes = "/sys/class/net/wlan0/statistics/rx_bytes";
const char *lan_opstate = "/sys/class/net/enp1s0/operstate";
const char *lan_speed = "/sys/class/net/enp1s0/speed";

const char *brightness = "/sys/class/backlight/intel_backlight/brightness";
const char *max_brightness = "/sys/class/backlight/intel_backlight/max_brightness";

const char *adp0 = "/sys/class/power_supply/ADP0/online";
const char *bat0 = "/sys/class/power_supply/BAT0/online";

//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Isfunc*/	/*Command*/			/*Update Interval*/	/*Update Signal*/
	{ "",		1,		"wifistat",			1,			0 },	// w -> for wifi
	{ "﬙",		1,		"cpustat",			1,			0 },	// c -> for cpu
//	{ "",		1,		"memstat",			1,			0 },	// m -> for memory
	{ "",		1,		"xbacklight",			0,			13 },	// x -> for backlight
	{ "",		1,		"volume",			0,			11 },	// v -> for volume
	{ "",		1,		"datet",			3600,			0 },	// d -> date
	{ "",		1,		"ltime",			1,			0 },	// l -> time
	{ "",		1,		"power",			1,			0 },	// p ->	power / battery
	{ "ﮮ",		1,		"updatestat",			0,			12 },	// u -> updates
	{ "",		1,		"busb",				0,			14 },	// b -> usb / pen drives plugged
	{ "",		1,		"android",			0,			15 },	// a -> android plugged
	{ "",		1,		"transmission",			60,			0 },	// t -> torrent status transmission
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim = ' ';
