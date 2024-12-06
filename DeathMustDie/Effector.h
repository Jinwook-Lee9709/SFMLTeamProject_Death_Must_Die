#pragma once
#include "GameObject.h"

class Effector : public GameObject
{
protected:
	Animator animator;
	sf::Sprite sprite;

	std::queue<std::string> animationQueue;

	float timer;
	float duration;
	bool isPlaying;
	bool isRealtime = false;
public:
	Effector(const std::string& name = "");
	~Effector() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetDuration(float duration);
	void AddAnimation(std::string animId);
	void PlayAnimation(std::string animId);

	void SetToRealDeltaTime(bool isRealtime);

	bool IsPlay() { return isPlaying; }
};
