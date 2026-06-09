#ifdef _WIN32
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#endif

#include "Game.h"

int main()
{
    #ifdef _WIN32
        // Enable ANSI escape codes in the Windows console
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut != INVALID_HANDLE_VALUE) {
            DWORD dwMode = 0;
            if (GetConsoleMode(hOut, &dwMode)) {
                dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
                SetConsoleMode(hOut, dwMode);
            }
        }

        PlaySound(TEXT("assets/audio/DungeonRPG.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    #endif

    PlaySound(TEXT("assets/audio/DungeonRPG.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    Game game;

    game.run();
    
    return 0;
}