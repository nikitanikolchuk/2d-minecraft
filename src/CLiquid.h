#pragma once

#include "CAir.h"
#include "CBlock.h"

/** @brief Class represents a liquid block */
class CLiquid : public CBlock
{
public:
    /**
     * @brief Construct a new CLiquid object. Set texture transparency to 50%
     * 
     * @param[in] coord coordinates of the liquid block 
     * @param[in] texture texture of the new liquid block
     */
    CLiquid ( const CCoord & coord, std::shared_ptr<CTexture> texture );

    /**
     * @brief Do nothing because it's a liquid
     */
    void takeDamage ( const int & amount ) override {}

    /**
     * @brief Check if entity os destroyed
     * 
     * @return false because liquids can't be destroyed 
     */
    bool isDestroyed() const override;

    /**
     * @brief Check collision with an entity
     * 
     * @param[in] entity to check collision with 
     * @param[in] result collision hitbox
     * @return false because liquids do not stop movement
     */
    bool entityCollision ( const CEntity & entity, SDL_Rect & result ) const override;

    /**
     * @brief If the block is liquid fill adjacent air blocks lower or
     *        on the same height as this.
     * 
     * @param[in] worldCoord width and height of the world
     * @param[in] map map of all blocks 
     * @param[in] creature vector of creature that might receive damage
     */
    void flow ( const CCoord & worldCoord, CBlock::vector & map, CEntity::vector & creature ) const override;

    /**
     * @brief Deal damage to an entity if the liquid is harmful
     * 
     * @param[in,out] entity entity to deal damage to
     */
    virtual void dealDamage ( CEntity & entity ) const {}

    /**
     * @brief Create a new liquid block of this type
     * 
     * @param[in] coord coordinates of the new block
     * @return std::unique_ptr<CBlock>
     */
    virtual std::unique_ptr<CBlock> newLiquid ( const CCoord & coord ) const = 0;

    /**
     * @brief Check if block is liquid.
     * 
     * @return true if the blokc is liquid, false otherwise
     */
    bool isLiquid() const override;
};