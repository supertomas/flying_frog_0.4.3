#pragma once
#include<Siv3D.hpp>

Point LoadSize(const FilePath& tomlPath);
Array<Point> Loaderror(const FilePath& tomlPath);
class Item
{
public:
	int32 r;
	Point pos;

	Item(Point _pos, int32 _r);

	Circle getBody() const;

	void draw() const;

private:
	Stopwatch timer;
	String texture;
};

class Player
{
public:
	Player(Point _pos, Point _size, Point _speed, Array<Point> errors, int32 texturesize);
	int32 action = 0;
	bool saveDirection = true;
	Point pos, speed, size;
	Array<Point> errors;
	std::array<String, 3> texture;
	bool m_isGround;
	bool a;
	int32 m_RjumpFrame = 0;
	int32 m_LjumpFrame = 0;
	Stopwatch timer;

	void checkGround(int groundPos);

	Vec2 getRandom();

	void update();

	Quad getBody() const;

	void draw() const;
private:

};
