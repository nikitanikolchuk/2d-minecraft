#pragma once

#include "CDirt.h"
#include "CDiamond.h"
#include "CCreature.h"
#include "CTextureSet.h"

/** @brief Initial player damage */
const int INIT_PLAYER_DAMAGE = 10;
/** @brief Maximal player hitpoints */
const int MAX_PLAYER_HITPOINTS = 100;
/** @brief Player width in pixels */
const int PLAYER_WIDTH = 56;
/** @brief Player height in pixels */
const int PLAYER_HEIGHT = BLOCK_SIZE * 2;
/** @brief Player sprite width in pixels */
const int PLAYER_SPRITE_WIDTH = 132;
/** @brief Distance from left player sprite side to player hitbox */
const int PLAYER_LEFT_GAP = 36;
/** @brief Distance from right player sprite side to player hitbox */
const int PLAYER_RIGHT_GAP = 40;
/** @brief Player velocity in pixels per move */
const int PLAYER_VELOCITY = BLOCK_SIZE / 2;
/** @brief Max punch distance in pixels */
const int PLAYER_MAX_PUNCH_DISTANCE = PLAYER_WIDTH / 2 + BLOCK_SIZE * 2;
/** @brief Distance from diplay left corner to player score in pixels */
const CCoord PLAYER_SCORE_COORD = { 5, 8 };
/** @brief Distance from diplay left corner to player healthbar in pixels */
const CCoord PLAYER_HEALTHBAR_COORD = { 5, 36 };
/** @brief Player code for ".map" file */
const int PLAYER_CODE = 9;
/** Enum for choosing player sprite */
enum { PLAYER_IDLE = 0, PLAYER_MOVE_BEGIN = 1, PLAYER_MOVE_END = 4,
       PLAYER_JUMP = 5, PLAYER_PUNCH_BEGIN = 6, PLAYER_PUNCH_END = 11 };

/** @brief Class represents a player */
class CPlayer : public CCreature
{
public:
    /**
     * @brief Construct a new player
     * 
     * @param[in] coord player coordinates
     * @param[in] texture player texture
     * @param[in] hitpoints player hitpoints
     * @param[in] score player score
     */
    CPlayer ( const CCoord & coord, std::shared_ptr<CTexture> texture, const int & hitpoints, const int & score, TTF_Font * font );

    /**
     * @brief Get player's coordinates
     * 
     * @return player coordinates
     */
    CCoord getCoord() const override;

    /**
     * @brief Get the player's width
     * 
     * @return player width
     */
    int getWidth() const override;

    /**
     * @brief Get the player's height
     * 
     * @return player height
     */
    int getHeight() const override;

    /**
     * @brief Render player and player info separately.
     * 
     * @param[in] x X coordinate
     * @param[in] y Y coordinate
     */
    void render ( const int & x, const int & y ) const override;

    /**
     * @brief Handle event by player
     * 
     * @param[in] event event to handle 
     * @param[in] map map of all blocks
     */
    void handleEvent ( SDL_Event & event, const CCoord & worldCoord, CBlock::vector & map, const SDL_Rect & camera,
                       CTextureSet & textureSet, CCreature::vector & creature );

    /**
     * @brief Choose frame based on current action and state.
     */
    void chooseFrame() override;

    /**
     * @brief Get water code for a "map" file
     */
    virtual int getCode() const override;

    /**
     * @brief Get player score
     * 
     * @return player score
     */
    int getScore() const;

private:
    /**
     * @brief Handle mouse event.
     * 
     * @param[in] event event to react to 
     * @param[in] worldCoord game world width and height
     * @param[in,out] map map of blocks
     * @param[in] camera displayed part of the game world
     * @param[in] textureSet map of pointers to textures
     * @param[in] creature vector of all creatures
     */
    void mouseEvent ( SDL_Event & event, const CCoord & worldCoord, CBlock::vector & map, const SDL_Rect & camera,
                      CTextureSet & textureSet, CCreature::vector & creature );

    /**
     * @brief Handle key down event.
     * 
     * @param[in] event event to react to
     * @param[in] map map of blocks
     */
    void keyDownEvent ( SDL_Event & event, CBlock::vector & map, CCreature::vector & creature );

    /**
     * @brief Handle key up event.
     * 
     * @param[in] event event to react to
     */
    void keyUpEvent ( SDL_Event & event );

    /**
     * @brief Deal damage to an entity
     * 
     * @param[in] mouseCoord mouse coordinates 
     * @param[in] worldWidth width and height of the world
     * @param[in] map vector of all blocks
     * @param[in] creature vector of all creatures
     */
    void punch ( const CCoord & mouseCoord, const int & worldWidth, CBlock::vector & map, CCreature::vector & creature );

    /**
     * @brief Build a block of dirt if there is an empty space
     * 
     * @param[in] mouseCoord coordinates of the mouse
     * @param[in] textureSet all loaded textures
     */
    void buildBlock ( const CCoord & mouseCoord, const int & worldWidth, CBlock::vector & map, std::shared_ptr<CTexture> dirtTexture );
    
    /** @brief Player score */
    int m_Score;
    /** @brief Flag for punchin */
    bool m_IsPunching;
    /** @brief Player score and helthbar font */
    TTF_Font * m_Font;
};