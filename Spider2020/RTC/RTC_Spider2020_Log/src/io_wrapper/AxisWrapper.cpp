/*!
 * @file AxisWrapper.cpp
 * @brief 軸キー入出力のラッパークラス
 * @author C.Saito
 * @date 2019/04/15
 */
#include "AxisWrapper.h"

/*!
 * @enum 列挙子
 * データのインデクサ
 */
enum DATA_INDEX_t
{
	DATA_INDEX_DIR_VERTICAL,		/*!< 十字ボタン(上下)		*/
	DATA_INDEX_DIR_HORIZONTAL,		/*!< 十字ボタン(左右)		*/
	DATA_INDEX_LSTICK_VERTICAL,		/*!< 左スティック(上下) 	*/
	DATA_INDEX_LSTICK_HORIZONTAL,	/*!< 左スティック(左右) 	*/
	DATA_INDEX_RSTICK_VERTICAL,		/*!< 右スティック(上下) 	*/
	DATA_INDEX_RSTICK_HORIZONTAL,	/*!< 右スティック(左右) 	*/
	DATA_INDEX_L2,					/*!< L2ボタン				*/
	DATA_INDEX_R2,					/*!< R2ボタン				*/
	DATA_INDEX_NUM,					/*!< データの数				*/
};

AxisWrapper::AxisWrapper(RTC::TimedDoubleSeq& Port)
	: m_Port(Port)
{
}

AxisWrapper::~AxisWrapper()
{
}

AxisWrapper& AxisWrapper::operator=(const AxisWrapper& rhs)
{
	m_Port = rhs.m_Port;
	return *this;
};

void AxisWrapper::SetTimestamp(void)
{
	// タイムスタンプを設定する
	setTimestamp(m_Port);
}

void AxisWrapper::InitData(void)
{
	// 軸キーの入出力の配列数を初期化する
	m_Port.data.length(DATA_INDEX_NUM);

	// 軸キーの入出力の配列値を初期化する
	SetDirVertical(0.0);
	SetDirHorizontal(0.0);
	SetLStickVertical(0.0);
	SetLStickHorizontal(0.0);
	SetRStickVertical(0.0);
	SetRStickHorizontal(0.0);
	SetL2(-1.0);
	SetR2(-1.0);
}

uint8_t AxisWrapper::GetDataNumber(void)
{
	return DATA_INDEX_NUM;
}

double AxisWrapper::GetDirHorizontal(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0.0;
	}

	return m_Port.data[DATA_INDEX_DIR_HORIZONTAL];
}

void AxisWrapper::SetDirHorizontal(const double dValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_DIR_HORIZONTAL] = dValue;
}

double AxisWrapper::GetDirVertical(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0.0;
	}

	return m_Port.data[DATA_INDEX_DIR_VERTICAL];
}

void AxisWrapper::SetDirVertical(const double dValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_DIR_VERTICAL] = dValue;
}

double AxisWrapper::GetLStickHorizontal(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0.0;
	}

	return m_Port.data[DATA_INDEX_LSTICK_HORIZONTAL];
}

void AxisWrapper::SetLStickHorizontal(const double dValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_LSTICK_HORIZONTAL] = dValue;
}

double AxisWrapper::GetLStickVertical(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0.0;
	}

	return m_Port.data[DATA_INDEX_LSTICK_VERTICAL];
}

void AxisWrapper::SetLStickVertical(const double dValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_LSTICK_VERTICAL] = dValue;
}

double AxisWrapper::GetRStickHorizontal(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0.0;
	}

	return m_Port.data[DATA_INDEX_RSTICK_HORIZONTAL];
}

void AxisWrapper::SetRStickHorizontal(const double dValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_RSTICK_HORIZONTAL] = dValue;
}

double AxisWrapper::GetRStickVertical(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return 0.0;
	}

	return m_Port.data[DATA_INDEX_RSTICK_VERTICAL];
}

void AxisWrapper::SetRStickVertical(const double dValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_RSTICK_VERTICAL] = dValue;
}

double AxisWrapper::GetL2(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return -1.0;
	}

	return m_Port.data[DATA_INDEX_L2];
}

void AxisWrapper::SetL2(const double dValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_L2] = dValue;
}

double AxisWrapper::GetR2(void)
{
	// データの数が不一致なら初期値を返す
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return -1.0;
	}

	return m_Port.data[DATA_INDEX_R2];
}

void AxisWrapper::SetR2(const double dValue)
{
	// データの数が不一致なら設定しない
	if(m_Port.data.length() != DATA_INDEX_NUM)
	{
		return;
	}

	m_Port.data[DATA_INDEX_R2] = dValue;
}
