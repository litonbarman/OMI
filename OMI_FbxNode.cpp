#include "OMI_OMI_FbxNode.hpp"
#include "OMI_FbxUtil.hpp"

using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::uint32_t;
using std::uint8_t;

namespace OMI {

    OMI_FbxNode::OMI_FbxNode(){ }

    OMI_FbxNode::OMI_FbxNode(std::string name):name(name) {}

    uint32_t OMI_FbxNode::read(std::ifstream &input, uint32_t start_offset){
    
	    OMI_FbxFileReader OMI_FbxFileReader(&input);
        uint32_t bytes = 0;

        uint32_t endOffset = OMI_FbxFileReader.readUint32();
        uint32_t numProperties = OMI_FbxFileReader.readUint32();
        uint32_t propertyListLength = OMI_FbxFileReader.readUint32();
        uint8_t nameLength = OMI_FbxFileReader.readUint8();
    
	    name = OMI_FbxFileReader.readString(nameLength);
        bytes += 13 + nameLength;


        for(uint32_t i = 0; i < numProperties; i++) {
            addProperty(FBXProperty(input));
        }
    
	    bytes += propertyListLength;

        while(start_offset + bytes < endOffset) {
            OMI_FbxNode child;
            bytes += child.read(input, start_offset + bytes);
            addChild(std::move(child));
        }
        
		return bytes;
    }

    
	
	uint32_t OMI_FbxNode::write(std::ofstream &output, uint32_t start_offset){
    
	    OMI_FbxFileWriter OMI_FbxFileWriter(&output);

        if(isNull()) {
            for(int i = 0; i < 13; i++) OMI_FbxFileWriter.write((uint8_t) 0);
            return 13;
        }

        uint32_t propertyListLength = 0;
        for(auto prop : properties) propertyListLength += prop.getBytes();
    
	    uint32_t bytes = 13 + name.length() + propertyListLength;
        for(auto child : children) bytes += child.getBytes();

        if(bytes != getBytes()) throw std::string("bytes != getBytes()");
        
		OMI_FbxFileWriter.write(start_offset + bytes); // endOffset
        OMI_FbxFileWriter.write((uint32_t) properties.size()); // numProperties
        OMI_FbxFileWriter.write(propertyListLength); // propertyListLength
        OMI_FbxFileWriter.write((uint8_t) name.length());
        OMI_FbxFileWriter.write(name);


        bytes = 13 + name.length() + propertyListLength;

        for(auto prop : properties) prop.write(output);
        for(auto child : children) bytes += child.write(output,  start_offset + bytes);

        return bytes;
    }

    void OMI_FbxNode::print(std::string prefix){
		
        cout << prefix << "{ \"name\": \"" << name << "\"" << (properties.size() + children.size() > 0 ? ",\n" : "\n");
        
		if(properties.size() > 0) {
            cout << prefix << "  \"properties\": [\n";
            bool hasPrev = false;
            
			for(FBXProperty prop : properties) {
                
				if(hasPrev) cout << ",\n";
                cout << prefix << "    { \"type\": \"" << prop.getType() << "\", \"value\": " << prop.to_string() << " }";
                hasPrev = true;
            }
        
		    cout << "\n";
            cout << prefix << "  ]" << (children.size() > 0 ? ",\n" : "\n");
        }  

        if(children.size() > 0) {
            cout << prefix << "  \"children\": [\n";
            bool hasPrev = false;
        
		    for(OMI_FbxNode node : children) {
                if(hasPrev) cout << ",\n";
                node.print(prefix+"    ");
                hasPrev = true;
            }
            
			cout << "\n";
            cout << prefix << "  ]\n";
        }

        cout << prefix << "}";
    }

    bool OMI_FbxNode::isNull(){
        return children.size() == 0 && properties.size() == 0 && name.length() == 0;
    }

// primitive values
    void OMI_FbxNode::addProperty(int16_t v) { addProperty(FBXProperty(v)); }
    void OMI_FbxNode::addProperty(bool v) { addProperty(FBXProperty(v)); }
    void OMI_FbxNode::addProperty(int32_t v) { addProperty(FBXProperty(v)); }
    void OMI_FbxNode::addProperty(float v) { addProperty(FBXProperty(v)); }
    void OMI_FbxNode::addProperty(double v) { addProperty(FBXProperty(v)); }
    void OMI_FbxNode::addProperty(int64_t v) { addProperty(FBXProperty(v)); }
    // arrays
    void OMI_FbxNode::addProperty(const std::vector<bool> v) { addProperty(FBXProperty(v)); }
    void OMI_FbxNode::addProperty(const std::vector<int32_t> v) { addProperty(FBXProperty(v)); }
    void OMI_FbxNode::addProperty(const std::vector<float> v) { addProperty(FBXProperty(v)); }
    void OMI_FbxNode::addProperty(const std::vector<double> v) { addProperty(FBXProperty(v)); }
    void OMI_FbxNode::addProperty(const std::vector<int64_t> v) { addProperty(FBXProperty(v)); }
    // raw / string
    void OMI_FbxNode::addProperty(const std::vector<uint8_t> v, uint8_t type) { addProperty(FBXProperty(v, type)); }
    void OMI_FbxNode::addProperty(const std::string v) { addProperty(FBXProperty(v)); }
    void OMI_FbxNode::addProperty(const char *v) { addProperty(FBXProperty(v)); }
    
    void OMI_FbxNode::addProperty(FBXProperty prop) { properties.push_back(prop); }
    
    
    void OMI_FbxNode::addPropertyNode(const std::string name, int16_t v) { OMI_FbxNode n(name); n.addProperty(v); addChild(n); }
    void OMI_FbxNode::addPropertyNode(const std::string name, bool v) { OMI_FbxNode n(name); n.addProperty(v); addChild(n); }
    void OMI_FbxNode::addPropertyNode(const std::string name, int32_t v) { OMI_FbxNode n(name); n.addProperty(v); addChild(n); }
    void OMI_FbxNode::addPropertyNode(const std::string name, float v) { OMI_FbxNode n(name); n.addProperty(v); addChild(n); }
    void OMI_FbxNode::addPropertyNode(const std::string name, double v) { OMI_FbxNode n(name); n.addProperty(v); addChild(n); }
    void OMI_FbxNode::addPropertyNode(const std::string name, int64_t v) { OMI_FbxNode n(name); n.addProperty(v); addChild(n); }
    void OMI_FbxNode::addPropertyNode(const std::string name, const std::vector<bool> v) { OMI_FbxNode n(name); n.addProperty(v); addChild(n); }
    void OMI_FbxNode::addPropertyNode(const std::string name, const std::vector<int32_t> v) { OMI_FbxNode n(name); n.addProperty(v); addChild(n); }
    void OMI_FbxNode::addPropertyNode(const std::string name, const std::vector<float> v) { OMI_FbxNode n(name); n.addProperty(v); addChild(n); }
    void OMI_FbxNode::addPropertyNode(const std::string name, const std::vector<double> v) { OMI_FbxNode n(name); n.addProperty(v); addChild(n); }
    void OMI_FbxNode::addPropertyNode(const std::string name, const std::vector<int64_t> v) { OMI_FbxNode n(name); n.addProperty(v); addChild(n); }
    void OMI_FbxNode::addPropertyNode(const std::string name, const std::vector<uint8_t> v, uint8_t type) { OMI_FbxNode n(name); n.addProperty(v, type); addChild(n); }
    void OMI_FbxNode::addPropertyNode(const std::string name, const std::string v) { OMI_FbxNode n(name); n.addProperty(v); addChild(n); }
    void OMI_FbxNode::addPropertyNode(const std::string name, const char *v) { OMI_FbxNode n(name); n.addProperty(v); addChild(n); }
    
    void OMI_FbxNode::addChild(OMI_FbxNode child) { children.push_back(child); }
    
    uint32_t OMI_FbxNode::getBytes() {
        uint32_t bytes = 13 + name.length();
        
		for(auto child : children) {
            bytes += child.getBytes();
        }
        
		for(auto prop : properties) {
            bytes += prop.getBytes();
        }
        
		return bytes;
    }
    
    const std::vector<OMI_FbxNode> OMI_FbxNode::getChildren(){
        return children;
    }
    
    const std::string OMI_FbxNode::getName(){
        return name;
    }

}
