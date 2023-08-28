#include "CGameMap.h"

CGameMap::CGameMap ( const CTextureSet & textureSet )
{
    m_Camera = { 0, 0, INIT_SCREEN_WIDTH, INIT_SCREEN_HEIGHT };
    m_TextureSet = textureSet;
    m_CtrlPressed = false;
    m_State = State::BEGIN;
    m_Font = nullptr;
}
CGameMap::~CGameMap()
{
    if ( m_Font != nullptr )
        TTF_CloseFont ( m_Font );
}
void CGameMap::addEntity ( const CCoord & coord, const int & code, const int & hitpoints, const int & score )
{
    switch ( code ) {
        case AIR_CODE:
            m_Map.push_back ( std::unique_ptr<CAir> ( new CAir ( coord ) ) );
            break;
        case DIRT_CODE:
            m_Map.push_back ( std::unique_ptr<CDirt> ( new CDirt ( coord, m_TextureSet.getTexture ( "dirt" ), hitpoints ) ) );
            break;
        case GRASS_CODE:
            m_Map.push_back ( std::unique_ptr<CGrass> ( new CGrass ( coord , m_TextureSet.getTexture ( "grass" ), hitpoints ) ) );
            break;
        case STONE_CODE:
            m_Map.push_back ( std::unique_ptr<CStone> ( new CStone ( coord, m_TextureSet.getTexture ( "stone" ), hitpoints ) ) );
            break;
        case DIAMOND_CODE:
            m_Map.push_back ( std::unique_ptr<CDiamond> ( new CDiamond ( coord, m_TextureSet.getTexture ( "diamond" ), hitpoints ) ) );
            break;
        case WATER_CODE:
            m_Map.push_back ( std::unique_ptr<CWater> ( new CWater ( coord, m_TextureSet.getTexture ( "water" ) ) ) );
            break;
        case LAVA_CODE:
            m_Map.push_back ( std::unique_ptr<CLava> ( new CLava ( coord, m_TextureSet.getTexture ( "lava" ) ) ) );
            break;
        case WOLF_CODE:
            m_Creature.push_back ( std::shared_ptr<CWolf> ( new CWolf ( coord, m_TextureSet.getTexture ( "wolf" ), WOLF_MAX_HITPOINTS ) ) );
            break;
        case ZOMBIE_CODE:
            m_Creature.push_back ( std::shared_ptr<CZombie> ( new CZombie ( coord, m_TextureSet.getTexture ( "zombie" ), ZOMBIE_MAX_HITPOINTS ) ) );
            break;
        case PLAYER_CODE:
            m_Player = std::shared_ptr<CPlayer> ( new CPlayer ( coord, m_TextureSet.getTexture ( "player" ), hitpoints, score, m_Font ) );
            m_Creature.push_back ( m_Player );
            break;
    }
}
bool CGameMap::load ( std::string & fileName )
{
    m_Font = TTF_OpenFont ( FONT_FILE.c_str(), FONT_SIZE );
    if ( m_Font == nullptr ) {
        std::cout << "Font open error:" << TTF_GetError() << std::endl;
        return false;
    }

    if ( fileName.length() < FILE_EXTENSION_LENGTH || (
         fileName.substr ( fileName.length() - FILE_EXTENSION_LENGTH, FILE_EXTENSION_LENGTH ) != "map" &&
         fileName.substr ( fileName.length() - FILE_EXTENSION_LENGTH, FILE_EXTENSION_LENGTH ) != "txt" ) )
        return false;

    if ( fileName.substr ( fileName.length() - FILE_EXTENSION_LENGTH, FILE_EXTENSION_LENGTH ) == "txt" )
        if ( !MapConverter::convertToMap ( fileName ) ) {
            std::cout << "\".txt\" file conversion error" << std::endl;
            return false;
        }

    SDL_RWops * file = SDL_RWFromFile( ( CONFIG_PATH + fileName ).c_str(), "r+b" );
    if ( file == nullptr ) {
        std::cout << "File read error for " << CONFIG_PATH + fileName << ": " << SDL_GetError() << std::endl;
        return false;
    }

    int entityCount, score;
    if ( SDL_RWread ( file, &m_Width, sizeof ( uint32_t ), 1 ) == 0 ||
         SDL_RWread ( file, &m_Height, sizeof ( uint32_t ), 1 ) == 0 ||
         SDL_RWread ( file, &entityCount, sizeof ( uint32_t ), 1 ) == 0 ||
         SDL_RWread ( file, &score, sizeof ( uint32_t ), 1 ) == 0 ) {
        std::cout << "Error for " << CONFIG_PATH + fileName << ": " << SDL_GetError() << std::endl;
        SDL_RWclose ( file );
        return false;
    }

    int x, y, code, hitpoints;
    for ( int i = 0; i < entityCount; i++ ) {
        if ( SDL_RWread ( file, &x, sizeof ( uint32_t ), 1 ) == 0 ||
             SDL_RWread ( file, &y, sizeof ( uint32_t ), 1 ) == 0 ||
             SDL_RWread ( file, &code, sizeof ( uint32_t ), 1 ) == 0 ||
             SDL_RWread ( file, &hitpoints, sizeof ( uint32_t ), 1 ) == 0 ) {
            std::cout << "Error for " << CONFIG_PATH + fileName << ": " << SDL_GetError() << std::endl;
            SDL_RWclose ( file );
            return false;
        }
        addEntity ( { x, y }, code, hitpoints, score );
    }

    SDL_RWclose( file );
    return true;
}
void CGameMap::save ( const std::string fileName ) const
{
    SDL_RWops * file = SDL_RWFromFile ( ( CONFIG_PATH + fileName ).c_str(), "w+b" );
	
    uint32_t entityCount = m_Map.size() + m_Creature.size();
    u_int32_t score = m_Player->getScore();
    SDL_RWwrite ( file, &m_Width, sizeof ( uint32_t ), 1 );
    SDL_RWwrite ( file, &m_Height, sizeof ( uint32_t ), 1 );
    SDL_RWwrite ( file, &entityCount, sizeof ( uint32_t ), 1 );
    SDL_RWwrite ( file, &score, sizeof ( uint32_t ), 1 );

    for ( auto & it : m_Map )
        it->writeToFile ( file, it->getCode() );
    for ( auto & it : m_Creature )
        it->writeToFile ( file, it->getCode() );
    
    SDL_RWclose( file );
    std::cout << "Saved game to \"" << CONFIG_PATH + fileName << "\"" << std::endl;
}
void CGameMap::handleEvent ( SDL_Event & event, bool & quit )
{
    if ( event.type == SDL_QUIT ) {
        quit = true;
        return;
    }

    if ( m_State != State::PLAY ) {
        if ( m_State == State::BEGIN && event.type == SDL_KEYDOWN && event.key.repeat == 0 && event.key.keysym.sym == SDLK_RETURN )
            m_State = State::PLAY;
        else if ( m_State == State::END && event.type == SDL_KEYDOWN && event.key.repeat == 0 && event.key.keysym.sym == SDLK_RETURN )
            quit = true;
        else
            return;
    }

    if ( event.type == SDL_KEYDOWN && event.key.repeat == 0 ) {
        if ( event.key.keysym.sym == SDLK_LCTRL || event.key.keysym.sym == SDLK_RCTRL )
            m_CtrlPressed = true;
        else if ( event.key.keysym.sym == SDLK_s && m_CtrlPressed )
            save ( "save.map" );
    } else if ( event.type == SDL_KEYUP && event.key.repeat == 0 && (
                event.key.keysym.sym == SDLK_LCTRL || event.key.keysym.sym == SDLK_RCTRL ) ) {
        m_CtrlPressed = false;
    }
    
    m_Player->handleEvent ( event, { m_Width, m_Height }, m_Map, m_Camera, m_TextureSet, m_Creature );
}
void CGameMap::action()
{
    for ( auto & it : m_Creature ) {
        it->move ( { m_Width, m_Height }, m_Map, m_Creature );
        it->chooseFrame();
    }

    CEntity::vector creatureCollision ( m_Creature.begin(), m_Creature.end() );
    for ( auto & it : m_Map )
        it->flow ( { m_Width, m_Height }, m_Map, creatureCollision );

    for ( auto it = m_Creature.begin(); it != m_Creature.end(); ) {
        if ( it->get()->isDestroyed() && it->get()->isEnemy() )
            m_Creature.erase ( it );
        else
            it++;
    }

    if ( m_Player->isDestroyed() || m_Player->getScore() >= VICTORY_SCORE )
        m_State = State::END;

    setCamera();
    renderAll();
}
void CGameMap::setCamera()
{
    m_Camera.x = ( m_Player->getCoord().m_X + PLAYER_WIDTH / 2 ) - INIT_SCREEN_WIDTH / 2;
	m_Camera.y = ( m_Player->getCoord().m_Y + PLAYER_HEIGHT / 2 ) - INIT_SCREEN_HEIGHT / 2;

	if( m_Camera.x < 0 )
		m_Camera.x = 0;
	if( m_Camera.y < 0 )
		m_Camera.y = 0;
	if( m_Camera.x > m_Width - m_Camera.w )
		m_Camera.x = m_Width - m_Camera.w;
	if( m_Camera.y > m_Height - m_Camera.h )
		m_Camera.y = m_Height - m_Camera.h;
}
void CGameMap::renderAll()
{
    if ( m_State == State::BEGIN ) {
        CTexture begin ( m_TextureSet.getTexture ( "dirt" )->getRenderer() );
        begin.loadText ( m_Font, "TO BEGIN GAME PRESS ENTER", { 0, 0, 0 } );
        begin.render ( ( INIT_SCREEN_WIDTH - begin.getWidth() ) / 2, ( INIT_SCREEN_HEIGHT - begin.getHeight() ) / 2 );
        return;
    }

    if ( m_State == State::END ) {
        CTexture end ( m_TextureSet.getTexture ( "dirt" )->getRenderer() );
        if ( m_Player->getScore() >= VICTORY_SCORE ) {
            end.loadText ( m_Font, "YOU WON", { 0, 0, 0 } );
            end.render ( ( INIT_SCREEN_WIDTH - end.getWidth() ) / 2, ( INIT_SCREEN_HEIGHT - end.getHeight() ) / 2 );
        } else {
            end.loadText ( m_Font, "GAME OVER", { 0, 0, 0 } );
            end.render ( ( INIT_SCREEN_WIDTH - end.getWidth() ) / 2, ( INIT_SCREEN_HEIGHT - end.getHeight() ) / 2 );
            int textHeight = end.getHeight();
            end.loadText ( m_Font, "your score = " + std::to_string ( m_Player->getScore() ), { 0, 0, 0 } );
            end.render ( ( INIT_SCREEN_WIDTH - end.getWidth() ) / 2, ( INIT_SCREEN_HEIGHT - end.getHeight() ) / 2 + textHeight * 3 / 2 );
        }
        end.loadText ( m_Font, "to exit game press enter", { 0, 0, 0 } );
        end.render ( ( INIT_SCREEN_WIDTH - end.getWidth() ) / 2, INIT_SCREEN_HEIGHT - end.getHeight() * 3 / 2 );
        return;
    }

    SDL_Rect blockRect;
    for ( auto & it : m_Map ) {
        blockRect = { it->getCoord().m_X, it->getCoord().m_Y, BLOCK_SIZE, BLOCK_SIZE };
        if ( !it->isLiquid() && SDL_HasIntersection ( &blockRect, &m_Camera ) )
            it->render ( it->getCoord().m_X - m_Camera.x, it->getCoord().m_Y - m_Camera.y );
    }

    for ( auto & it : m_Creature )
        it->render ( it->getCoord().m_X - m_Camera.x, it->getCoord().m_Y - m_Camera.y );

    for ( auto & it : m_Map ) {
        blockRect = { it->getCoord().m_X, it->getCoord().m_Y, BLOCK_SIZE, BLOCK_SIZE };
        if ( it->isLiquid() && SDL_HasIntersection ( &blockRect, &m_Camera ) )
            it->render ( it->getCoord().m_X - m_Camera.x, it->getCoord().m_Y - m_Camera.y );
    }
}