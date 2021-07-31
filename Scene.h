#pragma once
# include <Siv3D.hpp>

// シーンの名前
enum class State
{
	Title,
	Game,
	GameOver
};

// ゲームデータ
struct GameData
{
	//今回のスコア
	int32 now = 0;
	// ハイスコア
	int32 highScore = 0;
	int32 nowScore = 0;
	FilePath tomlPath = FileSystem::FullPath(U"example/config/config.toml");
	DirectoryWatcher watcher{ FileSystem::ParentPath(tomlPath) };
};

// シーン管理クラス
using MyApp = SceneManager<State, GameData>;

