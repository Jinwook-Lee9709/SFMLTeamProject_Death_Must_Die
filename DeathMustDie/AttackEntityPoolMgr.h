#pragma once
#include <AttackEntity.h>
#include <AttackEntityPool.h>

class AttackEntityPoolMgr : public GameObject
{
protected:
	std::unordered_map<std::string, AttackEntityPool*> poolContainer;
	std::unordered_map<std::string, std::list<AttackEntity*>> attackEntities;
	
public:
	AttackEntityPoolMgr(const std::string& name = "entityPoolMgr");
	~AttackEntityPoolMgr() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	AttackEntity* GetEntity(const std::string& name);
	void CreatePool(const std::string& name, const AttackEntityType& type, const json data);

};


