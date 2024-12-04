#pragma once

#include <random>
#include <list>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <limits>
#include <codecvt>
#include <functional>
#include <cmath>
#include <fstream>



#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "json.hpp"
#include "rapidcsv.h"
using json = nlohmann::json;


#include "Defines.h"
#include "Utils.h"
#include "Timer.h"
#include "Singleton.h"
#include "Variables.h"
#include "DataTable.h"
#include "StringTable.h"
#include "SkillTable.h"
#include "ExpTable.h"
#include "DataTableMgr.h"
#include "ResourceTableManager.h"
#include "HitBox.h"
#include "Framework.h"
#include "EventHandler.h"
#include "InputMgr.h"
#include "Animator.h"
#include "ResourceMgr.h"
#include "GameObject.h"
#include "TextGo.h"
#include "SpriteGo.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "ObjectPool.h"
#include "SoundMgr.h"
#include "Effector.h"
