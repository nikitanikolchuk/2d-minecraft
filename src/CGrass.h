#pragma once

#include "CBlock.h"

/** @brief Amount of damage blocked from each hit */
const int GRASS_DURABILITY = 5;
/** @brief Lava code for "map" file */
const int GRASS_CODE = 2;

/** @brief Class represents a grass block */
class CGrass : public CBlock
{
public:
    /**
     * @brief Construct a new grass block
     */
    CGrass ( const CCoord & coord, std::shared_ptr<CTexture> texture, const int & hitpoints );
    
    /**
     * @brief Decrease block hitpoints by amount - block durability
     * 
     * @param amount amount of damage taken
     */
    void takeDamage ( const int & amount ) override;

    /**
     * @brief Get grass block code for a "map" file
     */
    virtual int getCode() const override;
};