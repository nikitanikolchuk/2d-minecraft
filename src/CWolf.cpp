#include "CWolf.h"

CWolf::CWolf ( const CCoord & coord, std::shared_ptr<CTexture> texture, const int & hitpoints )
    : CEnemy ( coord, texture, hitpoints, WOLF_DAMAGE )
{
    m_Frame = WOLF_IDLE;
}
void CWolf::move ( const CCoord & worldCoord, CBlock::vector & map, CCreature::vector & creature  )
{
    std::shared_ptr<CCreature> player;
    for ( auto & it : creature )
        if ( !it->isEnemy() ) {
            player = it;
            break;
        }

    if ( std::abs ( player->getCoord().m_X + player->getWidth() / 2 - getCoord().m_X - getWidth() / 2 ) < getAggroRange() ) {
        if ( getCoord().m_X + getWidth() < player->getCoord().m_X ) {
            m_Velocity = getVelocity();
            m_Direction = Direction::RIGHT;
        } else if ( player->getCoord().m_X + getWidth() < getCoord().m_X ) {
            m_Velocity = -getVelocity();
            m_Direction = Direction::LEFT;
        } else {
            m_Velocity = 0;
            if ( std::abs ( player->getCoord().m_Y + player->getHeight() / 2 - getCoord().m_Y - getHeight() / 2 ) < ENEMY_MAX_ATTACK_HEIGHT )
                player->takeDamage ( m_Damage );
        }
    } else {
        m_Velocity = 0;
    }

    int checkBlockX, freeBlockPos, stepBlockPos;
    if ( m_Direction == Direction::RIGHT ) {
        checkBlockX = getCoord().m_X + 2 * BLOCK_SIZE;
        freeBlockPos = CBlock::findBlockPos ( { checkBlockX, m_Coord.m_Y - BLOCK_SIZE }, worldCoord.m_X );
        stepBlockPos = CBlock::findBlockPos ( { checkBlockX, m_Coord.m_Y }, worldCoord.m_X );
    } else {
        checkBlockX = getCoord().m_X - BLOCK_SIZE;
        freeBlockPos = CBlock::findBlockPos ( { checkBlockX, m_Coord.m_Y - BLOCK_SIZE }, worldCoord.m_X );
        stepBlockPos = CBlock::findBlockPos ( { checkBlockX, m_Coord.m_Y }, worldCoord.m_X );
    }

    if ( m_Velocity != 0 && m_PrevX == m_Coord.m_X &&
         ( typeid ( *map[stepBlockPos] ) != typeid ( CAir ) ) &&
         ( typeid ( *map[freeBlockPos] ) == typeid ( CAir ) ) )
        jump ( map, creature );

    CCreature::move ( worldCoord, map, creature );
    m_PrevX = m_Coord.m_X;
}
void CWolf::render ( const int & x, const int & y ) const
{
    SDL_Rect clip = { WOLF_WIDTH *  m_Frame, 0, WOLF_WIDTH, WOLF_HEIGHT };
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if ( m_Direction == Direction::LEFT )
        flip = SDL_FLIP_HORIZONTAL;
    m_Texture->render ( x, y, &clip, flip );
}
void CWolf::chooseFrame()
{
    if ( m_Velocity == 0 && m_FallStart != m_Coord.m_Y )
        m_Frame = WOLF_MOVE_BEGIN;
    else if ( m_Velocity == 0 )
        m_Frame = WOLF_IDLE;
    else if ( m_Frame == WOLF_MOVE_BEGIN )
        m_Frame = WOLF_MOVE_END;
    else
        m_Frame = WOLF_MOVE_BEGIN;
}
int CWolf::getWidth() const
{
    return WOLF_WIDTH;
}
int CWolf::getHeight() const
{
    return WOLF_HEIGHT;
}
int CWolf::getCode() const
{
    return WOLF_CODE;
}
int CWolf::getVelocity() const
{
    return WOLF_VELOCITY;
}
int CWolf::getAggroRange() const
{
    return WOLF_AGGRO_RANGE;
}