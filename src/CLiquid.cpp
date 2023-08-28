#include "CLiquid.h"

CLiquid::CLiquid ( const CCoord & coord, std::shared_ptr<CTexture> texture )
    : CBlock ( coord, texture ) {}
bool CLiquid::isDestroyed() const
{
    return false;
}
bool CLiquid::entityCollision ( const CEntity & entity, SDL_Rect & result ) const
{
    return false;
}
void CLiquid::flow ( const CCoord & worldCoord, CBlock::vector & map, CEntity::vector & creature ) const
{
    SDL_Rect collision;
    for ( auto & it : creature )
        if ( it->entityCollision ( *this, collision ) )
            dealDamage ( *it );

    std::vector<int> adjacentPos;
    int thisPos = findBlockPos ( m_Coord, worldCoord.m_X );

    if ( m_Coord.m_X > 0 && ( typeid ( *map[thisPos-1] ) == typeid ( CAir ) ) )
        map[thisPos-1] = newLiquid ( { m_Coord.m_X - BLOCK_SIZE, m_Coord.m_Y } );
 
    if ( m_Coord.m_X < worldCoord.m_X - BLOCK_SIZE && ( typeid ( *map[thisPos+1] ) == typeid ( CAir ) ) )
        map[thisPos+1] = newLiquid ( { m_Coord.m_X + BLOCK_SIZE, m_Coord.m_Y } );
    
    if ( m_Coord.m_Y < worldCoord.m_Y - BLOCK_SIZE &&
         ( typeid ( *map[ thisPos + worldCoord.m_X / BLOCK_SIZE ] ) == typeid ( CAir ) ) )
        map[ thisPos + worldCoord.m_X / BLOCK_SIZE ] = newLiquid ( { m_Coord.m_X, m_Coord.m_Y + BLOCK_SIZE } );
}
bool CLiquid::isLiquid() const
{
    return true;
}