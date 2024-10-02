#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <iostream>

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
pos[0].x=screen->clip_rect.w/2 - menu[0]->clip_rect.w/2;
pos[0].y=screen->clip_rect.h/2 - menu[0]->clip_rect.h;
pos[1].x=screen->clip_rect.w/2 - menu[0]->clip_rect.w/2;
pos[1].y=screen->clip_rect.h/2 - menu[0]->clip_rect.h;

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
        SDL_FreeSurface(menu[i]);
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
                menu[i]=TTF_RenderText_Solid(font,menus[i],color[1]);
            }
            }else{
                if(selected[i])
                {
                slected[i]=0;
                SDL_FreeSurface(menus[i]);
                menu[i]=TTF_RenderText_Solid(font,menus[i],color[1]);
                }
            }
          }
        case SDL_MOUSEBUTTONDOWN:
        x=event.button.x;
        y=event.button.y;
        for(int i=0;i<NUMMENU;i++)
        {

            if(x>=pos[i].x && x<=pos[i].x+pos[i].w && y>=pos[i].y
             && y<=pos[i].y+pos[i].h)
             return i;
             break;
             case SDL_KEYDOWN:
             if(event.key.keysym.sym==SDLK_ESCAPE)
             return 0;

        }
    }
  }

}





g++ -std=c++11 -Isrc/Include -Lsrc/lib -o wind wind.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2main -lSDL2

g++ -std=c++11 -Isrc/Include -Lsrc/lib -o test7s test7s.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2main -lSDL2

g++ -std=c++11 -Isrc/Include -Lsrc/lib -o testmenu testmenu.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2main -lSDL2


g++ -std=c++11 -Isrc/Include -Lsrc/lib -o m m.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2main -lSDL2 -lSDL2_ttf

g++ -std=c++11 -Isrc/Include -Lsrc/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2main -lSDL2

g++ -std=c++11 -Isrc/Include -Lsrc/lib -o test3 test3.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2main -lSDL2

g++ -std=c++11 -Isrc/Include -Lsrc/lib -o main2 main2.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2main -lSDL2

g++ -std=c++11 -Isrc/Include -Lsrc/lib -o test1 tes1.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2main -lSDL2

g++ -std=c++11 -Isrc/Include -Lsrc/lib -o main1 main1.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2main -lSDL2