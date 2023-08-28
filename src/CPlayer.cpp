#include "CPlayer.h"

CPlayer::CPlayer ( const CCoord & coord, std::shared_ptr<CTexture> texture, const int & hitpoints, const int & score, TTF_Font * font )
    : CCreature ( coord, texture, hitpoints, INIT_PLAYER_DAMAGE )
{
    m_Score = score;
    m_IsPunching = false;
    m_Frame = PLAYER_IDLE;
    m_Font = font;
}
CCoord CPlayer::getCoord() const
{
    return { m_Coord.m_X + PLAYER_LEFT_GAP, m_Coord.m_Y };
}
int CPlayer::getWidth() const
{
    return PLAYER_WIDTH;
}
int CPlayer::getHeight() const
{
    return PLAYER_HEIGHT;
}
void CPlayer::render ( const int & x, const int & y ) const
{
    SDL_Rect clip = { PLAYER_SPRITE_WIDTH *  m_Frame, 0, PLAYER_SPRITE_WIDTH, PLAYER_HEIGHT };
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if ( m_Direction == Direction::LEFT )
        flip = SDL_FLIP_HORIZONTAL;
    m_Texture->render ( x - PLAYER_LEFT_GAP, y, &clip, flip );

    CTexture score ( m_Texture->getRenderer() );
    score.loadText ( m_Font, "score = " + std::to_string ( m_Score ), { 0, 0, 0 } );
    score.render ( PLAYER_SCORE_COORD.m_X, PLAYER_SCORE_COORD.m_Y );

    CTexture healthbar ( m_Texture->getRenderer() );
    healthbar.loadText ( m_Font, "hp = " + std::to_string ( m_HitPoints ), { 0, 0, 0 } );
    healthbar.render ( PLAYER_HEALTHBAR_COORD.m_X, PLAYER_HEALTHBAR_COORD.m_Y );
}
void CPlayer::handleEvent ( SDL_Event & event, const CCoord & worldCoord, CBlock::vector & map,
                            const SDL_Rect & camera, CTextureSet & textureSet, CCreature::vector & creature )
{
    if ( event.type == SDL_MOUSEBUTTONDOWN )
        mouseEvent ( event, worldCoord, map, camera, textureSet, creature );
    else if ( event.type == SDL_KEYDOWN && event.key.repeat == 0 )
        keyDownEvent ( event, map, creature );
    else if ( event.type == SDL_KEYUP && event.key.repeat == 0 )
        keyUpEvent ( event );
}
void CPlayer::mouseEvent ( SDL_Event & event, const CCoord & worldCoord, CBlock::vector & map,
                           const SDL_Rect & camera, CTextureSet & textureSet, CCreature::vector & creature )
{
    CCoord mouseCoord;
    SDL_GetMouseState ( &mouseCoord.m_X, &mouseCoord.m_Y );
    mouseCoord += { camera.x, camera.y };

    if ( mouseCoord.m_X >= getCoord().m_X )
        m_Direction = Direction::RIGHT;
    else
        m_Direction = Direction::LEFT;

    if ( std::abs ( getCoord().m_X + PLAYER_WIDTH / 2 - mouseCoord.m_X ) > PLAYER_MAX_PUNCH_DISTANCE ||
         std::abs ( getCoord().m_Y + PLAYER_HEIGHT / 2 - mouseCoord.m_Y ) > PLAYER_MAX_PUNCH_DISTANCE ||
         mouseCoord.m_X > worldCoord.m_X || mouseCoord.m_X < 0 ||
         mouseCoord.m_Y > worldCoord.m_Y || mouseCoord.m_Y < 0 )
        return;
    
    switch ( event.button.button ) {
        case SDL_BUTTON_LEFT:
            if ( !m_IsPunching ) {
                m_IsPunching = true;
                m_Frame = PLAYER_PUNCH_BEGIN;
            }
            punch ( mouseCoord, worldCoord.m_X, map, creature );
            break;            
        case SDL_BUTTON_RIGHT:
            buildBlock ( mouseCoord, worldCoord.m_X, map, textureSet.getTexture ( "dirt" ) );
            break;
    }
}
void CPlayer::keyDownEvent ( SDL_Event & event, CBlock::vector & map, CCreature::vector & creature )
{
    switch ( event.key.keysym.sym ) {
        case SDLK_UP:
            if ( m_FallStart == m_Coord.m_Y )
                jump ( map, creature );
            break;
        case SDLK_LEFT:
            m_Velocity -= PLAYER_VELOCITY;
            m_Direction = Direction::LEFT;
            break;
        case SDLK_RIGHT:
            m_Velocity += PLAYER_VELOCITY;
            m_Direction = Direction::RIGHT;
            break;
    }
}
void CPlayer::keyUpEvent ( SDL_Event & event )
{
    switch ( event.key.keysym.sym ) {
            case SDLK_LEFT:
                m_Velocity += PLAYER_VELOCITY;
                break;
            case SDLK_RIGHT:
                m_Velocity -= PLAYER_VELOCITY;
                break;
        }
}
void CPlayer::chooseFrame()
{
    if ( m_Frame == PLAYER_PUNCH_END ) {
        m_Frame = PLAYER_IDLE;
        m_IsPunching = false;
    } else if ( m_IsPunching ) {
        m_Frame++;
    } else if ( m_FallStart != m_Coord.m_Y ) {
        m_Frame = PLAYER_JUMP;
    } else if ( m_Velocity == 0 ) {
        m_Frame = PLAYER_IDLE;
    } else if ( ( m_Frame == PLAYER_IDLE && m_Velocity != 0 ) || m_Frame == PLAYER_MOVE_END ) {
        m_Frame = PLAYER_MOVE_BEGIN;
    } else if ( m_Frame >= PLAYER_MOVE_BEGIN && m_Frame < PLAYER_MOVE_END ) {
        m_Frame++;
    }
}
void CPlayer::punch ( const CCoord & mouseCoord, const int & worldWidth, CBlock::vector & map, CCreature::vector & creature )
{
    SDL_Point mouse = { mouseCoord.m_X, mouseCoord.m_Y };
    for ( auto & it : creature ) {
        SDL_Rect creatureRect = { it->getCoord().m_X, it->getCoord().m_Y, it->getWidth(), it->getHeight() };
        if ( &(*it) != &(*this) && SDL_PointInRect ( &mouse, &creatureRect ) ) {
            it->takeDamage ( m_Damage );
            if ( it->isDestroyed() )
                m_Score++;
            return;
        }
    }

    int blockPos = CBlock::findBlockPos ( mouseCoord, worldWidth );
    map[blockPos]->takeDamage ( m_Damage );
    if ( map[blockPos]->isDestroyed() ) {
        if ( typeid ( *map[blockPos] ) == typeid ( CDiamond ) )
            m_Score++;
        CCoord newCoord = map[blockPos]->getCoord();
        map[blockPos] = std::unique_ptr<CAir> ( new CAir ( newCoord ) );
    }
}
void CPlayer::buildBlock ( const CCoord & mouseCoord, const int & worldWidth, CBlock::vector & map, std::shared_ptr<CTexture> dirtTexture )
{
    int blockPos = CBlock::findBlockPos ( mouseCoord, worldWidth );
    if ( ( typeid ( *map[blockPos] ) == typeid ( CAir ) ) || map[blockPos]->isLiquid() ) {
        CCoord newCoord = map[blockPos]->getCoord();
        std::unique_ptr<CDirt> newBlock = std::unique_ptr<CDirt> ( new CDirt ( newCoord, dirtTexture, BLOCK_MAX_HITPOINTS ) );
        SDL_Rect intersect;
        if ( !newBlock->entityCollision ( *this, intersect ) )
            map[blockPos] = std::move ( newBlock );
    }
}
int CPlayer::getCode() const
{
    return PLAYER_CODE;
}
int CPlayer::getScore() const
{
    return m_Score;
}
