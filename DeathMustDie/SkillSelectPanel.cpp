#include "stdafx.h"
#include "SkillSelectPanel.h"

SkillSelectPanel::SkillSelectPanel(const std::string& name)
	: GameObject(name)
{
}

void SkillSelectPanel::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	canvas.setPosition(position);
}

void SkillSelectPanel::SetRotation(float angle)
{
	rotation = angle;
	canvas.setRotation(rotation);
}

void SkillSelectPanel::SetScale(const sf::Vector2f& s)
{
	scale = s;
	canvas.setScale(scale);
}

void SkillSelectPanel::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(canvas, originPreset);
	}
}

void SkillSelectPanel::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void SkillSelectPanel::Init()
{
}

void SkillSelectPanel::Release()
{

	for (auto& pair : sprites)
	{
		delete pair.second;
	}
	sprites.clear();
	for (auto& pair : texts)
	{
		pair.second.Release();
	}
	texts.clear();
	delete texBuf;
}

void SkillSelectPanel::Reset()
{
	texBuf = new sf::RenderTexture();
	SetComponent();
	
}

void SkillSelectPanel::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::R))
	{
		Release();
		UI_SETTING_TABLE->Reload();
		Reset();
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::F))
	{
		animator.Play("boon_appear");
	}
	animator.Update(dt);
}

void SkillSelectPanel::Draw(sf::RenderWindow& window)
{
	texBuf->clear();
	for (auto& pair : sprites) { texBuf->draw(*pair.second); }
	for (auto& pair : texts) { texBuf->draw(pair.second.GetText()); }
	texBuf->display();
	canvas.setTexture(texBuf->getTexture(), true);
	window.draw(canvas);
}

void SkillSelectPanel::SetComponent()
{
	sprites.clear();
	texts.clear();

	json j = UI_SETTING_TABLE->Get("SkillSelectPanel");
	auto it = j["Sprites"].begin();
	while (it != j["Sprites"].end())
	{
		std::string name = it.key();
		SpriteInfo info = it.value();
		sf::Sprite* sprite = new sf::Sprite;
		sprite->setPosition(info.position);
		sprite->setScale(info.scale);
		Utils::SetOrigin((*sprite), info.origin);
		sprites.insert({ name, sprite });
		it++;
	}
	it = j["Texts"].begin();
	while (it != j["Texts"].end())
	{
		std::string name = it.key();
		TextInfo info = it.value();
		TextGo text;
		text.SetPosition(info.position);
		text.SetScale(info.scale);
		text.SetOrigin(info.origin);
		text.SetCharacterSize(info.chracterSize);
		text.SetFont(GET_FONT(info.font));
		text.SetString(L"TEST TEST");
		text.SetFillColor(sf::Color::Red);
		text.Reset();
		texts.insert({ name, text });
		it++;
	}

	sf::FloatRect panelRect = sprites["panel"]->getLocalBounds();
	std::vector<float > texSize = j["RenderTextureSize"].get<std::vector<float>>();
	texBuf->create(texSize[0], texSize[1]);

	animator.SetTarget(sprites["panel"]);
}

void to_json(json& j, const SpriteInfo& m)
{
	
}

void from_json(const json& j, SpriteInfo& m)
{
	std::vector<float> pos = j.at("position");
	m.position.x = pos[0];
	m.position.y = pos[1];
	std::vector<float> scale = j.at("scale");
	m.scale.x = scale[0];
	m.scale.y = scale[1];
	m.origin = (Origins)(j.at("origin").get<int>());

}

void to_json(json& j, const TextInfo& m)
{
}

void from_json(const json& j, TextInfo& m)
{
	std::vector<float> pos = j.at("position");
	m.position.x = pos[0];
	m.position.y = pos[1];
	std::vector<float> scale = j.at("scale");
	m.scale.x = scale[0];
	m.scale.y = scale[1];
	m.origin = (Origins)(j.at("origin").get<int>());
	m.chracterSize = j.at("characterSize").get<int>();
	m.font = j.at("font").get<std::string>();
}

