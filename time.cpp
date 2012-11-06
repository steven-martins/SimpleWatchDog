
#include "time.h"

int	tv_sub(t_tv a, t_tv b, t_tv *res)
{
  int	s;

  if (a.tv_usec < b.tv_usec)
    {
      s = (b.tv_usec - a.tv_usec) / 1000000 + 1;
      b.tv_usec -= 1000000 * s;
      b.tv_sec += s;
    }
  if ((a.tv_usec - b.tv_usec) > 1000000)
    {
      s = (a.tv_usec - b.tv_usec) / 1000000;
      b.tv_usec += 1000000 * s;
      b.tv_sec -= s;
    }
  if (res)
    {
      res->tv_sec = a.tv_sec - b.tv_sec;
      res->tv_usec = a.tv_usec - b.tv_usec;
    }
  if (a.tv_sec < b.tv_sec)
    return (-1);
  return (0);
}

void	tv_add(t_tv a, t_tv b, t_tv *res)
{
  int	s;

  a.tv_sec += b.tv_sec;
  a.tv_usec += b.tv_usec;
  if (a.tv_usec > 1000000)
    {
      s = a.tv_usec / 1000000;
      a.tv_usec = a.tv_usec % 1000000;
      a.tv_sec += s;
    }
  res->tv_sec = a.tv_sec;
  res->tv_usec = a.tv_usec;
}

void	mstotv(long ms, t_tv *res)
{
  res->tv_sec = ms / 1000;
  res->tv_usec = (ms % 1000) * 1000;
}

int	tvtoms(t_tv a)
{
  int	r;

  r = a.tv_sec * 1000 + a.tv_usec / 1000;
  return (r);
}
