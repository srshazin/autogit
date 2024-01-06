#ifndef AUTOGIT
#define AUTOGIT

typedef struct {
  unsigned int commit_interval;
  unsigned int push_interval;
  unsigned int max_commit;
} Autogit;

void init_autogit(const Autogit *agit_props);
#endif
