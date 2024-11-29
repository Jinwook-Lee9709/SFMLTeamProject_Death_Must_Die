#pragma once
#include "GameObject.h"

struct Offensive
{
	double damage = 0.000;
	double criticalChance = 0.000;
	double criticalDamage = 0.000;
	double area = 0.000;
	double duration = 0.000;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Offensive, damage, criticalChance, criticalDamage, area, duration)
};

struct Attack
{
	int attackDamageMin = 45;
	int attackDamageMax = 75;
	double attackTime = 0.52;
	int attackArea = 135;
	double attackCriticalChance = 0.000;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Attack, attackDamageMin, attackDamageMax, attackTime, attackArea, attackCriticalChance)
};

struct Dash
{
	int dashCharge = 2;
	double dashRechargeTime = 1.6;
	int dashDistance = 230;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Dash, dashCharge, dashRechargeTime, dashDistance)
};

struct Defensive
{
	int life = 45;
	int lifeRegen = 0;
	int armor = 0;
	double damageReduction = 0.000;
	int evasion = 0;
	int moveSpeed = 305;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Defensive, life, lifeRegen, armor, damageReduction, evasion, moveSpeed)
};

struct Utility
{
	double luck = 0.000f;
	int pullArea = 520;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Utility, luck, pullArea)
};

struct BlessingSlot
{
	int strikeSlot = 2;
	int castSlot = 2;
	int powerSlot = 4;
	int summonSlot = 1;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(BlessingSlot, strikeSlot, castSlot, powerSlot, summonSlot)
};

struct GodBlessings
{
	double adeptOffers = 0.100;
	double expertOffers = 0.033;
	double masterOffers = 0.017;
	double legendOffers = 0.153;
	double newOffers = 0.450;
	double levelupOffers = 0.520;
	double rarityupOffers = 0.030;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(GodBlessings, adeptOffers, expertOffers, 
		masterOffers, legendOffers, newOffers, levelupOffers, rarityupOffers)
};

struct Stat
{
	Offensive offensive;
	Attack attack;
	Dash dash;
	Defensive defensive;
	Utility utility;
	BlessingSlot blessingSlot;
	GodBlessings godBlessing;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Stat, offensive, attack, dash, defensive, utility, blessingSlot, godBlessing)
};

class Player : public GameObject
{
public:
	enum class Status
	{
		IDLE,
		WALK,
		DASH,
		ATTACK,
		ATTACK2,
	};
protected:

	sf::Sprite body;
	Animator animator;

	sf::Sprite body2;
	Animator animator2;

	sf::Sprite body3;
	Animator animator3;
	HitBox attackHB;

	sf::Sprite body4;
	Animator animator4;

	bool flip;
	sf::Vector2f direction;

	std::queue<Status> temp;

	std::string clipId = "knight_idle";
	std::string clipId2 = "knight_soward1";
	std::string clipId3 = "knight_attack_range";
	std::string clipId4 = "dash_spr";
	Status status;

	float attackTerm = 0.f;
	bool isAttack;
	bool isAttack2;
	sf::Vector2f attackPos;

	float speed = 500.f;
	int frame = 0;
	bool isDash;
	int dashCharge;
	float dashChargeTime;
	sf::Vector2f dashPos;
	sf::Vector2f dashDirection;

	Stat stat;
	Scene* scene;
public:
	Player(const std::string& name = "");
	~Player() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetStatus(Status cur);
	void Move(float dt);

	void Attack(float dt);
	void Dash(float dt);

	void SaveStat();
	void LoadStat();
};

