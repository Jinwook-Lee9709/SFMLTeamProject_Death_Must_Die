#pragma once


class GameObject
{
protected:
	std::string name;
	bool active = true; //determine object run Update, Draw
	sf::Vector2f position;
	float rotation = 0.f;
	sf::Vector2f scale;

	sf::Vector2f origin;
	Origins originPreset;

	HitBox hitbox;
public:
	SortingLayers sortingLayer = SortingLayers::Default;
	int sortingOrder = 0;
	int sortingY = 0;

	GameObject(const std::string& name = "");
	virtual ~GameObject();

	const std::string& GetName() const { return name; }
	void SetName(const std::string& n) { name = n; }


	bool IsActive() const { return active; }
	void SetActive(bool a) { active = a; }

	sf::Vector2f GetPosition() const { return position; }
	virtual void SetPosition(const sf::Vector2f& pos) { position = pos; }

	float GetRotation() const { return rotation; }
	virtual void SetRotation(float angle) { rotation = angle; }

	sf::Vector2f GetScale() const { return scale; }
	virtual void SetScale(const sf::Vector2f& size) { scale = size; }

	virtual void FlipX(bool flag);
	virtual void FlipY(bool flag);

	sf::Vector2f GetOrigin() const { return origin; }
	virtual void SetOrigin(Origins preset);
	virtual void SetOrigin(const sf::Vector2f& newOrigin)
	{
		origin = newOrigin;
		originPreset = Origins::Custom;
	}
	virtual sf::FloatRect GetLocalBounds() const {
		return { 0.f, 0.f, 0.f, 0.f };
	}
	virtual sf::FloatRect GetGlobalBounds() const
	{
		return { 0.f, 0.f, 0.f, 0.f };
	}

	virtual const HitBox& GetHitBox() const
	{
		return hitbox;
	}

	virtual HitBox& GetHitBox()
	{
		return hitbox;
	}
	bool IsClicked(sf::Vector2f pos);
	bool IsRightClicked(sf::Vector2f pos);
	bool IsHover(sf::Vector2f pos);

	virtual void Init();
	virtual void Release();

	virtual void Reset();

	virtual void Update(float dt);
	virtual void LateUpdate(float dt) {}
	virtual void FixedUpdate(float dt) {}
	virtual void Draw(sf::RenderWindow& window);

	virtual void OnLocalize(Languages lang) {}
};

struct DrawOrderComparer
{
	bool operator()(GameObject* a, GameObject* b)
	{
		if (a->sortingLayer != b->sortingLayer)
			return a->sortingLayer > b->sortingLayer;
		else if (a->sortingOrder != b->sortingOrder)
			return a->sortingOrder > b->sortingOrder;
		return a->sortingY > b->sortingY;
	}
};
