#include "CEntity.h"

CEntity::CEntity ( const CCoord & coord, std::shared_ptr<CTexture> texture, const int & hitpoints )
    : m_Coord ( coord ), m_Texture ( texture ), m_HitPoints ( hitpoints ) {}
void CEntity::render ( const int & x, const int & y ) const
{
    m_Texture->render ( x, y );
}
bool CEntity::entityCollision ( const CEntity & entity, SDL_Rect & result ) const
{
    SDL_Rect rect1 = { getCoord().m_X, getCoord().m_Y, getWidth(), getHeight() };
    SDL_Rect rect2 = { entity.getCoord().m_X, entity.getCoord().m_Y, entity.getWidth(), entity.getHeight() };
    return SDL_IntersectRect ( &rect1, &rect2, &result );
}
CCoord CEntity::getCoord() const
{
    return m_Coord;
}
void CEntity::takeDamage ( const int & amount )
{
    m_HitPoints -= amount;
}
bool CEntity::isDestroyed() const
{
    return m_HitPoints <= 0;
}
void CEntity::writeToFile ( SDL_RWops * file, const int & code ) const
{
    SDL_RWwrite( file, &m_Coord.m_X, sizeof ( uint32_t ), 1 );
    SDL_RWwrite( file, &m_Coord.m_Y, sizeof ( uint32_t ), 1 );
    SDL_RWwrite( file, &code, sizeof ( uint32_t ), 1 );
    SDL_RWwrite( file, &m_HitPoints, sizeof ( uint32_t ), 1 );  
}