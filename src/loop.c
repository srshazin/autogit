#include "autogit.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
struct autogit_status {
  unsigned short int commit_stat;
  unsigned short int push_stat;
};

void init_autogit(const Autogit *agit_props) {
  struct autogit_status agit_stat;
  if (agit_props->commit_interval != 0) {
    printf("commit interval set to %d seconds\n", agit_props->commit_interval);
    agit_stat.commit_stat = 1;

  } else {
    printf("autogit: no commit interval passed\n");
    exit(1);
  }
  if (agit_props->push_interval == 0) {
    printf("auto push is disabled, use -p <seconds> for adding auto push "
           "interval\n");
    agit_stat.push_stat = 0;
  } else {
    if (agit_props->push_interval <= agit_props->commit_interval) {
      printf("push interval <= commit interval, auto commit disabled\n");
      printf("auto push interval is set to %d seconds\n",
             agit_props->push_interval);
      agit_stat.push_stat = 1;
      agit_stat.commit_stat = 0;
    } else {
      printf("auto push interval is set to %d seconds\n",
             agit_props->push_interval);
      agit_stat.push_stat = 1;
      agit_stat.commit_stat = 1;
    }
  }
  system("mkdir hello");
}