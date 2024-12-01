#include "stdafx.h"
#include "SceneDev1.h"
#include "Player.h"
#include "TileMap2.h"

SceneDev1::SceneDev1() : Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{
	player = AddGo(new Player("Player"));
	for (int i = 0; i < tilesCount.x; i++)
	{
		std::vector<TileMap2*> temp;
		for (int j = 0; j < tilesCount.y; j++)
		{
			temp.push_back(AddGo(new TileMap2()));
		}
		tiles.push_back(temp);
	}
	
	//tiles.push_back(AddGo(new TileMap2("tile2")));
	Scene::Init();
	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(size);
	worldView.setCenter(0.f, 0.f);

	uiView.setSize(size);
	uiView.setCenter(size.x * 0.5f, size.y * 0.5f);

	//tiles[0]->SetScale({2.f, 2.f});
}

void SceneDev1::Enter()
{

	

	RES_TABLE_MGR.LoadScene("Dev1");
	Scene::Enter();
	sprite = new SpriteGo("background");
	sprite->Reset();
	player->SetScale({3.f, 3.f});

	sf::Vector2f tileSize = { tiles[0][0]->GetGlobalBounds().width * 0.5f + 5.f,  tiles[0][0]->GetGlobalBounds().height * 0.5f };

	for (int i = 0; i < tilesCount.x; i++)
	{
		for (int j = 0; j < tilesCount.y; j++)
		{
			if (j == 0 && i == 0)
			{
				tiles[i][j]->SetPosition({ 0.f, 0.f });
				continue;
			}
			else if (j == 0)
			{
				tiles[i][j]->SetPosition({ tiles[i - 1][j]->GetPosition().x - tileSize.x,
					tiles[i - 1][j]->GetPosition().y + tileSize.y });
				continue;
			}
			tiles[i][j]->SetPosition({ tiles[i][j - 1]->GetPosition().x + tileSize.x, 
				tiles[i][j - 1]->GetPosition().y + tileSize.y });
		}

	}
	

}

void SceneDev1::Exit()
{
	Scene::Exit();
}

void SceneDev1::Update(float dt)
{ 

	Scene::Update(dt);

	
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	
	//text->Draw(window);
	//sprite->Draw(window);
	Scene::Draw(window);
	
}
