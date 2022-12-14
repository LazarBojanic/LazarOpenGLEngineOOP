#include "ResourceManager.hpp"

ResourceManager* ResourceManager::instance;

ResourceManager::ResourceManager() {
    this->meshList = new std::vector<Mesh*>();
    this->shaderList = new std::vector<Shader*>();
    this->texture2DList = new std::vector<Texture2D*>();
    this->drawDataList = new std::vector<DrawData*>();
}
ResourceManager::~ResourceManager() {
    delete this->meshList;
    delete this->shaderList;
    delete this->texture2DList;
    delete this->drawDataList;
}
ResourceManager* ResourceManager::getInstance() {
    if (!instance) {
        instance = new ResourceManager();
    }
    return instance;
}

Mesh* ResourceManager::addMesh(Primitive& primitive, std::string name, int positionAttributeNumber, int positionDimensions, int colorAttributeNumber, int colorDimensions, int textureAttributeNumber, int textureDimensions){
    Mesh* mesh = new Mesh(primitive, name, positionAttributeNumber, positionDimensions, colorAttributeNumber, colorDimensions, textureAttributeNumber, textureDimensions);
    if (std::find(this->meshList->begin(), this->meshList->end(), mesh) == this->meshList->end()) {
        this->meshList->push_back(mesh);
        return mesh;
    }
    return nullptr;
}

Shader* ResourceManager::addShader(std::string vertexShaderPath, std::string fragmentShaderPath, std::string name){
    Shader* shader = new Shader(vertexShaderPath, fragmentShaderPath, name);
    if (std::find(this->shaderList->begin(), this->shaderList->end(), shader) == this->shaderList->end()) {
        this->shaderList->push_back(shader);
        return shader;
    }
    return nullptr;
}

Texture2D* ResourceManager::addTexture2D(std::string texture2DPath, bool alpha, std::string name){
    Texture2D* texture2D = new Texture2D(texture2DPath, alpha, name);
    if (std::find(this->texture2DList->begin(), this->texture2DList->end(), texture2D) == this->texture2DList->end()) {
        this->texture2DList->push_back(texture2D);
        return texture2D;
    }
    return nullptr;
}

DrawData* ResourceManager::addDrawData(std::string name, Mesh& mesh, Shader& shader, Texture2D& texture2D){
    DrawData* drawData = new DrawData(name, mesh, shader, texture2D);
    if (std::find(this->drawDataList->begin(), this->drawDataList->end(), drawData) == this->drawDataList->end()) {
        this->drawDataList->push_back(drawData);
        return drawData;
    }
    return nullptr;
}

Mesh* ResourceManager::getMeshByName(std::string name){
    for (int i = 0; i < this->meshList->size(); i++) {
        if (this->meshList->at(i)->getName() == name) {
            return this->meshList->at(i);
        }
    }
    return nullptr;
}

Shader* ResourceManager::getShaderByName(std::string name){
    for (int i = 0; i < this->shaderList->size(); i++) {
        if (this->shaderList->at(i)->getName() == name) {
            return this->shaderList->at(i);
        }
    }
    return nullptr;
}
Texture2D* ResourceManager::getTexture2DByName(std::string name) {
    for (int i = 0; i < this->texture2DList->size(); i++) {
        if (this->texture2DList->at(i)->getName() == name) {
            return this->texture2DList->at(i);
        }
    }
    return nullptr;
}
DrawData* ResourceManager::getDrawDataByName(std::string name){
    for (int i = 0; i < this->drawDataList->size(); i++) {
        if (this->drawDataList->at(i)->getName() == name) {
            return this->drawDataList->at(i);
        }
    }
    return nullptr;
}
void ResourceManager::clear(bool reinitialize) {
    delete this->meshList;
    delete this->shaderList;
    delete this->texture2DList;
    delete this->drawDataList;
    if (reinitialize) {
        this->meshList = new std::vector<Mesh*>();
        this->shaderList = new std::vector<Shader*>();
        this->texture2DList = new std::vector<Texture2D*>();
        this->drawDataList = new std::vector<DrawData*>();
    }
}