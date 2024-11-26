#pragma once
#include "Singleton.h"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

class AnimationClip;

class ResourceTableManager :
    public Singleton<ResourceTableManager>
{
    friend class Singleton<ResourceTableManager>;
private:
	json PATH;
	json ANIMATION;
	std::unordered_map <std::string, std::string> resourceTable;
	std::string err = "";
public:
	void Init();
	bool LoadAnimation();

	bool LoadScene(const std::string& scene);
	bool UnLoadScene(const std::string& scene);

	sf::Texture& GetTex(const std::string& texKey);
	sf::Font& GetFont(const std::string& fontKey);
	sf::SoundBuffer& GetSound(const std::string& soundKey);
	AnimationClip& GetAnim(const std::string& AnimId);

	std::string& GetPath(const std::string& key);

	json& GetAnimationList() { return ANIMATION; }
};

#define RES_TABLE_MGR (ResourceTableManager::Instance())
#define GET_TEX(X) (RES_TABLE_MGR.GetTex(X))
#define GET_FONT(X) (RES_TABLE_MGR.GetFont(X))
#define GET_SOUND(X) (RES_TABLE_MGR.GetSound(X))
#define GET_SHADER(X) (RES_TABLE_MGR.GetShader(X))
#define GET_ANIM(X) (RES_TABLE_MGR.GetAnim(X))
