#pragma once
#include "../../../../../../common/src/component/behaviour.h"

class BillbourdRenderer;
class BillbordAnimationMove : public Behaviour {
public:
    BillbordAnimationMove(GameObject* owner, BillbourdRenderer* target, int rowNum, int columnNum, int intervalFrame, int lifeFrame);

    virtual ~BillbordAnimationMove() override = default;
    void Update() override;

private:
    BillbourdRenderer* const mTargetBillbourd;
    const int mRowNum;
    const int mColumnNum;
    const int mIntervalFrame;
    const int mLifeFrame;
    int mRow;
    int mColumn;
    int mFrame;
};