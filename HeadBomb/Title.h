/// Title.h
// タイトル
// suthor syuki nishida
// 2014/09/24
#ifndef _TITLE_H_
#define _TITLE_H_

/// Includes
#include <snStudy.h>
#include <vector>

#define TITLE_NUM	(1)

/// Class
class TitleScene : public snStudy::SceneManager, snStudy::UpdateElement{

	// ポリゴンマネージャ？
	snStudy::SimplePrimitivePolygon2D* _polygonManager;

	// ポリゴンリスト
	std::vector<unsigned long> _polygonList;

	/// コンストラクタ
	TitleScene();

	/// デストラクタ
	virtual ~TitleScene();

	/// 遷移時の呼ばれる初期化開始
	virtual void InitStartCallback();

	/// 遷移時に呼ばれる終了
	virtual void UninitCallback();

	/// 更新
	virtual void Update();

public:
	/// クリエイタ
	static TitleScene* Create(){
		return new TitleScene();
	}

	///  リリース
	void Release(){
		delete this;
	}
};

#endif
//=EOF=