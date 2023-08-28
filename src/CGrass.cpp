#include "CGrass.h"

CGrass::CGrass ( const CCoord & coord, std::shared_ptr<CTexture> texture, const int & hitpoints )
    : CBlock ( coord, texture, hitpoints ) {}
void CGrass::takeDamage ( const int & amount )
{
    if ( amount > GRASS_DURABILITY )
        m_HitPoints -= ( amount - GRASS_DURABILITY );
}
int CGrass::getCode() const
{
    return GRASS_CODE;
}