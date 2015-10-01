#include <unistd.h>
#include <string.h>
#include <stdlib.h>

extern char **environ;

int
main(void)
{
  char *argv[] = { "/Applications/Skype.app/Contents/MacOS/Skype.orig", NULL };
  char **envp = NULL;
  int iii, jjj;

  for (iii = jjj = 0; environ[iii]; ++iii)
  {
    if (!strncmp(environ[iii], "DYLD_INSERT_LIBRARIES", 21))
      continue;
    envp = realloc(envp, ++jjj * sizeof(char *));
    envp[iii] = environ[iii];
  }

  envp = realloc(envp, (jjj + 2) * sizeof(char *));
  envp[jjj] = "DYLD_INSERT_LIBRARIES=/Applications/Skype.app/Contents/MacOS/skype-poll-fix.dylib";
  envp[jjj + 1] = NULL;

  execve(argv[0], argv, envp);
  return 0;
}
