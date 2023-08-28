#pragma once

#include "CEntity.h"
#include "CTexture.h"

/** @brief block size in pixels */
const int BLOCK_SIZE = 64;
/** @brief Block max hitpoints */
const int BLOCK_MAX_HITPOINTS = 10;

/** @brief Class represents a block */
class CBlock : public CEntity
{
public:
    /** Type for vector of blocks */
    typedef std::vector<std::unique_ptr<CBlock>> vector;

    /**
     * @brief Construct a new block
     */
    CBlock ( const CCoord & coord, std::shared_ptr<CTexture> texture = nullptr, const int & hitpoints = 0 );

    /**
     * @brief Get the block's width
     * 
     * @return block width 
     */
    int getWidth() const override;

    /**
     * @brief Get the block's width
     * 
     * @return block width 
     */
    int getHeight() const override;

    /**
     * @brief Find block on a map at given coordinates
     * 
     * @param[in] coord coordinates of a point inside this block
     * @param[in] wordlWidth width of the world in pixels
     * @return found block
     */
    static int findBlockPos ( const CCoord & coord, const int & worldWidth );

    /**
     * @brief If the block is liquid fill adjacent air blocks lower or
     *        on the same height as this.
     * 
     * @param[in] worldCoord width and height of the world
     * @param[in] map map of all blocks
     * @param[in] creature vector of creatures that might receive damage
     */
    virtual void flow ( const CCoord & worldCoord, CBlock::vector & map, CEntity::vector & creature ) const {}

    /**
     * @brief Check if block is liquid.
     * 
     * @return true if the blokc is liquid, false otherwise
     */
    virtual bool isLiquid() const;
};