#ifndef WINDOW_H
#define WINDOW_H


#include <memory>
#include <string>
#include "logger.h"

class iwindow
{
public:
    virtual ~iwindow() = default;
    virtual auto init(int x_pos, int y_pos, int width, int height, bool is_fullscreen)->bool = 0;
    
    static auto create(const std::string& title)->std::unique_ptr<iwindow>;
};
#endif
