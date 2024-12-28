// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "../../common/src/component.h"

class TargetComponent : public Component {
public:
    TargetComponent(class Actor* owner);
    ~TargetComponent();
    TypeID GetType() const override { return TTargetComponent; }
};
