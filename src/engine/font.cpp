#include "font.h"
#include "logger.h"
#include "text_renderer.h"
#include "GL/glew.h"

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
    for (unsigned char c = 0; c <128; c++)
    {
        if(FT_Load_Char(face,c,FT_LOAD_RENDER))
        {
            LOG(error)<<"Can't load glyph: "<<c;
            continue;
        }

        unsigned int texture_id;
        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D,texture_id);
        glTexImage2D
        (
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,                             // RED coz 1 byte internal format
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        character thisCharacter = {
            texture_id, 
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };

        characters.emplace(c,thisCharacter);
        glBindTexture(GL_TEXTURE_2D,0);
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

font::~font()
{
    for (auto character : characters)
    {
        //glDeleteTextures(1,&character.second.texture_id);
    }
    //characters.clear();
}
