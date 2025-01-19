#include "billbourdAnimationMove.h"
#include "../../../../../../common/src/gameObject.h"
#include "../../../../../../utils/src/math.h"
#include "../../../../component/billbourdRenderer.h"
BillbordAnimationMove::BillbordAnimationMove(GameObject* owner, BillbourdRenderer* target, int rowNum, int columnNum, int intervalFrame, int lifeFrame)
    : Behaviour(owner)
    , mTargetBillbourd(target)
    , mRowNum(rowNum)
    , mColumnNum(columnNum)
    , mIntervalFrame(intervalFrame)
    , mLifeFrame(lifeFrame)
    , mRow(0)
    , mColumn(0)
    , mFrame(0)
{
    float x = static_cast<float>(1.0f / mColumnNum);
    float y = static_cast<float>(1.0f / mRowNum);
    mTargetBillbourd->SetFrameSize(Vector2(x, y));
}

void BillbordAnimationMove::Update()
{
    // std::cout << "BillbordAnimationMove update" << std::endl;
    if (mFrame < mLifeFrame) {
        if (mIntervalFrame <= 0) {
            mTargetBillbourd->SetFrameIndex(Vector2(mColumn, mRow));
            mColumn++;
            if (mColumn >= mColumnNum) {
                mColumn = 0;
                mRow++;
                if (mRow >= mRowNum) {
                    mRow = 0;
                }
            }
        } else {
            if (mFrame % mIntervalFrame == 0) {
                mTargetBillbourd->SetFrameIndex(Vector2(mColumn, mRow));
                mColumn++;
                if (mColumn >= mColumnNum) {
                    mColumn = 0;
                    mRow++;
                    if (mRow >= mRowNum) {
                        mRow = 0;
                    }
                }
            }
        }
    } else if (mFrame == mLifeFrame) {
        mOwner->Destroy();
    }

    mFrame++;
}