#pragma once

#include "CBlock.h"

/** @brief Amount of damage blocked from each hit */
const int DIAMOND_DURABILITY = 9;
/** @brief Diamond code for "map" file */
const int DIAMOND_CODE = 4;

/** @brief Class represents a diamond block */
class CDiamond : public CBlock 
{
public:
    /**
     * @brief Construct a new stone object
     */
    CDiamond ( const CCoord & coord, std::shared_ptr<CTexture> texture, const int & hitpoints );
    
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