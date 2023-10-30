#include "font.h"
#include <freetype/freetype.h>
#include "logger.h"
#include "GL/glew.h"

const glm::ivec2 font::texture_size = {1024,1024};

font::font(const std::string& path, uint8_t size)
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        LOG(error)<<"Can't init Free type lib";
    }
    else
    {
        LOG(info)<<"Free Type Lib Init: Success";
    }
    
    FT_Face face;
    if(FT_New_Face(ft,path.c_str(),0,&face))
    {
        LOG(error)<<"Can't load font: "<<path;
    }
    else
    {
        LOG(info)<<"Font created: "<<path;
    }

    //creating map
    FT_Set_Pixel_Sizes(face,0,size); // width is adjusted according to height
    glPixelStorei(GL_UNPACK_ALIGNMENT,1); // by default opengl expects 4 bytes alignment but font is only 8-bit(1 byte)
    GLuint atlas_texture_id;
    glGenTextures(1,&atlas_texture_id);
    glBindTexture(GL_TEXTURE_2D,atlas_texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, texture_size.x, texture_size.y, 0,
        GL_RED, GL_UNSIGNED_BYTE, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    FT_GlyphSlot g= face->glyph;

    //for uv coords
    int x = 0;
    int y = 0;
    int max_height=0;
    for (unsigned char c =0;c<128; ++c)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            LOG(error) << "Error: Failed to load glyph";
            continue;
        }

        // Flip the glyph vertically
        for (int i = 0; i < g->bitmap.rows / 2; i++) {
            for (int j = 0; j < g->bitmap.width; j++) {
                std::swap(g->bitmap.buffer[i * g->bitmap.width + j], g->bitmap.buffer[(g->bitmap.rows - 1 - i) * g->bitmap.width + j]);
            }
        }
       
        glTexSubImage2D(GL_TEXTURE_2D,0,x,y,g->bitmap.width,g->bitmap.rows,
            GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);

        //normalize uv
        float u =static_cast<float>(x)/1024;
        float v =static_cast<float>(y)/1024;
        float u_max =static_cast<float>(g->bitmap.width)/1024;
        float v_max =static_cast<float>(g->bitmap.rows)/1024;
        uv_rect uv =
        {
            glm::vec2(u,v),
            glm::vec2(u_max,v_max)
        };
        character character=
        {
            atlas_texture_id,
            {g->bitmap.width, g->bitmap.rows},
            {g->bitmap_left, g->bitmap_top},
            g->advance.x,
            uv
        };
        if(g->bitmap.rows>max_height)
            max_height = g->bitmap.rows;
        
        characters.emplace(c,character);
        x+=g->bitmap.width +1; // advance to next character
        if(x + g->bitmap.width >=1024)
        {
            y+=max_height;
            x=0;
        }
       
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

font::~font()
{
    LOG(warning)<<"Font destructor";
    for (auto character : characters)
    {
        //glDeleteTextures(1,&character.second.texture_id);
    }
    //characters.clear();
}
