#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <errno.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
   
int main() 
{
	FILE * file; 
    struct hostent *host_entry; 

    for (;;) {
    	host_entry = gethostbyname("www.google.com"); 
    	if (host_entry == NULL) 
    	{ 
        	file = fopen("/tmp/internetav","w");
        	fprintf(file, "%d", 0);
        	fclose(file); 
    	} else {
    		file = fopen("/tmp/internetav","w");
    		fprintf(file, "%d", 1);
    		fclose(file);
    	}
    	usleep(3*1000*1000);
	}
    return 0; 
} 