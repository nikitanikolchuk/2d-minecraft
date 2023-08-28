#include "CBlock.h"

CBlock::CBlock ( const CCoord & coord, std::shared_ptr<CTexture> texture, const int & hitpoints )
    : CEntity ( coord, texture, hitpoints ) {}
int CBlock::getWidth() const
{
    return BLOCK_SIZE;
}
int CBlock::getHeight() const
{
    return BLOCK_SIZE;
}
int CBlock::findBlockPos ( const CCoord & coord, const int & worldWidth )
{
    int column = coord.m_X / BLOCK_SIZE;
    int row = coord.m_Y / BLOCK_SIZE;
    int rowLen = worldWidth / BLOCK_SIZE;
    return row * rowLen + column;
}
bool CBlock::isLiquid() const
{
    return false;
}