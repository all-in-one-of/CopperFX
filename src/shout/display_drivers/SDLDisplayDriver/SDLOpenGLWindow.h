#ifndef SDL_OPENGL_WINDOW_H
#define SDL_OPENGL_WINDOW_H

#include <string>

#ifdef __APPLE__
  #include <unistd.h>
  #include <OpenGL/gl3.h>
  #include <OpenGL/glext.h>
#elif __linux__
  #include <GL/glew.h>
  #include <GL/gl.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>


class SDLOpenGLWindow {
  public :
    SDLOpenGLWindow(const std::string &_name, int _x, int _y, int _width, int _height, int _ppp);

    void makeCurrent() { SDL_GL_MakeCurrent(m_window,m_glContext);}
    void swapWindow() { SDL_GL_SwapWindow(m_window); }

    void resizeWindow(int width, int height);
    int pollEvent(SDL_Event &_event);
    void createSurface();
    void updateImage(const float* _image);
    void draw();
    void setScale(float _f);
    float scale() const {return m_scale;}
    float gamma() const {return m_gamma;}
    float exposure() const {return m_exposure;}
    void setGamma(float _g);
    void setExposure(float _e);
    void reset();
    void setPosition(float _x, float _y);
    enum class RenderMode : int {ALL=0,RED,GREEN,BLUE,ALPHA,GREY};
    void setRenderMode(RenderMode _m);

  private :
    /// @brief width of screen
    int m_width;
    /// @brief height of screen
    int m_height;
    // xpos of window
    int m_x;
    // ypos of window
    int m_y;
    // name of window
    std::string m_name;
    GLuint m_texture;
    GLuint m_shaderProgram;
    GLuint m_vbo;
    GLuint m_vao;
    GLint m_translateUniform;
    GLint m_scaleUniform;
    GLint m_modeUniform;
    GLint m_gammaUniform;
    GLint m_exposureUniform;

    void init();

    SDL_GLContext m_glContext;
    void createGLContext();

    void ErrorExit(const std::string &_msg) const;

    SDL_Window *m_window;
    GLenum m_pixelFormat;
    float m_scale=1.0f;
    float m_xPos=0.0f;
    float m_yPos=0.0f;
    float m_gamma=1.0f;
    float m_exposure=0.0f;

};

#endif // SDL_OPENGL_WINDOW_H