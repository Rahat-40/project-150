#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>


// Screen dimensions
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float ROAD_SPEED = 1.0f;

// Number of falling rectangles
const int NUM_RECT_A = 1;
const int NUM_RECT_C = 1;
const int NUM_RECT_D = 1;
const int NUM_RECT_E = 1;
const int NUM_RECT_F = 1;
const int NUM_RECT_G = 1;

// Speed of falling rectangles (pixels per frame)
const int RECT_SPEED = 3;


int showmenu(SDL_Surface* screen,TTF_Font* font){

Unit32 time;
int x,y;
const int   NUMMENU =2;
const char * labels [NUMMENU]={"Continue","Exit"};
SDL_Surface* menus[NUMMENU];
bool selected[NUMMENU]={0,0};
SDL_Color color[2]={{255,255,255},{255,0,0};
menus[0]=TTF_RenderText_Solid(font,labels[0],color[0])};
menus[1]=TTF_RenderText_Solid(font,labels[1],color[0])};
SDL_Rect pos[NUMMENU];
pos[0].x=screen->clip_rect.w/2 - menus[0]->clip_rect.w/2;
pos[0].y=screen->clip_rect.h/2 - menus[0]->clip_rect.h;
pos[1].x=screen->clip_rect.w/2 - menus[0]->clip_rect.w/2;
pos[1].y=screen->clip_rect.h/2 - menus[0]->clip_rect.h;

SDL_FillRect(screen,&screen->clip_rect,SDL_MapRGB(screen->format,0x00,0x00,0x00));

SDL_Event event;
while(1)
{
    time=SDL_getTicks();
    while(SDL_PollEvent(&event))
    {
        switch (even.type)
        {
        case SDL_QUIT:
        //SDL_FreeSurface(menu[0]);
        for(int i=0;i<NUMMENU;i++)
        SDL_FreeSurface(menus[i]);
        return 1;
            break;
        
        case SDL_MOUSEMOTION:
        x=event.motion.x;
        y=event.motion.y;
        for(int i=0;i<NUMMENU;i++)
        {

            if(x>=pos[i].x && x<=pos[i].x+pos[i].w && y>=pos[i].y && y<=pos[i].y+pos[i].h)
            {
                if(!selected[i])
            {
                slected[i]=1;
                SDL_FreeSurface(menus[i]);
                menus[i]=TTF_RenderText_Solid(font,labels[i],color[1]);
            }
            }else{
                if(selected[i])
                {
                slected[i]=0;
                SDL_FreeSurface(menus[i]);
                menus[i]=TTF_RenderText_Solid(font,labels[i],color[1]);
                }
            }
          }
          break;
        case SDL_MOUSEBUTTONDOWN:
        x=event.button.x;
        y=event.button.y;
        for(int i=0;i<NUMMENU;i++)
        {

            if(x>=pos[i].x && x<=pos[i].x+pos[i].w && y>=pos[i].y
             && y<=pos[i].y+pos[i].h)
             {
                for(int j=0;j<NUMMENU;j++)
                SDL_FreeSurface(menus[i]);
             return i;
             }
             break;
             case SDL_KEYDOWN:
             if(event.key.keysym.sym==SDLK_ESCAPE)
             {
                for(int i=0;i<NUMMENU;i++)
                SDL_FreeSurface(menus[i]);
             return 0;
             }
        }
    }
    for(int i=0;i<NUMMENU;i++)
    SDL_BlitSurface(menus[i],NULL,screen,&pos[i]);
    SDL_Flip(screen);
    if(1000/30>(SDL_GetTricks()-time))
    SDL_Delay(1000/30-(SDL_GetTricks()-time));
  }

}

// Function to check if two rectangles are colliding
bool checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
    int leftA = a.x;
    int rightA = a.x + a.w;
    int topA = a.y;
    int bottomA = a.y + a.h;

    int leftB = b.x;
    int rightB = b.x + b.w;
    int topB = b.y;
    int bottomB = b.y + b.h;

    if (bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB) {
        return false;
    }

    return true;
}

int main(int argc, char* args[]) {
    srand(static_cast<unsigned int>(time(0)));

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow("SDL Collision Detection",
                    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Load background image
    SDL_Surface* bgSurface = SDL_LoadBMP("./assests/bg.bmp");
    if (!bgSurface) {
        std::cerr << "Unable to load background image! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);
    if (!bgTexture) {
        std::cerr << "Unable to create background texture! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Load images for moving objects
    SDL_Surface* surfaceA = SDL_LoadBMP("./assests/Car-Black_1.bmp");
    SDL_Surface* surfaceC = SDL_LoadBMP("./assests/Car-Blue_1.bmp");
    SDL_Surface* surfaceD = SDL_LoadBMP("./assests/Car-Brown_1.bmp");
    SDL_Surface* surfaceE = SDL_LoadBMP("./assests/Car-Green_1.bmp");
    SDL_Surface* surfaceF = SDL_LoadBMP("./assests/bc.bmp");
    SDL_Surface* surfaceG = SDL_LoadBMP("./assests/Car80.bmp");
    SDL_Surface* surfaceB = SDL_LoadBMP("./assests/Car-Red_1.bmp");

    if (!surfaceA || !surfaceC || !surfaceD || !surfaceE || !surfaceF|| !surfaceG || !surfaceB) {
        std::cerr << "Unable to load image! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyTexture(bgTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Create textures from surfaces
    SDL_Texture* textureA = SDL_CreateTextureFromSurface(renderer, surfaceA);
    SDL_Texture* textureC = SDL_CreateTextureFromSurface(renderer, surfaceC);
    SDL_Texture* textureD = SDL_CreateTextureFromSurface(renderer, surfaceD);
    SDL_Texture* textureE = SDL_CreateTextureFromSurface(renderer, surfaceE);
    SDL_Texture* textureF = SDL_CreateTextureFromSurface(renderer, surfaceF);
    SDL_Texture* textureG = SDL_CreateTextureFromSurface(renderer, surfaceG);
    SDL_Texture* textureB = SDL_CreateTextureFromSurface(renderer, surfaceB);

    SDL_FreeSurface(surfaceA);
    SDL_FreeSurface(surfaceC);
    SDL_FreeSurface(surfaceD);
    SDL_FreeSurface(surfaceE);
    SDL_FreeSurface(surfaceF);
    SDL_FreeSurface(surfaceG);
    SDL_FreeSurface(surfaceB);

    if (!textureA || !textureC || !textureD || !textureE ||!textureF || !textureG || !textureB) {
        std::cerr << "Unable to create texture! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyTexture(bgTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Define rectangles for the falling images
    std::vector<SDL_Rect> rectAs(NUM_RECT_A);
    std::vector<SDL_Rect> rectCs(NUM_RECT_C);
    std::vector<SDL_Rect> rectDs(NUM_RECT_D);
    std::vector<SDL_Rect> rectEs(NUM_RECT_E);
    std::vector<SDL_Rect> rectFs(NUM_RECT_F);
    std::vector<SDL_Rect> rectGs(NUM_RECT_G);

    for (int i = 0; i < NUM_RECT_A; ++i) {
        rectAs[i] = { rand() % (SCREEN_WIDTH - 100), rand() % (SCREEN_HEIGHT ), 50,80  };
    }
    for (int i = 0; i < NUM_RECT_C; ++i) {
        rectCs[i] = { rand() % (SCREEN_WIDTH - 100), rand() % (SCREEN_HEIGHT ), 50, 80 };
    }
    for (int i = 0; i < NUM_RECT_D; ++i) {
        rectDs[i] = { rand() % (SCREEN_WIDTH - 100), rand() % (SCREEN_HEIGHT), 50, 80 };
    }
    for (int i = 0; i < NUM_RECT_E; ++i) {
        rectEs[i] = { rand() % (SCREEN_WIDTH - 100), rand() % (SCREEN_HEIGHT), 50, 80 };
    }
    for (int i = 0; i < NUM_RECT_F; ++i) {
        rectFs[i] = { rand() % (SCREEN_WIDTH - 100), rand() % (SCREEN_HEIGHT), 50, 80 };
    }
    for (int i = 0; i < NUM_RECT_G; ++i) {
        rectGs[i] = { rand() % (SCREEN_WIDTH - 100), rand() % (SCREEN_HEIGHT), 50, 80 };
    }

    // Define rectangle for the controlled image
    SDL_Rect rectB = { 350, 500, 50, 80 };

    SDL_Rect roadRect1 = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Rect roadRect2 = {0, -SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT};

     float accumulatedMovement = 0.0f;

     int i=showmenu(screen,font);
     if(i==1)
     quit=true;

    // Main loop flag
    bool quit = false;

     int i=showmenu(screen,font);
     if(i==1)
     quit=true;
    SDL_Event e;

    // While application is running
    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        rectB.y -= 100;
                        break;
                    case SDLK_DOWN:
                        rectB.y += 100;
                        break;
                    case SDLK_LEFT:
                        rectB.x -= 50;
                        break;
                    case SDLK_RIGHT:
                        rectB.x += 50;
                        break;
                    case SDLK_ESCAPE:
                    int i=showmenu(screen,font);
                    if(i==1)
                    quit=true;
                    break;
                }
            }
        }

        accumulatedMovement += ROAD_SPEED;
        if (accumulatedMovement >= 1.0f) {
            int pixelsToMove = static_cast<int>(accumulatedMovement);
            roadRect1.y += pixelsToMove;
            roadRect2.y += pixelsToMove;
            accumulatedMovement -= pixelsToMove;

            if (roadRect1.y >= SCREEN_HEIGHT) {
                roadRect1.y = roadRect2.y - SCREEN_HEIGHT;
            }
            if (roadRect2.y >= SCREEN_HEIGHT) {
                roadRect2.y = roadRect1.y - SCREEN_HEIGHT;
            }
        }

        

        // Move falling rectangles
        auto moveRectangles = [](std::vector<SDL_Rect>& rects) {
            for (auto& rect : rects) {
                rect.y += RECT_SPEED;
                if (rect.y > SCREEN_HEIGHT) {
                    rect.y = 0;
                    rect.x = rand() % (SCREEN_WIDTH - rect.w);
                }
            }
        };

        moveRectangles(rectAs);
        moveRectangles(rectCs);
        moveRectangles(rectDs);
        moveRectangles(rectEs);
        moveRectangles(rectFs);
        moveRectangles(rectGs);

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, bgTexture, NULL, &roadRect1);
        SDL_RenderCopy(renderer, bgTexture, NULL, &roadRect2);

        // Render background
        //SDL_RenderCopy(renderer, bgTexture, NULL, NULL);

        // Render falling rectangles
        for (const auto& rectA : rectAs) {
            SDL_RenderCopy(renderer, textureA, NULL, &rectA);
        }
        for (const auto& rectC : rectCs) {
            SDL_RenderCopy(renderer, textureC, NULL, &rectC);
        }
        for (const auto& rectD : rectDs) {
            SDL_RenderCopy(renderer, textureD, NULL, &rectD);
        }
        for (const auto& rectE : rectEs) {
            SDL_RenderCopy(renderer, textureE, NULL, &rectE);
        }
        for (const auto& rectF : rectFs) {
            SDL_RenderCopy(renderer, textureF, NULL, &rectF);
        }
        for (const auto& rectG : rectGs) {
            SDL_RenderCopy(renderer, textureG, NULL, &rectG);
        }

        // Render controlled rectangle
        SDL_RenderCopy(renderer, textureB, NULL, &rectB);

        // Check for collision
        auto checkCollisions = [&](const std::vector<SDL_Rect>& rects) {
            for (const auto& rect : rects) {
                if (checkCollision(rect, rectB)) {
                    std::cout << "Collision detected!" << std::endl;
                    //quit = true;
                    return;
                }
            }
        };

        checkCollisions(rectAs);
        checkCollisions(rectCs);
        checkCollisions(rectDs);
        checkCollisions(rectEs);
        checkCollisions(rectFs);
        checkCollisions(rectGs);

        // Update screen
        SDL_RenderPresent(renderer);

        // Add a small delay to control the frame rate
        SDL_Delay(16); // Approximately 60 FPS
    }

    // Free resources and close SDL
    SDL_DestroyTexture(textureA);
    SDL_DestroyTexture(textureC);
    SDL_DestroyTexture(textureD);
    SDL_DestroyTexture(textureE);
    SDL_DestroyTexture(textureF);
    SDL_DestroyTexture(textureG);
    SDL_DestroyTexture(textureB);
    SDL_DestroyTexture(bgTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
