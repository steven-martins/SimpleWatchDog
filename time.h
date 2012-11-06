#pragma once

#ifdef _WIN32
	#include <Windows.h>
        int gettimeofday(struct timeval* p, struct timezone *tz);
#else
#include <sys/time.h>
#endif

typedef struct timeval t_tv;

int		tv_sub(t_tv a, t_tv b, t_tv *res);
void	tv_add(t_tv a, t_tv b, t_tv *res);
void	mstotv(long ms, t_tv *res);
int		tvtoms(t_tv a);
