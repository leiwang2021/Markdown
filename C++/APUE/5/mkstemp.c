#include "apue.h"
#include <errno.h>

void make_temp(char *template1);

int
main()
{
	char	good_template[] = "/tmp/dirXXXXXX";	/* right way */
	const char	*bad_template = "/tmp/dirXXXXXX";	/* wrong way*/

	printf("trying to create first temp file...\n");
	make_temp(good_template);
	printf("trying to create second temp file...\n");
	//make_temp(bad_template);
	exit(0);
}

void
make_temp(char *template1)
{
	int			fd;
	struct stat	sbuf;

	if ((fd = mkstemp(template1)) < 0)
		err_sys("can't create temp file");
	printf("temp name = %s\n", template1);
	close(fd);
	if (stat(template1, &sbuf) < 0) {
		if (errno == ENOENT)
			printf("file doesn't exist\n");
		else
			err_sys("stat failed");
	} else {
		printf("file exists\n");
		unlink(template1);
	}
}
