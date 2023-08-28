#include <assert.h>

#include "../CDisplay.h"
#include "../CGameMap.h"

int main ( int argc, char ** argv )
{
    SDL_Rect colRect;
    CDirt dirt1 ( { 0, 0 }, nullptr, 0 );
    
    CDirt dirt2 ( { BLOCK_SIZE / 2, BLOCK_SIZE / 2 }, nullptr, 0 );
    assert ( dirt2.entityCollision ( dirt1, colRect ) );
    assert ( colRect.w == BLOCK_SIZE / 2 && colRect.h == BLOCK_SIZE / 2 );

    CDirt dirt3 ( { BLOCK_SIZE, BLOCK_SIZE }, nullptr, 0 );
    assert ( !dirt3.entityCollision ( dirt1, colRect ) );
    assert ( colRect.w == 0 && colRect.h == 0 );

    CAir air ( { 0, 0 } );
    assert ( !air.entityCollision ( dirt1, colRect ) );
    assert ( colRect.w == 0 && colRect.h == 0 );

    CLava lava ( { 0, 0 }, nullptr );
    assert ( !lava.entityCollision ( dirt1, colRect ) );
    assert ( colRect.w == 0 && colRect.h == 0 );

    assert ( CBlock::findBlockPos ( {                   0 * BLOCK_SIZE,                   0 * BLOCK_SIZE }, 100 * BLOCK_SIZE ) ==    0 );
    assert ( CBlock::findBlockPos ( {                  49 * BLOCK_SIZE,                  24 * BLOCK_SIZE }, 100 * BLOCK_SIZE ) == 2449 );
    assert ( CBlock::findBlockPos ( {                  70 * BLOCK_SIZE,                  30 * BLOCK_SIZE }, 100 * BLOCK_SIZE ) == 3070 );
    assert ( CBlock::findBlockPos ( { BLOCK_SIZE / 2 + 70 * BLOCK_SIZE,                  30 * BLOCK_SIZE }, 100 * BLOCK_SIZE ) == 3070 );
    assert ( CBlock::findBlockPos ( {                  70 * BLOCK_SIZE, BLOCK_SIZE / 2 + 30 * BLOCK_SIZE }, 100 * BLOCK_SIZE ) == 3070 );
    assert ( CBlock::findBlockPos ( { BLOCK_SIZE / 2 + 70 * BLOCK_SIZE, BLOCK_SIZE / 2 + 30 * BLOCK_SIZE }, 100 * BLOCK_SIZE ) == 3070 );

    std::string fileName;

    fileName = "test_no_file.txt" ;
    assert ( !MapConverter::convertToMap ( fileName ) );
    fileName = "test_empty_map.txt" ;
    assert ( !MapConverter::convertToMap ( fileName ) );
    fileName = "test_small_map.txt" ;
    assert ( !MapConverter::convertToMap ( fileName ) );
    fileName = "test_no_player.txt" ;
    assert ( !MapConverter::convertToMap ( fileName ) );
    fileName = "test_wrong_format.txt" ;
    assert ( !MapConverter::convertToMap ( fileName ) );
    fileName = "test_not_rectangle.txt" ;
    assert ( !MapConverter::convertToMap ( fileName ) );

    CDisplay display;
    assert ( display.init() );

    CTextureSet textureSet;
    assert ( textureSet.load ( display.getRenderer() ) );

    CGameMap gameMap1 ( textureSet );
    fileName = "test_wrong_type.bin";
    assert ( !gameMap1.load ( fileName ) );
    CGameMap gameMap2 ( textureSet );
    fileName = "test_wrong_binary.map";
    assert ( !gameMap2.load ( fileName ) );
    
    std::cout << "Successfully passed all asserts" << std::endl;
}