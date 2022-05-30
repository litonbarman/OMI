#ifndef __OMI_FBXUTIL_HPP__
#define __OMI_FBXUTIL_HPP__

#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>




namespace OMI {
	// we are
    // assumes that float is 32bit and double is 64bit
    // both conforming to IEEE 754, it does not assume endianness
    // it also assumes that signed integers are two's complement
    class OMI_FbxFileReader {
        
		public:
		
            OMI_FbxFileReader(std::ifstream *input);
            OMI_FbxFileReader(char *input);
		    
            std::uint8_t readUint8();
            std::int8_t readInt8();
            std::uint16_t readUint16();
            std::int16_t readInt16();
            std::uint32_t readUint32();
            std::int32_t readInt32();
            std::uint64_t readUint64();
            std::string readString(uint32_t length);
            float readFloat();
            double readDouble();
		    
            void read(char*, uint32_t);
			
        private:
	
            uint8_t getc();
            std::ifstream *ifstream;
            char *buffer;
            uint32_t i;
    };
	
    class OMI_FbxFileWriter {
    
	    public:
            OMI_FbxFileWriter(std::ofstream *output);
		    
            void write(std::uint8_t);
            void write(std::int8_t);
            void write(std::uint16_t);
            void write(std::int16_t);
            void write(std::uint32_t);
            void write(std::int32_t);
            void write(std::uint64_t);
            void write(std::int64_t);
            void write(std::string);
            void write(float);
            void write(double);
        private:
            void putc(uint8_t);
            std::ofstream *ofstream;
    };
}

#endif