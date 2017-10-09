/// Game.h
// �Q�[���{��
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

	// �|���S���}�l�[�W���H
	snStudy::SimplePrimitivePolygon2D* _polygonManager;

	// �|���S�����X�g
	std::vector<unsigned long> _polygonList;

	// XModel�}�l�[�W���H
	snStudy::XModel* _modelManager;

	// XModel���X�g
	std::vector<unsigned long> _modelList;

	/// �R���X�g���N�^
	GameScene();

	/// �f�X�g���N�^
	virtual ~GameScene();

	/// �J�ڎ��̌Ă΂�鏉�����J�n
	virtual void InitStartCallback();

	/// �J�ڎ��ɌĂ΂��I��
	virtual void UninitCallback();

	/// �X�V
	virtual void Update();

public:
	/// �N���G�C�^
	static GameScene* Create(){
		return new GameScene();
	}

	///  �����[�X
	void Release(){
		delete this;
	}
};

#endif
//=EOF=