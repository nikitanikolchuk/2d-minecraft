#include "CDisplay.h"

CDisplay::CDisplay()
{
    m_Window = nullptr;
    m_Renderer = nullptr;
}
CDisplay::~CDisplay()
{
    SDL_DestroyRenderer ( m_Renderer );
    SDL_DestroyWindow ( m_Window );
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
bool CDisplay::init()
{
    if ( SDL_Init ( SDL_INIT_VIDEO ) < 0 ) {
        std::cout << "SDL init fail: " << SDL_GetError() << std::endl;
        return false;
    }

    if ( !SDL_SetHint ( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        std::cout << "Warning: hint set fail" << std::endl;
    
    m_Window = SDL_CreateWindow ( "2D Minecraft", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                             INIT_SCREEN_WIDTH, INIT_SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if ( m_Window == nullptr ) {
        std::cout << "Window create fail: " << SDL_GetError() << std::endl;
        return false;
    }

    m_Renderer = SDL_CreateRenderer ( m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if ( m_Renderer == nullptr ) {
        std::cout << "Renderer create fail: " << SDL_GetError() << std::endl;
        return false;
    }

    if ( !( IMG_Init ( IMG_INIT_PNG ) & IMG_INIT_PNG ) ) {
        std::cout << "Image init fail: " << SDL_GetError() << std::endl;
        return false;
    }

    if( TTF_Init() == -1 )
    {
    	std::cout << "TTF init fail: %s\n" << TTF_GetError() << std::endl;
    	return false;
    }
    
    SDL_SetRenderDrawColor( m_Renderer, BACKGROUND_COLOR[0], BACKGROUND_COLOR[1], BACKGROUND_COLOR[2], 0 );
    return true;
}
SDL_Renderer * CDisplay::getRenderer() const
{
    return m_Renderer;
}
void CDisplay::clear()
{
    SDL_RenderClear ( m_Renderer );
}
void CDisplay::update()
{
    SDL_RenderPresent ( m_Renderer );
}
