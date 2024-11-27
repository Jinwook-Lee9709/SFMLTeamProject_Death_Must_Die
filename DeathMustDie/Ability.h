#pragma once

class Ability : public GameObject
{
protected:

public:
	Ability(const std::string& name = "");
	~Ability() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

