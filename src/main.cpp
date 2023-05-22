
#include <SDL_video.h>
#include "engine/window.h"

int main(int argc, char *argv[])
{
    //create window
    const std::string title = "Dazai";
    const int screen_width= 640;
    const int screen_height= 480;

    const auto window = iwindow::create(title);
    window->init(SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,screen_width,screen_height,false);
    
    return 0;
}
