#ifndef __OMI_FBXNODE_HPP__
#define __OMI_FBXNODE_HPP__

#include "OMI_FbxProperty.hpp"



namespace OMI {

    class OMI_FbxNode {
        public:
        
		    OMI_FbxNode();
            OMI_FbxNode(std::string name);

            std::uint32_t read(std::ifstream &input, uint32_t start_offset);
            std::uint32_t write(std::ofstream &output, uint32_t start_offset);
            void print(std::string prefix="");
            bool isNull();

            void addProperty(int16_t);
            void addProperty(bool);
            void addProperty(int32_t);
            void addProperty(float);
            void addProperty(double);
            void addProperty(int64_t);
            void addProperty(const std::vector<bool>);
            void addProperty(const std::vector<int32_t>);
            void addProperty(const std::vector<float>);
            void addProperty(const std::vector<double>);
            void addProperty(const std::vector<int64_t>);
            void addProperty(const std::vector<uint8_t>, uint8_t type);
            void addProperty(const std::string);
            void addProperty(const char*);
            void addProperty(FBXProperty);

            void addPropertyNode(const std::string name, int16_t);
            void addPropertyNode(const std::string name, bool);
            void addPropertyNode(const std::string name, int32_t);
            void addPropertyNode(const std::string name, float);
            void addPropertyNode(const std::string name, double);
            void addPropertyNode(const std::string name, int64_t);
            void addPropertyNode(const std::string name, const std::vector<bool>);
            void addPropertyNode(const std::string name, const std::vector<int32_t>);
            void addPropertyNode(const std::string name, const std::vector<float>);
            void addPropertyNode(const std::string name, const std::vector<double>);
            void addPropertyNode(const std::string name, const std::vector<int64_t>);
            void addPropertyNode(const std::string name, const std::vector<uint8_t>, uint8_t type);
            void addPropertyNode(const std::string name, const std::string);
            void addPropertyNode(const std::string name, const char*);

            void addChild(OMI_FbxNode child);
            uint32_t getBytes();

            const std::vector<OMI_FbxNode> getChildren();
            const std::string getName();
        
		private:
            
			std::vector<OMI_FbxNode> children;
            std::vector<FBXProperty> properties;
            std::string name;
    };

}


#endif