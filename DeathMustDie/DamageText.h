#pragma once
#include "GameObject.h"

class DamageText : public GameObject
{
protected:
	TextGo text;

	sf::Vector2f posForAnim;

	std::queue<int> playQueue;

	float duration = 1;
	float timer;
	bool isPlay;

public:
	DamageText(const std::string& name = "");
	~DamageText() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void AddAnimation(int type);

	void PlayAnimation(int type);

	void SetDuration(float duration) { this->duration = duration; }
	void SetText(int type);
};

