#include "cpng_env.h"

#include <stdlib.h>

struct CpngEnv *cpng_env_new () {
	struct CpngEnv *env = malloc(sizeof(struct CpngEnv));
	return env;
}

struct CpngEnv *cpng_env_delete (struct CpngEnv *env) {
	free(env);
	return NULL;
}


