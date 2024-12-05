#include "stdafx.h"
#include "AbilitySelectPanel.h"

AbilitySelectPanel::AbilitySelectPanel(const std::string& name, int num)
	: GameObject(name), panelNum(num)
{
}

void AbilitySelectPanel::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	canvas.setPosition(position);
	if (sprites.find("selectEffect") != sprites.end())
	{
		sprites["selectEffect"]->setPosition(selectEffectPos + position);
	}
}

void AbilitySelectPanel::SetRotation(float angle)
{
	rotation = angle;
	canvas.setRotation(rotation);
}

void AbilitySelectPanel::SetScale(const sf::Vector2f& s)
{
	scale = s;
	canvas.setScale(scale);
}

void AbilitySelectPanel::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(canvas, originPreset);
	}
}

void AbilitySelectPanel::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	canvas.setOrigin(origin);
}

void AbilitySelectPanel::Init()
{
}

void AbilitySelectPanel::Release()
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

void AbilitySelectPanel::Reset()
{
	EVENT_HANDLER.AddEventInt("PanelClicked", std::bind(&AbilitySelectPanel::TurnOffPanel, this, std::placeholders::_1));
	texBuf = new sf::RenderTexture();
	SetComponent();
	sprites["rarityFrame"]->setTexture(GET_TEX("rarityFrame"));
	this->active = false;
}

void AbilitySelectPanel::Update(float dt)
{
	if (active)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::R))
		{
			Release();
			UI_SETTING_TABLE->Reload();
			Reset();
			SetPosition(position);
		}
		if (canvas.getGlobalBounds().contains(UI_MOUSE_POS) && !isHover)
		{
			hoverAnimator.Play("boon_hover");
			isHover = true;
		}
		else if (!canvas.getGlobalBounds().contains(UI_MOUSE_POS) && isHover)
		{
			hoverAnimator.Stop();
			sprites["hoverEffect"]->setTextureRect({ 0, 0, 0, 0, });
			isHover = false;
		}
		if (canvas.getGlobalBounds().contains(UI_MOUSE_POS) && InputMgr::GetMouseButtonDown(sf::Mouse::Left)
		&& opacity == 255 && !selected)
		{
			EVENT_HANDLER.InvokeEvent("PanelClicked", panelNum);
		}

		if (opacity < 254 && !selected)
		{
			opacity += 255 * FRAMEWORK.GetRealDeltaTime();
			if (opacity > 254)
			{
				opacity = 255;
			}
		}
		if (selected && opacity > 0)
		{
			opacity -= 400 * FRAMEWORK.GetRealDeltaTime();
			if (opacity < 0)
			{
				opacity = 0;
				active = false;
			}
		}
		animator.Update(FRAMEWORK.GetRealDeltaTime());
		hoverAnimator.Update(FRAMEWORK.GetRealDeltaTime());
	}
}

void AbilitySelectPanel::Draw(sf::RenderWindow& window)
{
	if (active)
	{
		texBuf->clear();
		texBuf->draw(*sprites["panel"]);
		for (auto& pair : sprites) { 
			if (pair.first != "panel" && pair.first != "selectEffect")
			{
				sf::Color color = pair.second->getColor();
				color.a = opacity;
				pair.second->setColor(color);
				texBuf->draw(*pair.second);
			}
		}
		for (auto& pair : texts) { 
			pair.second.SetOpacity(opacity);
			texBuf->draw(pair.second.GetText()); 
		}
		for (auto& pair : valueTexts) {
			pair.first.SetOpacity(opacity);
			pair.second.SetOpacity(opacity);
			texBuf->draw(pair.first.GetText());
			texBuf->draw(pair.second.GetText());
		}
		texBuf->display();
		canvas.setTexture(texBuf->getTexture(), true);
		window.draw(canvas);
		window.draw(*sprites["selectEffect"]);
	}

}

void AbilitySelectPanel::SetComponent()
{
	sprites.clear();
	texts.clear();

	setting = UI_SETTING_TABLE->Get("SkillSelectPanel");
	auto it = setting["Sprites"].begin();
	while (it != setting["Sprites"].end())
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
	selectEffectPos = sprites["selectEffect"]->getPosition();
	it = setting["Texts"].begin();
	while (it != setting["Texts"].end())
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
	valueCharacterSize = setting["ValueTextSize"];
	fontId = setting["ValueTextFont"];


	sf::FloatRect panelRect = sprites["panel"]->getLocalBounds();
	std::vector<float > texSize = setting["RenderTextureSize"].get<std::vector<float>>();
	texBuf->create(texSize[0], texSize[1]);

	animator.SetTarget(sprites["panel"]);
	hoverAnimator.SetTarget(sprites["hoverEffect"]);
}

void AbilitySelectPanel::UpdateDisplay(const json& skillInfo, UpgradeType type)
{
	AbilityGrade grade = skillInfo["grade"].get<AbilityGrade>();
	texts["skillName"].SetStringByString(skillInfo["name"].get<std::string>());
	texts["abilityType"].SetStringByString(AbilityTypeToString(skillInfo["abilityType"].get<AbilityType>()));
	texts["abilityType"].SetFillColor(sf::Color(120, 120, 120));
	std::wstring instruct = STR(skillInfo["name"].get<std::string>());
	texts["instruct"].SetString(Utils::ReplaceEscapeSequences(instruct));
	switch (type)
	{
		case UpgradeType::Earn:
		{
			texts["level"].SetStringByString("LV.1");
			texts["rarityText"].SetStringByString(GradeToString(grade));
			break;
		}
		case UpgradeType::LevelUp:
		{
			int level = skillInfo["level"].get<int>();
			std::string str = "LV." + std::to_string(level) + " -> " + "LV." + std::to_string(level + 1);
			texts["level"].SetStringByString(str);
			texts["rarityText"].SetStringByString(GradeToString(grade));
			break;
		}
		case UpgradeType::GradeUp:
		{
			int level = skillInfo["level"].get<int>();
			std::string str = "LV." + std::to_string(level) + " -> " + "LV." + std::to_string(level + 1);
			texts["level"].SetStringByString(str);
			AbilityGrade nextGrade = ++grade;
			str = GradeToString(grade) + " -> " + GradeToString(nextGrade);
			texts["rarityText"].SetStringByString(GradeToString(grade));
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
	for (auto& text : texts)
	{
		text.second.Reset();
	}
}

void AbilitySelectPanel::Display()
{
	animator.Play("boon_appear");
	hoverAnimator.SetTarget(sprites["hoverEffect"]);
	opacity = 0;
	selected = false;
	this->active = true;
}

void AbilitySelectPanel::CreateValueText(int count)
{
	valueTexts.clear();
	for (int i = 0; i < count; i++)
	{
		TextGo valueName, value;
		valueName.SetCharacterSize(valueCharacterSize);
		value.SetCharacterSize(valueCharacterSize);
		valueName.SetFont(GET_FONT(fontId));
		value.SetFont(GET_FONT(fontId));
		valueTexts.push_back({valueName, value});
	}
}

void AbilitySelectPanel::SetValueText(const json& valueText)
{
	sf::Vector2f firstPos = texts["instruct"].GetPosition() +
		sf::Vector2f(0.f, texts["instruct"].GetLocalBounds().height)
		+ sf::Vector2f(0.f, setting["InstructToValueMargin"].get<float>());
	sf::Vector2f margin = { 0, setting["ValueTextMargin"].get<float>() };
	auto it1 = valueTexts.begin();
	auto it2 = valueText.begin();
	while (it2 != valueText.end())
	{
		(*it1).first.SetStringByString((*it2)["valueName"].get<std::string>() + ": ");
		(*it1).first.SetPosition(firstPos + margin);
		(*it1).first.SetFillColor(sf::Color::White);
		sf::Vector2f xMargin ={(*it1).first.GetLocalBounds().width, 0};
		(*it1).second.SetStringByString((*it2)["value"].get<std::string>());
		(*it1).second.SetPosition(firstPos + margin + xMargin);
		(*it1).second.SetFillColor(sf::Color(54, 173, 50));
		margin += margin;
		it1++;
		it2++;
	}
}

void AbilitySelectPanel::TurnOffPanel(int num)
{
	this->selected = true;
	if (num == panelNum)
	{
		hoverAnimator.SetTarget(sprites["selectEffect"]);
		hoverAnimator.Play("boon_selected");
	}
	
}

std::string AbilitySelectPanel::AbilityTypeToString(const AbilityType& type)
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

std::string AbilitySelectPanel::GradeToString(const AbilityGrade& grade)
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

