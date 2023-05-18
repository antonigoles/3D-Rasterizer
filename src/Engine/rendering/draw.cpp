#include <SDL2/SDL.h>
#include <Engine/core/core.h>
#include <Engine/Debug.h>
#include <SDL2/SDL_ttf.h>
#include <filesystem>

namespace Engine::Draw 
{


    void draw_simple_triangle( Engine::Core::Vector2 screen_pts[3], Engine::Core::Color color, SDL_Renderer * renderer) 
    {
        const std::vector< SDL_Vertex > verts =
        {
            { SDL_FPoint{ screen_pts[0].x, screen_pts[0].y }, SDL_Color{ 255, 0, 0, 255 }, SDL_FPoint{ 0 }, },
            { SDL_FPoint{ screen_pts[1].x, screen_pts[1].y }, SDL_Color{ 0, 0, 255, 255 }, SDL_FPoint{ 0 }, },
            { SDL_FPoint{ screen_pts[2].x, screen_pts[2].y }, SDL_Color{ 0, 255, 0, 255 }, SDL_FPoint{ 0 }, },
        };
        
        SDL_SetRenderDrawColor( renderer, 0, 0, 0, SDL_ALPHA_OPAQUE );

        SDL_RenderGeometry( renderer, nullptr, verts.data(), verts.size(), nullptr, 0 );
    }

    void draw_text(std::string content, int x, int y, int size, Engine::Core::Color color, SDL_Window *window, SDL_Renderer *renderer) 
    {
        TTF_Font* font;
        font = TTF_OpenFont("../assets/Consolas.ttf", 24);

        bool font_exists = std::filesystem::exists("../assets/Consolas.ttf");

        if ( !font_exists ) {
            Engine::Debug::errorrich("Font does not exist");
            return;
        } 

        if ( !font ) {
            Engine::Debug::errorrich("Failed to load font: " + (std::string)TTF_GetError());
            return;
        }

        SDL_Surface* text;
        // Set color to black
        SDL_Color sdl_color = { (uint8_t)color.r, (uint8_t)color.g, (uint8_t)color.b };

        text = TTF_RenderText_Solid( font, content.c_str(), sdl_color );
        if ( !text ) {
            Debug::errorrich("Failed to render text: " + (std::string)TTF_GetError());
            return;
        }

        SDL_Texture* text_texture;

        text_texture = SDL_CreateTextureFromSurface( renderer, text );

        SDL_Rect dest; 
        double scale = (double)size / (double)18;
        dest.x = x;
        dest.y = y; 
        dest.w = (int)(text->w * scale); 
        dest.h = (int)(text->h * scale);

        SDL_RenderCopy( renderer, text_texture, NULL, &dest );

        SDL_DestroyTexture(text_texture);
		SDL_FreeSurface(text);
    }
}