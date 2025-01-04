#include "rider.h"
#include "../components/behaviour/riderMove.h"
#include <iostream>

Rider_S::Rider_S(Scene* scene, Transform* parent, RiderType riderType)
    : Rider(scene, parent, riderType, new RiderMove_S(this))
{
}
