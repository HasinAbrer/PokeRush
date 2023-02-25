#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace sf;
using namespace std;

int windowX = 1000;
int windowY = 600;
bool Over = false;
bool jump = false;
float pokeY = 440;
int dir = -1;
float gSpeed;
int score = 0;
string Pri = "";

int main()
{
    RenderWindow app(VideoMode(windowX, windowY), "Poke Rush!!!");
    app.setFramerateLimit(60);

    float objX[3]={1000,1500,1250};

    Texture tBG, tpoke, tobj, tpoint;
    tBG.loadFromFile("photo/bg.png");
    tpoke.loadFromFile("photo/poke.png");
    tobj.loadFromFile("photo/object.png");
    tpoint.loadFromFile("photo/point.png");

    Sprite sBG(tBG), sPoke(tpoke), sObj(tobj), sPoint(tpoint);

    Font font;
    font.loadFromFile("font/COOPBL.TTF");

    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }
        app.draw(sBG);



        if(!Over)
        {
            gSpeed=3+0.5*score;
            if(Keyboard::isKeyPressed(Keyboard::Space) && !jump)   jump = true;
            if(jump)
            {
                if(pokeY<=320)  dir=1;
                else if(pokeY>440)
                {
                    dir=-1;
                    jump=false;
                }
                pokeY+=gSpeed*dir;
            }
            for(int i=0;i<3;i++)
            {
                if(objX[i]<-30) objX[i]+=1000;
            }
            for(int i=0;i<2;i++)
            {
                objX[i]-=gSpeed;
                sObj.setPosition(objX[i],460);
                app.draw(sObj);
               if(objX[i]<70 && objX[i]>30 && pokeY>390) Over=true;
            }
            objX[2]-=gSpeed;
            sPoint.setPosition(objX[2],470);
            app.draw(sPoint);
            if(objX[2]<70 && pokeY>410)
            {
                objX[2]+=1000;
                score++;
            }
            Pri="\t\t\tPOKE RUSH\nPress Space For Jumping";
            Text pOver(Pri,font,40);
            pOver.setPosition(250,120);
            app.draw(pOver);


            sPoke.setPosition(30,pokeY);
            app.draw(sPoke);

        }
        else
        {
            Pri="GAME OVER";
            Text pOver(Pri,font,80);
            pOver.setPosition(250,100);
            app.draw(pOver);
            Pri="Press ESC Key to Exit";
            Text pOver2(Pri,font,30);
            pOver2.setPosition(355,190);
            app.draw(pOver2);
            if(Keyboard::isKeyPressed(Keyboard::Escape))    app.close();
        }

        Pri="Score: "+to_string(score);
        Text pScore(Pri, font, 40);
        pScore.setPosition(430, 220);
        app.draw(pScore);

        app.display();

    }
}
