#include "OMI_GbxUtil.hpp"



namespace OMI {

    namespace {
        bool isLittleEndian(){
            uint16_t number = 0x1;
            char *numPtr = (char*)&number;
            return (numPtr[0] == 1);
        }
    }
    
    uint8_t OMI_FbxFileReader::readUint8(){
        return getc();
    }
    
    int8_t OMI_FbxFileReader::readInt8(){
        return getc();
    }
    
    uint16_t OMI_FbxFileReader::readUint16(){
        uint16_t i;
        char *c = (char *)(&i);
		
        if( isLittleEndian() ){
            read(c, 2);
        }
		else{
            c[1] = getc();
            c[0] = getc();
        }
        
		return i;
    }
    
    int16_t OMI_FbxFileReader::readInt16(){
		
        int16_t i;
        char *c = (char *)(&i);
        
		if( isLittleEndian() ){
            read(c, 2);
        }
		else{
            c[1] = getc();
            c[0] = getc();
        }
        
		return i;
    }
    
    uint32_t OMI_FbxFileReader::readUint32(){
		
        uint32_t i;
        char *c = (char *)(&i);
        
		if( isLittleEndian() ){
            read(c, 4);
        }
		else{
            c[3] = getc();
            c[2] = getc();
            c[1] = getc();
            c[0] = getc();
        }
		
        return i;
    }
    
    int32_t OMI_FbxFileReader::readInt32(){
		
        int32_t i;
        char *c = (char *)(&i);
        
		if( isLittleEndian() ){
            read(c, 4);
        }
		else{
            c[3] = getc();
            c[2] = getc();
            c[1] = getc();
            c[0] = getc();
        }
        
		return i;
    }
    
    uint64_t OMI_FbxFileReader::readUint64(){
		
        uint64_t i;
        char *c = (char *)(&i);
        if( isLittleEndian() ){
            read(c, 8);
        }
		else{
            c[7] = getc();
            c[6] = getc();
            c[5] = getc();
            c[4] = getc();
            c[3] = getc();
            c[2] = getc();
            c[1] = getc();
            c[0] = getc();
        }
        
		return i;
    }
    
    
    std::string OMI_FbxFileReader::readString(uint32_t length){
		
        char buffer[length + 1];
        buffer[length] = 0;
        if(length) read(buffer, length);
        
		return std::string(buffer);
    }
    
    float OMI_FbxFileReader::readFloat(){
		
        float f;
        char *c = (char *)(&f);
        if( isLittleEndian() ){
            read(c, 4);
        }
		else{
            c[3] = getc();
            c[2] = getc();
            c[1] = getc();
            c[0] = getc();
        }
        
		return f;
    }
    
    double OMI_FbxFileReader::readDouble(){
		
        double f;
        char *c = (char *)(&f);
        if( isLittleEndian() ){
            read(c, 8);
        }
		else{
            c[7] = getc();
            c[6] = getc();
            c[5] = getc();
            c[4] = getc();
            c[3] = getc();
            c[2] = getc();
            c[1] = getc();
            c[0] = getc();
        }
        
		return f;
    }
    
    OMI_FbxFileReader::OMI_FbxFileReader(std::ifstream *input) : ifstream(input),buffer(NULL),i(0) {}
    
    OMI_FbxFileReader::OMI_FbxFileReader(char *input) : ifstream(NULL),buffer(input),i(0) {}
    
    uint8_t OMI_FbxFileReader::getc(){
		
        uint8_t tmp;
        
		if(ifstream != NULL)
			(*ifstream) >> tmp;
        else
			tmp = buffer[i++];
        
		return tmp;
    }
    
    void OMI_FbxFileReader::read(char *s, uint32_t n){
		
        if(ifstream != NULL) {
            ifstream->read(s, n);
        } 
		else for(uint32_t a = 0; a < n; a++) {
            s[a] = buffer[i++];
        }
    }
    
    OMI_FbxFileWriter::OMI_FbxFileWriter(std::ofstream *output):ofstream(output){}
    
    void OMI_FbxFileWriter::putc(uint8_t c){
        (*ofstream) << c;
    }
    
    void OMI_FbxFileWriter::write(std::uint8_t a){
        putc(a);
    }
    
    void OMI_FbxFileWriter::write(std::int8_t a){
        putc(a);
    }
    
    void OMI_FbxFileWriter::write(std::uint16_t a){
        putc(a);
        putc(a >> 8);
    }
    
    void OMI_FbxFileWriter::write(std::int16_t _a){
        
		uint16_t a = *(int16_t*)((char*) &_a);
        
		putc(a);
        putc(a >> 8);
    }
    
    void OMI_FbxFileWriter::write(std::uint32_t a){
        
		putc(a);
        putc(a >> 8);
        putc(a >> 16);
        putc(a >> 24);
    }
    
    void OMI_FbxFileWriter::write(std::int32_t _a){
        
		uint32_t a = *(uint32_t*)((char*) &_a);
        
		putc(a);
        putc(a >> 8);
        putc(a >> 16);
        putc(a >> 24);
    }
    
    void OMI_FbxFileWriter::write(std::uint64_t a){
        
		putc(a);
        putc(a >> 8);
        putc(a >> 16);
        putc(a >> 24);
        putc(a >> 32);
        putc(a >> 40);
        putc(a >> 48);
        putc(a >> 56);
    }
    
    void OMI_FbxFileWriter::write(std::int64_t _a){
        
		uint64_t a = *(uint64_t*)((char*) &_a);
        
		putc(a);
        putc(a >> 8);
        putc(a >> 16);
        putc(a >> 24);
        putc(a >> 32);
        putc(a >> 40);
        putc(a >> 48);
        putc(a >> 56);
    }
    
    void OMI_FbxFileWriter::write(std::string a){
        for(char c : a) {
            putc(c);
        }
    }
    
    void OMI_FbxFileWriter::write(float a){
        
		char *c = (char *)(&a);
        
		if(isLittleEndian()) {
            for(int i = 0; i < 4; i++) {
                putc(c[i]);
            }
        }
		else{
            for(int i = 3; i >= 0; i--) {
                putc(c[i]);
            }
        }
    }
    
    void OMI_FbxFileWriter::write(double a){
        
		char *c = (char *)(&a);
        
		if(isLittleEndian()) {
            for(int i = 0; i < 8; i++) {
                putc(c[i]);
            }
        }
		else{
            for(int i = 7; i >= 0; i--) {
                putc(c[i]);
            }
        }
    }

}