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

#define OMI_debug

#include <iostream>
#include "OMI_ObjReader.hpp"


int main(){
    
//    OMI_ObjMtlReader reader("aventador/LAMBORGHINI_CENTENARIO_INTERIOR_SDC.mtl");
    OMI_ObjReader reader("box/box.obj");
	 // OMI_ObjReader reader("aventador/LAMBORGHINI_CENTENARIO_INTERIOR_SDC.obj");
    
	reader.show();
	//reader.mtl_Data.show();
	

	return 0;
}
