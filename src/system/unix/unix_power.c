#include"system/elt_power.h"
#include<errno.h>
#include<dirent.h>
#include<linux/limits.h>
#include<regex.h>

#define _POWDIR "/sys/class/power_supply"

Enum ExGetPowerInfo(Int32* sec, Int32* pct){
	FILE* f_c, *f_f;
	long current, full;
	DIR* d;
	struct dirent* dp;
	char b[PATH_MAX];

	if((d = opendir(_POWDIR)) == NULL){
		fprintf(stderr, "opendir: %s\n", strerror(errno));
		return 3;
	}



	while((dp = readdir(d)) != NULL){
		snprintf(b, PATH_MAX, "%s/%s", _POWDIR, dp->d_name);

		regex_t regex;
		if(regcomp(&regex, "BAT[[:alnum:]]+", REG_EXTENDED) != 0){
			fprintf(stderr, "regcomp: %s\n", strerror(errno));
		}

		if(regexec(&regex, b, 0, NULL, 0 ) == 0){
			snprintf(b, PATH_MAX, "%s/%s/%s", _POWDIR, dp->d_name, "charge_now");
			f_c = fopen(b, "r");
			snprintf(b, PATH_MAX, "%s/%s/%s", _POWDIR, dp->d_name, "charge_full");
			f_f = fopen(b, "r");
			if(f_c != NULL  && f_f != NULL){
				if(fscanf(f_c, "%ld", &current) != 1 || fscanf(f_f, "%ld", &full) != 1)
					fprintf(stderr,"");
				else
					fprintf(stderr,"");

				fclose(f_c);
				fclose(f_f);
			}

		}

		regfree(&regex);
	}

	if(sec)
		*sec = 0;

	if(pct)
		*pct = 0;

	return 0;
}
