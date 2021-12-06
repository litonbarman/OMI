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