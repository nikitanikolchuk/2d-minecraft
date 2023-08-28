#include "MapConverter.h"

bool MapConverter::convertToMap ( std::string & fileName )
{
    std::ifstream input ( CONFIG_PATH + fileName );
    if ( !input.good() )
        return false;
    
    fileName = fileName.substr ( 0, fileName.length() - FILE_EXTENSION_LENGTH ) + "map";
    
    CCoord currentCoord = { 0, 0 };
    char code = 0;
    uint32_t mapWidth = 0;
    EntityVector blocks;
    EntityVector creatures;
    bool playerPresent = false;

    while ( input.get ( code ) ) {

        if ( code == '\n' ) {
            if ( mapWidth == 0 )
                mapWidth = currentCoord.m_X + BLOCK_SIZE;
            if ( mapWidth != 0 && currentCoord.m_X != static_cast<int> ( mapWidth - BLOCK_SIZE ) ) {
                input.close();
                return false;
            }
            currentCoord.m_X = 0;
            currentCoord.m_Y += BLOCK_SIZE;
            continue;
        }

        if ( !isdigit ( code ) ) {
            input.close();
            return false;
        }

        if ( code - '0' <= LAVA_CODE ) {
            blocks.push_back ( { currentCoord, code - '0' } );
        } else if ( code - '0' == WOLF_CODE ) {
            creatures.push_back ( { { currentCoord.m_X - BLOCK_SIZE + WOLF_WIDTH, currentCoord.m_Y }, WOLF_CODE } );
            blocks.push_back ( { currentCoord, AIR_CODE } );
        } else if ( code - '0' == ZOMBIE_CODE ) {
            creatures.push_back ( { { currentCoord.m_X - ( ZOMBIE_SPRITE_WIDTH - ZOMBIE_WIDTH ) / 2, currentCoord.m_Y - ZOMBIE_HEIGHT + BLOCK_SIZE }, ZOMBIE_CODE } );
            blocks.push_back ( { currentCoord, AIR_CODE } );
        } else if ( !playerPresent ) {
            playerPresent = true;
            creatures.push_back ( { { currentCoord.m_X - PLAYER_LEFT_GAP, currentCoord.m_Y - ( PLAYER_HEIGHT - BLOCK_SIZE ) }, PLAYER_CODE } );
            blocks.push_back ( { currentCoord, AIR_CODE } );
        } else if ( playerPresent ) {
            input.close();
            return false;
        }

        currentCoord.m_X += BLOCK_SIZE;
    }
    input.close();

    currentCoord.m_Y += BLOCK_SIZE;
    if ( !playerPresent || PLAYER_HEIGHT > currentCoord.m_Y )
        return false;

    SDL_RWops * file = SDL_RWFromFile ( ( CONFIG_PATH + fileName ).c_str(), "w+b" );
    uint32_t entityCount = blocks.size() + creatures.size();
    uint32_t score = 0;
    SDL_RWwrite( file, &currentCoord.m_X, sizeof ( uint32_t ), 1 ); 
    SDL_RWwrite( file, &currentCoord.m_Y, sizeof ( uint32_t ), 1 ); 
    SDL_RWwrite( file, &entityCount, sizeof ( uint32_t ), 1 );
    SDL_RWwrite( file, &score, sizeof ( uint32_t ), 1 );

    for ( auto & it : blocks )
        saveEntity ( file, it.first, it.second, BLOCK_MAX_HITPOINTS );

    for ( auto & it : creatures ) {
        if ( it.second == WOLF_CODE )
            saveEntity ( file, it.first, it.second, WOLF_MAX_HITPOINTS );
        else if ( it.second == ZOMBIE_CODE )
            saveEntity ( file, it.first, it.second, ZOMBIE_MAX_HITPOINTS );
        else if ( it.second == PLAYER_CODE )
            saveEntity ( file, it.first, it.second, MAX_PLAYER_HITPOINTS );
    }

    SDL_RWclose ( file );
    return true;
}
void MapConverter::saveEntity ( SDL_RWops * file, const CCoord & coord, const int & code, const int & hitpoints )
{
    SDL_RWwrite( file, &coord.m_X, sizeof ( uint32_t ), 1 ); 
    SDL_RWwrite( file, &coord.m_Y, sizeof ( uint32_t ), 1 ); 
    SDL_RWwrite( file, &code, sizeof ( uint32_t ), 1 ); 
    SDL_RWwrite( file, &hitpoints, sizeof ( uint32_t ), 1 );
}