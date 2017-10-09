/// CMotionModel.h
// モーションもでる
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

	// パーツリスト
	std::map<unsigned long, unsigned long> _partsNumToModelNumList;

	// パーツステータスリスト
	std::map<unsigned long, PartsData> _partsNumToDataList;

	/// コンストラクタ
	CMotionModel(char* FileName);

	/// デストラクタ
	virtual ~CMotionModel();

	/// 更新
	void Update();
	
public:

	/// クリエイト
	static CMotionModel* Create(char* FileName){
		return new CMotionModel(FileName);
	}

	/// リリース
	void Release(){
		delete this;
	}

	/// 行列適応
	void ApplyMatrix();
};

#endif
//=EOF=