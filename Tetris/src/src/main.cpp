//Coded by Juntian Deng
#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

const int M = 20;
const int N = 10;

int field[M][N] = {0};

struct Point
{int x,y;} a[5], b[5];

int figures[8][5] =
{
    7,4,1,0,2, 
    0,3,4,7,6, 
    0,1,4,7,10, 
    1,4,7,6,3,  
    2,1,4,7,10, 
    1,4,7,6,8, 
    3,6,7,8,5,
    3,0,1,2,5,
};

bool check()
{
   for (int i=0;i<5;i++)
      if (a[i].x<0 || a[i].x>=N || a[i].y>=M) return 0;
      else if (field[a[i].y][a[i].x]) return 0;
   return 1;
};


int main()
{
    srand(time(0));     

    RenderWindow window(VideoMode(320, 480), "The Game!");

    Texture t1,t2,t3;
    t1.loadFromFile("src/images/tiles.png");
    t2.loadFromFile("src/images/background.png");
    t3.loadFromFile("src/images/frame.png");

    Sprite s(t1), background(t2), frame(t3);
    int score = 0;
    int dx=0; bool rotate=0; int colorNum=1;
    float timer=0,delay=0.3; 

    Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();

            if (e.type == Event::KeyPressed)
              if (e.key.code==Keyboard::Up) rotate=true;
              else if (e.key.code==Keyboard::Left) dx=-1;
              else if (e.key.code==Keyboard::Right) dx=1;
        }

    if (Keyboard::isKeyPressed(Keyboard::Down)) delay=0.05;

    //// <- Move -> ///
    for (int i=0;i<5;i++)  { b[i]=a[i]; a[i].x+=dx; }
    if (!check()) for (int i=0;i<5;i++) a[i]=b[i];

    //////Rotate//////
    if (rotate)
      {
        Point p = a[1]; //center of rotation
        for (int i=0;i<5;i++)
          {
            int x = a[i].y-p.y;
            int y = a[i].x-p.x;
            a[i].x = p.x - x;
            a[i].y = p.y + y;
           }
           if (!check()) for (int i=0;i<5;i++) a[i]=b[i];
      }

    ///////Tick//////
    if (timer>delay)
      {
        for (int i=0;i<5;i++) { b[i]=a[i]; a[i].y+=1; }

        if (!check())
        {
         for (int i=0;i<5;i++) field[b[i].y][b[i].x]=colorNum;

         colorNum=1+rand()%7;
         int n=rand()%7;
         for (int i=0;i<5;i++)
           {
            a[i].x = figures[n][i] % 3;
            a[i].y = figures[n][i] / 3;
           }
        }

         timer=0;
      }

    ///////check lines//////////
    int k=M-1;
    for (int i=M-1;i>0;i--)
    {
        int count=0;
        for (int j=0;j<N;j++)
        {
            if (field[i][j]) count++;
            field[k][j]=field[i][j];
        }
        if (count<N) k--;
    }

    dx=0; rotate=0; delay=0.3;
    window.clear(Color::White);    
    window.draw(background);
          
    for (int i=0;i<M;i++)
     for (int j=0;j<N;j++)
       {
         if (field[i][j]==0) continue;
         s.setTextureRect(IntRect(field[i][j]*18,0,18,18));
         s.setPosition(j*18,i*18);
         s.move(28,31); //offset
         window.draw(s);
       }

    for (int i=0;i<5;i++)
      {
        s.setTextureRect(IntRect(colorNum*18,0,18,18));
        s.setPosition(a[i].x*18,a[i].y*18);
        s.move(28,31); //offset
        window.draw(s);
      }
    for (int i=0;i<5;i++) {
      if (a[i].y>20){
        window.close();
      }
    }

    window.draw(frame);
    window.display();
    }
    
    return 0;
}
