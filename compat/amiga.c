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


