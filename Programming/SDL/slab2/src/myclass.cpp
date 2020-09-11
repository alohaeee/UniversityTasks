#include "myclass.h"

void SDLmain::text_surf(Sint16 x, Sint16 y, const char *message, int size, SDL_Color tcolor)
{
    TTF_Font *ptr=TTF_OpenFont(font, size);
    if (ptr == NULL) throw Myexception(TTF_GetError(), 101);

    SDL_Surface *text=TTF_RenderUTF8_Solid(ptr, message, tcolor);
    if (text == NULL) throw Myexception(TTF_GetError(), 101);
    
    applysurface(text, x, y);
    SDL_FreeSurface(text); //need it???
    //SDL_Flip(screen);
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


void Plane::falling(void)
{
    double x, y;
    Sint16 screenX, screenY, scrXbegin=0, scrYbegin=HEIGHT-120;
    double xmin=0, xmax=V0*sqrt(2*h/10), ymin=0, ymax=h;
    double Xscale=WIDHT/(2*fabs(xmax-xmin));
    double Yscale=HEIGHT*0.75/fabs(ymax-ymin);
    double DX=pow(Xscale, -1)*2;
    string curH;
    for(double x=xmin; x<=xmax; x+=DX)
    {
        y=mathfunc(x);
        screenX=floor(x*Xscale + scrXbegin);
        screenY=floor(scrYbegin-y*Yscale);
            image_surf(0,0,"/home/vladislav/vscoderep/slab2/back.jpg");
            image_surf(screenX-75,screenY-75,"/home/vladislav/Загрузки/air3.png",new int[3] {0,0,0});
            curH = "H = " + double_string(y,1) + " м.";
            text_surf(WIDHT*0.85,HEIGHT*0.33, curH.c_str(), 30, {0,0,0});
            time(y);
            SDL_Delay(floor(ymax/1000));
            SDL_Flip(screen);
    }
    string ts="T = " + double_string(curT, 2) + " c.";
    for(;screenX<WIDHT-75;screenX+=12)
    {
        image_surf(0,0,"/home/vladislav/vscoderep/slab2/back.jpg");
        image_surf(screenX-75,screenY-75,"/home/vladislav/Загрузки/air3.png",new int[3] {0,0,0});
        text_surf(WIDHT*0.85,HEIGHT*0.25, ts.c_str(), 30, {0,0,0});
        text_surf(WIDHT*0.85,HEIGHT*0.33, "H = 0.0 м.", 30, {0,0,0});
        SDL_Flip(screen);
    }
    SDL_Flip(screen);
}

double Plane::mathfunc(double x)
{
    return h-10*x*x/(2*V0*V0);
}

void Plane::time(double y)
{
    curT=twhole-sqrt(2*y/10)*V0;
    string ts=double_string(curT, 2);
    ts= "T = " + ts + " c.";
    text_surf(WIDHT*0.85,HEIGHT*0.25, ts.c_str(), 30, {0,0,0});
    
}

std::string double_string(double digit, int accuracy)
{
    string str=to_string(digit);
    str.resize(str.find('.')+accuracy+1);
    return str;
}

void Plane::gif_surf(void)
{
   
    
    SDL_Event event;
    string str="/home/vladislav/vscoderep/slab2/back/fe2b3d46f0974263a77962b8304ca8f3-";
    int flag=71;
    bool quit=true;
    while(quit)
    { 
        if(flag==-1) flag=71;
        str.append(double_string(flag,0));
        str.append("jpeg");
        image_surf(0,0,str.c_str());
        image_surf(0, HEIGHT*0.35,"/home/vladislav/Загрузки/air3.png", new int[3] {0,0,0});
        str="/home/vladislav/vscoderep/slab2/back/fe2b3d46f0974263a77962b8304ca8f3-";
        flag--;
        SDL_Delay(40);
        SDL_Flip(screen);
        while(SDL_PollEvent(&event))
        {
            if(event.key.state == 0) continue;
            if(event.key.keysym.sym==13 ) quit=false;    
        }
        
    }
}

