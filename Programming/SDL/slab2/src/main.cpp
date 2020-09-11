#include "myclass.h"
#include <iostream>
#include <math.h>

class FirstWin : public SDLmain
{
public:
    FirstWin(int w, int h, int b) : SDLmain(w,h,b) 
    {};
    double keyboard_event(Sint16 xbegin, Sint16 ybegin, Sint16 sizetext, int line); //shitty func NEED tO do better
};


int main() {
try{
    double height;
    FirstWin obj(800,400,32);
    obj.text_surf(10, 10, "Введите начальную высоту полёта самолёта в метрах:", 26, {255,255,255});
    height=obj.keyboard_event(40,40,26, 11);
    
    Plane airplane(1600,800,32, height);
    if (height<=0 || height>37000) {
        airplane.text_surf(50,300,"Высота полёта введена некорректно!", 100, {255,0,0});
        obj.exit_event();
        exit(1);
    }
    airplane.image_surf(0,airplane.HEIGHT/2,"/home/vladislav/Загрузки/air1.png");
    airplane.gif_surf();
    airplane.image_surf(0, 0,"/home/vladislav/vscoderep/slab2/back.jpg");
    airplane.falling();
    airplane.exit_event();
    return 0;

}
catch(Myexception &e)
{
    cerr << "Error: " << e.GetErrM() << endl;  
    return e.GetValue();     
}
}








double FirstWin::keyboard_event(Sint16 xbegin, Sint16 ybegin, Sint16 sizetext, int line)
{
    SDL_Event event;
    bool quit=true;
    bool flag=false;
    bool flag1=false;
    char count=-1;
    char *num=(char*)malloc(line);
    memset(num,'\0', line);
    
    SDL_Flip(screen);
    while(quit)
    {
        while(SDL_PollEvent(&event))
        {   
            if(event.key.state == 0) continue;
            if(event.key.keysym.sym == 13 && strlen(num)!=0) quit = false ;
            if((event.key.keysym.sym>=48 && event.key.keysym.sym<=57) || event.key.keysym.sym=='.')
            {
                if (count==line-2);
                else{
                    if(count!=-1 && event.key.keysym.sym=='-'); 
                    else if (flag1 && event.key.keysym.sym=='-');
                    else if (flag && event.key.keysym.sym=='.');
                    else {
                        if(event.key.keysym.sym=='-') flag1=true;
                        if (event.key.keysym.sym=='.') flag=true;
                        
                        char *s;
                        count++;
                        s=(char*)calloc(sizeof(char), 2);
                        num[count]=s[0]=event.key.keysym.sym;
                        s[1]='\0';
                        text_surf(xbegin, ybegin, s, sizetext, {255,255,255});
                        free(s);
                        xbegin+=sizetext/2; 
                        SDL_Flip(screen);
                    }
                }

            }
            if(event.key.keysym.sym==SDLK_BACKSPACE) 
            {
                if (count==-1);
                else{
                    if(num[count]=='.') flag=false;
                    if(num[count]=='-') flag1=false;
                    xbegin-=sizetext/2;
                    Draw_FillRect(screen, xbegin ,ybegin, sizetext/2, sizetext, 0x0000000);
                    num[count]='\0';
                    count--;
                    SDL_Flip(screen);

                }
            }
        }
    } 
    SDL_PumpEvents();

     double point=0;
    char flag3;
    int dotind=count+1;
    int i=0;

    if(num[0]=='-') {
        i++;
        flag3=-1 ;
    }
    else flag3=1;
    
    {
        char *flag2;
        if((flag2=strchr(num,'.'))!=NULL) dotind=flag2-num; //get index of dot

    } 
    for(;i<=count; i++){
        if(i<dotind) point+=(num[i]-48)*pow(10,dotind-i-1);
        else if(i>dotind) point+=(num[i]-48)*pow(10, dotind-i);
    }

    return point*flag3;
}