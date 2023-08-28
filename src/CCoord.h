#pragma once

/** @brief Struct stores coordinates */
struct CCoord
{
    /**
     * @brief Add coordinates to this object.
     * 
     * @param[in] object coordinates to add
     */
    void operator += ( const CCoord & object )
    { m_X += object.m_X; m_Y += object.m_Y; }

    /** @brief X coordinate */
    int m_X;
    /** @brief Y coordinate */
    int m_Y;
};