/**
 * Application
*/

#include "Application.hpp"
#include "CubeRender.hpp"
#include "Model3D.hpp"

Application* AppCallback::app = nullptr;

Application::Application()
{
    _firstMouse = true;
}

Application::~Application()
{
    
}

void Application::init(unsigned int width, unsigned int height)
{
    this->width = width;
    this->heigth = height;
    
    initWindow();
    
    initViewport();
    
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Application::loop()
{
    
//    CubeRender cube(glm::vec3(2.0f, 0.0f, -2.0f), "resource/textures/bricks2.jpg");
//    CubeRender cube2(glm::vec3(-2.0f, 0.0f, -2.0f), "resource/textures/container.jpg");
//    CubeRender cube3(glm::vec3(-2.0f, 1.0f, -2.0f), "resource/textures/container.jpg");
//    CubeRender cube4(glm::vec3(-2.0f, 2.0f, -2.0f), "resource/textures/container.jpg");
//    CubeRender cube5(glm::vec3(-2.0f, 3.0f, -2.0f), "resource/textures/container.jpg");
//    CubeRender cube6(glm::vec3(-2.0f, 4.0f, -2.0f), "resource/textures/container.jpg");
//    CubeRender cube7(glm::vec3(-2.0f, 5.0f, -2.0f), "resource/textures/container.jpg");
//    CubeRender cube8(glm::vec3(-2.0f, 6.0f, -2.0f), "resource/textures/container.jpg");
    
    Shader shader;
    shader.init("resource/shader.vs", "resource/shader.fs");

    Model3D model3d("resource/objects/nanosuit/nanosuit.obj");
    while (!glfwWindowShouldClose(_window))
    {
        float currentTime = glfwGetTime();
        _deltaTime = currentTime - _lastTime;
        _lastTime = currentTime;
        
        handlerKeybord(_window);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //TODO
//        cube.render(_camera, this);
//        cube2.render(_camera, this);
//        cube3.render(_camera, this);
//        cube4.render(_camera, this);
//        cube5.render(_camera, this);
//        cube6.render(_camera, this);
//        cube7.render(_camera, this);
//        cube8.render(_camera, this);
        
        shader.useProgram();

        glm::vec3 pos = glm::vec3(0.0f, -8.0f, -22.0f);
        glm::mat4 model         = glm::mat4(1.0f);
        glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);
        
        projection = glm::perspective(glm::radians(_camera.Zoom), (float)width / (float)heigth, 0.1f, 100.0f);
        view = _camera.GetViewMatrix();
        model = glm::translate(model, glm::vec3(pos));
        
        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        
        model3d.Draw(shader);
        
        glfwSwapBuffers(_window);
        
        glfwPollEvents();
    }
    
    glfwTerminate();
}

bool Application::initWindow()
{
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    _window = glfwCreateWindow(width, heigth, "", nullptr, nullptr);
    if (_window == nullptr)
    {
        glfwTerminate();
        return false;
    }
    
    glfwMakeContextCurrent(_window);

    AppCallback::app = this;
    glfwSetCursorPosCallback(_window, &AppCallback::mouseCallback);
    glfwSetScrollCallback(_window, &AppCallback::scrollCallback);
    
    return true;
}

bool Application::initViewport()
{
    gladLoadGL();
    
    int width, height;
    glfwGetFramebufferSize(_window, &width, &height);

    glViewport(0, 0, width, height);
    
    glEnable(GL_DEPTH_TEST);
    
    return true;
}

void Application::handlerKeybord(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        _camera.ProcessKeyboard(FORWARD, _deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        _camera.ProcessKeyboard(LEFT, _deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        _camera.ProcessKeyboard(RIGHT, _deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        _camera.ProcessKeyboard(BACKWARD, _deltaTime);
    }
}

void Application::handlerMouse(GLFWwindow *window, double xpos, double ypos)
{
    if (_firstMouse)
    {
        _lastMouseX = xpos;
        _lastMouseY = ypos;
        _firstMouse = false;
    }
    double xoffset = xpos - _lastMouseX;
    double yoffset = _lastMouseY - ypos;

    _lastMouseX = xpos;
    _lastMouseY = ypos;

    _camera.ProcessMouseMovement(xoffset, yoffset);
}

void Application::handlerScroll(GLFWwindow *window, double xoffset, double yoffset)
{
    _camera.ProcessMouseScroll(yoffset);
}
