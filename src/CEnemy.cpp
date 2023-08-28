#include "CEnemy.h"

CEnemy::CEnemy ( const CCoord & coord, std::shared_ptr<CTexture> texture, const int & hitpoints, const int & damage )
    : CCreature ( coord, texture, hitpoints, damage )
{
    m_PrevX = coord.m_X;
}
void CEnemy::move ( const CCoord & worldCoord, CBlock::vector & map, CCreature::vector & creature  )
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

    int checkBlockX = getCoord().m_X - getCoord().m_X % BLOCK_SIZE + static_cast<int> ( m_Direction ) * BLOCK_SIZE;
    int freeBlockPos = CBlock::findBlockPos ( { checkBlockX, m_Coord.m_Y }, worldCoord.m_X );
    int stepBlockPos = CBlock::findBlockPos ( { checkBlockX, m_Coord.m_Y + BLOCK_SIZE }, worldCoord.m_X );

    if ( m_Velocity != 0 && m_PrevX == m_Coord.m_X &&
         ( typeid ( *map[stepBlockPos] ) != typeid ( CAir ) ) &&
         ( typeid ( *map[freeBlockPos] ) == typeid ( CAir ) ) )
        jump ( map, creature );

    CCreature::move ( worldCoord, map, creature );
    m_PrevX = m_Coord.m_X;
}
bool CEnemy::isEnemy() const
{
    return true;
}
