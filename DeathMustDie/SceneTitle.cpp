#include "stdafx.h"
#include "SceneTitle.h"
#include "Button.h"

SceneTitle::SceneTitle() : Scene(SceneIds::Title)
{
}

void SceneTitle::Init()
{
	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(size);
	uiView.setSize(size);
	Scene::Init();
}

void SceneTitle::Release()
{
}

void SceneTitle::Enter()
{
	GameObject* go;
	worldView.setCenter(FRAMEWORK.GetWindowSizeF() * 0.5f);
	uiView.setCenter(FRAMEWORK.GetWindowSizeF() * 0.5f);
	RES_TABLE_MGR.LoadScene("Title");
	go = AddGo(new SpriteGo("tilteBackground"));
	go->sortingLayer = SortingLayers::UI;
	go->sortingOrder = -1;
	go = AddGo(new Button("Play"));
	go->sortingLayer = SortingLayers::UI;
	go->sortingOrder = 0;
	SetButton((Button*)go);
	go = AddGo(new Button("Exit"));
	go->sortingLayer = SortingLayers::UI;
	go->sortingOrder = 0;
	SetButton((Button*)go);
	EVENT_HANDLER.AddEvent("ButtonPlayPressed", std::bind(&SceneTitle::GoToPlayScene, this));
	EVENT_HANDLER.AddEvent("ButtonExitPressed", std::bind(&SceneTitle::EndGame, this));

	ApplyAddGo();
	Scene::Enter();
}

void SceneTitle::Exit()
{
	RemoveAllGo();
	Scene::Exit();	
}

void SceneTitle::Update(float dt)
{
	if(InputMgr::GetKeyDown(sf::Keyboard::R))
	{
		SetButton((Button*)FindGo("ButtonPlay"));
		SetButton((Button*)FindGo("ButtonExit"));
	}
	
	Scene::Update(dt);
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneTitle::SetButton(Button* btn)
{
	UI_SETTING_TABLE->Reload();
	json j = UI_SETTING_TABLE->Get("Title");
	json info = j[btn->GetName()];
	std::vector<float> posVec= info["position"].get<std::vector<float>>();
	sf::Vector2f pos = { posVec[0], posVec[1] };
	Origins origin = (Origins)(info["origin"].get<int>());
	int characterSize = info["characterSize"].get<int>();
	std::string stringId = info["stringId"].get<std::string>();
	std::string font = info["font"].get<std::string>();

	btn->SetFont(font);
	btn->SetString(stringId);
	btn->SetCharacterSize(characterSize);
	btn->SetPosition(pos);
	btn->SetOrigin(origin);

}

void SceneTitle::GoToPlayScene()
{
	SCENE_MGR.ChangeScene(SceneIds::Game);
}

void SceneTitle::EndGame()
{
	FRAMEWORK.GetWindow().close();
}
