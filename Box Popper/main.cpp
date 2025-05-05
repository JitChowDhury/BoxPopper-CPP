#include<iostream>
#include "Game.h"


int main()
{
    //Window
//Init Game Engine
    Game game;

//Game Loop

    while (game.running())//check if open
    {
        //update
        game.update();
        //Render
        game.render();
    }
   return 0;
 
}
 
