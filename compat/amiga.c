#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "../git-compat-util.h"

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


extern char ** environ;

static char **copy_environ(void)
{
	char **env;
	int i = 0;
	while (environ[i])
		i++;
	env = xmalloc((i+1)*sizeof(*env));
	for (i = 0; environ[i]; i++)
		env[i] = xstrdup(environ[i]);
	env[i] = NULL;
	return env;
}

void free_environ(char **env)
{
	int i;
	for (i = 0; env[i]; i++)
		free(env[i]);
	free(env);
}

static int lookup_env(char **env, const char *name, size_t nmln)
{
	int i;

	for (i = 0; env[i]; i++) {
		if (0 == strncmp(env[i], name, nmln)
		    && '=' == env[i][nmln])
			/* matches */
			return i;
	}
	return -1;
}

/*
 * If name contains '=', then sets the variable, otherwise it unsets it
 */
static char **env_setenv(char **env, const char *name)
{
  char *eq = strchr(name, '='); /* FIXME: Strchrnul? */
	int i = lookup_env(env, name, eq-name);

	if (i < 0) {
		if (*eq) {
			for (i = 0; env[i]; i++)
				;
			env = xrealloc(env, (i+2)*sizeof(*env));
			env[i] = xstrdup(name);
			env[i+1] = NULL;
		}
	}
	else {
		free(env[i]);
		if (*eq)
			env[i] = xstrdup(name);
		else
			for (; env[i]; i++)
				env[i] = env[i+1];
	}
	return env;
}

/*
 * Copies global environ and adjusts variables as specified by vars.
 */
char **make_augmented_environ(const char *const *vars)
{
	char **env = copy_environ();

	while (*vars)
		env = env_setenv(env, *vars++);
	return env;
}
