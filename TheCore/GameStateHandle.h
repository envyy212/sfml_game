#pragma once
#include "pch.h"

class GameStateHandle
{
public:
	GameStateHandle() = default;
	virtual ~GameStateHandle();

	virtual void Update() = 0;
	virtual void Render() = 0;

	void test();
};

 