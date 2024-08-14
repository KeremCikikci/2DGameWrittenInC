/*#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Texture * tex;
void main(){
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("Texture",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          600, 400, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	//IMG_Init(IMG_INIT_PNG);
    printf("sdads");
    SDL_Surface * tmpSurface = IMG_Load("powerups.png");
    tex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    SDL_Rect a = {
        0, 0, 200, 200
    };
    SDL_Rect b = {
        201, 201, 200, 200
    };

    while(1==1){
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, tex, &a, &b);
        SDL_RenderPresent(renderer);
    }
}*/