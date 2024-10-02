#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

// Screen dimensions
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 700;
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

// Function to display the menu
int displayMenu(SDL_Renderer* renderer) {
    // Load button images
    SDL_Surface* newGameSurface = SDL_LoadBMP("./assests/g39.bmp");
    SDL_Surface* instructionSurface = SDL_LoadBMP("./assests/g56.bmp");
    SDL_Surface* quitSurface = SDL_LoadBMP("./assests/quit.sad.bmp");

    if (!newGameSurface || !instructionSurface || !quitSurface) {
         cerr << "Unable to load button image! SDL_Error: " << SDL_GetError() <<endl;
        return -1;
    }

    SDL_Texture* newGameTexture = SDL_CreateTextureFromSurface(renderer, newGameSurface);
    SDL_Texture* instructionTexture = SDL_CreateTextureFromSurface(renderer, instructionSurface);
    SDL_Texture* quitTexture = SDL_CreateTextureFromSurface(renderer, quitSurface);

    SDL_FreeSurface(newGameSurface);
    SDL_FreeSurface(instructionSurface);
    SDL_FreeSurface(quitSurface);

    if (!newGameTexture || !instructionTexture || !quitTexture) {
         cerr << "Unable to create button texture! SDL_Error: " << SDL_GetError() <<endl;
        return -1;
    }

    // Define button rectangles
    SDL_Rect newGameRect = { 300, 150, 200, 100 };
    SDL_Rect instructionRect = { 220,280, 350, 90 };
    SDL_Rect quitRect = { 270, 400, 240, 80 };

    // Main loop flag for menu
    bool quitMenu = false;
    SDL_Event e;

    while (!quitMenu) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                return 2; // Quit
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);

                if (x >= newGameRect.x && x <= newGameRect.x + newGameRect.w &&
                    y >= newGameRect.y && y <= newGameRect.y + newGameRect.h) {
                    return 0; // New Game
                } else if (x >= instructionRect.x && x <= instructionRect.x + instructionRect.w &&
                           y >= instructionRect.y && y <= instructionRect.y + instructionRect.h) {
                    return 1; // Instruction
                } else if (x >= quitRect.x && x <= quitRect.x + quitRect.w &&
                           y >= quitRect.y && y <= quitRect.y + quitRect.h) {
                    return 2; // Quit
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 45,12,188,75);
        SDL_RenderClear(renderer);

        // Render buttons
        SDL_RenderCopy(renderer, newGameTexture, NULL, &newGameRect);
        SDL_RenderCopy(renderer, instructionTexture, NULL, &instructionRect);
        SDL_RenderCopy(renderer, quitTexture, NULL, &quitRect);

        // Update screen
        SDL_RenderPresent(renderer);

        // Add a small delay to control the frame rate
        SDL_Delay(16); // Approximately 60 FPS
    }

    SDL_DestroyTexture(newGameTexture);
    SDL_DestroyTexture(instructionTexture);
    SDL_DestroyTexture(quitTexture);

    return -1; // Should not reach here
}

// Function to display game over window
void displayGameOver(SDL_Renderer* renderer, TTF_Font* font, int score) {
    // Render "Game Over" text
    SDL_Color textColor = {255, 0, 0, 255}; // Red color
    SDL_Surface* gameOverSurface = TTF_RenderText_Solid(font, "GAME OVER", textColor);
    SDL_Texture* gameOverTexture = SDL_CreateTextureFromSurface(renderer, gameOverSurface);
    SDL_Rect gameOverRect = {SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 200, 100};
    SDL_RenderCopy(renderer, gameOverTexture, NULL, &gameOverRect);
    SDL_FreeSurface(gameOverSurface);
    SDL_DestroyTexture(gameOverTexture);

    // Render score
    string scoreText = "Your Score: " + to_string(score);
    SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    SDL_Rect scoreRect = {SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 50, 200, 50};
    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
    SDL_FreeSurface(scoreSurface);
    SDL_DestroyTexture(scoreTexture);

    // Update screen
    SDL_RenderPresent(renderer);

    // Delay before quitting
    SDL_Delay(10000); // 10 seconds
}


int main(int argc, char* args[]) {
    srand(static_cast<unsigned int>(time(0)));

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
         cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() <<endl;
        return 1;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
         cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() <<endl;
        SDL_Quit();
        return 1;
    }
    

    // Create window
    SDL_Window* window = SDL_CreateWindow("SDL Collision Detection",
                    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
         cerr << "Window could not be created! SDL_Error: " << SDL_GetError() <<endl;
        SDL_Quit();
        return 1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
         cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() <<endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    // Load font
    TTF_Font* font = TTF_OpenFont("./assests/arial.ttf", 28);
    if (!font) {
         cerr << "Failed to load font! TTF_Error: " << TTF_GetError() <<endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Display menu
    int menuChoice = displayMenu(renderer);
    if (menuChoice == 2) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0; // Quit
    } else if (menuChoice == 1) {
        // Load instruction image
        SDL_Surface* instructionSurface = SDL_LoadBMP("./assests/g47.bmp");
        if (!instructionSurface) {
             cerr << "Unable to load instruction image! SDL_Error: " << SDL_GetError() <<endl;
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            return 1;
        }
        SDL_Texture* instructionTexture = SDL_CreateTextureFromSurface(renderer, instructionSurface);
        SDL_FreeSurface(instructionSurface);
        if (!instructionTexture) {
             cerr << "Unable to create instruction texture! SDL_Error: " << SDL_GetError() <<endl;
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            return 1;
        }

        // Display instruction image for 10 seconds
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, instructionTexture, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_Delay(10000); // 10 seconds
        SDL_DestroyTexture(instructionTexture);

        // Go back to menu
        menuChoice = displayMenu(renderer);
        if (menuChoice == 2) {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            return 0; // Quit
        }
    }

    // Load background image
    SDL_Surface* bgSurface = SDL_LoadBMP("./assests/bgcrop.bmp");
    if (!bgSurface) {
         cerr << "Unable to load background image! SDL_Error: " << SDL_GetError() <<endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);
    if (!bgTexture) {
         cerr << "Unable to create background texture! SDL_Error: " << SDL_GetError() <<endl;
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

    if (!surfaceA || !surfaceC || !surfaceD || !surfaceE || !surfaceF || !surfaceG || !surfaceB) {
         cerr << "Unable to load image! SDL_Error: " << SDL_GetError() <<endl;
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

    if (!textureA || !textureC || !textureD || !textureE || !textureF || !textureG || !textureB) {
         cerr << "Unable to create texture! SDL_Error: " << SDL_GetError() <<endl;
        SDL_DestroyTexture(bgTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Define rectangles for the falling images
     vector<SDL_Rect> rectAs(NUM_RECT_A);
     vector<SDL_Rect> rectCs(NUM_RECT_C);
     vector<SDL_Rect> rectDs(NUM_RECT_D);
     vector<SDL_Rect> rectEs(NUM_RECT_E);
     vector<SDL_Rect> rectFs(NUM_RECT_F);
     vector<SDL_Rect> rectGs(NUM_RECT_G);

    for (int i = 0; i < NUM_RECT_A; ++i) {
        rectAs[i] = { rand() % (SCREEN_WIDTH - 100), rand() % (SCREEN_HEIGHT), 50, 80 };
    }
    for (int i = 0; i < NUM_RECT_C; ++i) {
        rectCs[i] = { rand() % (SCREEN_WIDTH - 100), rand() % (SCREEN_HEIGHT), 50, 80 };
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

    SDL_Rect roadRect1 = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_Rect roadRect2 = { 0, -SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT };

    float accumulatedMovement = 0.0f;
    int score = 0;
    bool quit = false;
    bool gameOver = false;
    SDL_Event e;

// Define text color
    SDL_Color textColor = {255, 255, 255, 255}; // White color

    // While application is running
    // main game loop
    Uint32 lastUpdateTime = SDL_GetTicks();
    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                    if (rectB.y>0)
                        rectB.y -= 100;
                        break;
                    case SDLK_DOWN:
                    if (rectB.y<600)
                        rectB.y += 100;
                        break;
                    case SDLK_LEFT:
                    if(rectB.x>0)
                        rectB.x -= 50;
                        break;
                    case SDLK_RIGHT:
                    if(rectB.x<750)
                        rectB.x += 50;
                        break;
                }
            }
        }

        if (!gameOver) {
             Uint32 currentTime = SDL_GetTicks();
        Uint32 elapsedTime = currentTime - lastUpdateTime;
        if (elapsedTime >= 60) { // 1 second
            score += elapsedTime /60; // Increase score by number of seconds
            lastUpdateTime = currentTime;
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
        auto moveRectangles = []( vector<SDL_Rect>& rects) {
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
       
            // Update the score
           // score += 1;
        } 

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, bgTexture, NULL, &roadRect1);
        SDL_RenderCopy(renderer, bgTexture, NULL, &roadRect2);

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

// Render the score
         string scoreText = "Score: " +  to_string(score);
        SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
        SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
        SDL_FreeSurface(scoreSurface);
        int textW = 0;
        int textH = 0;
        SDL_QueryTexture(scoreTexture, NULL, NULL, &textW, &textH);
        SDL_Rect scoreRect = { 10, 10, textW, textH };

        // Render score texture
        SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
        SDL_DestroyTexture(scoreTexture);

        // Check for collision
        auto checkCollisions = [&](const  vector<SDL_Rect>& rects) {
            for (const auto& rect : rects) {
                if (checkCollision(rect, rectB)) {
                     cout << "Collision detected!" <<endl;
                     //cout << "!!!GAME OVER!!!" <<"\n"<<"Your Score:"<<score<<endl;
                   displayGameOver(renderer, font, score);
                   quit = true;
                   // gameOver =true;
                    //showGameOverWindow(score);
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
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
