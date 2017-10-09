/// CMotionModel.cpp
// モーションもでる
// aurhor syuki nishida
// 2014/09/25

/// Includes
#include "CMotionModel.h"

/// コンストラクタ
// 引数　：none
// 戻り値：none
// 2014/09/25
CMotionModel::CMotionModel(char* FileName){
	// ファイル読み込み
	std::map<unsigned long, std::string> fileList;
	FILE* fp;
	fopen_s(&fp,FileName,"r");
	_ASSERT_EXPR(fp, L"CMotionModel::File open failed");

	// 読み込み
	for(;;){
		char buf[512];
		unsigned long num;
		unsigned long par;
		char fileName[256];
		snStudy::Vector3f pos;
		snStudy::Vector3f rot;
		snStudy::XModel* curModel;
		unsigned long modelNum;

		// 値取得
		if (!fgets(buf, 512, fp)){
			break;
		}
		sscanf_s(buf, "%d %d %s pos %f %f %f rot %f %f %f", &num, &par, fileName, 256, &pos.x, &pos.y, &pos.z, &rot.x, &rot.y, &rot.z);

		// モデル作成
		curModel = snStudy::XModel::Create(fileName);
		modelNum = curModel->AddDraw();
		_partsNumToModelNumList[num] = modelNum;
		_partsNumToDataList[num].originalVal = curModel->GetOriginalValue(modelNum);
		_partsNumToDataList[num].manager = curModel;

		// データ保存
		_partsNumToDataList[num].parent = par;
		*(_partsNumToDataList[num].originalVal.pos) = pos;
		*(_partsNumToDataList[num].originalVal.rot) = rot;

		// ファイル名保存
		fileList[num] = fileName;
	}


	fclose(fp);
}

/// デストラクタ
// 引数　：none
// 戻り値：none
// 2014/09/25
CMotionModel::~CMotionModel(){
}

/// 更新
// 引数　：none
// 戻り値：none
// 2014/09/25
void CMotionModel::Update(){
	ApplyMatrix();
}

/// 行列適応
// 引数　：none
// 戻り値：none
// 2014/09/25
void CMotionModel::ApplyMatrix(){
	// 親から順番にかけていく
	for (std::map<unsigned long, PartsData>::iterator it = _partsNumToDataList.begin(); it != _partsNumToDataList.end(); it++){
		// 自分の行列計算
		it->second.manager->AppryMatrix(_partsNumToModelNumList[it->first]);

		// 親がいれば掛ける
		if(it->second.parent){
			it->second.originalVal.eachValue->worldMtx * _partsNumToDataList[it->second.parent].originalVal.eachValue->worldMtx;
		}
	}
}

//=EOF=