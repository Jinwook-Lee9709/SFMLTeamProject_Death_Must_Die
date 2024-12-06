#pragma once
#include "Scene.h"

class Button;

class SceneTitle :
    public Scene
{
private:
public:
    SceneTitle();
    virtual ~SceneTitle() = default;

	void Init() override;
	void Release() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetButton(Button* btn);
	void GoToPlayScene();
	void EndGame();
};

