#pragma once

#include <memory>
#include <vector>

#include "CCoord.h"
#include "CTexture.h"


/** @brief Class represents an entity like a creature or a block */
class CEntity
{
public:
    /** Type for vector of entities */
    typedef std::vector<std::shared_ptr<CEntity>> vector;

    /**
     * @brief Construct a new entity.
     * 
     * @param[in] coord entity's coordinates
     * @param[in] texture entity's texture
     * @param[in] hitpoints entity's hitpoints
     */
    CEntity ( const CCoord & coord, std::shared_ptr<CTexture> texture, const int & hitpoints );
    
    /**
     * @brief Render entity's texture.
     */
    virtual void render ( const int & x, const int & y ) const;
    
    /**
     * @brief Check if this entity has collision with another entity.
     *        Default function checks collision with the entity's hitbox.
     *
     * @param[in] entity entity to check collision with
     * @return true if there is a collision, false otherwise
     */
    virtual bool entityCollision ( const CEntity & entity, SDL_Rect & result ) const;

    /**
     * @brief Get the coordinates of the entity
     * 
     * @return entity coordinates
     */
    virtual CCoord getCoord() const;

    /**
     * @brief Get the entity's width
     * 
     * @return entity width 
     */
    virtual int getWidth() const = 0;

    /**
     * @brief Get the entity's height
     * 
     * @return entity height 
     */
    virtual int getHeight() const = 0;

    /**
     * @brief Damage entity.
     * 
     * @param amount amount of hitpoints to decrease
     */
    virtual void takeDamage ( const int & amount );

    /**
     * @brief Check if hitpoints <= 0.
     * 
     * @return true if hitpoints <= 0
     */
    virtual bool isDestroyed() const;

    /**
     * @brief Write data about entity to file.
     * 
     * @param[in] file file to write to
     * @param[in] code code of the entity
     */
    virtual void writeToFile ( SDL_RWops * file, const int & code ) const;

    /**
     * @brief Get entity code for a "map" file
     */
    virtual int getCode() const = 0;

protected:
    /** @brief Coordinates of the entity */
    CCoord m_Coord;
    /** @brief Texture of the entity */
    std::shared_ptr<CTexture> m_Texture;
    /** @brief Entity hitpoints */
    int m_HitPoints;
};