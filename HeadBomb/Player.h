/// Player.h
// �v���C���[
// author syuki nishida
// 2014/09/24
#ifndef _PLAYER_H_
#define _PLAYER_H_

/// Includes
#include <snStudy.h>

/// Class
class Player : public snStudy::UpdateElement{

	// ���f���ԍ�

	/// �R���X�g���N�^
	Player();

	/// �f�X�g���N�^
	virtual ~Player();

	/// �X�V
	virtual void Update();

public:
	/// �N���G�C�^
	static Player* Create(){
		return new Player();
	}

	///  �����[�X
	void Release(){
		delete this;
	}
};

#endif
//=EOF=