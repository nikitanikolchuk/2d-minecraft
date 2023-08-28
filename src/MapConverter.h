#pragma once

#include <fstream>

#include "CPlayer.h"
#include "CWolf.h"
#include "CZombie.h"
#include "CGrass.h"
#include "CStone.h"
#include "CWater.h"
#include "CLava.h"

/** @brief Path to game configuration files and saves */
const std::string CONFIG_PATH = "examples/";
/** @brief File type name lenght, example: ".txt", ".map" */
const int FILE_EXTENSION_LENGTH = 3;

/** @brief Namespace contains functions for conveting ".txt" files to ".map" files */
namespace MapConverter
{
    /** Type for saving entity coordinates and code */
    typedef std::vector<std::pair<CCoord,int>> EntityVector;

    /**
     * @brief Convert ".txt" file to a game ".map" file and save to "/examples".
     * 
     * @param[in,out] fileName name of ".txt" file to convert
     * @return true if convertion is succesful, false otherwise 
     */
    bool convertToMap ( std::string & fileName );

    /**
     * @brief Save entity to a file.
     * 
     * @param[out] file file to save to
     * @param[in] coord coordinates of the new entity 
     * @param[in] code code of new enity
     * @param[in] hitpoints hitpoints of the new entity
     * @return true if saving is succesfull, false otherwise
     */
    void saveEntity ( SDL_RWops * file, const CCoord & coord, const int & code, const int & hitpoints );
}