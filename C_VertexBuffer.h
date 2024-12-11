#pragma 
class C_VertexBuffer
{
private :
	
public:
	unsigned int vertexArrayScript;
	unsigned int vertexBufferScript;
	unsigned int vertexIndexedScript;
	C_VertexBuffer();
	~C_VertexBuffer();
	void CreateIndexedBuffer(const float vertices[], const short Nvert, const unsigned int index[], const short Triangles);
	void linkvertArray();
};

