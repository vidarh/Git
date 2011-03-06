#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

void __stack_chk_fail() {}

int getpagesize() { return 4096; }

int setitimer(int which, const struct itimerval *new_value,
	      struct itimerval *old_value)
{
  fprintf(stderr,"setitimer() not implemented\n");
  exit(1);
}

int poll(struct pollfd *ufds, unsigned int nfds, int timeout)
{
  fprintf(stderr,"POLL not implemented\n");
  exit(1);
}

int h_errno;

char * getpass(const char * prompt)
{
  static char buf[200];
  fgets(buf,sizeof(buf),stdin);
  return buf;
}

const char * hstrerror(int err)
{
  return "hstrerror() NOT IMPLEMENTED";
}


#ifdef __AROS__
/* FIXME: These are currently missing from AROS pthreads.library.
   They probably need to be implemented in AROS rather than stubbed out
   or worked around here.
*/

void pthread_exit(void * a)
{
}

void *pthread_getspecific(pthread_key_t k)
{
  return 0;
}

int   pthread_key_create(pthread_key_t * k , void (*f)(void *))
{
  return 0;
}

int   pthread_setspecific(pthread_key_t k, const void * s)
{
  return 0;
}

int   pthread_cond_broadcast(pthread_cond_t * c)
{
  return 0;
}

int   pthread_cond_wait(pthread_cond_t * c, pthread_mutex_t * m)
{
  return 0;
}


#endif
