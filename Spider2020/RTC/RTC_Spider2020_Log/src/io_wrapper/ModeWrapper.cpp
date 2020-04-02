/*!
 * @file ModeWrapper.cpp
 * @brief 動作指令の状態入出力のラッパークラス
 * @author C.Saito
 * @date 2019/04/16
 */
#include "ModeWrapper.h"

/*!
 * @enum 列挙子
 * データのインデクサ
 */
enum DATA_INDEX_t
{
	DATA_INDEX_CONTROL,					/*!< 操作モード							*/
	DATA_INDEX_SPEED_LEVEL,				/*!< 走行モード 速度レベル				*/
	DATA_INDEX_SPEED_MAX,				/*!< 走行モード 最大速度フラグ			*/
	DATA_INDEX_FLIPPER_SELECT,			/*!< 走行モード フリッパーの選択状態	*/
	DATA_INDEX_FLIPPER_STATUS,			/*!< 走行モード フリッパーの動作状態	*/
	DATA_INDEX_CRAWLER_POSE_CLEAR,		/*!< 走行モード 台車の位置姿勢のクリア	*/
	DATA_INDEX_NUM,						/*!< データの数							*/
};

/*!
 * @enum 列挙子
 * フリッパーの選択状態データのビット位置
 */
enum FLIPPER_SELECT_DATA_BIT_POS_t
{
	FLIPPER_SELECT_DATA_BIT_POS_FR,		/*!< 右前方フリッパー	*/
	FLIPPER_SELECT_DATA_BIT_POS_FL,		/*!< 左前方フリッパー	*/
	FLIPPER_SELECT_DATA_BIT_POS_BR,		/*!< 右後方フリッパー	*/
	FLIPPER_SELECT_DATA_BIT_POS_BL,		/*!< 左後方フリッパー	*/
	FLIPPER_SELECT_DATA_BIT_POS_NUM,	/*!< データのビットの数	*/
};

ModeWrapper::ModeWrapper(RTC::TimedLongSeq& Port)
	: m_Port(Port)
{
}

ModeWrapper::~ModeWrapper()
{
}

ModeWrapper& ModeWrapper::operator=(const ModeWrapper& rhs)
{
	m_Port = rhs.m_Port;
	return *this;
};

void ModeWrapper::SetTimestamp(void)
{
	// タイムスタンプを設定する
	setTimestamp(m_Port);
}

void ModeWrapper::InitData(void)
{
	// 動作指令の状態の入出力の配列数を初期化する
	m_Port.data.length(DATA_INDEX_NUM);

	// 軸キーの入出力の配列値を初期化する
	SetSpeedLevel(ModeWrapper::SPEED_LEVEL_LOW);
	SetSpeedMax(ModeWrapper::SPEED_MAX_OFF);
	SetControl(ModeWrapper::CONTROL_DRIVE);
	SetFrontRightFlipperSelect(ModeWrapper::FLIPPER_SELECT_OFF);
	SetFrontLeftFlipperSelect(ModeWrapper::FLIPPER_SELECT_OFF);
	SetBackRightFlipperSelect(ModeWrapper::FLIPPER_SELECT_OFF);
	SetBackLeftFlipperSelect(ModeWrapper::FLIPPER_SELECT_OFF);
	SetFlipperStatus(ModeWrapper::FLIPPER_STATUS_STAY);
	SetCrawlerPoseClear(ModeWrapper::CRAWLER_POSE_CLEAR_OFF);
}

uint8_t ModeWrapper::GetDataNumber(void)
{
	return DATA_INDEX_NUM;
}

int32_t ModeWrapper::GetSpeedLevel(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return ModeWrapper::SPEED_LEVEL_LOW;
	}

	return m_Port.data[DATA_INDEX_SPEED_LEVEL];
}

void ModeWrapper::SetSpeedLevel(const int32_t iValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_SPEED_LEVEL] = iValue;
}

int32_t ModeWrapper::GetSpeedMax(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return ModeWrapper::SPEED_MAX_OFF;
	}

	return m_Port.data[DATA_INDEX_SPEED_MAX];
}

void ModeWrapper::SetSpeedMax(const int32_t iValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_SPEED_MAX] = iValue;
}

int32_t ModeWrapper::GetControl(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return ModeWrapper::CONTROL_DRIVE;
	}

	return m_Port.data[DATA_INDEX_CONTROL];
}

void ModeWrapper::SetControl(const int32_t iValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_CONTROL] = iValue;
}

int32_t ModeWrapper::GetFrontRightFlipperSelect(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return ModeWrapper::FLIPPER_SELECT_OFF;
	}

	return ((m_Port.data[DATA_INDEX_FLIPPER_SELECT] >> FLIPPER_SELECT_DATA_BIT_POS_FR) & 1);
}

void ModeWrapper::SetFrontRightFlipperSelect(const int32_t iValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	if(iValue)
	{
		m_Port.data[DATA_INDEX_FLIPPER_SELECT] |= (1 << FLIPPER_SELECT_DATA_BIT_POS_FR);
	}
	else
	{
		m_Port.data[DATA_INDEX_FLIPPER_SELECT] &= ~(1 << FLIPPER_SELECT_DATA_BIT_POS_FR);
	}
}

int32_t ModeWrapper::GetFrontLeftFlipperSelect(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return ModeWrapper::FLIPPER_SELECT_OFF;
	}

	return ((m_Port.data[DATA_INDEX_FLIPPER_SELECT] >> FLIPPER_SELECT_DATA_BIT_POS_FL) & 1);
}

void ModeWrapper::SetFrontLeftFlipperSelect(const int32_t iValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	if(iValue)
	{
		m_Port.data[DATA_INDEX_FLIPPER_SELECT] |= (1 << FLIPPER_SELECT_DATA_BIT_POS_FL);
	}
	else
	{
		m_Port.data[DATA_INDEX_FLIPPER_SELECT] &= ~(1 << FLIPPER_SELECT_DATA_BIT_POS_FL);
	}
}

int32_t ModeWrapper::GetBackRightFlipperSelect(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return ModeWrapper::FLIPPER_SELECT_OFF;
	}

	return ((m_Port.data[DATA_INDEX_FLIPPER_SELECT] >> FLIPPER_SELECT_DATA_BIT_POS_BR) & 1);
}

void ModeWrapper::SetBackRightFlipperSelect(const int32_t iValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	if(iValue)
	{
		m_Port.data[DATA_INDEX_FLIPPER_SELECT] |= (1 << FLIPPER_SELECT_DATA_BIT_POS_BR);
	}
	else
	{
		m_Port.data[DATA_INDEX_FLIPPER_SELECT] &= ~(1 << FLIPPER_SELECT_DATA_BIT_POS_BR);
	}
}

int32_t ModeWrapper::GetBackLeftFlipperSelect(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return ModeWrapper::FLIPPER_SELECT_OFF;
	}

	return ((m_Port.data[DATA_INDEX_FLIPPER_SELECT] >> FLIPPER_SELECT_DATA_BIT_POS_BL) & 1);
}

void ModeWrapper::SetBackLeftFlipperSelect(const int32_t iValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	if(iValue)
	{
		m_Port.data[DATA_INDEX_FLIPPER_SELECT] |= (1 << FLIPPER_SELECT_DATA_BIT_POS_BL);
	}
	else
	{
		m_Port.data[DATA_INDEX_FLIPPER_SELECT] &= ~(1 << FLIPPER_SELECT_DATA_BIT_POS_BL);
	}
}

int32_t ModeWrapper::GetFlipperStatus(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return ModeWrapper::FLIPPER_STATUS_STAY;
	}

	return m_Port.data[DATA_INDEX_FLIPPER_STATUS];
}

void ModeWrapper::SetFlipperStatus(const int32_t iValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_FLIPPER_STATUS] = iValue;
}

int32_t ModeWrapper::GetCrawlerPoseClear(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return ModeWrapper::CRAWLER_POSE_CLEAR_OFF;
	}

	return m_Port.data[DATA_INDEX_CRAWLER_POSE_CLEAR];
}

void ModeWrapper::SetCrawlerPoseClear(const int32_t iValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_CRAWLER_POSE_CLEAR] = iValue;
}
