#include "CCreature.h"

CCreature::CCreature ( const CCoord & coord, std::shared_ptr<CTexture> texture, const int & hitpoints, const int & damage )
    : CEntity ( coord, texture, hitpoints )
{
    m_Velocity = 0;
    m_Direction = Direction::RIGHT;
    m_FallStart = coord.m_Y;
    m_Damage = damage;
}
bool CCreature::touchesEntities ( CBlock::vector & map, CCreature::vector & creature, SDL_Rect & intersect ) const
{
    for ( auto & it : map )
        if ( it->entityCollision ( *this, intersect ) )
            return true;
    for ( auto & it : creature )
        if ( &(*it) != &(*this) && it->entityCollision ( *this, intersect ) )
            return true;
    return false;
}
void CCreature::jump ( CBlock::vector & map, CCreature::vector & creature )
{
    SDL_Rect intersect;
    for ( int heightLeft = CREATURE_JUMP_FORCE; heightLeft > 0; heightLeft -= BLOCK_SIZE ) {
        m_Coord.m_Y -= std::min ( BLOCK_SIZE, heightLeft );
        if ( touchesEntities ( map, creature, intersect ) ) {
            m_Coord.m_Y += intersect.h - GRAVITY_PULL;
            break;
        }
    }

    if ( m_Coord.m_Y < 0 )
        m_Coord.m_Y = -GRAVITY_PULL;

    m_FallStart = m_Coord.m_Y;
}
void CCreature::move ( const CCoord & worldCoord, CBlock::vector & map, CCreature::vector & creature )
{
    SDL_Rect intersect;
    
    m_Coord.m_Y += GRAVITY_PULL;
    if ( m_Coord.m_Y + getHeight() > worldCoord.m_Y ) {
        m_Coord.m_Y = worldCoord.m_Y - getHeight();
        m_FallStart = m_Coord.m_Y;
    } else if ( touchesEntities ( map, creature, intersect ) ) {
        m_Coord.m_Y -= intersect.h;
        if ( m_Coord.m_Y - m_FallStart > SAFE_FALL_DISTANCE )
            takeDamage ( ( m_Coord.m_Y - m_FallStart - SAFE_FALL_DISTANCE ) / FALL_DAMAGE_DIVIDER );
        m_FallStart = m_Coord.m_Y;
    }

    m_Coord.m_X += m_Velocity;
    if ( getCoord().m_X < 0 )
        m_Coord.m_X = - ( getCoord().m_X - m_Coord.m_X );
    else if ( getCoord().m_X + getWidth() > worldCoord.m_X )
        m_Coord.m_X = worldCoord.m_X - ( getCoord().m_X - m_Coord.m_X + getWidth() );
    else if ( touchesEntities ( map, creature, intersect ) )
        m_Velocity >= 0 ? m_Coord.m_X -= intersect.w : m_Coord.m_X += intersect.w;
}
bool CCreature::isEnemy() const
{
    return false;
}