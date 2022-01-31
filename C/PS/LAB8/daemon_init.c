#include	<syslog.h>
#include <unistd.h>

#define	MAXFD	64

int
daemon_init(const char *pname, int facility, uid_t uid)
{
	int		i;
	pid_t	pid;

	if ( (pid = fork()) < 0)
		return (-1);
	else if (pid)
		exit(0);			/* parent terminates */

	/* child 1 continues... */

	if (setsid() < 0)			/* become session leader */
		return (-1);

	signal(SIGHUP, SIG_IGN);
	if ( (pid = fork()) < 0)
		return (-1);
	else if (pid)
		exit(0);			/* child 1 terminates */

	/* child 2 continues... */

	chdir("/");				/* change working directory - or chroot()*/

	/* close off file descriptors */
	for (i = 0; i < MAXFD; i++){
		close(i);
	}

	/* redirect stdin, stdout, and stderr to /dev/null */
	open("/dev/null", O_RDONLY);
	open("/dev/null", O_RDWR);
	open("/dev/null", O_RDWR);

	openlog(pname, LOG_PID, facility);
	
	setuid(uid); /* change user */
	
	return (0);				/* success */
}
