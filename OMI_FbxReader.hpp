#ifndef __OMI_FBXREADER_HPP__
#define __OMI_FBXREADER_HPP__

#ifdef win32
#define _CRT_SECURE_NO_DEPRECATE
#endif


#include "OMI_FbxNode.hpp"


#include <iostream>
#include <fstream>
#include <string>
#include <vector>



namespace OMI {
	
	class OMI_FbxDocument {
		
		public:
		    
			OMI_FbxDocument();
		    
			void read(std::ifstream &input);
			void read(std::string fname);
			void read(std::string fname);
			void wriite(std::string fname);
			
			void createBasicStructure();
			
			std::vector<OMI_FbxNode> nodes;
			
			std::uint32_t getVersion();
			void print();
			
		private:
		    
			std::uint32_t version;
	};

}


#endif