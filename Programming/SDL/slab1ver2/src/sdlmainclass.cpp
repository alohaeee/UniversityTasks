#include "sdlmainclass.h"

///////////////////////////
////////////////////
///////support func////////
///////////////////
//////////////////////////

double mathFunc(double x)
{
    return x*x-6/(x-1)+3;
}
bool check(double &x1, double &x2)
{
    if(x1==x2) return true;
    if(x1>x2) {
        double temp=x2;
        x2=x1;
        x1=temp;
    }
    if(fabs(x2-x1)<0.25 || fabs(x2-x1)>=50) return true;
    
    return false;
}

std::string double_string(double digit, int accuracy)
{
    string str=to_string(digit);
    str.resize(str.find('.')+accuracy+1);
    return str;
}


///////////////////////////
////////////////////
//////////////////////////
///////////////////
//////////////////////////

void SDLmain::text_surf(Sint16 x, Sint16 y, const char *message, int size, SDL_Color tcolor)
{
    if(f[size]==NULL){
        f[size]=TTF_OpenFont(font, size);
        if (f[size] == NULL) throw Myexception(TTF_GetError(), 101);
    }
    SDL_Surface *text=TTF_RenderUTF8_Solid(f[size], message, tcolor);
    if (text == NULL) throw Myexception(TTF_GetError(), 101);
    
    applysurface(text, x, y);
    SDL_FreeSurface(text); //need it???
}

void SDLmain::applysurface(SDL_Surface *source, Sint16 x, Sint16 y)
{
    SDL_Rect offset;
    offset.x=x;
    offset.y=y;

    if(SDL_BlitSurface(source, NULL, screen, &offset) == -1) throw Myexception(SDL_GetError(), -1);
}

void SDLmain::image_surf(Sint16 x, Sint16 y, const char *dirimg)
{
    SDL_Surface *temp=IMG_Load(dirimg);
    if (temp == NULL) throw Myexception(IMG_GetError(), 101);
    SDL_Surface *formatimg=SDL_ConvertSurface(temp, screen->format, NULL);
    if (formatimg == NULL) throw Myexception(IMG_GetError(), 101);

    SDL_FreeSurface(temp);
    applysurface(formatimg, x, y);
    SDL_FreeSurface(formatimg);// aakka
}

void SDLmain::image_surf(Sint16 x, Sint16 y, const char *dirimg, int fone[])
{
    SDL_Surface *temp=IMG_Load(dirimg);
    if (temp == NULL) throw Myexception(IMG_GetError(), 101);
    SDL_Surface *formatimg=SDL_ConvertSurface(temp, screen->format, NULL);
    if (formatimg == NULL) throw Myexception(IMG_GetError(), 101);

    Uint32 colorkey = SDL_MapRGB(formatimg->format, fone[0], fone[1], fone[2]);
    SDL_SetColorKey(formatimg, SDL_SRCCOLORKEY, colorkey); 

    SDL_FreeSurface(temp);
    applysurface(formatimg, x, y);
    SDL_FreeSurface(formatimg);// aakka
}


void SDLmain::exit_event(void)
{
    SDL_Event event;
    bool quit=true; 
    while (quit)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.key.keysym.sym == SDLK_ESCAPE ||
            event.type == SDL_QUIT) quit=false;
        }
    }
    SDL_PumpEvents();
}

void SDLmain::blipscreen(int color[])
{
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, color[0], color[1], color[2]));
}

///////////////////////////
////////////////////
//////////////////////////
///////////////////
//////////////////////////

bool Interval::keyevent(Sint16 x, Sint16 y, int size, SDL_Color color, double &out_x)
{
    SDL_Event event;
    bool flag=true;
    string str;
    
    image_surf(WIDHT-x*3, y-20, "arrow.png");
    SDL_Flip(screen);
    while(flag)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.key.state == 0) continue;
            if(event.key.keysym.sym == 13) flag = false; // enter
            if(event.key.keysym.sym == SDLK_BACKSPACE)
            {
                if (str.size()==0) continue;
                str.pop_back();
                Draw_FillRect(screen,x+str.size()*size/2, y, size/2, size*1.25, 0xFFFFFF);
                SDL_Flip(screen);
            }
            if(event.key.keysym.sym >= 31 && event.key.keysym.sym <= 118)
            {
                if(str.size()!=9)
                {
                    str += event.key.keysym.sym;
                    text_surf(x , y, str.c_str(), size, color);
                    SDL_Flip(screen);
                }
            }
        }
    }
    SDL_PumpEvents();
    Draw_FillRect(screen, WIDHT-x*3, y-20, 120, 70, 0xFFFFFF);
    return init_x(str,out_x);
}

void Interval::interface(void)
{
    blipscreen(new int[3] {255,255,255});
    image_surf(0, 0, "func.png");
    text_surf(270,50, "Введите интервал:", 40, {0,0,0});
    text_surf(10, 120, "x1=", 32, {0,0,0});
    text_surf(10, 200, "x2=", 32, {0,0,0});
    SDL_Flip(screen);
}

bool Interval::init_x(string s, double &x)
{
    istringstream ss(s);
    if(ss >> x) return false;
    return true;
} 


///////////////////////////
////////////////////
//////////////////////////
///////////////////
//////////////////////////

void Grapher::makegraphic(void)
{
    double y;
    Sint16 xscreen, yscreen;
    

    for(double x=coor.x1; x<=coor.x2; x+=zoom.DX)
    {
        y=mathFunc(x); 
        if(y<coor.ymin|| y>coor.ymax) continue;
        xscreen=floor((x-zoom.cx)*zoom.xzoom);
        yscreen=HEIGHT-floor((y-zoom.cy)*zoom.yzoom);
        if(yscreen>=HEIGHT) continue;
        Draw_Pixel(screen, xscreen, yscreen, 0xFF00FF);
    }
    axis();
    SDL_Flip(screen);
    
}

void Grapher::axis(void)
{
    Sint16 x1=0,x2=0,y1=0,y2=HEIGHT-1;
    double dY=fabs(coor.ymax-coor.ymin)/11;
    double ynums=coor.ymin;
    if(coor.x1>0)
    {
        Draw_Line(screen,x1,0,20,30,0xFFFFFF);
        for(int i=HEIGHT-HEIGHT/10-1; i>20; i-=HEIGHT/10)
        {   
            ynums+=dY;
            text_surf(WIDHT/100,i+HEIGHT/100, double_string(ynums, 2).c_str(), 20, {255,255,255});
            Draw_Line(screen,x1, i, 10, i, 0xFFFFFF);
        }
        text_surf(30, 20, "Y", 30, {255,255,255});
    }
    else if(coor.x2<0) 
    {
        x1=WIDHT-1;
        Draw_Line(screen, x1,0, x1-20, 30, 0xFFFFFF); 
        for(int i=HEIGHT-HEIGHT/10-1; i>20; i-=HEIGHT/10)
        {   
            ynums+=dY;
            text_surf(WIDHT-WIDHT/25,i+HEIGHT/100, double_string(ynums, 2).c_str(), 20, {255,255,255});
            Draw_Line(screen,x1, i, x1-20, i, 0xFFFFFF);
        }
        text_surf(x1-WIDHT/25, 20, "Y", 30, {255,255,255});
    }
    else
    {
        x1=floor(-1*zoom.cx*zoom.xzoom);  
        Draw_Line(screen, x1, 0, x1-20, 30, 0xFFFFFF);
        Draw_Line(screen, x1, 0, x1+20, 30, 0xFFFFFF);
        for(int i=HEIGHT-HEIGHT/10-1; i>20; i-=HEIGHT/10)
        {   
            ynums+=dY;
            text_surf(x1+WIDHT/100,i+HEIGHT/100, double_string(ynums, 2).c_str(), 20, {255,255,255});
            Draw_Line(screen,x1-20, i, x1+20, i, 0xFFFFFF);
        }
        text_surf(x1+WIDHT/25, 20, "Y", 30, {255,255,255});
    }
    Draw_Line(screen,x1,y1,x1,y2,0xFFFFFF);

    x1=0; x2=WIDHT-1;
    dY=fabs(coor.x2-coor.x1)/21;
    ynums=coor.x1;
    if(coor.ymin>0) {
        y1=HEIGHT-1;
        Draw_Line(screen, x2-30, y1-20, x2,y1, 0xFFFFFF);
        for(int i=WIDHT/20; i<WIDHT-20; i+=WIDHT/20)
        {   
            ynums+=dY;
            text_surf(i+10, y1-50, double_string(ynums, 2).c_str(), 20, {255,255,255});
            Draw_Line(screen,i, y1, i, y1-20, 0xFFFFFF);
        }
        text_surf(x2-30, y1-60, "X", 30, {255,255,255});
    }
    else if(0>coor.ymax) {
        y1=0;
        Draw_Line(screen, x2-30, 20, x2, y1, 0xFFFFFF);
        for(int i=WIDHT/20; i<WIDHT-20; i+=WIDHT/20)
        {   
            ynums+=dY;
            text_surf(i+10, y1+20, double_string(ynums, 2).c_str(), 20, {255,255,255});
            Draw_Line(screen,i, y1, i, y1+20, 0xFFFFFF);
        }
        text_surf(x2-30, y1+30, "X", 30, {255,255,255});
    }
    else
    {
        y1=HEIGHT-floor(-1*zoom.cy*zoom.yzoom);
        if(y1+20>HEIGHT) Draw_Line(screen, x2-30, HEIGHT-(HEIGHT-y1), x2, y1, 0xFFFFFF);
        else Draw_Line(screen, x2-30, y1+20, x2, y1, 0xFFFFFF);
        if(y1-20<0) Draw_Line(screen, x2-30, 20-y1, x2, y1, 0xFFFFFF);
        else Draw_Line(screen, x2-30, y1-20, x2, y1, 0xFFFFFF);
        for(int i=WIDHT/20; i<WIDHT-20; i+=WIDHT/20)
        {   
            ynums+=dY;
            if(y1<20){
                text_surf(i+10, y1+20, double_string(ynums, 2).c_str(), 20, {255,255,255});
                Draw_Line(screen,i, 20-y1, i, y1+20, 0xFFFFFF);
            }
            else if(y1>HEIGHT-20)
            {
                text_surf(i+10, y1-20, double_string(ynums, 2).c_str(), 20, {255,255,255});
                Draw_Line(screen,i, y1-HEIGHT-20, i, y1+20, 0xFFFFFF);
            }
            else{
                text_surf(i+10, y1+20, double_string(ynums, 2).c_str(), 20, {255,255,255});
                Draw_Line(screen,i, y1-20, i, y1+20, 0xFFFFFF);
            }
        }
        text_surf(x2-30, y1+30, "X", 30, {255,255,255});
        
    }
    Draw_Line(screen,x1,y1,x2,y1,0xFFFFFF);
    
}

bool Grapher::arrow_event(void)
{
    SDL_Event event;
    bool flag=true;
    double dy=fabs(coor.ymax-coor.ymin)/3;
    double dx=fabs(coor.x2-coor.x1)/3;
    while(flag)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.key.state == 0) continue;
            if(event.type == SDL_QUIT) return false;
            switch(event.key.keysym.sym)
            {
                case SDLK_UP:
                    coor.ymin+=dy;
                    coor.ymax+=dy;
                    zoom.cy=coor.ymin;
                    break;
                case SDLK_DOWN:
                    coor.ymin-=dy;
                    coor.ymax-=dy;
                    break;
                case SDLK_RIGHT:
                    coor.x1+=dx;
                    coor.x2+=dx;
                    break;
                case SDLK_LEFT:
                    coor.x1-=dx;
                    coor.x2-=dx;
                    break;
                case 49:
                    if(fabs(coor.x2-coor.x1)<0.5) break;
                    coor.x2*=0.75;
                    coor.ymax*=0.75;
                    coor.x1*=0.75;
                    coor.ymin*=0.75;
                    zoom.xzoom=WIDHT/fabs(coor.x2-coor.x1);
                    zoom.yzoom=HEIGHT/fabs(coor.ymax-coor.ymin);
                    break;
                case 50:
                    if(fabs(coor.ymax-coor.ymin)>200) break;
                    coor.x2*=1.25;
                    coor.ymax*=1.25; 
                    coor.x1*=1.25;
                    coor.ymin*=1.25;
                    zoom.xzoom=WIDHT/fabs(coor.x2-coor.x1);
                    zoom.yzoom=HEIGHT/fabs(coor.ymax-coor.ymin);
                    break;
                case 13:
                    return true;
                case SDLK_ESCAPE:
                    return false;
            }
            zoom.cy=coor.ymin;
            zoom.cx=coor.x1;
            dy=fabs(coor.ymax-coor.ymin)/3;
            dx=fabs(coor.x2-coor.x1)/3;
            blipscreen(new int[3] {0,0,0});
            makegraphic();
        }
    }
    SDL_PumpEvents();
}

bool Grapher::circle(void)
{
    SDL_Event event;
    SDL_PumpEvents();
    while(SDL_PollEvent(&event))
    {
        if(event.key.keysym.sym == 13) return true;
        if(event.type == SDL_QUIT) return false;
    }
}
