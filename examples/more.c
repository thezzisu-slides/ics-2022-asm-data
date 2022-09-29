#include <stdio.h>

void variable_overwrite()
{
  volatile int is_admin = 0;
  char username[8];
  scanf("%s", username);
  if (is_admin)
  {
    printf("Hello admin %s!\n", username);
  }
  else
  {
    printf("You are not admin. I am calling 110!\n");
  }
}

void success()
{
  printf("HaHaHa! No one can reach here!\n");
}

void echo()
{
  char buf[8];
  scanf("%s", buf);
  printf("You entered: %s\n", buf);
}

int main()
{
  // variable_overwrite();
  echo();
  return 0;
}