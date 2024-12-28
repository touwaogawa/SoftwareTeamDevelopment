#include "commandData.h"
#include <iostream>
void CommandDataCout(CommandData cd)
{
    std::cout << "attack1: " << cd.attack1 << std::endl;
    std::cout << "attack2: " << cd.attack2 << std::endl;
    std::cout << "jump: " << cd.jump << std::endl;
    std::cout << "moveAxis.x: " << cd.moveAxis.x << std::endl;
    std::cout << "moveAxis.y: " << cd.moveAxis.y << std::endl;
    std::cout << "subAxis.x: " << cd.subAxis.x << std::endl;
    std::cout << "subAxis.y: " << cd.subAxis.y << std::endl;
    std::cout << "frame: " << cd.frame << std::endl;
}