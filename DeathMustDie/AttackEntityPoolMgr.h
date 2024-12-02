#pragma once
#include <AttackEntity.h>
#include <AttackEntityPool.h>

struct PairHash {
	template <typename T1, typename T2>
	std::size_t operator()(const std::pair<T1, T2>& pair) const {
		std::hash<T1> hash1;
		std::hash<T2> hash2;
		return hash1(pair.first) ^ (hash2(pair.second) << 1);
	}
};


class AttackEntityPoolMgr : public GameObject
{
protected:
	std::unordered_map<	std::pair<std::string, std::string>, AttackEntityPool*, PairHash> poolContainer;
	std::unordered_map<	std::pair<std::string, std::string>, std::list<AttackEntity*>, PairHash> attackEntities;
	
public:
	AttackEntityPoolMgr(const std::string& name = "AttackEntityPoolMgr");
	~AttackEntityPoolMgr() = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	AttackEntity* GetEntity(const std::string& name, const std::string& user = "Player");
	void CreatePool(const std::string& name, const AttackEntityType& type, const json data, const std::string& user = "Player");

};


