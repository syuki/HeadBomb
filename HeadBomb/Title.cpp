/// Title.cpp
// タイトル
// suthor syuki nishida
// 2014/09/24

/// Include
#include "Title.h"
#include "Input.h"

/// コンストラクタ
// 引数　：none
// 戻り値：none
// 2014/09/24
TitleScene::TitleScene() : snStudy::SceneManager(TITLE_NUM){
	_polygonManager = NULL;

	// 更新フラグ設定
	SetUpdateFlag(false);
}

/// デストラクタ
// 引数　：none
// 戻り値：none
// 2014/09/24
TitleScene::~TitleScene(){
	// マネージャ終了
	if (_polygonManager){
		_polygonManager->Release();
		_polygonManager = NULL;
	}
}

/// 初期化
// 引数　：none
// 戻り値：none
// 2014/09/24
void TitleScene::InitStartCallback(){
	// 描画マネージャ系初期化
	_polygonManager = snStudy::SimplePrimitivePolygon2D::Create(500, 500, snStudy::DrawElement::PERTH);

	// ポリゴン追加
	unsigned long buf = _polygonManager->AddDraw();

	// ポリゴンの設定用のポインタ取得
	snStudy::SimplePrimitivePolygon2D::OriginalValue originalVal = _polygonManager->CopyOriginalValue(buf);

	// 行列作成
	snStudy::Matrix44f polygonMtx = polygonMtx.Identity();
	polygonMtx.RotatinX(snStudy::Pi / 2);
	polygonMtx.Translation(-250, -15, 250);

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
void TitleScene::UninitCallback(){
	// マネージャ終了
	if (_polygonManager){
		_polygonManager->Release();
		_polygonManager = NULL;
	}

	// リスト削除
	_polygonList.clear();

	// 更新フラグ設定
	SetUpdateFlag(false);
}

/// 更新
// 引数　：none
// 戻り値：none
// 2014/09/24
void TitleScene::Update(){
	DirectInputKeyboardUpdate();
	// シーン遷移
	if(GetDirectInputKeyboardInfo(DIK_RETURN,DI_MODE_TRIGG)){
		ChangeNextScene(2);
	}
}

//=EOF=