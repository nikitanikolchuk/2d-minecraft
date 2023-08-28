#pragma once

#include "CEnemy.h"

/** @brief WOlf width in pixels */
const int WOLF_WIDTH = 112;
/** @brief Zombie height in pixels */
const int WOLF_HEIGHT = BLOCK_SIZE;
/** @brief Damage per hit */
const int WOLF_DAMAGE = 1;
/** @brief Maximal number of hitpoints */
const int WOLF_MAX_HITPOINTS = 50;
/** @brief Zombie velocity in pixels */
const int WOLF_VELOCITY = BLOCK_SIZE / 4;
/** @brief Maximal distance to player for reacting */
const int WOLF_AGGRO_RANGE = BLOCK_SIZE * 8;
/** @brief Wolf code for "map" file */
const int WOLF_CODE = 7;
/** @brief Enum for choosing wolf sprite */
enum { WOLF_IDLE = 0, WOLF_MOVE_BEGIN = 1, WOLF_MOVE_END = 2 };

/** @brief Class represents a wolf */
class CWolf : public CEnemy
{
public:
    /**
     * @brief Construct a new wolf
     * 
     * @param[in] coord coordinates of the new wolf 
     * @param[in] texture texture of the new wolf
     * @param[in] hitpoints hitpoints of the new wolf
     */
    CWolf ( const CCoord & coord, std::shared_ptr<CTexture> texture, const int & hitpoints );

    /**
     * @brief Render wolf
     * 
     * @param[in] x X coordinate
     * @param[in] y Y coordinate
     */
    void render ( const int & x, const int & y ) const override;

    /**
     * @brief Move depending on velocity on X axis and GRAVITY_PULL on Y axis. If this is an enemy
     *        set the X velocity and attack player if nearby.
     * 
     * @param[in] worldCoord width and height of the world
     * @param[in] map vector of all blocks
     * @param[in] creature vector of all creatures
     */
    void move ( const CCoord & worldCoord, CBlock::vector & map, CCreature::vector & creature  ) override;

    /**
     * @brief Choose frame based on current action and state.
     */
    void chooseFrame() override;

    /**
     * @brief Get the wolf's width
     * 
     * @return wolf width
     */
    int getWidth() const override;

    /**
     * @brief Get the wolf's height
     * 
     * @return wolf height
     */
    int getHeight() const override;

    /**
     * @brief Get wolf code for a "map" file
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