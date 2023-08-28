#include "CAir.h"

CAir::CAir ( const CCoord & coord )
    : CBlock ( coord )
{
}
void CAir::render ( const int & x, const int & y ) const
{
}
bool CAir::entityCollision ( const CEntity & entity, SDL_Rect & result ) const
{
    return false;
}
void CAir::takeDamage ( const int & amount )
{
}
bool CAir::isDestroyed() const
{ 
    return false;
}
int CAir::getCode() const
{ 
    return AIR_CODE;
}