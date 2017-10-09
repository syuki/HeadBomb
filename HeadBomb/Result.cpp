/// Result.cpp
// �^�C�g��
// suthor syuki nishida
// 2014/09/24

/// Include
#include "Result.h"
#include "Input.h"

/// �R���X�g���N�^
// �����@�Fnone
// �߂�l�Fnone
// 2014/09/24
ResultScene::ResultScene() : snStudy::SceneManager(RESULT_NUM){
	_polygonManager = NULL;

	// �X�V�t���O�ݒ�
	SetUpdateFlag(false);
}

/// �f�X�g���N�^
// �����@�Fnone
// �߂�l�Fnone
// 2014/09/24
ResultScene::~ResultScene(){
	// �}�l�[�W���I��
	if (_polygonManager){
		_polygonManager->Release();
		_polygonManager = NULL;
	}
}

/// ������
// �����@�Fnone
// �߂�l�Fnone
// 2014/09/24
void ResultScene::InitStartCallback(){
	// �`��}�l�[�W���n������
	_polygonManager = snStudy::SimplePrimitivePolygon2D::Create(500, 500, snStudy::DrawElement::PERTH);

	// �|���S���ǉ�
	unsigned long buf = _polygonManager->AddDraw();

	// �|���S���̐ݒ�p�̃|�C���^�擾
	snStudy::SimplePrimitivePolygon2D::OriginalValue originalVal = _polygonManager->CopyOriginalValue(buf);

	// �s��쐬
	snStudy::Matrix44f polygonMtx = polygonMtx.Identity();
	polygonMtx.RotatinX(snStudy::Pi / 2);
	polygonMtx.Translation(-250, -20, 250);

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
void ResultScene::UninitCallback(){
	// �}�l�[�W���I��
	if (_polygonManager){
		_polygonManager->Release();
		_polygonManager = NULL;
	}

	// ���X�g�폜
	_polygonList.clear();

	// �X�V�t���O�ݒ�
	SetUpdateFlag(false);
}

/// �X�V
// �����@�Fnone
// �߂�l�Fnone
// 2014/09/24
void ResultScene::Update(){
	DirectInputKeyboardUpdate();
	// �V�[���J��
	if (GetDirectInputKeyboardInfo(DIK_RETURN, DI_MODE_TRIGG)){
		ChangeNextScene(1);
	}
}

//=EOF=