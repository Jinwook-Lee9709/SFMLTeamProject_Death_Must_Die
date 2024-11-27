#pragma once
class FallAttack;

class SceneDev3 : public Scene
{
private:
	SpriteGo* sprite;
	FallAttack* attack;
	json j;
	ObjectPool<FallAttack>* pool;
	std::vector<FallAttack*> attacks;
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

