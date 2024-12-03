#pragma once
class AbilityMgr;
class Player;
class AniSkeleton;
class MonsterPoolManager;
class MonsterSpawner;

class SceneDev3 : public Scene
{
private:

	sf::Sprite sprite;
	sf::Sprite sprite2;
	sf::Text text;
	sf::Texture tex;
	sf::RenderTexture renTex;

public:

	SceneDev3();
	virtual ~SceneDev3() = default;

	virtual void Init();
	virtual void Release();

	virtual void Enter();
	virtual void Exit();

	virtual void Update(float dt);
	virtual void LateUpdate(float dt);
	virtual void FixedUpdate(float dt);

	virtual void Draw(sf::RenderWindow& window);



};

