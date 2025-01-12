#pragma once
#include "../../../../common/src/gameObject.h"
#include "../../../../utils/src/math.h"
#include <string>

class SimpleSprite : public GameObject {
public:
    explicit SimpleSprite(const std::string& fileName);
    ~SimpleSprite() override = default;

private:
};