/// Result.h
// ���U���g
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

	// �|���S���}�l�[�W���H
	snStudy::SimplePrimitivePolygon2D* _polygonManager;

	// �|���S�����X�g
	std::vector<unsigned long> _polygonList;

	/// �R���X�g���N�^
	ResultScene();

	/// �f�X�g���N�^
	virtual ~ResultScene();

	/// �J�ڎ��̌Ă΂�鏉�����J�n
	virtual void InitStartCallback();

	/// �J�ڎ��ɌĂ΂��I��
	virtual void UninitCallback();

	/// �X�V
	virtual void Update();

public:
	/// �N���G�C�^
	static ResultScene* Create(){
		return new ResultScene();
	}

	///  �����[�X
	void Release(){
		delete this;
	}
};

#endif
//=EOF=