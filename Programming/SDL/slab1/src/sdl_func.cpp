#include "sdl_func.h"

void all_init(SDL_Surface *&screen, double &x1, double &x2)
{
    
    if(SDL_Init(SDL_INIT_EVERYTHING)==-1) throw Myexception(SDL_GetError(), -1);
    if(TTF_Init() == -1) throw Myexception(TTF_GetError(), -1);

    screen=SDL_SetVideoMode(800,500,BPP, SDL_HWSURFACE);
   
    screen=textfunc(screen,30,"Введите интервал,на котором будет изображён график:",50,20,{255,255,255});
    Draw_Rect(screen,0,0,800,500,0xFFFFFFF);
    Draw_Rect(screen,1,1,800,500,0xFFFFFFF);

    screen=textfunc(screen,60,"x1=",100,160,{255,255,255});
    SDL_Flip(screen);
    x1=numevent(190,160,screen,60, 10);

    screen=textfunc(screen,60,"x2=",100,230,{255,255,255});
    SDL_Flip(screen);
    x2=numevent(190,230,screen,60, 10);
  
    if(x1==x2) throw Myexception("Interval edges are equal", 222);
    if(x1>x2){
        double temp=x1;
        x1=x2;
        x2=temp;
    }

    nextwindow();


    screen=SDL_SetVideoMode(WIDHT,HEIGHT,BPP,SDL_HWSURFACE);
    if (screen == NULL) throw Myexception(SDL_GetError(), 0);
    SDL_WM_SetCaption("Graphic.Lab1", NULL);
    
}
double numevent(Sint16 xbegin, Sint16 ybegin, SDL_Surface *&screen, Sint16 sizetext, int line)
{
    SDL_Event event;
    bool quit=true;
    bool flag=false;
    bool flag1=false;
    char count=-1;
    char *num=(char*)malloc(line);
    memset(num,'\0', line);
    

    while(quit)
    {
        while(SDL_PollEvent(&event))
        {   
            if(event.key.state == 0) continue;
            if(event.key.keysym.sym == 13 && strlen(num)!=0) quit = false ;
            if((event.key.keysym.sym>=48 && event.key.keysym.sym<=57) || event.key.keysym.sym=='.' || event.key.keysym.sym=='-')
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
                        screen=textfunc(screen, sizetext, s,xbegin,ybegin,{255,255,255});
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

void stopevent(void)
{

    SDL_Event event;
    bool quit=true;
    while (quit)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT || 
            event.key.keysym.sym == SDLK_ESCAPE || 
            event.key.keysym.sym  == 13)
            {
                quit=false;
            }
        }
    }
    SDL_PumpEvents();
}

void nextwindow(void){
    SDL_Event event;
    bool quit=true;
    while (quit)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.key.keysym.sym== 13|| event.type == SDL_QUIT)
            {
                quit=false;
            }
        }
    }
    SDL_PumpEvents(); //обновляем очередь
}
void cleanup(SDL_Surface *&screen)
{
    SDL_FreeSurface(screen);
    SDL_Quit();
}

void graphic(SDL_Surface *&screen, double x1, double x2)
{   
    double delta=(x2-x1)/16;
    int del=0;

    for(int i=0;i<=WIDHT;i+=100){ //digits for x
        
        if (del==8) screen=textfunc(screen, 20, double_string(x1+delta*del, 2).c_str(), i+10, XAXIS+20,{255,255,255});
        else{
             screen=textfunc(screen, 20, double_string(x1+delta*del, 2).c_str(), i, XAXIS+20,{255,255,255});
             Draw_Line(screen, i, XAXIS-20, i, XAXIS+20, 0xFFFFFF);
        }
        del++;
    }
    screen=textfunc(screen, 20, double_string(x2, 2).c_str(), WIDHT-51, XAXIS+20,{255,255,255});

    del=0; //digits for y
    delta=sqrt(sin(M_PI/2)/2)/6;
    for(int i=XAXIS; i>0; i-=100)
    {
        if (del==0) screen=textfunc(screen, 23, "0", i+50, XAXIS+25,{255,255,255});
        else{
             Draw_Line(screen,WIDHT/2-20, i, WIDHT/2+20, i, 0xFFFFFF);
             screen=textfunc(screen, 20, double_string(delta*del, 2).c_str(), WIDHT/2-60, i,{255,255,255});
        }
        del++;
    }
    Draw_Line(screen,WIDHT/2-20, XAXIS+100, WIDHT/2+20, XAXIS+100, 0xFFFFFF);
    screen=textfunc(screen, 20, double_string(-delta*del, 2).c_str(), WIDHT/2-60, XAXIS+100,{255,255,255});
    
    
    
    Draw_Line(screen, 0, XAXIS, WIDHT-1, XAXIS, 0xFFFFFF); // x-axis
    Draw_Line(screen,WIDHT-1, XAXIS, WIDHT-21, XAXIS+20, 0xFFFFFF); //x-arrows
    Draw_Line(screen,WIDHT-1, XAXIS, WIDHT-21, XAXIS-20,0xFFFFFF); 
    Draw_Line(screen,WIDHT-21, XAXIS+20, WIDHT-21, XAXIS-20,0xFFFFFF);
    screen=textfunc(screen,25, "X",WIDHT-21, XAXIS-49, {255,255,255}); 
    

    Draw_Line(screen, WIDHT/2-1,0,WIDHT/2-1,HEIGHT-1, 0xFFFFFF); //y-axis
    Draw_Line(screen, WIDHT/2-1,0, WIDHT/2-21, 20,0xFFFFFF); //y-arrows
    Draw_Line(screen, WIDHT/2-1,0, WIDHT/2+21, 20,0xFFFFFF);
    screen=textfunc(screen,25, "Y",WIDHT/2+21, 0, {255,255,255}); 

    SDL_Flip(screen);

}


void apply_surface(SDL_Surface *source, SDL_Surface * direct, Sint16 x, Sint16 y)
{
    SDL_Rect offset;
    offset.x=x;
    offset.y=y;

    if(SDL_BlitSurface(source, NULL, direct, &offset) == -1) throw Myexception(SDL_GetError(), -1);
}


SDL_Surface* textfunc(SDL_Surface *direct,int size, const char* messeg, Sint16 x, Sint16 y, SDL_Color tcolor)
{
    TTF_Font *text;

    text=TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeSerif.ttf", size);
    
    if (text==NULL) throw Myexception(TTF_GetError(), 0);
    SDL_Surface *messege=TTF_RenderUTF8_Solid(text, messeg,tcolor);
    if (messege==NULL) throw Myexception(TTF_GetError(), 0);
    apply_surface(messege,direct,x,y);
    SDL_FreeSurface(messege);
    return direct; 
}

void draw_myfunc(SDL_Surface *&direct, double xmin, double xmax, Uint32 dotcolor)
{
    double y;
    double MX=WIDHT/fabs(xmax-xmin);
    double MY=HEIGHT;
    double dx=pow(MX,-1)/1000;
    Sint16 x0scr, y0scr, xscr, yscr;
    x0scr=floor(-1*xmin*MX);
    y0scr=XAXIS; 
    for(double x=xmin; x<=xmax;x+=dx)
    {
        if(sin(x)>=0)
        {
            y=sqrt(sin(x)/2);
            xscr=x0scr+floor(x*MX);
            yscr=y0scr-floor(y*MY);
            Draw_Pixel(direct, xscr, yscr, 0xFF0000); 
            //SDL_Flip(direct);
            
        }
    }
}

std::string double_string(double digit, int accuracy)
{
    string str=to_string(digit);
    str.resize(str.find('.')+accuracy+1);
    return str;
}



