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

#ifndef __OMI_OBJREADER_H__

#define __OMI_OBJREADER_H__

#ifdef win32

#define _CRT_SECURE_NO_DEPRECATE 

#endif


#include "OMI_ObjMtlReader.hpp"


#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <vector>

struct Vertex3 {
	float x;
	float y;
	float z;
};

struct Vertex2 {
    float x;
    float y;	
};


class OMI_ObjReader {

	public:

	    OMI_ObjReader(const char* filePath);
        
       ~OMI_ObjReader();
	   
	    void release();
        
        std::vector<Vertex3> getVertices();
		std::vector<Vertex2> getTexCoords();
		std::vector<Vertex3> getNormals();
 		
		void show();
		
    //private:
	    void OMI_loadMTL_file(const char*);
	
	    char path[100];
		
	    int noOfVertices;
		int noOfTexCoords;
		int noOfNormals;
		int noOfObject;
		char mtlfilename[120];
		
		OMI_ObjMtlReader mtl_Data;
		
		std::vector< std::vector<Vertex3> > Vertices;
		std::vector< std::vector<Vertex2> > TexCoords;
		std::vector< std::vector<Vertex3> > Normals;
		
		std::vector< std::vector<unsigned int> > vertIndex;
		std::vector< std::vector<unsigned int> > textIndex;
		std::vector< std::vector<unsigned int> > normIndex;
};


#include "OMI_ObjReader.cpp"

#endif
