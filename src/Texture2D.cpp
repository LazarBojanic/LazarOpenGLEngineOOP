#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>
#include "Texture2D.hpp"

Texture2D::Texture2D() {
}

Texture2D::Texture2D(std::string textureFilePath, bool alpha, std::string name) {
    this->name = name;
    this->wrap_S = GL_REPEAT;
    this->wrap_T = GL_REPEAT;
    this->filterMin = GL_LINEAR;
    this->filterMax = GL_LINEAR;
    this->imageFormat = GL_RGB;
    if (alpha) {
        this->imageFormat = GL_RGBA;
    }
    glGenTextures(1, &this->textureID);
    int tempWidth, tempHeight, tempNumberOfChannels;
    unsigned char* data = stbi_load(textureFilePath.c_str(), &tempWidth, &tempHeight, &tempNumberOfChannels, 0);
    this->width = tempWidth;
    this->height = tempHeight;
    generate(data);
    stbi_image_free(data);
}
Texture2D::~Texture2D() {
}
void Texture2D::generate(unsigned char* data) {
    
    bind(0);
    glTexImage2D(GL_TEXTURE_2D, 0, this->imageFormat, this->width, this->height, 0, this->imageFormat, GL_UNSIGNED_BYTE, data);
    std::cout << glGetError() << std::endl;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrap_S);
    std::cout << glGetError() << std::endl;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrap_T);
    std::cout << glGetError() << std::endl;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filterMin);
    std::cout << glGetError() << std::endl;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filterMax);
    std::cout << glGetError() << std::endl;
    unbind();
}
void Texture2D::bind(unsigned int textureChannel) {
    glActiveTexture(GL_TEXTURE0 + textureChannel);
    glBindTexture(GL_TEXTURE_2D, this->textureID);
}
void Texture2D::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}