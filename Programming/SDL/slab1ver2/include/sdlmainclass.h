#include <SDL.h>
#include <SDL_draw.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "myexc.h"
/////////////////
////////includes for Interval
////////////////
#include <string>
#include <sstream>
using namespace std;

/////////////////
////////includes for Grapher
////////////////
#include <math.h>
///////////////////////////
////////////////////
///////support func////////
///////////////////
//////////////////////////

double mathFunc(double x);
bool check(double &x1, double &x2);
std::string double_string(double digit, int accuracy);

///////////////////////////
////////////////////
//////////////////////////
///////////////////
//////////////////////////

class SDLmain
{
protected:
    char *font;
    TTF_Font *f[120];
    SDL_Surface *screen;
    const int WIDHT;
    const int HEIGHT;
    const int BPP;
    //func for bliting on main surface
    void applysurface(SDL_Surface *source, Sint16 x, Sint16 y);

public:
    SDLmain(int w, int h, int b) : WIDHT(w), HEIGHT(h), BPP(b)
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) == -1) throw Myexception(SDL_GetError(), -1);
        if (TTF_Init() == -1) throw Myexception(TTF_GetError(), -1);
        int imgflag= IMG_INIT_PNG|IMG_INIT_JPG;
        if (IMG_Init(imgflag) == -1) throw Myexception(IMG_GetError(), -1);
        screen = SDL_SetVideoMode(WIDHT,HEIGHT,BPP, SDL_HWSURFACE);
        if(screen == NULL) throw Myexception(SDL_GetError(), 101);
        font_init("FreeSerif.ttf");
        for(int i=0;i<120; i++)
        {
            f[i]=NULL;
        }
    };
    ~SDLmain()
    {
        SDL_FreeSurface(screen);
        SDL_Quit();
    };
     /*func for bliting text on main surface
    *x and y - screen coordinates
    *message - c.type string 
    *size - size of font
    *tcolor - color with type {R,G,B}*/
    void text_surf(Sint16 x, Sint16 y, const char *message, int size, SDL_Color tcolor);

    /*func for bliting image on main surface
    *x and y - screen coordinates
    *dirimg- direction of ur image*/
    void image_surf(Sint16 x, Sint16 y, const char *dirimg);

    /*func for bliting image on main surface
    with colorkeying
    *x and y - screen coordinates
    *dirimg- direction of ur image
    *fone - int array {R,G,B}*/
    void image_surf(Sint16 x, Sint16 y, const char *dirimg, int fone[]);

    /*simple event
    press ESC or red cross*/
    void exit_event(void);

    //init font path
    void font_init(char *path) { font=path; };

    //blip main surface with typed color {R,G,B}
    void blipscreen(int color[]);

    //flip screen
    void FLIP(void) { SDL_Flip(screen); };
};

///////////////////////////
////////////////////
//////////////////////////
///////////////////
//////////////////////////

class Interval : public SDLmain
{
public:
    Interval(int w, int h, int b) : SDLmain(w,h,b)
    {};

    /* keyevent///bliting main surface
    *x and y - screen coordinates 
    *size - size of font
    *tcolor - color with type {R,G,B}
    !dont forgot to init font*/
    bool keyevent(Sint16 x, Sint16 y, int size, SDL_Color color, double &out_x);
    /* init_x
    string - double in format x
    double - out x
    return flag */
    bool init_x(string, double &);
    //Interface 
    void interface(void);
};

///////////////////////////
////////////////////
//////////////////////////
///////////////////
//////////////////////////

class Grapher : public SDLmain
{
private:
    struct coordinates
    {
        double x1;
        double x2;
        double ymax;
        double ymin;
    } coor;

    struct zoomfactor
    {
        double xzoom;
        double yzoom;
        double DX;
        double cx;
        double cy;
    } zoom;
public: 
    Grapher(int w, int h, int b, double x1, double x2, double (*mathF)(double)) : SDLmain(w, h, b) 
    {
        coor.x1=x1;
        coor.x2=x2;
        coor.ymin=mathFunc(coor.x1);
        coor.ymax=mathFunc(coor.x2);
        zoom.DX=fabs(x2-x1)/(WIDHT*10);
        for(double x=coor.x1; x<=coor.x2; x+=zoom.DX)
        {
            if(coor.ymin>mathFunc(x) && coor.ymin>=-50) coor.ymin=mathFunc(x);
            if(coor.ymax<mathFunc(x) && coor.ymax<=50) coor.ymax=mathFunc(x);
            if(coor.ymin<-50) coor.ymin=-50;
            if(coor.ymax>50) coor.ymax=50;
        }
        zoom.xzoom=WIDHT/fabs(x2-x1);
        zoom.yzoom=HEIGHT/(coor.ymax-coor.ymin);
        zoom.cx = x1;
        zoom.cy = coor.ymin;
    };
    void makegraphic(void);
    /*need to remake
    !!!!!!!!!!!!!!!!!!!!!!!!*/
    void axis(void);
    bool arrow_event(void);
    friend double mathFunc(double);
    bool circle(void);
};

