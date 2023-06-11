#pragma once
#include "glm/vec2.hpp"
#include <string>

class texture2d
{
public:
    texture2d() = default;
    texture2d(const std::string& path);
    
    auto get_size()const->glm::vec2;
    auto get_path()const->const std::string&;
    auto get_slot()const->int;
    auto bind(unsigned int slot =0) ->void;
    auto unbind()->void;
    auto destroy() const ->void;
private:
    int m_width_;
    int m_height_;
    int m_slot_;
    unsigned int m_renderer_id_;
    unsigned char* m_raw_data_{};
    int m_channels_count_;
    std::string m_path_;
};
