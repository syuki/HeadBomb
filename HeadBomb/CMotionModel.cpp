/// CMotionModel.cpp
// ���[�V�������ł�
// aurhor syuki nishida
// 2014/09/25

/// Includes
#include "CMotionModel.h"

/// �R���X�g���N�^
// �����@�Fnone
// �߂�l�Fnone
// 2014/09/25
CMotionModel::CMotionModel(char* FileName){
	// �t�@�C���ǂݍ���
	std::map<unsigned long, std::string> fileList;
	FILE* fp;
	fopen_s(&fp,FileName,"r");
	_ASSERT_EXPR(fp, L"CMotionModel::File open failed");

	// �ǂݍ���
	for(;;){
		char buf[512];
		unsigned long num;
		unsigned long par;
		char fileName[256];
		snStudy::Vector3f pos;
		snStudy::Vector3f rot;
		snStudy::XModel* curModel;
		unsigned long modelNum;

		// �l�擾
		if (!fgets(buf, 512, fp)){
			break;
		}
		sscanf_s(buf, "%d %d %s pos %f %f %f rot %f %f %f", &num, &par, fileName, 256, &pos.x, &pos.y, &pos.z, &rot.x, &rot.y, &rot.z);

		// ���f���쐬
		curModel = snStudy::XModel::Create(fileName);
		modelNum = curModel->AddDraw();
		_partsNumToModelNumList[num] = modelNum;
		_partsNumToDataList[num].originalVal = curModel->GetOriginalValue(modelNum);
		_partsNumToDataList[num].manager = curModel;

		// �f�[�^�ۑ�
		_partsNumToDataList[num].parent = par;
		*(_partsNumToDataList[num].originalVal.pos) = pos;
		*(_partsNumToDataList[num].originalVal.rot) = rot;

		// �t�@�C�����ۑ�
		fileList[num] = fileName;
	}


	fclose(fp);
}

/// �f�X�g���N�^
// �����@�Fnone
// �߂�l�Fnone
// 2014/09/25
CMotionModel::~CMotionModel(){
}

/// �X�V
// �����@�Fnone
// �߂�l�Fnone
// 2014/09/25
void CMotionModel::Update(){
	ApplyMatrix();
}

/// �s��K��
// �����@�Fnone
// �߂�l�Fnone
// 2014/09/25
void CMotionModel::ApplyMatrix(){
	// �e���珇�Ԃɂ����Ă���
	for (std::map<unsigned long, PartsData>::iterator it = _partsNumToDataList.begin(); it != _partsNumToDataList.end(); it++){
		// �����̍s��v�Z
		it->second.manager->AppryMatrix(_partsNumToModelNumList[it->first]);

		// �e������Ί|����
		if(it->second.parent){
			it->second.originalVal.eachValue->worldMtx * _partsNumToDataList[it->second.parent].originalVal.eachValue->worldMtx;
		}
	}
}

//=EOF=