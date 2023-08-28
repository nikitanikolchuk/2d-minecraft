#pragma once

#include "CAir.h"

/** @brief Number of pixels to decrease when falling */
const int GRAVITY_PULL = BLOCK_SIZE * 2 / 3;
/** @brief Player jump force in pixels */
const int CREATURE_JUMP_FORCE = BLOCK_SIZE + GRAVITY_PULL;
/** @brief Height of safe fall in pixels */
const int SAFE_FALL_DISTANCE = BLOCK_SIZE * 5;
/** @brief Number that determines connection between fall distance and taken damage */
const int FALL_DAMAGE_DIVIDER = 5;
/** Enum for creature directions */
enum class Direction { LEFT = -1, RIGHT = 1 };

/** @brief Class represents a creature */
class CCreature : public CEntity
{
public:
    /** Type for a vector of creature pointers */
    typedef std::vector<std::shared_ptr<CCreature>> vector;

    /**
     * @brief Construct a new creature.
     * 
     * @param[in] coord coordinates of the new creature
     * @param[in] texture texture of the new creature
     * @param[in] hitpoints hitpoints of the new creature
     * @param[in] damage damage of the new creature
     */
    CCreature ( const CCoord & coord, std::shared_ptr<CTexture> texture, const int & hitpoints, const int & damage );

    /**
     * @brief Choose frame based on current action and state.
     */
    virtual void chooseFrame() = 0;

    /**
     * @brief Check if creature touches entities
     * 
     * @param[in] map map of all blocks
     * @param[out] intersect rectangle of intersection of entities 
     * @return true if touches an entity, false otherwise
     */
    bool touchesEntities ( CBlock::vector & map, CCreature::vector & creature, SDL_Rect & insersect ) const;

    /**
     * @brief Move depending on velocity on X axis and GRAVITY_PULL on Y axis. If this is an enemy
     *        set the X velocity and attack player if nearby.
     * 
     * @param[in] worldCoord width and height of the world
     * @param[in] map vector of all blocks
     * @param[in] creature vector of all creatures
     */
    virtual void move ( const CCoord & worldCoord, CBlock::vector & map, CCreature::vector & creature  );

    /**
     * @brief Check if the creature is an enemy
     * 
     * @return true if the creature is an enemy, fale otherwise
     */
    virtual bool isEnemy() const;

protected:
    /**
     * @brief Decrease Y coordinate by CREATURE_JUMP_FORCE or lesser
     *        value if there is a collision.
     *      
     * @param[in] map vector of blocks to check collision with 
     */
    void jump ( CBlock::vector & map, CCreature::vector & creature );

    /** @brief Creature damage */
    int m_Damage;
    /** @brief Creature velocity on X axis */
    int m_Velocity;
    /** @brief Creature direction */
    Direction m_Direction;
    /** @brief Y coordinate of position where falling started from */
    int m_FallStart;
    /** @brief Creature frame */
    int m_Frame;
};