#pragma once
#include "../../../../common/src/gameObject.h"
#include "../../../../utils/src/math.h"
#include <string>

class SimpleEffect : public GameObject {
public:
    explicit SimpleEffect(const std::string& objFileName, const std::string& imageFileName);
    ~SimpleEffect() override = default;

private:
};