#include"Player.hpp"

using namespace::std;

Item::Item(Point _pos, int32 _r) :
	pos(_pos),
	r(_r)
{

}

Point LoadSize(const FilePath& tomlPath)
{
	const TOMLReader toml(tomlPath);

	Point size = { 0,0 };
	if (!toml)
	{
		return size;
	}

	size = Point(toml[U"Point.size.x"].get<int32>(), toml[U"Point.size.y"].get<int32>());

	return size;
}

Array<Point> Loaderror(const FilePath& tomlPath)
{
	const TOMLReader toml(tomlPath);

	Array<Point> errors;

	if (!toml)
	{
		return errors;
	}

	for (const auto& object : toml[U"errors"].tableArrayView())
	{
		Point error;
		error = Point(object[U"size.x"].get<int32>(), object[U"size.y"].get<int32>());
		errors << error;
	}

	return errors;
}
Circle Item::getBody() const
{
	return Circle(pos, r);
}

void Item::draw() const
{
	auto tex = TextureAsset(U"item");
	tex.drawAt(pos.x, pos.y);
}
Player::Player(Point _pos, Point _size, Point _speed, Array<Point> _errors, int32 actionsize) :
	pos(_pos),
	size(_size),
	speed(_speed),
	errors(_errors),
	action(actionsize)
{

}

void Player::checkGround(int groundPos)
{
	m_isGround = false;
	if (pos.y >= groundPos)
	{
		m_isGround = true;
	}
}
Quad Player::getBody() const
{
	if (action == 0 || action == 1)
	{
		Rect rect(pos.x + errors[0].x, pos.y + errors[0].y, 50, 50);
		return rect.rotated(0_deg);
	}
	else if (action == 2 || action == 3)
	{
		Rect rect(pos.x - size.x / 2 + errors[1].x, pos.y - size.y + errors[1].y, size.x, size.y);
		Quad quad;
		if (action == 2)
		{
			quad = rect.rotated(45_deg);
		}
		else if (action == 3)
		{
			quad = rect.rotated(-45_deg);
		}
		return quad;
	}

	else if (action == 4 || action == 5)
	{
		Rect rect(pos.x - size.x / 2 + errors[2].x, pos.y - size.y + errors[2].y, size.x, size.y);
		Quad quad = rect.rotated(90_deg);
		return quad;
	}

	else if (action == 6)
	{
		Rect rect(pos.x - size.x / 2 + errors[3].x, pos.y - size.y + errors[3].y, size.x, size.y);
		Quad quad = rect.rotated(90_deg);
		return quad;
	}
}

Vec2 Player::getRandom()
{
	return { Random(-1.0, 1.0) ,Random(-0.707,1.0) };
}

void Player::update()
{
	if (action != 6)
	{
		if (const auto joy = JoyConR(0))
		{
			if (joy.buttonLR.down())
			{
				AudioAsset(U"jump").play();
				m_RjumpFrame = 25;
				m_LjumpFrame = 0;
				saveDirection = false;
			}
		}
		if (const auto joy = JoyConL(0))
		{
			if (joy.buttonLR.down())
			{
				AudioAsset(U"jump").play();
				m_LjumpFrame = 25;
				m_RjumpFrame = 0;
				saveDirection = true;
			}
		}

		if (MouseR.down())
		{
			AudioAsset(U"jump").play();
			m_RjumpFrame = 25;
			m_LjumpFrame = 0;
			saveDirection = false;
		}

		if (MouseL.down())
		{
			AudioAsset(U"jump").play();
			m_LjumpFrame = 25;
			m_RjumpFrame = 0;
			saveDirection = true;
		}
	}
	if (m_isGround)
	{
		if (saveDirection)
		{
			action = 0;
		}
		else
		{
			action = 1;
		}
	}

	else if (!m_isGround && m_RjumpFrame == 0 && m_LjumpFrame == 0)
	{
		if (saveDirection)
		{
			action = 4;
		}
		else
		{
			action = 5;
		}

	}
	if (m_RjumpFrame > 0)
	{
		action = 3;
		if (m_isGround == false)
		{
			pos.x += speed.x;
		}
		pos.y -= speed.y;
		m_RjumpFrame--;

	}

	else if (m_LjumpFrame > 0)
	{
		action = 2;
		if (m_isGround == false)
		{
			pos.x -= speed.x;
		}
		pos.y -= speed.y;
		m_LjumpFrame--;
	}

	if (pos.x >= Scene::Width() - 50 && m_RjumpFrame != 0)
	{
		m_LjumpFrame = m_RjumpFrame;
		m_RjumpFrame = 0;
		saveDirection = true;
	}

	else if (pos.x <= 40 && m_LjumpFrame != 0)
	{
		m_RjumpFrame = m_LjumpFrame;
		m_LjumpFrame = 0;
		saveDirection = false;
	}

	if (!m_isGround)
	{
		pos.y += 9;
	}
	if (timer.isRunning() && timer.ms() <= 1000)
	{
		action = 6;
		pos.y -= (speed.y + 10);
	}

}

void Player::draw() const
{
	//getBody().draw();
	if (action == 6)
	{
		auto tex = TextureAsset(U"texture3");
		tex.drawAt(pos.x, pos.y - tex.size().y / 2);
	}
	else if (action % 2 == 0)
	{
		const String name = U"texture{}"_fmt(action / 2);
		auto tex = TextureAsset(name);
		tex.drawAt(pos.x, pos.y - tex.size().y / 2);
	}
	else if (action % 2 == 1)
	{
		const String name = U"texture{}"_fmt(action / 2);
		auto tex = TextureAsset(name);
		tex.mirrored().drawAt(pos.x, pos.y - tex.size().y / 2);
	}

}