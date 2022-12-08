#pragma once

#include "GLData.hpp"
#include "GameObject.hpp"
#include "GameObject3D.hpp"
#include "ResourceManager.hpp"

class Renderer {
private:
	Renderer();
	~Renderer();
	static Renderer* instance;

public:
	static Renderer* getInstance();
	void draw(GameObject& gameObject, bool scaled);
	void drawUntextured(GameObject& gameObject, bool scaled);
	void draw3DUntextured(GameObject3D& gameObject3D, bool scaled);
	void colorBackground(glm::vec4 color);
};