#include "bey.h"
#include "beyMove.h"
#include <iostream>
Bey_S::Bey_S(Scene* scene, Transform* parent, BeyType beyType)
    : Bey(scene, parent, beyType, new BeyMove_S(this))
{
}
