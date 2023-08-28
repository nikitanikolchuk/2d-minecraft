#pragma once

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/** @brief Initial screen width in pixels */
const int INIT_SCREEN_WIDTH = 1280;
/** @brief Initial screen height in pixels */
const int INIT_SCREEN_HEIGHT = 720;
/** @brief Cap FPS of the game */
const int DISPLAY_FPS = 12;
/** @brief Ticks per frame */
const int DISPLAY_TICKS_PER_FRAME = 1000 / DISPLAY_FPS; 
/** @brief Background color as RGB value */
const int BACKGROUND_COLOR[3] = { 64, 196, 255 };

/** @brief Class contains data about connected display and operates with them. */
class CDisplay
{
public:
    /**
     * @brief Construct a new CDisplay object. Set pointers to nullptr and
     *        set screen default size.
     */
    CDisplay();

    /**
     * @brief Quit SDL subsystems and close the window.
     */
    ~CDisplay();

    /**
     * @brief Initialize SDL subsystems and open the window.
     * 
     * @return true if there was no significant error, false otherwise
     */
    bool init();

    /**
     * @brief Get the display renderer
     * 
     * @return SDL_Renderer* 
     */
    SDL_Renderer * getRenderer() const;

    /**
     * @brief Fill screen with background color
     */
    void clear();

    /**
     * @brief Update the screen.
     */
    void update();

private:
    /** @brief Window to render to */
    SDL_Window * m_Window;
    /** @brief WIndow renderer */
    SDL_Renderer * m_Renderer;
};