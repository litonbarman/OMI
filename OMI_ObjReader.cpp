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


#include "OMI_ObjReader.h"
#include "OMI_verbose.h"

#ifdef win32

#define _CRT_SECURE_NO_DEPRECATE 

#endif

#include <string>
#include <cstring>
#include <stdio.h>
#include <vector>

OMI_ObjReader::OMI_ObjReader(const char* filePath){
	
	// calculating file path
	
	int pos = 0;
    int x = 0;

    for (x = 0; x < strlen(filePath); x++) {
        if (filePath[x]=='/') {
            pos = x;
        }
    }
	
	for (x = 0; x < pos; x++) {
        path[x] = filePath[x];
    }

    path[x] = '/';
    path[x+1] = '\0';
	
	// done
	
	FILE* file = fopen(filePath, "r");
    
	noOfObject = -1;
	
	if (file == NULL) {
		printf("Error : OBJ, Invalid path\n");
		return;
	}
	else{
		
		char line[228];
		
		while(true){
			int res = fscanf(file, "%s", &line);
			
			if(res == EOF){
				break;
			}
			else{
				
				if( strcmp(line, "o") == 0 ){
					
					noOfObject++;
					
					Vertices.resize( Vertices.size() + 1 );
					TexCoords.resize( TexCoords.size() + 1 );
					Normals.resize( Normals.size() + 1 );
					
					vertIndex.resize( vertIndex.size() + 1 );
		            textIndex.resize( textIndex.size() + 1 );
		            normIndex.resize( normIndex.size() + 1 );
				}
				
				
				if( strcmp(line, "v") == 0 ){
					Vertex3 vertex;
					
					fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
					
					Vertices[noOfObject].push_back(vertex);
				}
                else if( strcmp(line, "vt") == 0 ){
					Vertex2 vertex;
					
					fscanf(file, "%f %f\n", &vertex.x, &vertex.y);
					
					TexCoords[noOfObject].push_back(vertex);
				}
				else if( strcmp(line, "vn") == 0 ){
					Vertex3 vertex;
					
					fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
					
					Normals[noOfObject].push_back(vertex);
				}
				else if( strcmp(line, "f") == 0 ){
					unsigned int vertex[3]; 
					unsigned int texture[3]; 
					unsigned int normal[3];

                    fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertex[0], &texture[0], &normal[0], &vertex[1], &texture[1], &normal[1], &vertex[2], &texture[2], &normal[2]);

                    for(int c=0; c<3; c++){
						vertIndex[noOfObject].push_back( vertex[c] );
		                textIndex[noOfObject].push_back( texture[c] );
		                normIndex[noOfObject].push_back( normal[c] );
					}				
					
				}
				else if( strcmp(line, "mtllib") == 0 ){
					
					char fname[120];
					
					fscanf(file, "%s\n", &fname);
					
					printf("\nmtllib name : %s\n", fname);
					
					strcpy( mtlfilename, fname );
				}
				
			}
		}
		
		OMI_loadMTL_file(mtlfilename);
		
		fclose(file);
	}
};

void OMI_ObjReader::OMI_loadMTL_file(const char* mtlFileName){
	printf("\nLoading mtl data from : %s\n\n", mtlFileName);
	
	char fna[256];
	strcpy(fna, path);
	strcat(fna, mtlFileName);
	
	printf("\nRelative mtl file path : %s\n", fna);
	mtl_Data.OMI_ObjMtlLoad(fna);
	
}

void OMI_ObjReader::release(){
	    Vertices.empty();
		TexCoords.empty();
		Normals.empty();
		
	    vertIndex.empty();
		textIndex.empty();
		normIndex.empty();
}


void OMI_ObjReader::show(){
	
	for(int s=0; s < noOfObject+1; s++){
		int size = Vertices[s].size();
	
	    for(int x=0; x< size; x++){
		    printf("%f %f %f\n", Vertices[s][x].x, Vertices[s][x].y, Vertices[s][x].z);
	    }
	
	    size = TexCoords[s].size();
	
	    for(int x=0; x< size; x++){
		    printf("%f %f\n", TexCoords[s][x].x, TexCoords[s][x].y);
	    }
	
	    size = Normals[s].size();
	
	    for(int x=0; x< size; x++){
		    printf("%f %f %f\n", Normals[s][x].x, Normals[s][x].y, Normals[s][x].z);
	    }
		
		size = vertIndex[s].size();
	    printf("\nvertINDEX : ");
	    for(int x=0; x< size; x++){
		    printf("%d ", vertIndex[s][x]);
	    }
		
		size = textIndex[s].size();
	    printf("\ntextINDEX : ");
	    for(int x=0; x< size; x++){
		    printf("%d ", textIndex[s][x]);
	    }
		
		size = normIndex[s].size();
	    printf("\nnormINDEX : ");
	    for(int x=0; x< size; x++){
		    printf("%d ", normIndex[s][x]);
	    }
	}
	
	printf("\n\nNo of object : %d\n", noOfObject+1);
	printf("\nmtllib : %s", mtlfilename);
}

OMI_ObjReader::~OMI_ObjReader(){
        Vertices.empty();
		TexCoords.empty();
		Normals.empty();
		
		vertIndex.empty();
		textIndex.empty();
		normIndex.empty();
}