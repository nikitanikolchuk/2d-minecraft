#pragma once

#include "CCreature.h"

/** @brief Max distance between enemy and player on Y axis for attack */
const int ENEMY_MAX_ATTACK_HEIGHT = BLOCK_SIZE * 5 / 2;

/** @brief Class represents an enemy */
class CEnemy : public CCreature
{
public:
    /**
     * @brief Construct a new eneny
     * 
     * @param[in] coord coordinates of new enemy 
     * @param[in] texture texture of new enemy
     * @param[in] hitpoints hitpoints of new enemy
     * @param[in] damage damage of new enemy
     */
    CEnemy ( const CCoord & coord, std::shared_ptr<CTexture> texture, const int & hitpoints, const int & damage );

    /**
     * @brief Get the enemy damage
     * 
     * @return enemy damage
     */
    int getDamage() const;

    /**
     * @brief Check if player is close
     * 
     * @param playerHitbox 
     * @return true if player is close enough, false otherwise
     */
    bool isClose ( const SDL_Rect & playerHitbox ) const;

    /**
     * @brief Move depending on velocity on X axis and GRAVITY_PULL on Y axis. If this is an enemy
     *        set the X velocity and attack player if nearby.
     * 
     * @param[in] worldCoord width and height of the world
     * @param[in] map vector of all blocks
     * @param[in] creature vector of all creatures
     */
    virtual void move ( const CCoord & worldCoord, CBlock::vector & map, CCreature::vector & creature  ) override;

    /**
     * @brief Check if the creature is an enemy
     * 
     * @return true if the creature is an enemy, fale otherwise
     */
    bool isEnemy() const override;

protected:
    /**
     * @brief Get velocity of the enemy
     * 
     * @return enemy velocity
     */
    virtual int getVelocity() const = 0;

    /**
     * @brief Get aggro range of the enemy
     * 
     * @return enemy aggro range
     */
    virtual int getAggroRange() const = 0;

    /** @brief Previous x coord for checking if enemy should jump */
    int m_PrevX;
};