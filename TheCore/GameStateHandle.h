#pragma once
#include "pch.h"

#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"

class GameStateHandle
{
public:
	GameStateHandle() = default;
	virtual ~GameStateHandle();

	virtual void Update() = 0;
	virtual void Render() = 0;

	void test();
};

 