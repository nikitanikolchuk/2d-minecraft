#include "CStone.h"

CStone::CStone ( const CCoord & coord, std::shared_ptr<CTexture> texture, const int & hitpoints )
    : CBlock ( coord, texture, hitpoints ) {}
void CStone::takeDamage ( const int & amount )
{
    if ( amount > STONE_DURABILITY )
        m_HitPoints -= ( amount - STONE_DURABILITY );
}
int CStone::getCode() const
{
    return STONE_CODE;
}