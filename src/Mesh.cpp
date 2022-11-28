#include "Mesh.hpp"

Mesh::Mesh( ) {

}

Mesh::Mesh(float* data, unsigned int dataSize, unsigned int* indices, unsigned int indicesSize, std::string name, int positionAttributeNumber, int positionDimensions, int colorAttributeNumber, int colorDimensions, int textureAttributeNumber, int textureDimensions, const Texture2D& texture2D, unsigned int textureChannel){
	this->data = data;
	this->indices = indices;
	this->vertexCount = indicesSize;
	this->name = name;
	this->textureChannel = textureChannel;
	this->texture2D = new Texture2D(texture2D);
	this->vertexArray = new VertexArray();
	this->vertexArray->bind();
	this->vertexBuffer = new VertexBuffer(
		data,
		dataSize,
		indices,
		indicesSize,
		positionAttributeNumber,
		positionDimensions,
		colorAttributeNumber,
		colorDimensions,
		textureAttributeNumber,
		textureDimensions);
	this->texture2D->bind(this->textureChannel);
	this->vertexArray->unbind();
}

Mesh::~Mesh(){
	delete this->texture2D;
	delete this->vertexArray;
	delete this->vertexBuffer;
	delete[] this->data;
	delete[] this->indices;
}
/*float* Mesh::copyFloatArray(float* source, unsigned int sourceSize) {
	float* result = new float[sourceSize];
	for (int i = 0; i < sourceSize; i++) {
		result[i] = source[i];
	}
	return result;
}
unsigned int* Mesh::copyUnsignedIntArray(unsigned int* source, unsigned int sourceSize) {
	unsigned int* result = new unsigned int[sourceSize];
	for (int i = 0; i < sourceSize; i++) {
		result[i] = source[i];
	}
	return result;
}*/