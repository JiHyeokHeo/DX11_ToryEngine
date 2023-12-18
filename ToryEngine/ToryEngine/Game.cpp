#include "pch.h"
#include "Game.h"
#include "Camera.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Awake(HWND hwnd)
{
	_hwnd = hwnd;
	
	_graphics = make_shared<Graphics>(hwnd);
	_pipeline = make_shared<Pipeline>(_graphics->GetDeviceContext());
	
	//GO
	_monster = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	{
		_monster->GetOrAddTransform();
	}

	_camera = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	{
		_camera->GetOrAddTransform();
		_camera->AddComponent(make_shared<Camera>());
	}
}

void Game::Update()
{
	_monster->Update();
	_camera->Update();
}

void Game::Render()
{
	_graphics->RenderBegin();
	
	{
		_monster->Render(_pipeline);
	}

	_graphics->RenderEnd();
}






