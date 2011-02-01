#ifndef __COMPAT_AROS_H
#define __COMPAT_AROS_H

#include <libraries/dos.h>
#include <proto/exec.h>
#include <proto/dos.h>

#include <defines/bsdsocket.h>
#include <exec/types.h>
#undef connect

#define is_dir_sep(c) (((c) == '/') || (c) == ':')

/* Needed for AROS bsdsockets library */
struct Library * SocketBase;

extern int h_errno;


#ifndef POLLIN
struct pollfd {
	int fd;           /* file descriptor */
	short events;     /* requested events */
	short revents;    /* returned events */
};
#define POLLIN 1
#define POLLHUP 2
#endif

#define ITIMER_REAL 0

/*
 * trivial stubs
 */

static inline int fork(void)
{ errno = ENOSYS; return -1; }
static inline unsigned int alarm(unsigned int seconds)
{ return 0; }

/*
 * implementations of missing functions
 */

/* FIXME: Temporary */
int setitimer(int which, const struct itimerval *new_value,
	      struct itimerval *old_value);
char * getpass(const char * prompt);
const char * hstrerror(int err);
int getpagesize();
int poll(struct pollfd *ufds, unsigned int nfds, int timeout);

/* Work around a problem with the AROS gcc port */
void __stack_chk_fail();

/* Workaround for definition of connect as macro in AROS
   headers, which collide with it being used as a structure
   member in git */
static inline int connect(int sockfd, const struct sockaddr *addr,
	    socklen_t addrlen)
{
  return __connect_WB(SocketBase,sockfd,(struct sockaddr *)addr,addrlen);
}

static inline int select(int nfds, fd_set *readfds, fd_set *writefds,
	   fd_set *exceptfds, struct timeval *timeout)
{
  return WaitSelect(nfds,readfds,writefds,exceptfds, timeout,0);
}

static inline char *inet_ntoa(struct in_addr in)
{
  return Inet_NtoA(*(unsigned long *)&in);
}

#define is_absolute_path(path) (strchr(path,':') != 0)

static inline int chk_abort()
{
  Delay(30);
  /* Check & clear CTRL_C signal */
  return CheckSignal(SIGBREAKF_CTRL_C);
}

#define CHKABORT 1

#endif
