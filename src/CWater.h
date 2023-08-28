#pragma once

#include "CLiquid.h"

/** @brief Alpha mod value for setting water transparent */
const int WATER_TRANSPARENCY = 127;
/** @brief Water code for "map" file */
const int WATER_CODE = 5;

/** @brief Class represents a water block */
class CWater : public CLiquid
{
public:
    /**
     * @brief Construct a new water block
     * 
     * @param[in] coord coordinates of the new water block
     * @param[in] texture water texture
     */
    CWater ( const CCoord & coord, std::shared_ptr<CTexture> texture );

    /**
     * @brief Get water code for a "map" file
     */
    int getCode() const override;

    /**
     * @brief Create a new water block
     * 
     * @param[in] coord coordinates of the new block
     * @return std::unique_ptr<CBlock>
     */
    std::unique_ptr<CBlock> newLiquid ( const CCoord & coord ) const override;
};