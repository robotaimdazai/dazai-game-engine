
#include <SDL_timer.h>
#include <SDL_video.h>
#include "engine/game.h"
#include "engine/logger.h"
#include "engine/timer.h"
#include "engine/window.h"

struct log_config log_config = {};

int main(int argc, char *argv[])
{
    //create window
    const std::string title = "Dazai";
    const int screen_width= 640;
    const int screen_height= 480;
    log_config.reporting_level = debug;
    log_config.restart = true;
    if(log_config.restart)
        logger::restart();

    timer time;
    int delta_time;
    const auto window = iwindow::create(title);
    window->init(SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,screen_width,screen_height,false);
    game game;
    game.init(screen_width,screen_height);
    game.load();

    while(game.is_running)
    {
        delta_time = time.delta_time();
        game.handle_inputs();
        game.update(delta_time);

        //render here

        time.delay_time();
    }

    game.clean();
    //clean window here
    
    return 0;
}


