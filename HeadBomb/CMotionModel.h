/// CMotionModel.h
// ���[�V�������ł�
// aurhor syuki nishida
// 2014/09/25
#ifndef _C_MOTION_MODEL_H_
#define _C_MOTION_MODEL_H_

/// Includes
#include <snStudy.h>
#include <map>

/// Class
class CMotionModel : public snStudy::UpdateElement{
	struct PartsData{
		snStudy::XModel::OriginalValue originalVal;
		unsigned long parent;
		snStudy::XModel* manager;
	};

	// �p�[�c���X�g
	std::map<unsigned long, unsigned long> _partsNumToModelNumList;

	// �p�[�c�X�e�[�^�X���X�g
	std::map<unsigned long, PartsData> _partsNumToDataList;

	/// �R���X�g���N�^
	CMotionModel(char* FileName);

	/// �f�X�g���N�^
	virtual ~CMotionModel();

	/// �X�V
	void Update();
	
public:

	/// �N���G�C�g
	static CMotionModel* Create(char* FileName){
		return new CMotionModel(FileName);
	}

	/// �����[�X
	void Release(){
		delete this;
	}

	/// �s��K��
	void ApplyMatrix();
};

#endif
//=EOF=