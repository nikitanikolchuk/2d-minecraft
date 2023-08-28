#pragma once

#include "CDisplay.h"
#include "MapConverter.h"

/** @brief Path to ttf font file */
const std::string FONT_FILE = "assets/fonts/font.ttf";
/** @brief Font size for text in the game */
const int FONT_SIZE = 20;
/** @brief Name of initial configuration file */
const std::string INIT_MAP_FILE = "init.txt";
/** @brief Score needed for a victory */
const int VICTORY_SCORE = 10;
/** Enum of game states */
enum class State { BEGIN, PLAY, END };

/** @brief Class represents map of the game world */
class CGameMap
{
public:
    /**
     * @brief Construct a new game map
     */
    CGameMap ( const CTextureSet & textureSet );

    /**
     * @brief Destroy the game map
     */
    ~CGameMap();

    /**
     * @brief Load map from a file.
     * 
     * @param[in] fileName name of the map to load
     * @param[in] textureSet textures to load from
     * @return true if loading is succesfull, false otherwise
     */
    bool load ( std::string & fileName );

    /**
     * @brief Handle event
     * 
     * @param[in] event event to react to
     * @param[in] quit quit flag for closing the game
     */
    void handleEvent ( SDL_Event & event, bool & quit );

    /**
     * @brief Make actions in the game based on events
     */
    void action();

private:
    /**
     * @brief Add new entity to the game map
     * 
     * @param[in] coord coordinates of the new entity
     * @param[in] code code of the new entity from 0 to 9
     * @param[in] hitpoints hitpoints of the new entity
     * @param[in] score player score to add
     */
    void addEntity ( const CCoord & coord, const int & code, const int & hitpoints, const int & score );

    /**
     * @brief Save current game state to a file.
     * 
     * @param[in] filePath file to save to
     */
    void save ( const std::string fileName ) const;

    /**
     * @brief Set the camera centered on player if possible
     */
    void setCamera();

    /**
     * @brief Render all entities.
     */
    void renderAll();

    /** @brief Width of game world */
    int m_Width;
    /** @brief Height of game world */
    int m_Height;
    /** @brief Part of the game world displayed on the screen */
    SDL_Rect m_Camera;
    /** @brief Set of all textures */
    CTextureSet m_TextureSet;
    /** @brief Game font */
    TTF_Font * m_Font;
    /** @brief Vector of all blocks */
    CBlock::vector m_Map;
    /** @brief Vector of all creatures */
    CCreature::vector m_Creature;
    /** @brief The player */
    std::shared_ptr<CPlayer> m_Player;
    /** @brief Flag for Ctrl button */
    bool m_CtrlPressed;
    /** @brief Game state */
    State m_State;
};