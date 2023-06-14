#include "system_animation.h"
#include "../ecs.h"
#include "../../resource_manager.h"
#include "../components/animator.h"
#include "../components/sprite.h"

extern ecs g_ecs;
auto system_animation::update(float delta_time) -> void
{
    for (const auto& entity:entities)
    {
        auto& this_animator = g_ecs.get_component<animator>(entity);
        auto& this_sprite = g_ecs.get_component<sprite>(entity);

        if(this_animator.active._Equal(""))
            continue;
        
        auto& this_animation = this_animator.animations[this_animator.active];
        auto& sprite_sheet = resource_manager::get_texture(this_sprite.texture_id);
        //normalize frame width and height
        const float normalized_frame_width= this_animation.frame_size.x/(sprite_sheet.get_size().x );
        const float normalized_frame_height= this_animation.frame_size.y/(sprite_sheet.get_size().y);
        //inverse row from top to bottom
        const int row = (sprite_sheet.get_size().y/this_animation.frame_size.y) - (float)(this_animation.row+1);
        //normalized y
        float y = normalized_frame_height * static_cast<float>(row);
        //normalized x
        const int current_frame = static_cast<int>(this_animation.time);
        float x = normalized_frame_width * static_cast<float>(current_frame);
        
        this_animation.time += delta_time * this_animation.fps;
        if(this_animation.time >= this_animation.frames)
            this_animation.time = 0;
        
        if(x>1 || y>1)
        {
            LOG(error)<<"Tex coords are out of bound in sprite sheet: "<<this_sprite.texture_id;
        }

        this_sprite.clip_buffer=
        {
          -0.5f, -0.5f, 0.0f, x,                          y,
           0.5f, -0.5f, 0.0f, x + normalized_frame_width, y,
           0.5f,  0.5f, 0.0f, x + normalized_frame_width, y + normalized_frame_height, 
          -0.5f,  0.5f, 0.0f, x,                          y + normalized_frame_height  
        };
    }
}
