#pragma once

#include "CLiquid.h"

/** @brief Damage to entities standing in lava */
const int LAVA_DAMAGE = 1;
/** @brief Lava code for "map" file */
const int LAVA_CODE = 6;

/** @brief Class represents a lava block */
class CLava : public CLiquid
{
public:
    /**
     * @brief Construct a new lava block
     * 
     * @param[in] coord coordinates of the new lava block
     * @param[in] texture lava texture
     */
    CLava ( const CCoord & coord, std::shared_ptr<CTexture> texture );
    
    /**
     * @brief Deal damage to an entity inside lava
     * 
     * @param[in,out] entity entity to deal damage to
     */
    void dealDamage ( CEntity & entity ) const override;

    /**
     * @brief Get water code for a "map" file
     */
    virtual int getCode() const override;

    /**
     * @brief Create a new lava block
     * 
     * @param[in] coord coordinates of the new lava block
     * @return std::unique_ptr<CBlock>
     */
    std::unique_ptr<CBlock> newLiquid ( const CCoord & coord ) const override;
};