#include "stdafx.h"
#include "TileMap2.h"

TileMap2::TileMap2(const std::string& name)
	: GameObject(name)
{
}

void TileMap2::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	UpdateTransform();
}

void TileMap2::SetRotation(float angle)
{
	rotation = angle;
	UpdateTransform();
}

void TileMap2::SetScale(const sf::Vector2f& s)
{
	scale = s;
	UpdateTransform();
}

void TileMap2::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		sf::FloatRect rect = GetLocalBounds();
		origin.x = rect.width * ((int)preset % 3) * 0.5f - rect.width * 0.5f;
		origin.y = rect.height * ((int)preset / 3) * 0.5f;
	}
	UpdateTransform();
}

void TileMap2::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	UpdateTransform();
}

sf::FloatRect TileMap2::GetLocalBounds() const
{
	return { 0.f, 0.f, cellCount.x * cellSize.x, cellCount.y * cellSize.y };
}

sf::FloatRect TileMap2::GetGlobalBounds() const
{
	sf::FloatRect bounds = GetLocalBounds();
	return transform.transformRect(bounds);
}

sf::FloatRect TileMap2::GetMoveableBounds() const
{
	sf::FloatRect bounds = GetGlobalBounds();
	bounds.width -= 2 * cellSize.x;
	bounds.height -= 2 * cellSize.y;
	bounds.left += cellSize.x;
	bounds.top += cellSize.y;

	return bounds;
}

void TileMap2::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = -1;

	//Set({ 50, 50 }, { 50.f, 50.f });
}

void TileMap2::Release()
{
}

void TileMap2::Reset()
{
	texture = &TEXTURE_MGR.Get(spriteSheetId);
	sf::Vector2u tSize = texture->getSize();


	Set({ 2, 2 }, { (float)tSize.x / 2, (float)tSize.y / 2 });
	SetOrigin(Origins::MC);
	SetScale({ 0.1f, 0.1f });
	SetPosition({0.f, 0.f});
	temp.setTexture(TEXTURE_MGR.Get("graphics/test.png"));
	Utils::SetOrigin(temp, Origins::TC);
	SetPoint(temp, { 0,0 });
}

void TileMap2::Update(float dt)
{

}

void TileMap2::Draw(sf::RenderWindow& window)
{
	sf::RenderStates state;
	state.texture = texture;
	state.transform = transform;
	window.draw(va, state);
}

void TileMap2::Set(const sf::Vector2i& count, const sf::Vector2f& size)
{
	//screen.x = (map.x - map.y) * TILE_WIDTH_HALF;
	//screen.y = (map.x + map.y) * TILE_HEIGHT_HALF;
	cellCount = count;
	cellSize = size;

	va.clear();
	va.setPrimitiveType(sf::Quads);
	va.resize(count.x * count.y * 4);

	sf::Vector2f posOffset[4] =
	{
		{ 0.f, 0.f },
		{ size.x * 0.5f, size.y * 0.5f },
		{ 0.f, size.y },
		{ -size.x * 0.5f, size.y * 0.5f },
	};

	sf::Vector2f texCoords[4] =
	{
		{ 0, 0 },
		{ size.x, 0 },
		{ size.x, size.y },
		{ 0, size.y },
	};

	for (int i = 0; i < count.y; ++i)
	{
		for (int j = 0; j < count.x; ++j)
		{
			sf::Vector2i texIndex = { i, j };

			int quadIndex = i * count.x + j;
			sf::Vector2f quadPos((i - j) * size.x * 0.5f, (i + j) * size.y * 0.5f);

			for (int k = 0; k < 4; ++k)
			{
				int vertexIndex = quadIndex * 4 + k;
				va[vertexIndex].position = quadPos + posOffset[k];
				va[vertexIndex].texCoords = texCoords[k];
				va[vertexIndex].texCoords.x += texIndex.x * size.x;
				va[vertexIndex].texCoords.y += texIndex.y * size.y;
			}
		}
	}
}

void TileMap2::SetPoint(sf::Transformable& obj, const sf::Vector2i& pos)
{
	sf::Vector2f objPos;
	objPos.x = GetGlobalBounds().left + (pos.x - pos.y) * cellSize.x * 0.5f;
	objPos.y = GetGlobalBounds().top + (pos.x + pos.y) * cellSize.y * 0.5f;
	obj.setPosition(objPos);
}

void TileMap2::UpdateTransform()
{
	transform = sf::Transform::Identity;
	transform.translate(position);
	transform.rotate(rotation);
	transform.scale(scale);
	transform.translate(-origin);
}
