#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib") 

#include "Game.h"

int main()
{
    PlaySound(TEXT("assets/audio/DungeonRPG.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    Game game;

    game.run();
    
    return 0;
}