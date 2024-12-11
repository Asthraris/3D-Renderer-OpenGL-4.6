#pragma 
class C_Buffer
{
private :
	
public:
	unsigned int vertexArrayScript;
	unsigned int vertexBufferScript;
	unsigned int vertexIndexedScript;
	C_Buffer();
	void createBuffer(const float vertices[], short nVerts ,const unsigned int index[], const short Triangles);
	void linkvertArray(unsigned short layer  , short stroke , short offset , short start );
	void revoke();
};

