#include <stdio.h>
#ifndef _MSC_VER
#include <unistd.h>
#endif
#include "getPassword.h"

char *passwordPrompt(void) {
  char *password;
#ifndef _MSC_VER
  password = getpass("Enter MySQL Password: ");
#endif
  return password;
}
