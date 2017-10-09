/// Game.cpp
// タイトル
// suthor syuki nishida
// 2014/09/24

/// Include
#include "Game.h"
#include "Input.h"
#include "CMotionModel.h"

/// コンストラクタ
// 引数　：none
// 戻り値：none
// 2014/09/24
GameScene::GameScene() : snStudy::SceneManager(GAME_NUM){
	_polygonManager = NULL;
	_modelManager = NULL;
//	CMotionModel* model = CMotionModel::Create("data/MODEL/akrModel.spm");

	// 更新フラグ設定
	SetUpdateFlag(false);
}

/// デストラクタ
// 引数　：none
// 戻り値：none
// 2014/09/24
GameScene::~GameScene(){
	// マネージャ終了
	if (_polygonManager){
		_polygonManager->Release();
		_polygonManager = NULL;
	}
	if (_modelManager){
		_modelManager->Release();
		_modelManager = NULL;
	}
}

/// 初期化
// 引数　：none
// 戻り値：none
// 2014/09/24
void GameScene::InitStartCallback(){
	// 描画マネージャ系初期化
	_polygonManager = snStudy::SimplePrimitivePolygon2D::Create(500, 500, snStudy::DrawElement::PERTH);
	_modelManager= snStudy::XModel::Create("data/MODEL/arm_l.x");

	// ポリゴン追加
	unsigned long buf = _polygonManager->AddDraw();
	
	_modelManager->AddDraw();

	// ポリゴンの設定用のポインタ取得
	snStudy::SimplePrimitivePolygon2D::OriginalValue originalVal = _polygonManager->CopyOriginalValue(buf);

	// 行列作成
	snStudy::Matrix44f polygonMtx = polygonMtx.Identity();
	polygonMtx.RotatinX(snStudy::Pi / 2);
	polygonMtx.Translation(-250, -35, 250);

	// 値設定
	originalVal.eachValue->worldMtx = polygonMtx;
	originalVal.eachValue->textureNum = snStudy::TextureManager::GetPointer()->GetTextuneNum("tex01.jpg");

	// リストに追加
	_polygonList.push_back(buf);

	// 更新フラグ設定
	SetUpdateFlag(true);
}

/// 終了
// 引数　：none
// 戻り値：none
// 2014/09/24
void GameScene::UninitCallback(){
	// マネージャ終了
	if (_polygonManager){
		_polygonManager->Release();
		_polygonManager = NULL;
	}
//	if (_modelManager){
//		_modelManager->Release();
//		_modelManager = NULL;
//	}

	// リスト削除
	_polygonList.clear();

	// 更新フラグ設定
	SetUpdateFlag(false);
}

/// 更新
// 引数　：none
// 戻り値：none
// 2014/09/24
void GameScene::Update(){
	DirectInputKeyboardUpdate();

	// シーン遷移
	if (GetDirectInputKeyboardInfo(DIK_RETURN, DI_MODE_TRIGG)){
		ChangeNextScene(3);
	}
}

//=EOF=