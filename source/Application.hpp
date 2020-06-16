/**
 * Application
 */
#ifndef renderer_hpp
#define renderer_hpp

#include "common.h"
#include "camera.h"

class Application{
public:
    Application();
    ~Application();
    
    void init(unsigned int width, unsigned int height);
    
    void run();
    
    void handlerMouse(GLFWwindow* window, double xpos, double ypos);
    
    void handlerScroll(GLFWwindow* window, double xoffset, double yoffset);
    
    unsigned int        width;
    unsigned int        heigth;
private:
    bool initWindow();
    
    bool initViewport();
    
    void handlerKeybord(GLFWwindow* window);

    
private:

    GLFWwindow*         _window;
    
    double              _deltaTime;
    double              _lastTime;
    double              _lastMouseX;
    double              _lastMouseY;
    
    Camera              _camera;
    bool                _firstMouse;
};


struct AppCallback {
    static Application* app;

    static void mouseCallback(GLFWwindow* window, double a, double b) {
        app->handlerMouse(window, a, b);
    }
    
    static void scrollCallback(GLFWwindow* window, double a, double b) {
        app->handlerScroll(window, a, b);
    }
};

#endif /* renderer_hpp */
