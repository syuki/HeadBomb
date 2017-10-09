/// Game.cpp
// �^�C�g��
// suthor syuki nishida
// 2014/09/24

/// Include
#include "Game.h"
#include "Input.h"
#include "CMotionModel.h"

/// �R���X�g���N�^
// �����@�Fnone
// �߂�l�Fnone
// 2014/09/24
GameScene::GameScene() : snStudy::SceneManager(GAME_NUM){
	_polygonManager = NULL;
	_modelManager = NULL;
//	CMotionModel* model = CMotionModel::Create("data/MODEL/akrModel.spm");

	// �X�V�t���O�ݒ�
	SetUpdateFlag(false);
}

/// �f�X�g���N�^
// �����@�Fnone
// �߂�l�Fnone
// 2014/09/24
GameScene::~GameScene(){
	// �}�l�[�W���I��
	if (_polygonManager){
		_polygonManager->Release();
		_polygonManager = NULL;
	}
	if (_modelManager){
		_modelManager->Release();
		_modelManager = NULL;
	}
}

/// ������
// �����@�Fnone
// �߂�l�Fnone
// 2014/09/24
void GameScene::InitStartCallback(){
	// �`��}�l�[�W���n������
	_polygonManager = snStudy::SimplePrimitivePolygon2D::Create(500, 500, snStudy::DrawElement::PERTH);
	_modelManager= snStudy::XModel::Create("data/MODEL/arm_l.x");

	// �|���S���ǉ�
	unsigned long buf = _polygonManager->AddDraw();
	
	_modelManager->AddDraw();

	// �|���S���̐ݒ�p�̃|�C���^�擾
	snStudy::SimplePrimitivePolygon2D::OriginalValue originalVal = _polygonManager->CopyOriginalValue(buf);

	// �s��쐬
	snStudy::Matrix44f polygonMtx = polygonMtx.Identity();
	polygonMtx.RotatinX(snStudy::Pi / 2);
	polygonMtx.Translation(-250, -35, 250);

	// �l�ݒ�
	originalVal.eachValue->worldMtx = polygonMtx;
	originalVal.eachValue->textureNum = snStudy::TextureManager::GetPointer()->GetTextuneNum("tex01.jpg");

	// ���X�g�ɒǉ�
	_polygonList.push_back(buf);

	// �X�V�t���O�ݒ�
	SetUpdateFlag(true);
}

/// �I��
// �����@�Fnone
// �߂�l�Fnone
// 2014/09/24
void GameScene::UninitCallback(){
	// �}�l�[�W���I��
	if (_polygonManager){
		_polygonManager->Release();
		_polygonManager = NULL;
	}
//	if (_modelManager){
//		_modelManager->Release();
//		_modelManager = NULL;
//	}

	// ���X�g�폜
	_polygonList.clear();

	// �X�V�t���O�ݒ�
	SetUpdateFlag(false);
}

/// �X�V
// �����@�Fnone
// �߂�l�Fnone
// 2014/09/24
void GameScene::Update(){
	DirectInputKeyboardUpdate();

	// �V�[���J��
	if (GetDirectInputKeyboardInfo(DIK_RETURN, DI_MODE_TRIGG)){
		ChangeNextScene(3);
	}
}

//=EOF=