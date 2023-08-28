#include "CTexture.h"

CTexture::CTexture ( SDL_Renderer * renderer )
{
    m_Renderer = renderer;
    m_Texture = nullptr;
}
CTexture::~CTexture()
{
    if ( m_Texture != nullptr )
        SDL_DestroyTexture ( m_Texture );
}
bool CTexture::loadImage ( const std::string & fileName )
{
    if ( m_Texture != nullptr ) //TODO: possibly delete
        SDL_DestroyTexture ( m_Texture );

    SDL_Surface * tempSurface = IMG_Load ( ( TEXTURE_PATH + fileName ).c_str() );
    if ( tempSurface == nullptr ) {
        std::cout << "Image load error for \"" << fileName << "\": " << IMG_GetError() << std::endl;
        return false;
    }

    SDL_SetColorKey ( tempSurface, SDL_TRUE, SDL_MapRGB ( tempSurface->format, 0, 0xFF, 0xFF ) );
    m_Texture = SDL_CreateTextureFromSurface ( m_Renderer, tempSurface );
    if ( m_Texture == nullptr ) {
        std::cout << "Create texture error for \"" << fileName << "\": " << IMG_GetError() << std::endl;
        SDL_FreeSurface ( tempSurface );
        return false; 
    }

    m_Height = tempSurface->h;
    m_Width = tempSurface->w;
    SDL_FreeSurface ( tempSurface );
    SDL_SetTextureBlendMode ( m_Texture, SDL_BLENDMODE_BLEND );
    return true;
}
bool CTexture::loadText ( TTF_Font * font, const std::string & text, const SDL_Color & color )
{
    if ( m_Texture != nullptr ) //TODO: possibly delete
        SDL_DestroyTexture ( m_Texture );

    SDL_Surface * tempSurface = TTF_RenderText_Solid ( font, text.c_str(), color );
    if ( tempSurface == nullptr ) {
        std::cout << "Text surface render error: " << TTF_GetError() << std::endl;
        return false;
    }

    m_Texture = SDL_CreateTextureFromSurface ( m_Renderer, tempSurface );
    if ( m_Texture == nullptr ) {
        std::cout << "Create texture error for text: " << IMG_GetError() << std::endl;
        SDL_FreeSurface ( tempSurface );
        return false; 
    }

    m_Height = tempSurface->h;
    m_Width = tempSurface->w;
    SDL_FreeSurface ( tempSurface );
    return true;
}
void CTexture::setAlpha ( const int8_t & value )
{
    SDL_SetTextureAlphaMod ( m_Texture, value );
}
void CTexture::render ( const int & x, const int & y, SDL_Rect * clip, const SDL_RendererFlip & flip, double angle, SDL_Point * center )
{
    SDL_Rect renderRect = { x, y, m_Width, m_Height };
    if ( clip != nullptr ) {
        renderRect.w = clip->w;
        renderRect.h = clip->h;
    }
    SDL_RenderCopyEx ( m_Renderer, m_Texture, clip, &renderRect, angle, center, flip );
}
int CTexture::getWidth() const
{
    return m_Width;
}
int CTexture::getHeight() const
{
    return m_Height;
}
SDL_Renderer * CTexture::getRenderer() const
{
    return m_Renderer;
}