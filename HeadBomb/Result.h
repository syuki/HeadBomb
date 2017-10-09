/// Result.h
// リザルト
// author syuki nishida
// 2014/09/24
#ifndef _RESULT_H_
#define _RESULT_H_

/// Includes
#include <snStudy.h>
#include <vector>

#define RESULT_NUM	(3)

/// Class
class ResultScene : public snStudy::SceneManager, snStudy::UpdateElement{

	// ポリゴンマネージャ？
	snStudy::SimplePrimitivePolygon2D* _polygonManager;

	// ポリゴンリスト
	std::vector<unsigned long> _polygonList;

	/// コンストラクタ
	ResultScene();

	/// デストラクタ
	virtual ~ResultScene();

	/// 遷移時の呼ばれる初期化開始
	virtual void InitStartCallback();

	/// 遷移時に呼ばれる終了
	virtual void UninitCallback();

	/// 更新
	virtual void Update();

public:
	/// クリエイタ
	static ResultScene* Create(){
		return new ResultScene();
	}

	///  リリース
	void Release(){
		delete this;
	}
};

#endif
//=EOF=