/*
------------------------------------------------
 Open Model Importer (OMI)
------------------------------------------------
 Author : Liton Barman
  
 This software is License under GNU General Public License
 version 3 ( GPLv3 )
 
 Redistribution and use of this software in source and binary forms, 
 with or without modification, are permitted provided that 
 the following conditions are met:
 
 . The source code must be made public whenever a distribution of
   the software is made.
 . Modifications of the software must be realised under the same license
 . Changes made to the Source Code must be documented


*/

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
