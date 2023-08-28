#include "CLava.h"

CLava::CLava ( const CCoord & coord, std::shared_ptr<CTexture> texture )
        : CLiquid ( coord, texture ) {}
void CLava::dealDamage ( CEntity & entity ) const
{
    entity.takeDamage ( LAVA_DAMAGE );
}
int CLava::getCode() const
{
    return LAVA_CODE;
}
std::unique_ptr<CBlock> CLava::newLiquid ( const CCoord & coord ) const
{
    return std::unique_ptr<CBlock> ( new CLava ( coord, m_Texture ) );
}