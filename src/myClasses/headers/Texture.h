#pragma once
#include <string>
#include<glad/glad.h>
#include<STB/stb_image.h>

class Texture
{
private:
	unsigned int texture_id;
	int tex_width, tex_height , color_channels;
	unsigned char* prosessed_img;
public:
	Texture(const std::string& path);
	~Texture();
	void Bind(unsigned int save_slot = 0);
	void Unbind();


};

