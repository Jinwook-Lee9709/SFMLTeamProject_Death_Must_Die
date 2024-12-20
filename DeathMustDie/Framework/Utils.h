#pragma once
#include "HitBox.h"

class Utils
{
private:
	static std::mt19937 generator;
	static const float PI;

public:
	static void Init();

	//String
	static std::wstring ReplaceEscapeSequences(const std::wstring& input);
	//
	static int RandomRange(int min, int max);
	static float RandomRange(float min, float max);
	static float RandomValue();	// 0.0f ~ 1.0f
	static int RandomByWeight(const std::vector<float>& weights);
	static bool RollTheDice(float probability);
	static sf::Vector2f RandomOnUnitCircle();
	static sf::Vector2f RandomInUnitCircle();
	static sf::Color RandomColor(bool opaque = true);
	static sf::Vector2f RandomPointInRect(const sf::FloatRect& rect);

	// Origin
	static sf::Vector2f SetOrigin(sf::Transformable& obj, Origins preset, const sf::FloatRect bound);
	static sf::Vector2f SetOrigin(sf::Shape& obj, Origins preset);
	static sf::Vector2f SetOrigin(sf::Text& obj, Origins preset);
	static sf::Vector2f SetOrigin(sf::Sprite& obj, Origins preset);

	// Math
	static float Clamp(float value, float min, float max);
	static float Clamp01(float value);
	static int Truncate(float value);

	static float Lerp(float min, float max, float t, bool clamp = true);
	static sf::Vector2f Lerp(const sf::Vector2f& min, const sf::Vector2f& max, float t, bool clamp = true);
	static sf::Color Lerp(const sf::Color& min, const sf::Color& max, float t, bool clamp = true);

	static float SqrMagnitude(const sf::Vector2f& vec);
	static float Magnitude(const sf::Vector2f& vec);

	static void Normalize(sf::Vector2f& vec);
	static sf::Vector2f GetNormal(const sf::Vector2f& vec);
	static float Distance(const sf::Vector2f& p1, const sf::Vector2f& p2);

	static float RadianToDegree(float radian);
	static float DegreeToRadian(float degree);

	static float NormalizeAngle(float angle);

	static float AngleRadian(const sf::Vector2f& vec);
	static float Angle(const sf::Vector2f& vec);
	static sf::Vector2f AngleToVector(float rotation);
	static sf::Vector2f GetRotateVector(float angle, const sf::Vector2f& target);
	static float Dot(const sf::Vector2f& a, const sf::Vector2f& b);
	static bool PointInTransformBounds(const sf::Transformable& transformable,
		const sf::FloatRect& localBounds, const sf::Vector2f point);

	static bool CheckCollision(const sf::Sprite& shapeA, const sf::Sprite& shapeB);
	static bool CheckCollision(const sf::RectangleShape& shapeA, const sf::RectangleShape& shapeB);
	static bool CheckCollision(const sf::Vector2f& wedgeCenter, float degree, float degreeRange, float radius, const sf::FloatRect& rect);
	static bool CheckCollision(const sf::Vector2f& elipseCenter, const sf::Vector2f& ellipseRadius, const sf::FloatRect& rect);
	static bool CheckCollision(const HitBox& shapeA, const HitBox& shapeB);
	static std::vector<sf::Vector2f> GetShapePoints(const sf::Sprite& shape);
	static std::vector<sf::Vector2f> GetShapePoints(const sf::RectangleShape& shape);
	static std::vector<sf::Vector2f> GetRectanglePointsFromBounds(const sf::FloatRect& localBounds);
	static bool PolygonsIntersect(const std::vector<sf::Vector2f>& polygonA, const sf::Transform& transformA, const std::vector<sf::Vector2f>& polygonB, const sf::Transform& transformB);



};