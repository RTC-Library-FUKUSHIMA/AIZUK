/*!
 * @file ButtonWrapper.cpp
 * @brief ボタン入出力のラッパークラス
 * @author C.Saito
 * @date 2019/04/15
 */
#include "ButtonWrapper.h"

/*!
 * @enum 列挙子
 * データのビット位置
 */
enum DATA_BIT_POS_t
{
	DATA_BIT_POS_SQUARE,		/*!< SQUAREボタン		*/
	DATA_BIT_POS_CROSS,			/*!< CROSSボタン		*/
	DATA_BIT_POS_CIRCLE,		/*!< CIRCLEボタン		*/
	DATA_BIT_POS_TRIANGLE,		/*!< TRIANGLEボタン		*/
	DATA_BIT_POS_L1,			/*!< L1ボタン			*/
	DATA_BIT_POS_R1,			/*!< R1ボタン			*/
	DATA_BIT_POS_L2,			/*!< L2ボタン			*/
	DATA_BIT_POS_R2,			/*!< R2ボタン			*/
	DATA_BIT_POS_SHARE,			/*!< SHAREボタン		*/
	DATA_BIT_POS_OPTIONS,		/*!< OPTIONSボタン		*/
	DATA_BIT_POS_L3,			/*!< L3ボタン			*/
	DATA_BIT_POS_R3,			/*!< R3ボタン			*/
	DATA_BIT_POS_PS,			/*!< PSボタン			*/
	DATA_BIT_POS_TOUCH,			/*!< TOUCHボタン		*/
	DATA_BIT_POS_NUM,			/*!< データのビットの数	*/
};

ButtonWrapper::ButtonWrapper(RTC::TimedULong& Port)
	: m_Port(Port)
{
}

ButtonWrapper::~ButtonWrapper()
{
}

ButtonWrapper& ButtonWrapper::operator=(const ButtonWrapper& rhs)
{
	m_Port = rhs.m_Port;
	return *this;
};

void ButtonWrapper::SetTimestamp(void)
{
	// タイムスタンプを設定する
	setTimestamp(m_Port);
}

void ButtonWrapper::InitData(void)
{
	// ボタンの入出力の値を初期化する
	m_Port.data = 0;
}

uint8_t ButtonWrapper::GetDataNumber(void)
{
	return DATA_BIT_POS_NUM;
}

int16_t ButtonWrapper::GetSquare(void)
{
	return ((m_Port.data >> DATA_BIT_POS_SQUARE) & 1);
}

void ButtonWrapper::SetSquare(const int16_t iValue)
{
	if(iValue)
	{
		m_Port.data |= (1 << DATA_BIT_POS_SQUARE);
	}
	else
	{
		m_Port.data &= ~(1 << DATA_BIT_POS_SQUARE);
	}
}

int16_t ButtonWrapper::GetCross(void)
{
	return ((m_Port.data >> DATA_BIT_POS_CROSS) & 1);
}

void ButtonWrapper::SetCross(const int16_t iValue)
{
	if(iValue)
	{
		m_Port.data |= (1 << DATA_BIT_POS_CROSS);
	}
	else
	{
		m_Port.data &= ~(1 << DATA_BIT_POS_CROSS);
	}
}

int16_t ButtonWrapper::GetCircle(void)
{
	return ((m_Port.data >> DATA_BIT_POS_CIRCLE) & 1);
}

void ButtonWrapper::SetCircle(const int16_t iValue)
{
	if(iValue)
	{
		m_Port.data |= (1 << DATA_BIT_POS_CIRCLE);
	}
	else
	{
		m_Port.data &= ~(1 << DATA_BIT_POS_CIRCLE);
	}
}

int16_t ButtonWrapper::GetTriangle(void)
{
	return ((m_Port.data >> DATA_BIT_POS_TRIANGLE) & 1);
}

void ButtonWrapper::SetTriangle(const int16_t iValue)
{
	if(iValue)
	{
		m_Port.data |= (1 << DATA_BIT_POS_TRIANGLE);
	}
	else
	{
		m_Port.data &= ~(1 << DATA_BIT_POS_TRIANGLE);
	}
}

int16_t ButtonWrapper::GetL1(void)
{
	return ((m_Port.data >> DATA_BIT_POS_L1) & 1);
}

void ButtonWrapper::SetL1(const int16_t iValue)
{
	if(iValue)
	{
		m_Port.data |= (1 << DATA_BIT_POS_L1);
	}
	else
	{
		m_Port.data &= ~(1 << DATA_BIT_POS_L1);
	}
}

int16_t ButtonWrapper::GetR1(void)
{
	return ((m_Port.data >> DATA_BIT_POS_R1) & 1);
}

void ButtonWrapper::SetR1(const int16_t iValue)
{
	if(iValue)
	{
		m_Port.data |= (1 << DATA_BIT_POS_R1);
	}
	else
	{
		m_Port.data &= ~(1 << DATA_BIT_POS_R1);
	}
}

int16_t ButtonWrapper::GetL2(void)
{
	return ((m_Port.data >> DATA_BIT_POS_L2) & 1);
}

void ButtonWrapper::SetL2(const int16_t iValue)
{
	if(iValue)
	{
		m_Port.data |= (1 << DATA_BIT_POS_L2);
	}
	else
	{
		m_Port.data &= ~(1 << DATA_BIT_POS_L2);
	}
}

int16_t ButtonWrapper::GetR2(void)
{
	return ((m_Port.data >> DATA_BIT_POS_R2) & 1);
}

void ButtonWrapper::SetR2(const int16_t iValue)
{
	if(iValue)
	{
		m_Port.data |= (1 << DATA_BIT_POS_R2);
	}
	else
	{
		m_Port.data &= ~(1 << DATA_BIT_POS_R2);
	}
}

int16_t ButtonWrapper::GetShare(void)
{
	return ((m_Port.data >> DATA_BIT_POS_SHARE) & 1);
}

void ButtonWrapper::SetShare(const int16_t iValue)
{
	if(iValue)
	{
		m_Port.data |= (1 << DATA_BIT_POS_SHARE);
	}
	else
	{
		m_Port.data &= ~(1 << DATA_BIT_POS_SHARE);
	}
}

int16_t ButtonWrapper::GetOptions(void)
{
	return ((m_Port.data >> DATA_BIT_POS_OPTIONS) & 1);
}

void ButtonWrapper::SetOptions(const int16_t iValue)
{
	if(iValue)
	{
		m_Port.data |= (1 << DATA_BIT_POS_OPTIONS);
	}
	else
	{
		m_Port.data &= ~(1 << DATA_BIT_POS_OPTIONS);
	}
}

int16_t ButtonWrapper::GetL3(void)
{
	return ((m_Port.data >> DATA_BIT_POS_L3) & 1);
}

void ButtonWrapper::SetL3(const int16_t iValue)
{
	if(iValue)
	{
		m_Port.data |= (1 << DATA_BIT_POS_L3);
	}
	else
	{
		m_Port.data &= ~(1 << DATA_BIT_POS_L3);
	}
}

int16_t ButtonWrapper::GetR3(void)
{
	return ((m_Port.data >> DATA_BIT_POS_R3) & 1);
}

void ButtonWrapper::SetR3(const int16_t iValue)
{
	if(iValue)
	{
		m_Port.data |= (1 << DATA_BIT_POS_R3);
	}
	else
	{
		m_Port.data &= ~(1 << DATA_BIT_POS_R3);
	}
}

int16_t ButtonWrapper::GetPS(void)
{
	return ((m_Port.data >> DATA_BIT_POS_PS) & 1);
}

void ButtonWrapper::SetPS(const int16_t iValue)
{
	if(iValue)
	{
		m_Port.data |= (1 << DATA_BIT_POS_PS);
	}
	else
	{
		m_Port.data &= ~(1 << DATA_BIT_POS_PS);
	}
}

int16_t ButtonWrapper::GetTouch(void)
{
	return ((m_Port.data >> DATA_BIT_POS_TOUCH) & 1);
}

void ButtonWrapper::SetTouch(const int16_t iValue)
{
	if(iValue)
	{
		m_Port.data |= (1 << DATA_BIT_POS_TOUCH);
	}
	else
	{
		m_Port.data &= ~(1 << DATA_BIT_POS_TOUCH);
	}
}
