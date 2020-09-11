#include <SDL.h>
#include <SDL_draw.h>
#include <SDL_ttf.h>
#include <Myexc.h>
#include <math.h>

extern const int HEIGHT;
extern const int WIDHT;
extern const int BPP;
extern const int XAXIS;



//line its size of char massive , keep in mind that size will be line-2
double numevent(Sint16 xbegin, Sint16 ybegin, SDL_Surface *&screen, Sint16 sizetext, int line);
//draw func
void draw_myfunc(SDL_Surface *&direct, double xmin, double xmax, Uint32 dotcolor);
//init all our SDL stuff
void all_init (SDL_Surface *&screen, double &x1, double &x2);
//stop window after exit programm
void stopevent(void);
//press n to next window
void nextwindow(void);
//clean all surface and quit
void cleanup(SDL_Surface *&screen);
//graphics lines
void graphic(SDL_Surface *&screen, double x1, double x2);
//blit surface
void apply_surface(SDL_Surface *source, SDL_Surface * direct, Sint16 x, Sint16 y);
//blit text 
SDL_Surface* textfunc(SDL_Surface *screen, int size, const char* messeg, Sint16 x, Sint16 y, SDL_Color);
//from double to string with accuracy
std::string double_string(double digit, int accuracy);