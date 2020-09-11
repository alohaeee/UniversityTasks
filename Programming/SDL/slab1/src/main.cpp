#include <iostream>
#include "sdl_func.h"

const int HEIGHT = 900; //our screen format
const int WIDHT = 1600;
const int BPP = 32;
const int XAXIS = HEIGHT-HEIGHT/5;
double x1, x2;
int main() {
try{
    SDL_Surface *screen=NULL;
    double x1,x2;
    all_init(screen, x1,x2);
    draw_myfunc(screen, x1, x2, 0xFFFFFF);
    graphic(screen,x1 , x2);
    stopevent();
    cleanup(screen);
    return 0;
}
catch (Myexception &e){
    cerr << "Error: " << e.GetErrM() << endl;
    cerr << "Value: " << e.GetValue() << endl;
    return 1;
}
    
}
