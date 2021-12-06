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


#include "OMI_ObjMtlReader.hpp"

#ifdef win32
#define _CRT_SECURE_NO_DEPRECATE 
#endif

#define __VERBOSE_H__

#include "OMI_verbose.hpp"

#include <vector>
#include <stdio.h>
#include <string.h>
#include <string>
#include <stdlib.h>

OMI_ObjMtlReader::OMI_ObjMtlReader(){
	initialised = false;
}

OMI_ObjMtlReader::OMI_ObjMtlReader(const char* filePath){
	
	initialised = true;
	
	FILE* file = fopen(filePath, "r");
    
	signed int count = -1;
	
	if (file == NULL) {
		printf("Error : Invalid path\n");
		return;
	}
	else{
		
		char line[228];
		
		while(true){
			int res = fscanf(file, "%s", &line);
			
			if(res == EOF){
				break;
			}
			
			if( strcmp(line, "newmtl") == 0){
				fscanf(file, "%s\n", &line);
				count++;
				
				mtl_data.resize( mtl_data.size() + 1 );
				
				strcpy( mtl_data[count].materialName, line);
			}
			else if( strcmp(line, "Ka") == 0 ){
				
				OMI_OBJMTL_vec3 temp;
				
				fscanf(file, "%f %f %f\n", &temp.x, &temp.y, &temp.z);
				
				mtl_data[count].Ka = temp;
				
			}
			else if( strcmp(line, "Kd") == 0 ){
				OMI_OBJMTL_vec3 temp;
				
				fscanf(file, "%f %f %f\n", &temp.x, &temp.y, &temp.z);
				
				mtl_data[count].Kd = temp;
			}
			else if( strcmp(line, "Ks") == 0 ){
				OMI_OBJMTL_vec3 temp;
				
				fscanf(file, "%f %f %f\n", &temp.x, &temp.y, &temp.z);
				
				mtl_data[count].Ks = temp;
			}
			else if( strcmp(line, "Ke") == 0 ){
				OMI_OBJMTL_vec3 temp;
				
				fscanf(file, "%f %f %f\n", &temp.x, &temp.y, &temp.z);
				
				mtl_data[count].Ke = temp;
			}
			else if( strcmp(line, "Ns") == 0 ){
				fscanf(file, "%f\n", &mtl_data[count].Ns);
			}
			else if( strcmp(line, "Ni") == 0 ){
				fscanf(file, "%f\n", &mtl_data[count].Ni);
			}
			else if( strcmp(line, "d") == 0 ){
				fscanf(file, "%f\n", &mtl_data[count].d);
			}
			else if( strcmp(line, "illum") == 0 ){
				fscanf(file, "%d\n", &mtl_data[count].illum);
			}
			else if( strcmp(line, "map_Kd") == 0 ){
				fscanf(file, "%s\n", &mtl_data[count].map_Kd);
			}
			else if( strcmp(line, "refl") == 0 ){
				fscanf(file, "%s\n", &mtl_data[count].refl);
			}
			
		}
		
		
		fclose(file);
	}	
	
	noOfMaterial = count + 1;
};

void OMI_ObjMtlReader::OMI_ObjMtlLoad(const char* filePath){
	printf("\nMtl Loading, none default\n");
	initialised = true;
	
	FILE* file = fopen(filePath, "r");
    
	
	
	signed int count = -1;
	
	if (file == NULL) {
		printf("Error : Invalid path\n");
		return;
	}
	else{
		
		char line[228];
		
		while(true){
			int res = fscanf(file, "%s", &line);
			
			if(res == EOF){
				break;
			}
			
			if( strcmp(line, "newmtl") == 0){
				fscanf(file, "%s\n", &line);
				count++;
				
				mtl_data.resize( mtl_data.size() + 1 );
				
				strcpy( mtl_data[count].materialName, line);
			}
			else if( strcmp(line, "Ka") == 0 ){
				
				OMI_OBJMTL_vec3 temp;
				
				fscanf(file, "%f %f %f\n", &temp.x, &temp.y, &temp.z);
				
				mtl_data[count].Ka = temp;
				
			}
			else if( strcmp(line, "Kd") == 0 ){
				OMI_OBJMTL_vec3 temp;
				
				fscanf(file, "%f %f %f\n", &temp.x, &temp.y, &temp.z);
				
				mtl_data[count].Kd = temp;
			}
			else if( strcmp(line, "Ks") == 0 ){
				OMI_OBJMTL_vec3 temp;
				
				fscanf(file, "%f %f %f\n", &temp.x, &temp.y, &temp.z);
				
				mtl_data[count].Ks = temp;
			}
			else if( strcmp(line, "Ke") == 0 ){
				OMI_OBJMTL_vec3 temp;
				
				fscanf(file, "%f %f %f\n", &temp.x, &temp.y, &temp.z);
				
				mtl_data[count].Ke = temp;
			}
			else if( strcmp(line, "Ns") == 0 ){
				fscanf(file, "%f\n", &mtl_data[count].Ns);
			}
			else if( strcmp(line, "Ni") == 0 ){
				fscanf(file, "%f\n", &mtl_data[count].Ni);
			}
			else if( strcmp(line, "d") == 0 ){
				fscanf(file, "%f\n", &mtl_data[count].d);
			}
			else if( strcmp(line, "illum") == 0 ){
				fscanf(file, "%d\n", &mtl_data[count].illum);
			}
			else if( strcmp(line, "map_Kd") == 0 ){
				fscanf(file, "%s\n", &mtl_data[count].map_Kd);
			}
			else if( strcmp(line, "refl") == 0 ){
				fscanf(file, "%s\n", &mtl_data[count].refl);
			}
			
		}
		
		
		fclose(file);
	}	
	
	noOfMaterial = count + 1;
}

void OMI_ObjMtlReader::show(){
	if(initialised == true){
	  for(int x=0; x<noOfMaterial; x++){
		printf("\n%d. Material name : %s\nKa : %f %f %f\nKd : %f %f %f\nKs : %f %f %f\nKe : %f %f %f\nNs : %f\nNi : %f\nd : %f\nillum : %d\nmap_Kd : %s\nrefl : %s\n", x+1, mtl_data[x].materialName, mtl_data[x].Ka.x, mtl_data[x].Ka.y, mtl_data[x].Ka.z, mtl_data[x].Kd.x, mtl_data[x].Kd.y, mtl_data[x].Kd.z, mtl_data[x].Ks.x, mtl_data[x].Ks.y, mtl_data[x].Ks.z, mtl_data[x].Ke.x, mtl_data[x].Ke.y, mtl_data[x].Ke.z, mtl_data[x].Ns, mtl_data[x].Ni, mtl_data[x].d, mtl_data[x].illum, mtl_data[x].map_Kd, mtl_data[x].refl);
	  }	
	}
	else{
		printf("\nNot initialised yet\n");
	}
};

OMI_ObjMtlReader::~OMI_ObjMtlReader(){
	mtl_data.empty();
};

void OMI_ObjMtlReader::release(){
	mtl_data.empty();
}

