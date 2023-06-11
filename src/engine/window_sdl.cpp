#define GLEW_STATIC
#include "window_sdl.h"

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"
#include "GL/glew.h"

window_sdl::window_sdl(const std::string& title): m_title_(title),m_sdl_renderer_(nullptr)
{
    
}

window_sdl::~window_sdl()
{
    SDL_GL_DeleteContext(m_context_);
    SDL_DestroyRenderer(m_sdl_renderer_);
    SDL_Quit();
}

auto window_sdl::init(const int x_pos, const int y_pos, const int width, const int height, const bool is_fullscreen) -> bool
{
    bool success = true;
    int flags = SDL_WINDOW_SHOWN |SDL_WINDOW_OPENGL;
    if(is_fullscreen)flags|=SDL_WINDOW_FULLSCREEN;
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        LOG(info)<<"Subsystems init success";
        //openGL attrib
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
        
        m_window_ = std::unique_ptr<SDL_Window,sdl_window_destroyer>(
            SDL_CreateWindow(m_title_.c_str(),x_pos,y_pos,width,height,flags));
        
        if(m_window_)
        {
            LOG(info)<<"Window created";
            m_sdl_renderer_ = SDL_CreateRenderer(m_window_.get(),-1,SDL_RENDERER_ACCELERATED);
            if(m_sdl_renderer_)
            {
                LOG(info)<<"Windows renderer created";
            }
        }
        else
            success = false;

        //openGL context
        m_context_ = SDL_GL_CreateContext(m_window_.get());
        if(m_context_)
            LOG(info)<<"openGL context init successful";
        else
            success = false;

        auto init_glew = glewInit();
        if(init_glew ==  GLEW_OK)
            LOG(info)<<"glew init successful";
        else
            success = false;

        //setting viewport to fit window
        glViewport(0, 0, width, height);
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //enable logging
        glEnable(GL_DEBUG_OUTPUT);
        
        glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
        {
            auto gl_error = glGetError();
            if(gl_error != GL_NO_ERROR && severity==GL_DEBUG_SEVERITY_HIGH)
            {
                LOG(error)<<"OpenGL Log: ("<<id<<")"<<message;
            }
            
        },nullptr);

        //setup imGUI
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; 
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        ImGui::StyleColorsDark();
        ImGui_ImplSDL2_InitForOpenGL(m_window_.get(),m_context_);
        ImGui_ImplOpenGL3_Init("#version 130");
    }
    else
    {
        success = false;
        LOG(info)<<"Subsystems init failed";
    }
    
    return success;
}

auto window_sdl::clear() -> void
{
    glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

auto window_sdl::swap_buffers() -> void
{
    SDL_GL_SwapWindow(m_window_.get());
}

auto window_sdl::update_fps_counter(long delta_time) -> void
{
    double elapsed_seconds;
    m_currentSeconds_ += delta_time / 1000.0;
    elapsed_seconds = m_currentSeconds_ - m_previous_seconds_;
    /* limit text updates to 4 per second */
    if (elapsed_seconds > 0.25)
    {
        m_previous_seconds_ = m_currentSeconds_;
        char tmp[128];
        double fps = (double)m_frameCount_ / elapsed_seconds;
        sprintf_s(tmp, "%s @ fps: %.2f", m_title_.c_str(), fps);
        SDL_SetWindowTitle(m_window_.get(), tmp);
        m_frameCount_ = 0;
    }
    m_frameCount_++;
}

auto window_sdl::get_sdl_renderer() ->  SDL_Renderer*
{
    return m_sdl_renderer_;
}


auto iwindow::create(const std::string& title) -> std::unique_ptr<iwindow>
{
    return std::make_unique<window_sdl>(title);
}



