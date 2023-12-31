#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "my_readline.h"


int main(int argc, char** argv) {
	if (argc == 1) {
		return 0;
	}
	for (int index = 1; index < argc; index ++) {
		int fd = open(argv[index], O_RDONLY);
    	char* str = NULL;
		if (fd < 0) {
			break;
		}

		int initialize = READLINE_READ_SIZE;

    	while ((str = my_readline(fd)) != NULL) {
        	printf("%s\n", str);
        	free(str);
    	}
    	close(fd);

		init_my_readline(initialize);
	}
	
    return 0;
}

