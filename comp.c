static long double workJiffies2;
static long double workJiffies1;
static long double totalJiffies2;
static long double totalJiffies1;
static long double totalJiffiesDiff;
static long double workJiffiesDiff;
static long double rxBytesdiff;
static long double rxBytes1;
static char cpu_temp[64];
static char wifi_opstate[64];
static char wifi_rxbytes[64];

const char *getstsmods(const char *fak, char *value)
{
	int i = strlen(value);
	time_t t;
	FILE * file;
	switch (fak[0]){
		case 'm':	// Case Memory Info
			file = fopen("/proc/meminfo","r");
			if (file != NULL) {
				int memusage;
				long double memTotal, memFree;
				fscanf(file, "MemTotal: %Lf kB\nMemFree: %Lf", &memTotal, &memFree);
				fclose(file);
				memusage = ((memTotal - memFree) / memTotal) * 100;
				sprintf(value+i, "{%d%} ", memusage);
			}
		break;
		case 'c':	// Case Cpu Info
			file = fopen("/proc/stat","r");
			if (file != NULL) {
				int cpuusage;
				long double cpuStat[7];
				fscanf(file, "cpu %Lf %Lf %Lf %Lf %Lf %Lf %Lf", &cpuStat[0], &cpuStat[1], &cpuStat[2], &cpuStat[3], &cpuStat[4], &cpuStat[5], &cpuStat[6]);
				fclose(file);
				workJiffies2 = cpuStat[0] + cpuStat[1] + cpuStat[2];
				totalJiffies2 = cpuStat[0] + cpuStat[1] + cpuStat[2] + cpuStat[3] + cpuStat[4] + cpuStat[5] + cpuStat[6];
				workJiffiesDiff = workJiffies2 - workJiffies1;
				totalJiffiesDiff = totalJiffies2 - totalJiffies1;
				workJiffies1 = workJiffies2;
				totalJiffies1 = totalJiffies2;
				cpuusage = (workJiffiesDiff / totalJiffiesDiff) * 100;
				sprintf(cpu_temp, "/sys/class/hwmon/%s/temp1_input", cpu_hwmon_name);
				file = fopen(cpu_temp,"r");
				if (file != NULL) {
					int cputemp;
					long double cpuTemp;
					fscanf(file, "%Lf", &cpuTemp);
					fclose(file);
					cputemp = cpuTemp / 1000;
					sprintf(value+i, "{%d%(%d˚C)} ", cpuusage, cputemp);
				} else
					sprintf(value+i, "{%d%} ", cpuusage);
			}
		break;
		case 'd':	// Case Date And Time info
			time(&t);
			struct tm *date = localtime(&t);
			sprintf(value+i, "{%02d-%02d(%d)-%02d} ", date->tm_mon+1, date->tm_mday, date->tm_wday+1, date->tm_year-100);
		break;
		case 'l':
			time(&t);
			struct tm *time = localtime(&t);
			sprintf(value+i, "{%02d:%02d} ", time->tm_hour, time->tm_min);
		break;
		case 'w':	// Case WiFi Info
			sprintf(wifi_opstate, "/sys/class/net/%s/operstate", network_wifi_name);
			file = fopen(wifi_opstate,"r");
			if (file != NULL) {
				char wifiState[4];
				fscanf(file, "%s", wifiState);
				fclose(file);
				if (*(wifiState+0) != 'd') {
					file = fopen("/tmp/internetav","r");
					if (file != NULL)
					{
						int internetav;
						fscanf(file, "%d", &internetav);
						fclose(file);
						if (internetav != 0) {
							sprintf(wifi_rxbytes, "/sys/class/net/%s/statistics/rx_bytes", network_wifi_name);
							file = fopen(wifi_rxbytes,"r");
			 				if (file != NULL) {
			 					fscanf(file, "%Lf", &rxBytes);
			 					fclose(file);
			 				}
			 				rxBytesdiff = rxBytes - rxBytes1;
							rxBytes1 = rxBytes;
							wifispeed = rxBytesdiff / 1024;
							sprintf(value+i, "直{%dkB/s} ", wifispeed);			
						} else {
							sprintf(value+i, "%s ", "");	
						}
					} else {
						sprintf(value+i, "%s ", "");
					}
				} else
					sprintf(value+i, "%s ", "睊");
			}	
		break;
		case 'n':	// Case LAN Info
			file = fopen(lan_opstate, "r");
			if (file != NULL) {
				char lanopstate[4];
				fscanf(file, "%s", lanopstate);
				fclose(file);
				if (*(lanopstate+0) != 'd') {
					file = fopen("/tmp/internetav","r");
					if (file != NULL) {
						int internetav;
						fscanf(file, "%d", &internetav);
						fclose(file);
						if (internetav != 0) {
							sprintf(value+i, "%s ", "ﯲ");
						} else {
							sprintf(value+i, "%s ", "ﯳ");
						}
					} else {
						sprintf(value+i, "%s ", "ﯳ");
					}
				} else {
					sprintf(value+i, "%s ", "");
				}
			}
		break;
		case 'u':	// Case Updates Info
			file = fopen("/tmp/updates","r");
			if (file != NULL) {
				int u = 0;
				fscanf(file, "%d", &u);
				fclose(file);
				if (u != 0)
					sprintf(value+i, "{%d} ", u);
				else
					value[0] = '\0';
			}
		break;
		case 'a':	// Case Android Devices-Phones 
			file = popen("mtp-detect 2>/dev/null | awk '/Model/' | wc -l", "r");
			if (file != NULL) {
				int devs = 0;
				fscanf(file, "%d", &devs);
				pclose(file);
				if (devs != 0)
					sprintf(value+i, "{%d} ", devs);
				else
					value[0] = '\0';
			}
		break;
		case 'b':	// Case Usb Disk Drives 
			file = popen("lsblk -lo RM,TYPE | grep '1 disk' | wc -l", "r");
			if (file != NULL) {
				int devs = 0;
				fscanf(file, "%d", &devs);
				pclose(file);
				if (devs != 0)
					sprintf(value+i, "{%d} ", devs);
				else
					value[0] = '\0';
			}
		break;
		case 't':	// Case transmission remote cli torrents 
			file = popen("transmission-remote -l | wc -l", "r");
			if (file != NULL) {
				int torrents = 0;
				fscanf(file, "%d", &torrents);
				pclose(file);
				if (torrents > 2) {
					int count = 2;
					char trans[64];
					char pri[8*torrents];
					char percentdone[8];
					while (count < torrents)
					{
						sprintf(trans, "transmission-remote -l | sed '%dq;d' | awk '{ print $2 }'", count);
						file = popen(trans, "r");
						fscanf(file, "%s", percentdone);
						fclose(file);
						sprintf(pri+strlen(pri), "%s:", percentdone);
						count++;
					}
					pri[strlen(pri)-1] = '\0';
					sprintf(value+i, "{%s} ", pri);
				} else
					value[0] = '\0';
			}
		break;
		case 'x':	// Case X-Backlight
			file = fopen(max_brightness, "r");
			if (file != NULL) {
				int light;
				int max_light;
				fscanf(file, "%d", &max_light);
				fclose(file);
				file = fopen(brightness, "r");
				fscanf(file, "%d", &light);
				fclose(file);
				light = (light * 100) / max_light;
				if (light >= 0 && light <= 10)
					sprintf(value+i, "%s ", "{░    }");
				else if (light > 10 && light <= 20)
					sprintf(value+i, "%s ", "{░░   }");
				else if (light > 20 && light <= 30)
					sprintf(value+i, "%s ", "{░░░  }");
				else if (light > 30 && light <= 40)
					sprintf(value+i, "%s ", "{░░░░ }");
				else if (light > 40 && light <= 50)
					sprintf(value+i, "%s ", "{░░░░░}");
				else if (light > 50 && light <= 60)
					sprintf(value+i, "%s ", "{█░░░░}");
				else if (light > 60 && light <= 70)
					sprintf(value+i, "%s ", "{██░░░}");
				else if (light > 70 && light <= 80)
					sprintf(value+i, "%s ", "{███░░}");
				else if (light > 80 && light <= 90)
					sprintf(value+i, "%s ", "{████░}");
				else
					sprintf(value+i, "%s ", "{█████}");
			}
		break;
		case 'v':	// Case Volume	
			file = popen("pamixer --get-mute", "r");
			if (file != NULL) {
				char mute[5];
				fscanf(file, "%s", mute);
				fclose(file);
				if (*(mute+0) != 't'){
					int vol;
					file = popen("pamixer --get-volume", "r");
					fscanf(file, "%d", &vol);
					fclose(file);
					if (vol == 0)
						sprintf(value+i, "%s ", "ﱝ{     }");
					else if (vol > 0 && vol <= 10)
						sprintf(value+i, "%s ", "奄{░    }");
					else if (vol > 10 && vol <= 20)
						sprintf(value+i, "%s ", "奄{░░   }");
					else if (vol > 20 && vol <= 30)
						sprintf(value+i, "%s ", "奄{░░░  }");
					else if (vol > 30 && vol <= 40)
						sprintf(value+i, "%s ", "奔{░░░░ }");
					else if (vol > 40 && vol <= 50)
						sprintf(value+i, "%s ", "奔{░░░░░}");
					else if (vol > 50 && vol <= 60)
						sprintf(value+i, "%s ", "墳{█░░░░}");
					else if (vol > 60 && vol <= 70)
						sprintf(value+i, "%s ", "墳{██░░░}");
					else if (vol > 70 && vol <= 80)
						sprintf(value+i, "%s ", "墳{███░░}");
					else if (vol > 80 && vol <= 90)
						sprintf(value+i, "%s ", "{████░}");
					else if (vol > 90 && vol <=100)
						sprintf(value+i, "%s ", "{█████}");
					else
						sprintf(value+i, "ﱛ{█%d█} ", vol);
				} else 
					sprintf(value+i, "%s ", "");
			}
		break;
		case 'p':	// Case Battery/Adapter A.K.A. Power
			file = fopen(bat0, "r");
			if (file != NULL) {
				int online;
				fscanf(file, "%d", &online);
				fclose(file);
			} else {
				file = fopen(adp0, "r");
				if (file != NULL) {
					int online;
					fscanf(file, "%d", &online);
					fclose(file);
					if (online != 0)
						sprintf(value+i, "%s ", "ﳦ");
				}
			}
		break;
	}
	i = strlen(value);
	if (delim != '\0' && i--)
		value[i++] = delim;
	value[i++] = '\0';
}
