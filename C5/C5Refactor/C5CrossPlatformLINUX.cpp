// COPYRIGHT: Open source by GPL (GNU General Public License)
// Based on C5.0 GPL Edition provided by Rulequest Research Pty Ltd.
//===================================================================
//
// Platform dependet functions implementation for LINUX
//
//===================================================================
//  FEB 2013  Creation:                       Ramirez, GOD RECEPRION
//===================================================================

#ifdef LINUX

#include "C5CrossPlatform.h"

#include <sys/time.h>

double GetSystemClock();
{
    struct timeval	TV;
    struct timezone	TZ={0,0};

    gettimeofday(&TV, &TZ);
    return (double)(TV.tv_sec + TV.tv_usec / 1000000.0);
}

void SetRunTimeStackSize(unsigned long int iValue_KB)
{
  getrlimit(RLIMIT_STACK, &RL);
  RL.rlim_cur = Max(RL.rlim_cur, iValue_KB * 1024);
  if ( RL.rlim_max > 0 ) { /* -1 if unlimited */
    RL.rlim_cur = Min(RL.rlim_max, RL.rlim_cur);
  }
  setrlimit(RLIMIT_STACK, &RL);
}

#endif
