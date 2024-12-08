#include "stdafx.h"
#include "Framework.h"
#include "SpriteGo.h"

void Framework::Init(int width, int height, const std::string& name)
{
    FONT_MGR.Load("fonts/Sansation.ttf");

	window.create(sf::VideoMode(width, height), name);
    RES_TABLE_MGR.Init();
    DATATABLE_MGR.Init();
    Utils::Init();
    SCENE_MGR.Init();
    InputMgr::Init();
    SOUND_MGR.Init();

   /* SOUND_MGR.Init();*/
}

void Framework::Do()
{
    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        realDeltaTime = deltaTime = dt.asSeconds();
        deltaTime *= timeScale;
        realTime += realDeltaTime;
        time += deltaTime;

        InputMgr::Clear();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            InputMgr::UpdateEvent(event);
        }
        InputMgr::Update(deltaTime);
        SOUND_MGR.Update(deltaTime);
        SCENE_MGR.Update(deltaTime);
        SCENE_MGR.LateUpdate(deltaTime);
        SCENE_MGR.FixedUpdate(deltaTime);

        if (InputMgr::GetKeyDown(sf::Keyboard::H))
        {
            Variables::isDrawHitBox = !Variables::isDrawHitBox;
        }


        window.clear();
        SCENE_MGR.Draw(window);
        window.display();
    }
}

void Framework::Release()
{
    SCENE_MGR.Release();
    FONT_MGR.Unload("fonts/DS-DIGI.ttf");
    DATATABLE_MGR.Release();
    SOUND_MGR.Release();
}
