#include "CDiamond.h"

CDiamond::CDiamond ( const CCoord & coord, std::shared_ptr<CTexture> texture, const int & hitpoints )
    : CBlock ( coord, texture, hitpoints ) {}
void CDiamond::takeDamage ( const int & amount )
{
    if ( amount > DIAMOND_DURABILITY )
        m_HitPoints -= ( amount - DIAMOND_DURABILITY );
}
int CDiamond::getCode() const
{
    return DIAMOND_CODE;
}