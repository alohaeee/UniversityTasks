#include <iostream>
#include "sdlmainclass.h"

using namespace std;

int main() {
try{
    SDLmain *p;
    SDL_Event event;
    double x1, x2;
    bool flag1=true, flag2=true, flag3=true;
    bool flag=true;
    system("ls");
Again:
    while(flag1 || flag2 || flag3)
    {
        p = new Interval(600,400,32);
        ((Interval*)p)->interface();
        flag1=((Interval*)p)->keyevent(70,120,32, {0,0,0}, x1);
        flag2=((Interval*)p)->keyevent(70,200,32, {0,0,0}, x2);  
        flag3=check(x1,x2);
        delete(p);   
    }
    flag1=flag2=flag3=true;
    p = new Grapher(1600, 900, 32, x1, x2, mathFunc);
    ((Grapher*)p)->makegraphic();
    flag=((Grapher*)p)->arrow_event();
    if (flag) goto Again;
    
    return 0;
}
catch(Myexception &e){
    cerr << "Error: " << e.GetErrM() << endl;
    return e.GetValue();
}; 
}