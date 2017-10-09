/// Title.h
// �^�C�g��
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

	// �|���S���}�l�[�W���H
	snStudy::SimplePrimitivePolygon2D* _polygonManager;

	// �|���S�����X�g
	std::vector<unsigned long> _polygonList;

	/// �R���X�g���N�^
	TitleScene();

	/// �f�X�g���N�^
	virtual ~TitleScene();

	/// �J�ڎ��̌Ă΂�鏉�����J�n
	virtual void InitStartCallback();

	/// �J�ڎ��ɌĂ΂��I��
	virtual void UninitCallback();

	/// �X�V
	virtual void Update();

public:
	/// �N���G�C�^
	static TitleScene* Create(){
		return new TitleScene();
	}

	///  �����[�X
	void Release(){
		delete this;
	}
};

#endif
//=EOF=