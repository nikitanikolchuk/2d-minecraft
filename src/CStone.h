#pragma once

#include "CBlock.h"

/** @brief Amount of damage blocked from each hit */
const int STONE_DURABILITY = 8;
/** @brief Stone code for "map" file */
const int STONE_CODE = 3;

/** @brief Class represents a stone block */
class CStone : public CBlock 
{
public:
    /**
     * @brief Construct a new stone object
     */
    CStone ( const CCoord & coord, std::shared_ptr<CTexture> texture, const int & hitpoints );
    
    /**
     * @brief Decrease block hitpoints by amount - block durability
     * 
     * @param amount amount of damage taken
     */
    void takeDamage ( const int & amount ) override;

    /**
     * @brief Get stone code for a "map" file
     */
    virtual int getCode() const override;
};