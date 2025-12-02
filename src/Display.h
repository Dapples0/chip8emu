#include <SDL2/SDL.h>
#include <stdexcept>
#include "constants.h"

class Display {
    public:
        Display();
        ~Display();
        void render(SDL_Window *window);
        void draw(SDL_Texture *texture, uint32_t gfx[WIDTH * SCALE]);
        void createTexture();
        SDL_Renderer *getRenderer();
        SDL_Texture *getTexture();

    private:
        SDL_Renderer *renderer = nullptr;
        SDL_Texture *texture = nullptr;

};
