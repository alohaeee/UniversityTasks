#include <SDL.h>
#include <SDL_draw.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <math.h>
#include "Myexc.h"
#include <string>
using namespace std;

class SDLmain
{
protected:
    SDL_Surface *screen;
    char *font;

    void applysurface(SDL_Surface *source, Sint16 x, Sint16 y);

public:
    const int WIDHT;
    const int HEIGHT;
    const int BPP;
    SDLmain(int w, int h, int b) : WIDHT(w), HEIGHT(h), BPP(b)
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) == -1) throw Myexception(SDL_GetError(), -1);
        if (TTF_Init() == -1) throw Myexception(TTF_GetError(), -1);
        int imgflag= IMG_INIT_PNG|IMG_INIT_JPG;
        if (IMG_Init(imgflag) == -1) throw Myexception(IMG_GetError(), -1);
        screen = SDL_SetVideoMode(WIDHT,HEIGHT,BPP, SDL_HWSURFACE);
        if(screen == NULL) throw Myexception(SDL_GetError(), 101);
        font_init("/usr/share/fonts/truetype/freefont/FreeSerif.ttf");
    };
    ~SDLmain()
    {
        SDL_FreeSurface(screen);
        SDL_Quit();
    };
    void text_surf(Sint16 x, Sint16 y, const char *message, int size, SDL_Color tcolor);
    void image_surf(Sint16 x, Sint16 y, const char *dirimg);
    void image_surf(Sint16 x, Sint16 y, const char *dirimg, int fone[]);
    void exit_event(void);
    void font_init(char *path) { font=path; };
    void blipscreen(int color[]);

};
///////////////////////////
////////////////////
//////////////////////////
///////////////////
//////////////////////////
class Plane :public SDLmain
{
private:
    double h;
    double V0;
    double twhole;
    double curT;
    void time(double y);
    double mathfunc(double x); 
public:
    Plane(int w, int h, int b, double y) : SDLmain(w, h, b)
    {           
        this->h=y;
        this->V0=200 ;
        this->twhole=sqrt(2*y/10)*V0;
    };
    void falling(void);
    void gif_surf(void);
};

std::string double_string(double digit, int accuracy);

