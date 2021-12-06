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

#ifndef __OMI_OBJMTL_READER_H__

#define __OMI_OBJMTL_READER_H__


#include <vector>

struct OMI_OBJMTL_vec3 {
	float x;
	float y;
	float z;
}; 


struct OMI_MtlInforomation {
	char materialName[180];
	
	OMI_OBJMTL_vec3 Ka;       // ambient
	OMI_OBJMTL_vec3 Kd;       // diffuse
	OMI_OBJMTL_vec3 Ks;       // specular
	
	OMI_OBJMTL_vec3 Ke;       // emissive coeficient   goes together with the ambient diffuse and specular and represent the amount of light radiate/emit from that material (light source)
	
	float Ns;                 // specular highlights   0 - 1000 
	float Ni;                 // refractive index      0.0 - 1.0 
	float d;                  // opacity               0.0 - 1.0
	int illum;                // illumination model    0-any number           can be ignored
	
    char map_Kd[280];         // texture file name
	char refl[280];           // reflection file name but not sure
	
};

class OMI_ObjMtlReader {
	public:
	    OMI_ObjMtlReader();
	    OMI_ObjMtlReader(const char*);
		
	   ~OMI_ObjMtlReader();
	    
		void OMI_ObjMtlLoad(const char*);
		
		void show();
	   
	    void release();
        
	    
	    bool initialised;
		
	    unsigned int noOfMaterial;
	    std::vector<OMI_MtlInforomation> mtl_data;
};

#include "OMI_ObjMtlReader.cpp"

#endif