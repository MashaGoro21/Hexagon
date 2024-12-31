//#include <stdio.h>


#include <iostream>
#include "Game.hpp"

int main()
{
    //Init Game engine
    Game game;
    
    //Game loop
    while(game.running())
    {
        //Update
        game.update();
        
        //Render
        game.render();
    }
    
    //End of application
    return 0;
}

