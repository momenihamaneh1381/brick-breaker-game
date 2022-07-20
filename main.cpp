//ali najafi
//mohammad hossein momeni hamaneh
#include <iostream>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <string>
#include <stdlib.h>
#include<time.h>
#include<fstream>
using namespace std;

typedef struct
{
    int x;
    int y;
    int strength;
}brick[50][8];

SDL_Texture *img;
int img_w, img_h;
SDL_Rect img_rect;
int w,h;
SDL_Rect texr;

SDL_Texture *sako;
int sako_w, sako_h;
SDL_Rect sako_rect;
int w1,h1;
SDL_Rect texr_sako;


void print_one_digit(int X,int Y,int R,SDL_Renderer *renderer);
int number_of_digits(int n);
void p_brick(brick &b,int level);
void loadgame(string name,int &level,int &lives,int &score,int &y);
void shapes(SDL_Renderer *m_renderer,brick b,int level,int x_ball,int y_ball,int x_s,int y_s,int lives,int score,int color);
void shift_down(brick &b);
double rand_theta(double theta,double m,double M);
void toop(int &x_ball,int &y_ball,int x1,int y1,double theta,int x_dir,int y_dir);
void mahdode(brick &b,int x_ball,int y_ball,int &x_dir,int &y_dir,int x_s,int y_s,double &theta,int &x1,int &y1,int &damage,int &broken_brick);

int main( int argc, char * argv[] )
{
     brick b;
     int score=0,lives=3,level=1,damage=1,x_ball=600,y_ball=610,x_s=600,y_s=640,i=0,f=0,j,flag=0,broken_brick=0,x_dir=1,y_dir=-1,w_s=70;
     string name;
     for(i=0;i<50;i++)
    {
        for(j=0;j<8;j++)
            b[i][j].strength=0;
    }
    for(i=0;i<50;i++)
    {
        for(j=0;j<8;j++)
        {
            b[i][j].y=70-70*i;
            b[i][j].x=150*(j+1)-70;
    }
    }
    cout<<"Enter your first name:"<<endl;
    getline(cin,name);
    int choice=1,color;
    cout<<"Choose the color of ball:"<<endl;
    cout<<"Green:1      Blue:2      Pink:3"<<endl;
    cin>>color;
    loadgame(name,level,lives,score,choice);
    if(choice==2){
    cout<<"CHOOSE NEW GAME:1 OR LATEST GAME:2"<<endl;
    cin>>choice;
    }
        if(choice ==1)
    {
        level=1;
        lives=3;
        score=0;
    }

    string namebrick=name+"_brick";
    ifstream in;
    in.open(namebrick.c_str());
    if((in.good())&&(choice==2))
    {
        for(i=0;i<50;i++)
        {
            for(j=0;j<8;j++)
                in>>b[i][j].strength;
        }
    }
    in.close();
    double theta=rand_theta(0,0,(M_PI)/2);

    Uint32 SDL_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER ;
    Uint32 WND_flags = SDL_WINDOW_SHOWN;
    SDL_Window * m_window;
    SDL_Renderer * m_renderer;
    const Uint8 *state=SDL_GetKeyboardState(NULL);
    int img_w, img_h;
    SDL_Rect img_rect;
    SDL_Init( SDL_flags );
    SDL_CreateWindowAndRenderer( 1210, 700, WND_flags, &m_window, &m_renderer );
    SDL_RaiseWindow(m_window);
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    int W = 1210;
    int H = 700;
     SDL_RenderCopy(m_renderer,img,NULL,&texr);


    img = IMG_LoadTexture(m_renderer,"image.jpg");
    SDL_QueryTexture(img , NULL,NULL,&w,&h);
    texr.x=0;
    texr.y=0;
    texr.w=1210;
    texr.h=700;

    sako = IMG_LoadTexture(m_renderer,"sako.jpg");
    SDL_QueryTexture(sako, NULL,NULL,&w1,&h1);
    texr_sako.x=x_s-70;
    texr_sako.y=y_s-10;
    texr_sako.w=140;
    texr_sako.h=20;



    SDL_Texture *endt;
    int endt_w, endt_h;
    SDL_Rect endt_rect;
    int w_endt,h_endt;
    SDL_Rect texr_end;
    endt = IMG_LoadTexture(m_renderer,"end.jpg");
    SDL_QueryTexture(endt, NULL,NULL,&w_endt,&h_endt);
    texr_end.x=0;
    texr_end.y=0;
    texr_end.w=1210;
    texr_end.h=700;

    if((level==1)&&(choice==1))
    {
        p_brick(b,level);
    }
    for(int t=1;t<level;t++)
    shift_down(b);
    shapes(m_renderer,b,level,x_ball,y_ball,x_s,y_s,lives,score,color);
    SDL_RenderPresent( m_renderer );



        game:
            damage=2*level;
            x_ball=600;
            y_ball=610;
            x_s=600;
            y_s=640;
            texr_sako.x=x_s-70;
            texr_sako.y=y_s-10;
            flag=0;
            broken_brick=0;
            shapes(m_renderer,b,level,x_ball,y_ball,x_s,y_s,lives,score,color);
            SDL_RenderPresent(m_renderer);
         while(lives>0)
    {
        SDL_PumpEvents();

        if((state[SDL_SCANCODE_M])&&(state[SDL_SCANCODE_I])&&(state[SDL_SCANCODE_D]))
        {
            for(i=0;i<50;i++)
            for(j=0;j<8;j++)
            {
                if(j%2==0)
                b[i][j].strength=0;
            }
        }
        if((state[SDL_SCANCODE_D])&&(x_s<=1140))
        {
            x_dir=1;
            theta=rand_theta(theta,0,(M_PI)/2);
            x_s++;
            texr_sako.x++;
            if(flag==0)
                x_dir=1;
            x_ball++;
            SDL_Delay(1);
        shapes(m_renderer,b,level,x_ball,y_ball,x_s,y_s,lives,score,color);
        SDL_RenderPresent(m_renderer);
        }

        if((state[SDL_SCANCODE_A])&&(x_s>=70))
           {
            theta=rand_theta(theta,(M_PI)/2,M_PI);
            x_dir=-1;
            x_s--;
            texr_sako.x--;
            if(flag==0)
            x_dir=-1;
            x_ball--;
            SDL_Delay(1);
        shapes(m_renderer,b,level,x_ball,y_ball,x_s,y_s,lives,score,color);
        SDL_RenderPresent(m_renderer);
           }

           if((state[SDL_SCANCODE_SPACE]))
            {
                flag++;
                int x1=x_ball,y1=y_ball;


                while((y_ball<=700)&&(damage>0))
                {
                    mahdode(b,x_ball,y_ball,x_dir,y_dir,x_s,y_s,theta,x1,y1,damage,broken_brick);
                    toop(x_ball,y_ball,x1,y1,theta,x_dir,y_dir);

                    SDL_PumpEvents();
                if((state[SDL_SCANCODE_D])&&(x_s<=1140))
            {
            texr_sako.x++;
            x_s++;
            SDL_Delay(1);
            }
                if((state[SDL_SCANCODE_A])&&(x_s>=70))
            {
            texr_sako.x--;
            x_s--;
            SDL_Delay(1);
            }


                    shapes(m_renderer,b,level,x_ball,y_ball,x_s,y_s,lives,score,color);
                    SDL_RenderPresent(m_renderer);
                }
                if(damage<=0)
                    {
                       for(i=0;i<50;i++)
                       {
                           for(j=0;j<8;j++)
                           {
                               if(b[i][j].y>=630)
                               {
                                   if(b[i][j].strength>0)
                                   {
                                       goto END;
                                   }
                               }
                           }
                       }
                       score+=level*broken_brick;
                       level++;
                       p_brick(b,level);
                       goto game;
                    }
                    else if(y_ball>=630)
                    {
                        score+=level*broken_brick;
                        lives--;
                        if(lives==0)
                        {
                            goto END;
                        }
                        else
                            goto game;
                    }
            }

            if((state[SDL_SCANCODE_ESCAPE]))
            {
            END:
            SDL_RenderClear( m_renderer );
            SDL_RenderCopy(m_renderer,endt,NULL,&texr_end);
            SDL_RenderPresent(m_renderer);
            SDL_Delay(1000);
            ofstream outfile;
            outfile.open(name.c_str(),ios::app);
            outfile<<score<<endl;
            outfile<<level<<endl;
            outfile<<lives<<endl;
            outfile.close();
            ofstream out;
            out.open(namebrick.c_str());
            for(i=0;i<50;i++)
            {
                for(j=0;j<8;j++)
                    out<<b[i][j].strength<<endl;
            }
            out.close();
            delete state;
            delete b;
            SDL_DestroyWindow( m_window );
            SDL_DestroyRenderer( m_renderer );
            SDL_DestroyTexture(img);
            SDL_DestroyTexture(endt);
            SDL_DestroyTexture(sako);
            IMG_Quit();
            SDL_Quit();
            cout<<"GAME OVER!!"<<endl;
            cout<<"your score:"<<score<<endl;
            cout<<"your level:"<<level<<endl;
            cout<<"your lives:"<<lives<<endl;
            return 0;
            }
        }



}

void p_brick(brick &b,int level)
{
    int i=level-1,j,r;
    srand((time(NULL)));
        for(j=0;j<8;j++)
        {
            r=rand()%(level+2);
            if(r>level/3)
            b[i][j].strength=r;
        }
        if(level>1)
            shift_down(b);
}

void shapes(SDL_Renderer *m_renderer,brick b,int level,int x_ball,int y_ball,int x_s,int y_s,int lives,int score,int color)
{
    int i,j;
    SDL_RenderClear( m_renderer );
    SDL_RenderCopy(m_renderer,img,NULL,&texr);
    for(i=0;i<50;i++)
    {
        for(j=0;j<8;j++)
        {
            if(b[i][j].strength>0)
            {
                if(b[i][j].strength<=2)
                boxRGBA(m_renderer,b[i][j].x-70,b[i][j].y-20,b[i][j].x+70,b[i][j].y+20,0, 255, 0,250);
                if((b[i][j].strength>2)&&(b[i][j].strength<=4))
                    boxRGBA(m_renderer,b[i][j].x-70,b[i][j].y-20,b[i][j].x+70,b[i][j].y+20,0, 0, 255,255);
                if((b[i][j].strength>4)&&(b[i][j].strength<=6))
                    boxRGBA(m_renderer,b[i][j].x-70,b[i][j].y-20,b[i][j].x+70,b[i][j].y+20,255, 0, 0,255);
                if((b[i][j].strength>6)&&(b[i][j].strength<=8))
                    boxRGBA(m_renderer,b[i][j].x-70,b[i][j].y-20,b[i][j].x+70,b[i][j].y+20,0, 153, 0,255);
                if((b[i][j].strength>8)&&(b[i][j].strength<=10))
                    boxRGBA(m_renderer,b[i][j].x-70,b[i][j].y-20,b[i][j].x+70,b[i][j].y+20,0, 51, 0,255);
                if((b[i][j].strength>10)&&(b[i][j].strength<=12))
                     boxRGBA(m_renderer,b[i][j].x-70,b[i][j].y-20,b[i][j].x+70,b[i][j].y+20,255, 102, 255,255);
                if((b[i][j].strength>12)&&(b[i][j].strength<=14))
                    boxRGBA(m_renderer,b[i][j].x-70,b[i][j].y-20,b[i][j].x+70,b[i][j].y+20,255, 51, 153,255);
                if((b[i][j].strength>14)&&(b[i][j].strength<=16))
                    boxRGBA(m_renderer,b[i][j].x-70,b[i][j].y-20,b[i][j].x+70,b[i][j].y+20,102, 0, 102,255);
                if((b[i][j].strength>16)&&(b[i][j].strength<=18))
                    boxRGBA(m_renderer,b[i][j].x-70,b[i][j].y-20,b[i][j].x+70,b[i][j].y+20,0, 255, 255,255);
                 if((b[i][j].strength>18)&&(b[i][j].strength<=20))
                    boxRGBA(m_renderer,b[i][j].x-70,b[i][j].y-20,b[i][j].x+70,b[i][j].y+20,0, 102, 255,255);
                if((b[i][j].strength>20)&&(b[i][j].strength<=22))
                    boxRGBA(m_renderer,b[i][j].x-70,b[i][j].y-20,b[i][j].x+70,b[i][j].y+20,0, 0, 153,255);
                if((b[i][j].strength>22)&&(b[i][j].strength<=24))
                    boxRGBA(m_renderer,b[i][j].x-70,b[i][j].y-20,b[i][j].x+70,b[i][j].y+20,255, 255, 0,255);
                if((b[i][j].strength>24)&&(b[i][j].strength<=26))
                    boxRGBA(m_renderer,b[i][j].x-70,b[i][j].y-20,b[i][j].x+70,b[i][j].y+20,255, 51, 0,255);
                if((b[i][j].strength>26)&&(b[i][j].strength<=28))
                    boxRGBA(m_renderer,b[i][j].x-70,b[i][j].y-20,b[i][j].x+70,b[i][j].y+20,255, 0, 0,255);
                if((b[i][j].strength>28)&&(b[i][j].strength<=30))
                    boxRGBA(m_renderer,b[i][j].x-70,b[i][j].y-20,b[i][j].x+70,b[i][j].y+20,128, 0, 0,255);
                if((b[i][j].strength>30)&&(b[i][j].strength<=32))
                    boxRGBA(m_renderer,b[i][j].x-70,b[i][j].y-20,b[i][j].x+70,b[i][j].y+20,153, 102, 0,255);
                if((b[i][j].strength>32)&&(b[i][j].strength<=34))
                    boxRGBA(m_renderer,b[i][j].x-70,b[i][j].y-20,b[i][j].x+70,b[i][j].y+20,102, 51, 0,255);
                if((b[i][j].strength>34)&&(b[i][j].strength<=36))
                    boxRGBA(m_renderer,b[i][j].x-70,b[i][j].y-20,b[i][j].x+70,b[i][j].y+20,255, 255, 153,255);
                if((b[i][j].strength>36)&&(b[i][j].strength<=38))
                    boxRGBA(m_renderer,b[i][j].x-70,b[i][j].y-20,b[i][j].x+70,b[i][j].y+20,255, 204, 255,255);
                if((b[i][j].strength>38)&&(b[i][j].strength<=40))
                    boxRGBA(m_renderer,b[i][j].x-70,b[i][j].y-20,b[i][j].x+70,b[i][j].y+20,255, 255, 255,255);
            }
        }
    }
    //boxRGBA(m_renderer,x_s-70,y_s-10,x_s+70,y_s+10,255,0,0,255);
    SDL_RenderCopy(m_renderer,sako,NULL,&texr_sako);
    if(color==1)
    filledEllipseRGBA(m_renderer,x_ball,y_ball,20,20,0,192,163,255);
    else if(color==2)
        filledEllipseRGBA(m_renderer,x_ball,y_ball,20,20,8,39,245,255);
    else if(color==3)
        filledEllipseRGBA(m_renderer,x_ball,y_ball,20,20,254, 1, 154,255);
    print_one_digit( 270, 650,score,m_renderer);
    print_one_digit( 600, 650,level,m_renderer);
    print_one_digit( 990, 650,lives,m_renderer);

}

void shift_down(brick &b)
{
    int i,j;
    for(i=0;i<50;i++)
    {
        for(j=0;j<8;j++)
            b[i][j].y+=70;
    }
}
double rand_theta(double theta,double m,double M)
{
    srand(time(NULL));
    theta=(rand()%30)+30;
    theta*=(M_PI)/180;
    again_theta:
    if((theta>=m)&&(theta<=M))
        return theta;
    else
    {
        theta+=(M_PI)/2;
        goto again_theta;
    }
}

void toop(int &x_ball,int &y_ball,int x1,int y1,double theta,int x_dir,int y_dir)
{
    if(x_dir==1)
    {
        x_ball++;
        SDL_Delay(1);
        y_ball=y1+(x_ball-x1)*tan(theta);
    }
    else
    {
        x_ball--;
        SDL_Delay(1);
        y_ball=y1+(x_ball-x1)*tan(theta);
    }
}

void  mahdode(brick &b,int x_ball,int y_ball,int &x_dir,int &y_dir,int x_s,int y_s,double &theta,int &x1,int &y1,int &damage,int &broken_brick)
{
    if(x_ball>=1190)
    {
        x_dir*=-1;
        x1=x_ball;
        y1=y_ball;
        theta =(M_PI)-theta;
    }
    else if(x_ball<=20)
    {
        x_dir*=-1;
        x1=x_ball;
        y1=y_ball;
        theta =(M_PI)-theta;
    }
    else if(y_ball<=20)
    {
        y_dir*=-1;
        x1=x_ball;
        y1=21;
        theta =2*(M_PI)-theta;
    }
    else if((y_ball>=610)&&(y_ball<=630)&&(x_ball>=x_s-70)&&(x_ball<=x_s+70))
    {
        y_dir*=-1;
        x1=x_ball;
        y1=y_ball;
        theta =2*(M_PI)-theta;
    }
    else if((y_ball>=610)&&(y_ball<=630)&&(x_ball>=x_s+70)&&(x_ball<=x_s+90))
    {
        if(x_dir>0)
        {
        y_dir*=-1;
        x1=x_ball;
        y1=y_ball;
        theta =-(M_PI)/6;
        }
        else if(x_dir<0)
            {
            y_dir*=-1;
            x_dir*=-1;
            x1=x_ball;
            y1=y_ball;
            theta =-(M_PI)/6;
            }

    }
    else if((y_ball>=610)&&(y_ball<=630)&&(x_ball>=x_s-90)&&(x_ball<=x_s-70))
    {
        if(x_dir>0)
        {
        y_dir*=-1;
        x_dir*=-1;
        x1=x_ball;
        y1=y_ball;
        theta =(M_PI)/6;
        }
        else if(x_dir<0)
            {
            y_dir*=-1;
            x1=x_ball;
            y1=y_ball;
            theta =(M_PI)/6;
            }
    }
    for(int i=0;i<50;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(b[i][j].strength>0)
            {
                if((x_ball<=b[i][j].x+90)&&(x_ball>=b[i][j].x-90)&&(y_ball<=b[i][j].y+40)&&(y_ball>=b[i][j].y-40))
                {
                    int k=b[i][j].strength;
                    b[i][j].strength-=damage;
                    damage-=k;
                    if(b[i][j].strength<=0)
                        broken_brick++;
                   if((x_ball<=b[i][j].x+70)&&(x_ball>=b[i][j].x-70))
                   {
                       if((y_ball<=b[i][j].y+40)&&(y_ball>=b[i][j].y+20))
                       {
                           y_dir*=-1;
                           x1=x_ball;
                           y1=y_ball;
                           theta=2*(M_PI)-theta;
                       }
                       else if((y_ball<=b[i][j].y-20)&&(y_ball>=b[i][j].y-40))
                       {
                           y_dir*=-1;
                           x1=x_ball;
                           y1=y_ball;
                           theta=2*(M_PI)-theta;
                       }
                   }
                   else if((x_ball>=b[i][j].x+70)&&(x_ball<=b[i][j].x+90))
                   {
                       if((y_ball>=b[i][j].y+20)&&(y_ball<=b[i][j].y+40))
                       {
                         if(x_dir>0)
                         {
                           y_dir*=-1;
                           x1=x_ball;
                           y1=y_ball;
                           theta=(M_PI)/6;
                         }
                         else
                         {
                             x_dir*=-1;
                             y_dir*=-1;
                             x1=x_ball;
                             y1=y_ball;
                             theta=(M_PI)/6;
                         }
                       }
                       else if((y_ball>=b[i][j].y-20)&&(y_ball<=b[i][j].y+20))
                       {
                           x_dir*=-1;
                           x1=x_ball;
                           y1=y_ball;
                           theta=M_PI-theta;
                       }
                       else if((y_ball>=b[i][j].y-40)&&(y_ball<=b[i][j].y-20))
                       {
                           if(x_dir<0)
                           {
                               x_dir*=-1;
                               x1=x_ball;
                               y1=y_ball;
                               theta=-(M_PI)/6;
                           }
                           else
                           {
                               y_dir*=-1;
                               x1=x_ball;
                               y1=y_ball;
                               theta=-(M_PI)/6;
                           }
                       }
                   }
                   else if((x_ball<=b[i][j].x-70)&&(x_ball>=b[i][j].x-90))
                   {
                       if((y_ball>=b[i][j].y+20)&&(y_ball<=b[i][j].y+40))
                       {
                         if(x_dir<0)
                         {
                           y_dir*=-1;
                           x1=x_ball;
                           y1=y_ball;
                           theta=-(M_PI)/6;
                         }
                         else
                         {
                             x_dir*=-1;
                             y_dir*=-1;
                             x1=x_ball;
                             y1=y_ball;
                             theta=-(M_PI)/6;
                         }
                       }
                       else if((y_ball>=b[i][j].y-20)&&(y_ball<=b[i][j].y+20))
                       {
                           x_dir*=-1;
                           x1=x_ball;
                           y1=y_ball;
                           theta=M_PI-theta;
                       }
                       else if((y_ball>=b[i][j].y-40)&&(y_ball<=b[i][j].y-20))
                       {
                           if(x_dir>0)
                           {
                               x_dir*=-1;
                               y_dir*=-1;
                               x1=x_ball;
                               y1=y_ball;
                               theta=(M_PI)/6;
                           }
                           else
                           {
                               y_dir*=-1;
                               x1=x_ball;
                               y1=y_ball;
                               theta=(M_PI)/6;
                           }
                       }

                   }
                }
            }
        }
    }
}

void loadgame(string name,int &level,int &lives,int &score,int &y)
{
    int s0,s,i=1;
    ifstream ofile;
    ofile.open(name.c_str());
        if(ofile.good())
    {
        y++;
        while(ofile>>s0)
            i++;
            i--;
    int line=i;
    i=1;
    ofile.close();
    ofile.open(name.c_str());
    while((i<=line-15)&&(ofile>>s))
        i++;
    while ((i<=line)&&(ofile>>s))
    {
        if(i%3==1)
        {
            score=s;
            cout<<"score:"<<s<<endl;
        }
        else if(i%3==2)
        {
            cout<<"level:"<<s<<endl;
            level=s;
        }
        else
        {
            lives=s;
            cout<<"lives:"<<s<<endl;
            cout<<"\n";
        }
        i++;
    }

    ofile.close();
}
}
void print_one_digit(int X,int Y,int R,SDL_Renderer *renderer)
{
    int i,j,k,t;
    if(number_of_digits(R)==1)
    {
    if (R==0) {
        thickLineRGBA(renderer, X+5, Y+10, X+30, Y+10,4,255,0,0,255);
        thickLineRGBA(renderer, X+5, Y+40, X+30, Y+40,4,255,0,0,255);
        thickLineRGBA(renderer, X+5, Y+10, X+5, Y+40,4,255,0,0,255);
        thickLineRGBA(renderer, X+30, Y+10, X+30, Y+40,4,255,0,0,255);
    }
    if (R==1) {
        thickLineRGBA(renderer, X+17, Y+40, X+17, Y+10,4,255,0,0,255);
    }
    if (R==2) {
        thickLineRGBA(renderer, X+5, Y+10, X+30, Y+10,4,255,0,0,255);
        thickLineRGBA(renderer, X+5, Y+40, X+30, Y+40,4,255,0,0,255);
        thickLineRGBA(renderer, X+5, Y+25, X+30, Y+25,4,255,0,0,255);
        thickLineRGBA(renderer, X+30, Y+10, X+30, Y+25,4,255,0,0,255);
        thickLineRGBA(renderer, X+5, Y+25, X+5, Y+40,4,255,0,0,255);
    }
    if (R==3) {
        thickLineRGBA(renderer, X+5, Y+10, X+30, Y+10,4,255,0,0,255);
        thickLineRGBA(renderer, X+5, Y+40, X+30, Y+40,4,255,0,0,255);
        thickLineRGBA(renderer, X+5, Y+25, X+30, Y+25,4,255,0,0,255);
        thickLineRGBA(renderer, X+30, Y+10, X+30, Y+40,4,255,0,0,255);
    }
    if (R==4) {
        thickLineRGBA(renderer, X+30, Y+10, X+30, Y+40,4,255,0,0,255);
        thickLineRGBA(renderer, X+5, Y+10, X+5, Y+20,4,255,0,0,255);
        thickLineRGBA(renderer, X+5, Y+20, X+30, Y+20,4,255,0,0,255);
    }
    if (R==5) {
        thickLineRGBA(renderer, X+5, Y+10, X+30, Y+10,4,255,0,0,255);
        thickLineRGBA(renderer, X+5, Y+25, X+30, Y+25,4,255,0,0,255);
        thickLineRGBA(renderer, X+5, Y+40, X+30, Y+40,4,255,0,0,255);
        thickLineRGBA(renderer, X+5, Y+10, X+5, Y+25,4,255,0,0,255);
        thickLineRGBA(renderer, X+30, Y+25, X+30, Y+40,4,255,0,0,255);
    }
    if (R==6) {
        thickLineRGBA(renderer, X+5, Y+10, X+30, Y+10,4,255,0,0,255);
        thickLineRGBA(renderer, X+5, Y+25, X+30, Y+25,4,255,0,0,255);
        thickLineRGBA(renderer, X+5, Y+40, X+30, Y+40,4,255,0,0,255);
        thickLineRGBA(renderer, X+30, Y+25, X+30, Y+40,4,255,0,0,255);
        thickLineRGBA(renderer, X+5, Y+10, X+5, Y+40,4,255,0,0,255);
    }
    if (R==7) {
        thickLineRGBA(renderer, X+5, Y+10, X+30, Y+10,4,255,0,0,255);
        thickLineRGBA(renderer, X+30, Y+10, X+5, Y+40,4,255,0,0,255);
    }
    if (R==8) {
        thickLineRGBA(renderer, X+5, Y+10, X+30, Y+10,4,255,0,0,255);
        thickLineRGBA(renderer, X+5, Y+25, X+30, Y+25,4,255,0,0,255);
        thickLineRGBA(renderer, X+5, Y+40, X+30, Y+40,4,255,0,0,255);
        thickLineRGBA(renderer, X+30, Y+10, X+30, Y+40,4,255,0,0,255);
        thickLineRGBA(renderer, X+5, Y+10, X+5, Y+40,4,255,0,0,255);
    }
    if (R==9) {
        thickLineRGBA(renderer, X+30, Y+10, X+30, Y+40,4,255,0,0,255);
        thickLineRGBA(renderer, X+5, Y+10, X+5, Y+20,4,255,0,0,255);
        thickLineRGBA(renderer, X+5, Y+20, X+30, Y+20,4,255,0,0,255);
        thickLineRGBA(renderer, X+5, Y+10, X+30, Y+10,4,255,0,0,255);
    }
    }
    else if(number_of_digits(R)==2)
    {
        k=R%10;
        R/=10;
        print_one_digit(X,Y,R,renderer);
        print_one_digit(X+30,Y,k,renderer);
    }
    else if(number_of_digits(R)==3)
    {
        k=R%10;
        R/=10;
        j=R%10;
        R/=10;
        print_one_digit(X,Y,R,renderer);
        print_one_digit(X+30,Y,j,renderer);
        print_one_digit(X+60,Y,k,renderer);
    }
    else if(number_of_digits(R)==4)
    {
        k=R%10;
        R/=10;
        j=R%10;
        R/=10;
        t=R%10;
        R/=10;
        print_one_digit(X,Y,R,renderer);
        print_one_digit(X+30,Y,t,renderer);
        print_one_digit(X+60,Y,j,renderer);
        print_one_digit(X+90,Y,k,renderer);
    }
}

int number_of_digits(int n)
{
    int s=0;
    if(n==0)
        return 1;
    else
    {
    while(n!=0)
    {
        n/=10;
        s++;
    }
    return s;
    }
}