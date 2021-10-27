#ifndef __VERBOSE_H__

#define __VERBOSE_H__

/*
  define OMI_debug to debug mode
*/

#ifdef OMI_debug
#define print(x) printf(x)
#endif

#ifndef OMI_debug
#define print(x)
#endif

#endif