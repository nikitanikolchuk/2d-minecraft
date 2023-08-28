#pragma once

#include "CBlock.h"

/** @brief Amount of damage ingored by block */
const int DIRT_DURABILITY = 5;
/** @brief Dirt code for "map" file */
const int DIRT_CODE = 1;

/** @brief Class represents a dirt block */
class CDirt : public CBlock
{
public:
    /**
     * @brief Construct a new dirt block
     */
    CDirt ( const CCoord & coord, std::shared_ptr<CTexture> texture, const int & hitpoints );
    
    /**
     * @brief Decrease block hitpoints by amount - block durability
     * 
     * @param amount amount of damage taken
     */
    void takeDamage ( const int & amount ) override;

    /**
     * @brief Get water code for a "map" file
     */
    virtual int getCode() const override;
};