#include "stdafx.h"
#include "StatusUi.h"
#include "Player.h"
#include "SceneGame.h"
#include "Structure.h"

StatusUi::StatusUi(const std::string& name)
	: GameObject(name)
{
}

void StatusUi::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void StatusUi::SetRotation(float angle)
{
	rotation = angle;
}

void StatusUi::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void StatusUi::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void StatusUi::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void StatusUi::Init()
{
	RES_TABLE_MGR.LoadScene("UI");
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;
}

void StatusUi::Release()
{
}

void StatusUi::Reset()
{
	scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	
	SetBoons();
	SetInventory();
	SetExpFrame();
	SetPortrait();
	SetHpFrame();
	SetStaminaFrame();
	SetBtns();
}

void StatusUi::Update(float dt)
{
	cursorBoons(dt);
	cursorInventory(dt);
	UpdateDashCount(dynamic_cast<Player*>(scene->FindGo("Player"))->GetDashCharge());
	for (auto& btn : btns)
	{
		btn.Update(dt);
	}

	visibleTime += dt;
	if (visibleTime > 3.f)
	{
		for (int i = 0; i < 7; i++)
		{
			btns[i].SetButtonVisible(true);
		}
	}

	for (auto obj : scene->GetObjList())
	{
		if (obj->GetInteract())
		{
			btns[7].SetActive(true);
			break;
		}
		btns[7].SetActive(false);
	}
}

void StatusUi::Draw(sf::RenderWindow& window)
{
	expUnderFrame.Draw(window);
	exp.Draw(window);
	expFrame.Draw(window);
	
	boonsBtn.Draw(window);
	boonsBtnGlow.Draw(window);

	inventoryBtn.Draw(window);
	inventoryBtnGlow.Draw(window);

	portrait.Draw(window);
	portraitFrame.Draw(window);
	level.Draw(window);
	levelNum.Draw(window);

	hpTrace.Draw(window);
	hp.Draw(window);
	hpFrame.Draw(window);
	hpText.Draw(window);
	
	
	for (auto st : stamina)
	{
		st.Draw(window);
	}
	for (auto stFrame : staminaFrame)
	{
		stFrame.Draw(window);
	}
	for (auto btn : btns)
	{
		btn.Draw(window);
	}
	staminaEnd.Draw(window);
}

void StatusUi::SetBoons()
{
	stat = dynamic_cast<Player*>(scene->FindGo("Player"))->GetCurStat();
	boonsBtn = SpriteGo("boonsButton");
	boonsBtnGlow = SpriteGo("boonsButtonGlow");
	boonsBtn.Reset();
	boonsBtnGlow.Reset();

	boonsBtn.SetOrigin(Origins::BL);
	boonsBtn.SetPosition({ 0.f, winSize.y });
	boonsBtnGlow.SetOrigin(Origins::BL);
	boonsBtnGlow.SetPosition({ boonsBtn.GetPosition().x + 9.f, boonsBtn.GetPosition().y - 45.f});
	boonsBtnGlow.SetFillColor(sf::Color(255, 255, 255, 0));

	boonsBtnGlow.SetScale({ 3.f, 3.f });
	boonsBtn.SetScale({ 3.f, 3.f });
}

void StatusUi::SetInventory()
{
	stat = dynamic_cast<Player*>(scene->FindGo("Player"))->GetCurStat();
	inventoryBtn = SpriteGo("inventoryButton");
	inventoryBtnGlow = SpriteGo("inventoryButtonGlow");
	inventoryBtn.Reset();
	inventoryBtnGlow.Reset();

	inventoryBtn.SetOrigin(Origins::BR);
	inventoryBtn.SetPosition({ winSize.x, winSize.y });
	inventoryBtnGlow.SetOrigin(Origins::BR);
	inventoryBtnGlow.SetPosition({ inventoryBtn.GetPosition().x + 1.f , inventoryBtn.GetPosition().y - 60.f});
	inventoryBtnGlow.SetFillColor(sf::Color(255, 255, 255, 0));

	inventoryBtnGlow.SetScale({ 3.f, 3.f });
	inventoryBtn.SetScale({ 3.f, 3.f });
}

void StatusUi::SetExpFrame()
{
	stat = dynamic_cast<Player*>(scene->FindGo("Player"))->GetCurStat();
	expFrame = SpriteGo("expFrame");
	expUnderFrame = SpriteGo("expUnderFrame");
	exp = SpriteGo("exp");
	expFrame.Reset();
	expUnderFrame.Reset();
	exp.Reset();

	expFrame.SetOrigin(Origins::BC);
	expFrame.SetPosition({ winSize.x * 0.5f, winSize.y });

	expUnderFrame.SetOrigin(Origins::MC);
	expUnderFrame.SetPosition({ expFrame.GetPosition().x, expFrame.GetPosition().y - expFrame.GetLocalBounds().height * 0.5f});
	expUnderFrame.SetFillColor(sf::Color(180, 180, 180, 255));
	
	exp.SetTextureRect({ 0,0,0,3 });

	expFrame.SetScale({ 3.f, 3.f });
	expUnderFrame.SetScale({ 3.f, 3.f });
	exp.SetScale({ 3.f, 3.f });

	exp.SetPosition({ expUnderFrame.GetGlobalBounds().left, expUnderFrame.GetGlobalBounds().top });
}

void StatusUi::SetPortrait()
{
	stat = dynamic_cast<Player*>(scene->FindGo("Player"))->GetCurStat();
	portraitFrame = SpriteGo("portrait");
	portrait = SpriteGo("knight");
	level = SpriteGo("level");
	levelNum = TextGo("PtSerifRegular_Font");
	portraitFrame.Reset();
	portrait.Reset();
	level.Reset();
	levelNum.Reset();

	portraitFrame.SetOrigin(Origins::BC);
	portraitFrame.SetPosition({ winSize.x * 0.5f, winSize.y});

	portrait.SetOrigin(Origins::MC);
	portrait.SetPosition({ portraitFrame.GetGlobalBounds().left + portraitFrame.GetGlobalBounds().width * 0.5f
		, portraitFrame.GetGlobalBounds().top - portraitFrame.GetGlobalBounds().height / 4 });

	level.SetOrigin(Origins::BC);
	level.SetPosition({ winSize.x * 0.5f, winSize.y });

	levelNum.SetString(L"1");
	levelNum.SetCharacterSize(200);
	levelNum.SetOrigin(Origins::MC);
	levelNum.SetPosition({ level.GetGlobalBounds().left + level.GetGlobalBounds().width * 0.5f - 2.f, level.GetGlobalBounds().top});

	portraitFrame.SetScale({ 3.f, 3.f });
	portrait.SetScale({ 3.f, 3.f });
	level.SetScale({ 3.f, 3.f });
	levelNum.SetScale({ 0.1f, 0.1f });
}

void StatusUi::SetHpFrame()
{
	stat = dynamic_cast<Player*>(scene->FindGo("Player"))->GetCurStat();
	hpFrame = SpriteGo("hpFrame");
	hpTrace = SpriteGo("hpTrace");
	hp = SpriteGo("hp");
	hpText = TextGo("PtSerifRegular_Font");

	hpFrame.Reset();
	hpTrace.Reset();
	hp.Reset();
	hpText.Reset();
	hpFrame.SetOrigin(Origins::BR);
	hpFrame.SetPosition({ winSize.x * 0.5f + hpFrame.GetGlobalBounds().width / 7, winSize.y});

	hpTrace.SetOrigin(Origins::BR);
	hpTrace.SetPosition({ hpFrame.GetPosition().x , hpFrame.GetPosition().y });

	hp.SetOrigin(Origins::BR);
	hp.SetPosition({ hpFrame.GetPosition().x, hpFrame.GetPosition().y});
	
	hpText.SetString(std::to_wstring(stat.defensive.life) + L" / " + std::to_wstring(stat.defensive.life));
	hpText.SetCharacterSize(200);
	hpText.SetOrigin(Origins::MC);
	hpText.SetPosition({ hpFrame.GetGlobalBounds().left - 40.f, hpFrame.GetGlobalBounds().top - 40.f});
	
	hpFrame.SetScale({ 3.f, 3.f });
	hpTrace.SetScale({ 3.f, 3.f });
	hp.SetScale({ 3.f, 3.f });
	hpText.SetScale({ 0.1f, 0.1f });
	

}

void StatusUi::SetStaminaFrame()
{
	stat = dynamic_cast<Player*>(scene->FindGo("Player"))->GetCurStat();
	Scene* scene = SCENE_MGR.GetCurrentScene();
	Player* player = dynamic_cast<Player*>(scene->FindGo("Player"));
	staminaFrame.clear();
	stamina.clear();
	for (int i = 0; i < stat.dash.dashCharge; i++)
	{
		staminaFrame.push_back(SpriteGo("staminaFrame"));
		stamina.push_back(SpriteGo("stamina"));
		staminaFrame[i].Reset();
		stamina[i].Reset();

		staminaFrame[i].SetOrigin(Origins::BL);
		staminaFrame[i].SetPosition({ portrait.GetPosition().x + portrait.GetGlobalBounds().width * 0.5f +  i * (staminaFrame[i].GetGlobalBounds().width * 2 + 5.f) + 10.f ,
			portrait.GetPosition().y + portrait.GetGlobalBounds().height * 0.5f + 5.f });

		stamina[i].SetOrigin(Origins::BL);
		stamina[i].SetPosition({ staminaFrame[i].GetPosition().x + 10.f, staminaFrame[i].GetPosition().y - 9.f});

		staminaFrame[i].SetScale({ 3.f, 3.f });
		stamina[i].SetScale({ 3.f, 3.f });
	}
	staminaEnd = SpriteGo("staminaFrameEnd");
	staminaEnd.Reset();

	staminaEnd.SetOrigin(Origins::BL);
	staminaEnd.SetPosition({ staminaFrame[stat.dash.dashCharge - 1].GetPosition().x +
		staminaFrame[stat.dash.dashCharge - 1].GetGlobalBounds().width - 15.f,
		portrait.GetPosition().y + portrait.GetGlobalBounds().height * 0.5f + 5.f });

	staminaEnd.SetScale({3.f, 3.f});
}

void StatusUi::SetBtns()
{
	for (int i = 0; i < 8; i++)
	{
		btns.push_back(ButtonUi());
		btns[i].Reset();
	}
	btns[0].SetButton("MOUSEL");
	btns[0].SetPosition({ winSize.x * 0.5f, winSize.y * 0.5f + 300.f - 3 * 60.f });
	btns[0].SetButtonName(L"Attack");

	btns[1].SetButton("SPACE");
	btns[1].SetPosition({ winSize.x * 0.5f, winSize.y * 0.5f + 300.f - 2 * 60.f });
	btns[1].SetButtonName(L"Dash");

	btns[2].SetButton("D");
	btns[2].SetPosition({ winSize.x * 0.5f, winSize.y * 0.5f + 300.f - 1 * 60.f });
	btns[2].SetButtonName(L"Move");
	btns[3].SetButton("A");
	btns[3].SetPosition({ winSize.x * 0.5f - 1 * 60.f, winSize.y * 0.5f + 300.f - 1 * 60.f });
	btns[4].SetButton("S");
	btns[4].SetPosition({ winSize.x * 0.5f - 2 * 60.f, winSize.y * 0.5f + 300.f - 1 * 60.f });
	btns[5].SetButton("W");
	btns[5].SetPosition({ winSize.x * 0.5f - 3 * 60.f, winSize.y * 0.5f + 300.f - 1 * 60.f });

	btns[6].SetButton("MOUSE");
	btns[6].SetPosition({ winSize.x * 0.5f, winSize.y * 0.5f + 300.f - 0 * 60.f });
	btns[6].SetButtonName(L"Aim");

	btns[7].SetButton("E");
	btns[7].SetPosition({ winSize.x * 0.5f, winSize.y * 0.5f + 300.f + 80.f });
	btns[7].SetButtonName(L"Instruct");
	btns[7].SetActive(false);

}

void StatusUi::cursorBoons(float dt)
{
	Scene* scene = SCENE_MGR.GetCurrentScene();
	sf::Vector2i mPos = InputMgr::GetMousePosition();
	sf::Vector2f cursor = scene->ScreenToUi(mPos);

	if (boonsBtnGlow.GetGlobalBounds().contains(cursor))
	{
		
		boonTrans += dt * 255 * 3;
		boonsBtnGlow.SetFillColor(sf::Color(255, 255, 255, Utils::Clamp(boonTrans, 0, 255)));
	}
	else
	{
		boonsBtnGlow.SetFillColor(sf::Color(255, 255, 255, 0));
		boonTrans = 0;
	}
}

void StatusUi::cursorInventory(float dt)
{
	
	sf::Vector2i mPos = InputMgr::GetMousePosition();
	sf::Vector2f cursor = scene->ScreenToUi(mPos);

	if (inventoryBtnGlow.GetGlobalBounds().contains(cursor))
	{
		inventoryTrans += dt * 255 * 3;
		inventoryBtnGlow.SetFillColor(sf::Color(255, 255, 255, Utils::Clamp(inventoryTrans, 0, 255)));
	}
	else
	{
		inventoryBtnGlow.SetFillColor(sf::Color(255, 255, 255, 0));
		inventoryTrans = 0;
	}
}

void StatusUi::UpdateDashCount(int dashCharge)
{
	stat = dynamic_cast<Player*>(scene->FindGo("Player"))->GetCurStat();
	int count = stat.dash.dashCharge;
	for (int i = 0; i < count; i++)
	{
		stamina[i].SetActive(false);
	}
	for (int i = 0; i < dashCharge; i++)
	{
		stamina[i].SetActive(true);
	}
}

void StatusUi::UpdateHp(float changeHp, float damage)
{
	stat = dynamic_cast<Player*>(scene->FindGo("Player"))->GetCurStat();
	hp.SetTextureRect({ (52 + 88 * (int)(stat.defensive.life - changeHp) / stat.defensive.life) , 0,
		(112 - 88 * (int)(stat.defensive.life - changeHp) / stat.defensive.life), 60 });
	hp.SetOrigin(Origins::BR);
	hpText.SetString(std::to_wstring((int)changeHp) + L" / " + std::to_wstring(stat.defensive.life));
}

void StatusUi::UpdateTrace()
{
	hpTrace.SetTextureRect(hp.GetTextureRect());
	hpTrace.SetOrigin(Origins::BR);
}

void StatusUi::UpdateExp(float exp, int level)
{
	int max = EXP_TABLE->Get(level + 1).curExp;
	this->exp.SetTextureRect({0,0,(int)(640 * exp / max),3});
	levelNum.SetString(std::to_wstring(level));
}

void StatusUi::isInteract(bool interact)
{
	btns[7].SetActive(interact);
}
