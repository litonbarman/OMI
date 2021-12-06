/*
------------------------------------------------
 Open Model Importer (OMI)
------------------------------------------------
 Author : Liton Barman
  
 This software is License under GNU General Public License
 version 3 ( GLPv3 )
 
 Redistribution and use of this software in source and binary forms, 
 with or without modification, are permitted provided that 
 the following conditions are met:
 
 . The source code must be made public whenever a distribution of
   the software is made.
 . Modifications of the software must be realised under the same license
 . Changes made to the Source Code must be documented


*/

#ifndef __OMI_FILEREADER_H__

#define __OMI_FILEREADER_H__



#ifdef win32

#define _CRT_SECURE_NO_DEPRECATE 

#endif



#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <vector>

struct Vertex3{
	float x;
	float y;
	float z;
};

struct Vertex2{
    float x;
    float y;	
};

class OMI_fileReader {
    public:
        
		OMI_fileReader(const char* filePath);
        
       ~OMI_fileReader();
        
        std::string getLine(){
			
			if(lineNo < noLine){
                std::string line;
			    line = fileData.at(lineNo);
				
			    lineNo++;
				
				if(line == ""){
					lineNo = noLine+2;
				}
				
			    return line;				
			}
			else{
				lineNo = noLine+2;
                return "";				
			}
			
		}		
    private:
	    int lineNo;
		int noLine;
	    std::vector<std::string> fileData;
        		
};


#include "OMI_fileReader.cpp"


#endif