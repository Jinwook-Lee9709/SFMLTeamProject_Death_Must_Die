#pragma once
class AbilityMgr;
class Player;
class MonsterPoolManager;

class SceneDev3 : public Scene
{
private:
	SpriteGo* sprite;
	Player* player;
	AbilityMgr* abilMgr;
	MonsterPoolManager* MPMgr;

	json j;
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

