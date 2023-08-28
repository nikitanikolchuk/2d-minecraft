#pragma once

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/** @brief Path to directory with textures */
const std::string TEXTURE_PATH = "assets/textures/"; 

/** @brief Class represents an SDL texture. */
class CTexture
{
public:

    /**
     * @brief CTexture default constructor
     */
    CTexture() = default;

    /**
     * @brief Construct a new CTexture object with a pointer to renderer.
     */
    CTexture ( SDL_Renderer * renderer );

    /**
     * @brief Destroy the CTexture object.
     */
    ~CTexture();

    /**
     * @brief Load image and convert it to texture.
     * 
     * @param[in] fileName name of image as a string 
     * @return true if the image was found and convertion
     *         was successfull, false otherwise
     */
    bool loadImage ( const std::string & fileName );

    /**
     * @brief Convert text to texture.
     * 
     * @param[in] font ttf font pointer
     * @param[in] text text to convert
     * @param[in] color text color
     * @return true if conversion was successfull, false otherwise
     */
    bool loadText ( TTF_Font * font, const std::string & text, const SDL_Color & color );

    /**
     * @brief Set alpha mode to make texture transparent.
     * 
     * @param[in] alpha alpha mode value
     */
    void setAlpha ( const int8_t & value );

    /**
     * @brief Render the texture
     * 
     * @param[in] x first coordinate
     * @param[in] y second coordinate
     * @param[in] clip part of texture to render
     * @param[in] flip briefiable that defines flip 
     * @param[in] angle angle for texture rotation
     * @param[in] center center point for rotation
     */
    void render ( const int & x, const int & y, SDL_Rect * clip = nullptr,
                  const SDL_RendererFlip & flip = SDL_FLIP_NONE, double angle = 0, SDL_Point * center = nullptr );

    /**
     * @brief Get the texture width
     * 
     * @return texture width
     */
    int getWidth() const;

    /**
     * @brief Get the texture height
     * 
     * @return texture height
     */
    int getHeight() const;

    /**
     * @brief Get renderer
     * 
     * @return SDL_Renderer *
     */
    SDL_Renderer * getRenderer() const;

private:
    /**
     * @brief Destroy the current texture. Useful for changing the texture.
     */
    void destroy();

    /** @brief Display renderer */
    SDL_Renderer * m_Renderer;
    /** @brief Actual texture */
    SDL_Texture * m_Texture;
    /** @brief Texture width */
    int m_Width;
    /** @brief Texture height */
    int m_Height;
};