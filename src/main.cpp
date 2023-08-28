#include "CGameMap.h"

int main ( int argc, char ** argv )
{
    CDisplay display;
    if ( !display.init() )
        return 1;

    CTextureSet textureSet;
    if ( !textureSet.load ( display.getRenderer() ) )
        return 2;

    CGameMap gameMap ( textureSet );
    std::string fileName = INIT_MAP_FILE;
    if ( argc > 1 )
        fileName = argv[1];
    if ( !gameMap.load ( fileName ) )
        return 3;

    bool quit = false;
    SDL_Event event;
    uint32_t startTime, timeDiff;
    while ( !quit ) {
        startTime = SDL_GetTicks();
        
        while ( SDL_PollEvent ( &event ) != 0 )
            gameMap.handleEvent ( event, quit );
        display.clear();
        gameMap.action();
        display.update();

        timeDiff = SDL_GetTicks() - startTime;
        if ( timeDiff < DISPLAY_TICKS_PER_FRAME )
            SDL_Delay ( DISPLAY_TICKS_PER_FRAME - timeDiff );
    }
    
    return 0;
}