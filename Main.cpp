// タイトルシーン
#include<Siv3D.hpp>
#include"Title.h"
#include"Game.h"
// ゲームシーン

void Main()
{
	const String titleText = U"フライング";
	TextureAsset::Register(U"texture0", U"Images/frogstop.png");
	TextureAsset::Register(U"texture1", U"Images/frogjump.png");
	TextureAsset::Register(U"texture2", U"Images/frogdrop.png");
	TextureAsset::Register(U"texture3", U"Images/frog.png");
	TextureAsset::Register(U"back", U"Images/grass.png");
	TextureAsset::Register(U"toge", U"Images/_enemy.png");
	TextureAsset::Register(U"crow", U"Images/_crow.png");
	TextureAsset::Register(U"back2", U"Images/backgrounds.png");
	TextureAsset::Register(U"grass", U"Images/grassfront.png");
	TextureAsset::Register(U"item", U"Images/item.png");
	TextureAsset::Register(U"tree", U"Images/tree.png");
	TextureAsset::Register(U"tree2", U"Images/tree2.png");

	AudioAsset::Register(U"jump", U"Sound/jump.mp3");
	AudioAsset::Register(U"damage", U"Sound/damage.mp3");
	AudioAsset::Register(U"hijump", U"Sound/hijump.mp3");

	// 使用するフォントアセットを登録
	FontAsset::Register(U"Title", 120, Typeface::Regular);
	FontAsset::Register(U"Restart", 70, Typeface::Regular);
	FontAsset::Register(U"Menu", 30, Typeface::Regular);
	FontAsset::Register(U"Score", 36, Typeface::Bold);

	// 背景色を設定
	Scene::SetBackground(ColorF(0.2, 0.5, 0.8));

	// シーンと遷移時の色を設定
	MyApp manager;
	manager
		.add<Title>(State::Title)
		.add<Game>(State::Game)
		.add<GameOver>(State::GameOver)
		.setFadeColor(ColorF(1.0));

	while (System::Update())
	{

		if (!manager.update())
		{
			break;
		}
	}
};