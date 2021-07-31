#pragma once
#include"Player.hpp"
#include<Siv3D.hpp>
enum class EnemyMoveType
{
	Shindo,
	Stop
};

class Enemy
{
public:

	Enemy(Vec2 _pos, Point _size, String _texture, EnemyMoveType _type);
	Vec2 pos;
	Point size;
	Stopwatch timer;
	String texture;
	bool attack = false;
	Vec2 Flight_direction = { 0.0,0.0 };
	EnemyMoveType type;
	int32 distance = 0;
	bool direction = false;
	Vec2 GenerateEnemy();
	void update();
	Quad CrowgetBody();
	Circle TogegetBody();
	void draw() const;
private:

};
