#include "CDirt.h"

CDirt::CDirt ( const CCoord & coord, std::shared_ptr<CTexture> texture, const int & hitpoints )
    : CBlock ( coord, texture, hitpoints ) {}
void CDirt::takeDamage ( const int & amount )
{
    if ( amount > DIRT_DURABILITY )
        m_HitPoints -= ( amount - DIRT_DURABILITY );
}
int CDirt::getCode() const
{
    return DIRT_CODE;
}