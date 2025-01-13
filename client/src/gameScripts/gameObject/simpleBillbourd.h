#pragma once
#include "../../../../common/src/gameObject.h"
#include "../../../../utils/src/math.h"
#include <string>

class SimpleBillbourd : public GameObject {
public:
    explicit SimpleBillbourd(const std::string& fileName);
    ~SimpleBillbourd() override = default;

private:
};