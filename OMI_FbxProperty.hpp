#ifndef __OMI_OMI_FbxProperty_HPP__
#define __OMI_OMI_FbxProperty_HPP__


#include <memory>
#include <iostream>
#include <vector>





namespace OMI {

    union OMI_FbxPropertyValue {
        int16_t i16;  // Y
        bool boolean; // C, b
        int32_t i32;  // I, i
        float f32;    // F, f
        double f64;   // D, d
        int64_t i64;  // L, l
    };
    
    class OMI_FbxProperty{
        
		public:
            
			OMI_FbxProperty(std::ifstream &input);
            
			// primitive values
            OMI_FbxProperty(int16_t);
            OMI_FbxProperty(bool);
            OMI_FbxProperty(int32_t);
            OMI_FbxProperty(float);
            OMI_FbxProperty(double);
            OMI_FbxProperty(int64_t);
            
			// arrays
            OMI_FbxProperty(const std::vector<bool>);
            OMI_FbxProperty(const std::vector<int32_t>);
            OMI_FbxProperty(const std::vector<float>);
            OMI_FbxProperty(const std::vector<double>);
            OMI_FbxProperty(const std::vector<int64_t>);
            
			// raw / string
            OMI_FbxProperty(const std::vector<uint8_t>, uint8_t type);
            OMI_FbxProperty(const std::string);
            OMI_FbxProperty(const char *);
		    
            void write(std::ofstream &output);
		    
            std::string to_string();
            char getType();
		    
            bool is_array();
            uint32_t getBytes();
        
		private:
            
			uint8_t type;
            
			OMI_FbxPropertyValue value;
            std::vector<uint8_t> raw;
            std::vector<OMI_FbxPropertyValue> values;
    };

}


#endif