#pragma once
#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>
#include <vector>
#include "../../common/src/math/common_math.h"

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	bool mIsRunning;
	
	class Renderer* mRenderer;

};

