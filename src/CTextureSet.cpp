#include "CTextureSet.h"

bool CTextureSet::load ( SDL_Renderer * renderer )
{
    for ( auto & it : TEXTURES_TO_LOAD ) {
        std::shared_ptr<CTexture> texture = std::make_shared<CTexture> ( renderer );
        if ( !texture->loadImage ( it + PNG ) )
            return false;
        m_TextureMap.emplace ( it, texture );
    }
    return true;
}
std::shared_ptr<CTexture> CTextureSet::getTexture ( const std::string & name )
{
    return m_TextureMap[name];
}