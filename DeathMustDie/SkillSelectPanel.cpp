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
	canvas.setOrigin(origin);
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
		text.SetFillColor(sf::Color::White);
		text.Reset();
		texts.insert({ name, text });
		it++;
	}
	valueCharacterSize = j["ValueTextSize"];
	fontId = j["ValueTextFont"];


	sf::FloatRect panelRect = sprites["panel"]->getLocalBounds();
	std::vector<float > texSize = j["RenderTextureSize"].get<std::vector<float>>();
	texBuf->create(texSize[0], texSize[1]);

	animator.SetTarget(sprites["panel"]);
}

void SkillSelectPanel::UpdateDisplay(const json& skillInfo, UpgradeType type)
{
	AbilityGrade grade = skillInfo["grade"].get<AbilityGrade>();
	texts["skillName"].SetString(skillInfo["name"].get<std::string>());
	texts["skillType"].SetString(SkillTypeToString(skillInfo["skillType"].get<AbilityType>()));
	texts["skillType"].SetFillColor(sf::Color(120, 120, 120));
	texts["instruct"].SetString(STR(skillInfo["grade"].get<std::string>()));
	switch (type)
	{
		case UpgradeType::Earn:
		{
			texts["level"].SetString("LV.1");
			texts["rarityText"].SetString(GradeToString(grade));
			break;
		}
		case UpgradeType::LevelUp:
		{
			int level = skillInfo["level"].get<int>();
			std::string str = "LV." + std::to_string(level) + " -> " + "LV." + std::to_string(level + 1);
			texts["level"].SetString(str);
			texts["rarityText"].SetString(GradeToString(grade));
			break;
		}
		case UpgradeType::GradeUp:
		{
			int level = skillInfo["level"].get<int>();
			std::string str = "LV." + std::to_string(level) + " -> " + "LV." + std::to_string(level + 1);
			texts["level"].SetString(str);
			AbilityGrade nextGrade = ++grade;
			str = GradeToString(grade) + " -> " + GradeToString(nextGrade);
			texts["rarityText"].SetString(GradeToString(grade));
			break;
		}
			
	}

	switch (grade)
	{
		case AbilityGrade::Novice:
		{
			sprites["rarityFrame"]->setColor(sf::Color::White);
			texts["skillName"].SetFillColor(sf::Color::White);
			break;
		}
		case AbilityGrade::Adept:
		{
			texts["skillName"].SetFillColor(sf::Color(94, 107, 184));
			sprites["rarityFrame"]->setColor(sf::Color(94, 107, 184));
			break;
		}
		case AbilityGrade::Expert:
		{
			texts["skillName"].SetFillColor(sf::Color(117, 31, 153));
			sprites["rarityFrame"]->setColor(sf::Color(117, 31, 153));
			break;
		}
		case AbilityGrade::Master:
		{
			texts["skillName"].SetFillColor(sf::Color(191, 0, 57));
			sprites["rarityFrame"]->setColor(sf::Color(191, 0, 57));
			break;
		}
		case AbilityGrade::Legend:
		{
			texts["skillName"].SetFillColor(sf::Color(239, 78, 93));
			sprites["rarityFrame"]->setColor(sf::Color(239, 78, 93));
			break;
		}
	}
	CreateValueText(skillInfo["valueCount"].get<int>());
	SetValueText(skillInfo["valueText"]);
}

void SkillSelectPanel::CreateValueText(int count)
{
	valueTexts.clear();
	for (int i = 0; i < count; i++)
	{
		TextGo valueName, value;
		valueName.SetCharacterSize(valueCharacterSize);
		value.SetCharacterSize(valueCharacterSize);
		valueName.SetFont(GET_FONT(fontId));
		value.SetFont(GET_FONT(fontId));
	}
}

void SkillSelectPanel::SetValueText(const json& valueText)
{
	for (auto& pair : valueText)
	{
		std::string valueName = pair["valueName"].get<std::string>();
		std::string value = pair["value"].get<std::string>();

	}
}

const std::string& SkillSelectPanel::SkillTypeToString(const AbilityType& type)
{
	std::string str;
	switch (type)
	{
	case AbilityType::Attack:
		{
			str = "Attack";
			break;
		}
		case AbilityType::Cast:
		{
			str = "Cast";
			break;
		}
		case AbilityType::Dash:
		{
			str = "Dash";
			break;
		}
		case AbilityType::Passive:
		{
			str = "Passive";
			break;
		}
		case AbilityType::Power:
		{
			str = "Power";
			break;
		}
		case AbilityType::Strike:
		{
			str = "Strike";
			break;
		}
		case AbilityType::Summon:
		{
			str = "Summon";
			break;
		}
	}
	return str;
}

const std::string& SkillSelectPanel::GradeToString(const AbilityGrade& grade)
{
	std::string str;
	switch (grade)
	{
		case AbilityGrade::Novice:
		{
			str = "Novice";
			break;
		}
		case AbilityGrade::Adept:
		{
			str = "Adept";
			break;
		}
		case AbilityGrade::Expert:
		{
			str = "Expert";
			break;
		}
		case AbilityGrade::Master:
		{
			str = "Master";
			break;
		}
		case AbilityGrade::Legend:
		{
			str = "Legend";
			break;
		}
	}
	return str;
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

