#include "CWater.h"

CWater::CWater ( const CCoord & coord, std::shared_ptr<CTexture> texture )
    : CLiquid ( coord, texture )
{
    m_Texture->setAlpha ( WATER_TRANSPARENCY );
}
int CWater::getCode() const
{
    return WATER_CODE;
}
std::unique_ptr<CBlock> CWater::newLiquid ( const CCoord & coord ) const
{
    return std::unique_ptr<CBlock> ( new CWater ( coord, m_Texture ) );
}