/// Game.h
// ゲーム本体
// author syuki nishida
// 2014/09/24
#ifndef _GAME_H_
#define _GAME_H_

/// Includes
#include <snStudy.h>
#include <vector>

#define GAME_NUM	(2)

/// Class
class GameScene : public snStudy::SceneManager, snStudy::UpdateElement{

	// ポリゴンマネージャ？
	snStudy::SimplePrimitivePolygon2D* _polygonManager;

	// ポリゴンリスト
	std::vector<unsigned long> _polygonList;

	// XModelマネージャ？
	snStudy::XModel* _modelManager;

	// XModelリスト
	std::vector<unsigned long> _modelList;

	/// コンストラクタ
	GameScene();

	/// デストラクタ
	virtual ~GameScene();

	/// 遷移時の呼ばれる初期化開始
	virtual void InitStartCallback();

	/// 遷移時に呼ばれる終了
	virtual void UninitCallback();

	/// 更新
	virtual void Update();

public:
	/// クリエイタ
	static GameScene* Create(){
		return new GameScene();
	}

	///  リリース
	void Release(){
		delete this;
	}
};

#endif
//=EOF=