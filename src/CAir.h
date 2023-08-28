#pragma once

#include "CBlock.h"
/** @brief Air block code for "map" file */
const int AIR_CODE = 0;

/** @brief Class represents air block */
class CAir : public CBlock
{
public:
    /**
     * @brief Construct a new air block
     */
    CAir ( const CCoord & coord );
    
    /**
     * @brief Do nothing as air block is empty
     */
    void render ( const int & x, const int & y ) const override;

    /**
     * @brief Check collision with another entity. Always return false because
     *        air does not collide with anything.
     * 
     * @param[in] entity entity to check collision with
     * @return false
     */
    bool entityCollision ( const CEntity & entity, SDL_Rect & result ) const override;

    /**
     * @brief Do nothing because air has no hitpoints
     * 
     * @param amount amount of damage dealt
     */
    void takeDamage ( const int & amount ) override;
    
    /**
     * @brief Check if block is destroyed
     * 
     * @return false because air cannot be destroyed
     */
    bool isDestroyed() const override;

    /**
     * @brief Get water code for a "map" file
     */
    virtual int getCode() const override;
};