﻿#include <SDL_timer.h>
#include <SDL_video.h>
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"
#include "engine/game.h"
#include "engine/globals.h"
#include "engine/logger.h"
#include "engine/timer.h"
#include "engine/window.h"


struct log_config log_config = {};

int main(int argc, char *argv[])
{
    //create window
    const std::string title = "Dazai";
    log_config.reporting_level = debug;
    log_config.restart = true;
    if(log_config.restart)
        logger::restart();

    timer time;
    const float FIXED_DELTA_TIME = 1/GLOBALS::target_fps;
    float accumulated_time=0.0f;
    
    const auto window =  iwindow::create(title);
    window->init(SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,GLOBALS::screen_size.x,GLOBALS::screen_size.y,false);
    const auto renderer = window->get_sdl_renderer();
    game game;
    game.init(GLOBALS::screen_size.x,GLOBALS::screen_size.y, renderer);
    game.load();

    while(game.is_running)
    {
        //calculate delta time and fps
        float delta_time = time.delta_time();
        window->update_fps_counter(delta_time);
        delta_time /=1000;
        accumulated_time+=delta_time;
        //----------------------------
        
        //updates here----------------
        game.handle_inputs();
        //update
        game.update(delta_time);
        //fixed update
        while(accumulated_time>=FIXED_DELTA_TIME)
        {
            game.fixed_update(FIXED_DELTA_TIME);
            accumulated_time-=FIXED_DELTA_TIME;
        }
        //----------------------------
        
        //imGUI render---------------
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        game.on_gui();
        ImGui::Render();
        //---------------------------

        //render here----------------
        window->clear();
        game.on_debug_draw();
        game.render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        //----------------------------

        //swap buffers and delay-----
        window->swap_buffers();
        //make sure frame is delayed to lock FPS
        time.delay_time();
        //---------------------------
    }

    game.clean();
    //clean window here if requires
    return 0;
}


