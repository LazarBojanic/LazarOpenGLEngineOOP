#include "Application.hpp"


Application::Application(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;
    initWindow();
    Game::getInstance(this->width, this->height)->init();
}
Application::~Application() {

}

void Application::initGlfw() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
}
void Application::initGlad() {
    gladLoadGL();
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            std::cout << "Key " << key << " Pressed" << std::endl;
            Game::getInstance()->getKeys()[key] = true;
        }
        else if (action == GLFW_RELEASE) {
            std::cout << "Key " << key << " Released" << std::endl;
            Game::getInstance()->getKeys()[key] = false;
        }
    }
}
void Application::initWindow() {
    initGlfw();
    this->window = glfwCreateWindow(this->width, this->height, "LazarOpenGLGame", NULL, NULL);
    if (this->window == NULL) {
        std::cout << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(this->window);
    initGlad();
    glfwSetKeyCallback(this->window, key_callback);
    glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);
    glfwSwapInterval(1);
}

void Application::run() {
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    while (!glfwWindowShouldClose(this->window)){
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        Game::getInstance(this->width, this->height)->processInput(deltaTime);

        Game::getInstance(this->width, this->height)->update(deltaTime);
        Game::getInstance(this->width, this->height)->render(deltaTime);

        glfwPollEvents();
        glfwSwapBuffers(this->window);
    }
    //ResourceManager::getInstance()->clear();
    glfwTerminate();
}