#pragma once
class SceneDev3 : public Scene
{
private:
	sf::Sprite sprite;
	Animator anim;
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

