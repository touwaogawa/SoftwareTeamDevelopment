#include "component.h"
#include "gameObject.h"
#include <iostream>

void Component::Init()
{
    if (mIsInitialized) {
        std::cout << "this component is already initialized" << std::endl;
    } else {
        mTransform     = mOwner->GetTransform();
        mIsInitialized = true;
    }
}