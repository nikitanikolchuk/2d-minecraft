#pragma once

#include <map>
#include <memory>
#include <vector>

#include "CTexture.h"

/** @brief Name of textures to load */
const std::vector<std::string> TEXTURES_TO_LOAD = { "dirt", "grass", "stone", "diamond", "water", "lava", "wolf", "zombie", "player" };
/** @brief Image type for textures */
const std::string PNG = ".png";
/** Shortened type of texture container */
typedef std::map<std::string,std::shared_ptr<CTexture>> TextureMap;

/** @brief Class represents a collection of textures */
class CTextureSet
{
public:
    /**
     * @brief Load textures from assets.
     * 
     * @param[in] renderer renderer for all textures
     * @return true if loading is successfull, false otherwise
     */
    bool load ( SDL_Renderer * renderer );

    /**
     * @brief Get shared_ptr of a texture.
     * 
     * @param name name of needed texture
     * @return shared_ptr of the needed texture
     */
    std::shared_ptr<CTexture> getTexture ( const std::string & name );

private:
    /** @brief map of all textures */
    TextureMap m_TextureMap;
};