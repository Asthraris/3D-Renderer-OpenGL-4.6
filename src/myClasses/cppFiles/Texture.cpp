#include "../headers/Texture.h"

Texture::Texture(const std::string& path):
	texture_id(0),tex_width(0),tex_height(0), color_channels(0), prosessed_img(nullptr)
{
	stbi_set_flip_vertically_on_load(true);
	prosessed_img = stbi_load(path.c_str(), &tex_width, &tex_height, &color_channels, 0);
	if (!prosessed_img) {
		return ;
	}
	//check out the 4th param
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//make mipmap by doing linear interpolation blurry image
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//clamps the texture in 1:1 ratio
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_width , tex_height , GL_FALSE ,GL_RGB , GL_UNSIGNED_BYTE , prosessed_img);
	//yaha par 0  denoted its not multilevel tex --begineer lvl end me hum diff map with tex use karenge

	glBindTexture(GL_TEXTURE_2D , 0);

}

Texture::~Texture()
{
	stbi_image_free(prosessed_img);
	glDeleteTextures(1 ,&texture_id);
}



void Texture::Bind(unsigned int save_slot)
{
	glActiveTexture(GL_TEXTURE0 + save_slot);
	//similar as glenablevertexarray at that slot to use
	glBindTexture(GL_TEXTURE_2D, texture_id);
	//bind my texture to that slot of sampler in gpu
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
