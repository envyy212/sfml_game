#pragma once
#include "GameStateHandle.h"

class GameState : public GameStateHandle
{
public:
	GameState();
	virtual ~GameState();

	void Update();
	void Render();
private:
};

