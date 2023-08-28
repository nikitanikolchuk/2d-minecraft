#pragma once

#include "CEnemy.h"

/** @brief Zombie width in pixels */
const int ZOMBIE_WIDTH = 56;
/** @brief Zombie sprite width in pixels */
const int ZOMBIE_SPRITE_WIDTH = 132;
/** @brief Zombie height in pixels */
const int ZOMBIE_HEIGHT = BLOCK_SIZE * 2;
/** @brief Zombie damage */
const int ZOMBIE_DAMAGE = 1;
/** @brief Zombie max hitpoints */
const int ZOMBIE_MAX_HITPOINTS = 30;
/** @brief Zombie velocity in pixels */
const int ZOMBIE_VELOCITY = BLOCK_SIZE / 8;
/** @brief Distance of player detection for a zombie */
const int ZOMBIE_AGGRO_RANGE = BLOCK_SIZE * 5;
/** @brief Lava code for "map" file */
const int ZOMBIE_CODE = 8;
/** @brief Enum for choosing zombie sprite */
enum { ZOMBIE_IDLE = 0, ZOMBIE_MOVE_BEGIN = 1, ZOMBIE_MOVE_END = 2 };

/** @brief Class represents a zombie */
class CZombie : public CEnemy
{
public:
    /**
     * @brief Construct a new zombie
     * 
     * @param[in] coord coordinates of the new zombie 
     * @param[in] texture texture of the new zombie
     * @param[in] hitpoints hitpoints of the new zombie
     */
    CZombie ( const CCoord & coord, std::shared_ptr<CTexture> texture, const int & hitpoints );

    /**
     * @brief Render player and player info separately.
     * 
     * @param[in] x X coordinate
     * @param[in] y Y coordinate
     */
    void render ( const int & x, const int & y ) const override;

    /**
     * @brief Choose frame based on current action and state.
     */
    void chooseFrame() override;

    /**
     * @brief Get the zombie's coordinates
     * 
     * @return zombie coordinates
     */
    CCoord getCoord() const override;

    /**
     * @brief Get the zombie's width
     * 
     * @return player width
     */
    int getWidth() const override;

    /**
     * @brief Get the zombie's height
     * 
     * @return player height
     */
    int getHeight() const override;

    /**
     * @brief Get zombie code for a "map" file
     */
    virtual int getCode() const override;

private:
    /**
     * @brief Get velocity of the enemy
     * 
     * @return enemy velocity
     */
    int getVelocity() const override;

    /**
     * @brief Get aggro range of the enemy
     * 
     * @return enemy aggro range
     */
    int getAggroRange() const override;
};