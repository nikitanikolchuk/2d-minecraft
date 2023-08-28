#include "CZombie.h"

CZombie::CZombie ( const CCoord & coord, std::shared_ptr<CTexture> texture, const int & hitpoints )
    : CEnemy ( coord, texture, hitpoints, ZOMBIE_DAMAGE )
{
    m_Frame = ZOMBIE_IDLE;
}
void CZombie::render ( const int & x, const int & y ) const
{
    SDL_Rect clip = { ZOMBIE_SPRITE_WIDTH *  m_Frame, 0, ZOMBIE_SPRITE_WIDTH, ZOMBIE_HEIGHT };
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if ( m_Direction == Direction::LEFT )
        flip = SDL_FLIP_HORIZONTAL;
    m_Texture->render ( x - ( ZOMBIE_SPRITE_WIDTH - ZOMBIE_WIDTH ) / 2, y, &clip, flip );
}
void CZombie::chooseFrame()
{
    if ( m_Velocity == 0 && m_FallStart != m_Coord.m_Y )
        m_Frame = ZOMBIE_MOVE_BEGIN;
    else if ( m_Velocity == 0 )
        m_Frame = ZOMBIE_IDLE;
    else if ( m_Frame == ZOMBIE_MOVE_BEGIN )
        m_Frame = ZOMBIE_MOVE_END;
    else
        m_Frame = ZOMBIE_MOVE_BEGIN;
}
CCoord CZombie::getCoord() const
{
    return { m_Coord.m_X + ( ZOMBIE_SPRITE_WIDTH - ZOMBIE_WIDTH ) / 2, m_Coord.m_Y };
}
int CZombie::getWidth() const
{
    return ZOMBIE_WIDTH;
}
int CZombie::getHeight() const
{
    return ZOMBIE_HEIGHT;
}
int CZombie::getCode() const
{
    return ZOMBIE_CODE;
}
int CZombie::getVelocity() const
{
    return ZOMBIE_VELOCITY;
}
int CZombie::getAggroRange() const
{
    return ZOMBIE_AGGRO_RANGE;
}