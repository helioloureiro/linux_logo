/******************************************************************
 *     sysinfo_bsd.c  - FreeBSD patch for linux_logo              * 
 * August 31, 2000 by Shawn Rapp                                  *
 * - Made cute little devil pic from daemon screen saver for the  *
 *   linux_logo to use.  Bye Bye fat little penguin  =)           *
 * - CPU information                                              *
 * - OS information                                               *
 * - Somewhat gets the build date (needs parsing)                 *
 * - BogoMips                                                     *
 * - Physical Memory total (not averaged to convention though)    *
 *                                                                *
 * Left to be done                                                *
 * - CPU mgz                                                      *
 * - Patch telnetd to display /etc/issue when specified in        * 
 *   /etc/gettytab.                                               *
 * - System uptime                                                *
 * - Load average                                                 *
 ******************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/utsname.h>
#include <sys/sysctl.h>
#include <string.h>

#include "sysinfo.h"
#include "generic.h"

#define SIZE(x) sizeof(x)/sizeof(x[0])

int external_bogomips(char *bogomips_total);

int get_os_info(os_info_t *os_info) {
    return uname_get_os_info(os_info);
}


/* Not implemented */
int get_uptime (void) {
   
       return 0;
}
/* Not Implemented */
void get_load_average(float *load_1,float *load_5,float *load_15) {
   
   return;
}



char *get_host_name(char hostname[65],char domain[65]) {
    return uname_get_host_name(hostname,domain);
}


long int get_mem_size(void) {
   
    int ctl_ram[] = { CTL_HW, HW_PHYSMEM };
    long int mem_size=-1;

    int val_int;
    int val_len;
   
    val_len = sizeof(val_int);
    if (sysctl(ctl_ram, SIZE(ctl_ram), &val_int, &val_len,0,0))
       perror("sysctl");
    else {
       mem_size=(val_int/1000000);
    }
      
    return mem_size;     
}

