/// Player.h
// プレイヤー
// author syuki nishida
// 2014/09/24
#ifndef _PLAYER_H_
#define _PLAYER_H_

/// Includes
#include <snStudy.h>

/// Class
class Player : public snStudy::UpdateElement{

	// モデル番号

	/// コンストラクタ
	Player();

	/// デストラクタ
	virtual ~Player();

	/// 更新
	virtual void Update();

public:
	/// クリエイタ
	static Player* Create(){
		return new Player();
	}

	///  リリース
	void Release(){
		delete this;
	}
};

#endif
//=EOF=