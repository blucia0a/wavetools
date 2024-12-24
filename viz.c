#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <SDL2/SDL.h>

/*sample size in bytes*/
#define SAMPLE_TYPE short 
#define SAMPLE_SIZE 2 
#define NUM_SAMPLES 2048 
#define NUM_BUFS 8

#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH 2048 

int main(int argc, char *argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init: %s\n", SDL_GetError());
        return 1;
    }

    // Create window
    SDL_Window *window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 2048, 480, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindow: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateRenderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

   
    int curbuf = 0; 
    char buffer[NUM_BUFS][NUM_SAMPLES * sizeof(SAMPLE_TYPE)] = {0};
    ssize_t bytesRead;

    // Event loop
    SDL_Event event;
    int quit = 0;
    unsigned int x0 = 100, y0 = 100;
    while (!quit) {
   
      // Read from standard input (stdin)
      bytesRead = read(STDIN_FILENO, buffer[curbuf], NUM_SAMPLES * sizeof(SAMPLE_TYPE));

      // Set render color to blue
      SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

      // Clear the screen
      SDL_RenderClear(renderer);

      int num = 0;
      for(int j = curbuf, num = 0; num < NUM_BUFS; j = (j + 1) % NUM_BUFS,num++){
      SAMPLE_TYPE *sampbuf = (SAMPLE_TYPE *)buffer[j];
      SDL_SetRenderDrawColor(renderer, (255. / (float)NUM_BUFS) * (float)num, 0, 255 - (255. / (float)NUM_BUFS) * (float)num, 255);
      for (ssize_t i = 1; i < NUM_SAMPLES; ++i) {

         // Draw a red rectangle
         //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
         //fprintf(stderr,"%d ",(int)sampbuf[i]);
         int y = (int)(((float)(sampbuf[i]+SHRT_MAX) / (float)(2 * SHRT_MAX)) * (float) SCREEN_HEIGHT);
         SDL_Rect rect = { i, y, 2, 2};
         SDL_RenderFillRect(renderer, &rect);
         //SDL_RenderDrawPoint(renderer, i, y);
      
      }
      }
      curbuf = (curbuf + 1) % NUM_BUFS;
      // Update the screen
      SDL_RenderPresent(renderer);



      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          quit = 1;
        }
      }
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
