#include"enemy.hpp"

Enemy::Enemy(Vec2 _pos, Point _size, String _texture, EnemyMoveType _type)
{
	pos = _pos;
	type = _type;
	size = _size;
	texture = _texture;
	timer.restart();
}

void Enemy::update()
{
	switch (type)
	{
	case EnemyMoveType::Stop:
		if (!attack)
		{
			break;
		}
	case EnemyMoveType::Shindo:
		if (!attack)
		{
			distance++;
			if (distance < 50)
			{
				pos.x += 8;
				direction = true;
			}
			else if (distance >= 50 && distance < 100)
			{
				pos.x -= 8;
				direction = false;
			}
			else
			{
				distance = 0;
			}
			break;
		}
	default:
		break;
	}
}

Quad Enemy::CrowgetBody()
{
	Rect rect(pos.x - size.x / 2, pos.y - size.y - 10, size.x + 10, size.y + 10);
	return rect.rotated(0_deg);
}

Circle Enemy::TogegetBody()
{
	return Circle(pos, size.x);
}

Vec2 Enemy::GenerateEnemy()
{
	return RandomVec2({ 50, 750 }, -20);
}

void Enemy::draw() const
{
	//CrowgetBody().draw();
	auto tex = TextureAsset(texture);
	switch (type)
	{
	case EnemyMoveType::Stop:
		if (!attack)
		{
			tex.drawAt(pos.x, pos.y);
		}
		else
		{
			tex.rotated(Scene::Time() * 600_deg).drawAt(pos.x, pos.y);
		}
		break;
	case EnemyMoveType::Shindo:
		if (!attack)
		{
			if (direction == false)
			{
				tex.drawAt(pos.x, pos.y);
			}
			else
			{
				tex.mirrored().drawAt(pos.x, pos.y);
			}
		}
		else
		{
			tex.rotated(Scene::Time() * 600_deg).drawAt(pos.x, pos.y);
		}
	default:
		break;
	}
}
