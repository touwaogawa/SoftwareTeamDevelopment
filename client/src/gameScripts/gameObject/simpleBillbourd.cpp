#include "simpleBillbourd.h"
#include "../../../../common/src/component/transform.h"
#include "../../component/billbourdRenderer.h"
#include "../../renderer.h"

SimpleBillbourd::SimpleBillbourd(const std::string& fileName)
    : GameObject()
{
    // Billbourd
    BillbourdRenderer* Billbourd = new BillbourdRenderer(this, fileName);
    AddComponent(Billbourd);
}