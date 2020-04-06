// -*- C++ -*-
/*!
 * @file IMU_GX5_25_Capture.cpp
 * @brief LORD製3DM-GX5-25の情報の取得クラス
 * @author C.Saito
 * @date 2020/02/12
 */

#include "IMU_GX5_25_Capture.h"

IMU_GX5_25_Capture::IMU_GX5_25_Capture()
	: m_pConnection(nullptr)
	, m_fEstLinearAccelX(0.0)
	, m_fEstLinearAccelY(0.0)
	, m_fEstLinearAccelZ(0.0)
	, m_fEstEulerAnglesR(0.0)
	, m_fEstEulerAnglesP(0.0)
	, m_fEstEulerAnglesY(0.0)
{
}

IMU_GX5_25_Capture::~IMU_GX5_25_Capture()
{
	// シリアルポートを閉じる
	Close();
}

bool IMU_GX5_25_Capture::Open(const std::string &sDeviceName)
{
	// 多重オープンを防止する
	if(m_pConnection != nullptr)
	{
		printf("open(%s) is failed\n", sDeviceName.c_str());
		return false;
	}

	try
	{
		// シリアル接続管理クラスを生成する
		m_pConnection = new mscl::Connection();
		if(m_pConnection == nullptr)
		{
			printf("memory allocation is failed\n");
			return false;
		}

		// シリアルポートを開く
		*m_pConnection = mscl::Connection::Serial(sDeviceName.c_str(), 115200);
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}

	return true;
}

void IMU_GX5_25_Capture::Close()
{
	if(m_pConnection != nullptr)
	{
		delete m_pConnection;
		m_pConnection = nullptr;
	}
}

bool IMU_GX5_25_Capture::ResetEstFilter(void)
{
	if(m_pConnection == nullptr)
	{
		return false;
	}

	// 通信ノードを作成する
	mscl::InertialNode iNode(*m_pConnection);

	// ESTFILTERをリセットする
	iNode.resetFilter();

	return true;
}

bool IMU_GX5_25_Capture::InitEstFilter(float fRoll, float fPitch, float fYaw)
{
	mscl::EulerAngles ea(fRoll, fPitch, fYaw);

	if(m_pConnection == nullptr)
	{
		return false;
	}

	// 通信ノードを作成する
	mscl::InertialNode iNode(*m_pConnection);

	// ESTFILTERを初期化する
	iNode.setInitialAttitude(ea);

	return true;
}

bool IMU_GX5_25_Capture::PollEstLinearAccel(void)
{
	mscl::MipTypes::MipChannelFields fields;
	mscl::MipDataPackets packets;
	mscl::MipDataPoints data;

	if(m_pConnection == nullptr)
	{
		return false;
	}

	try
	{
		// 通信ノードを作成する
		mscl::InertialNode iNode(*m_pConnection);

		// ポーリング対象データを登録する
		fields.push_back(mscl::MipTypes::ChannelField::CH_FIELD_ESTFILTER_ESTIMATED_LINEAR_ACCEL);

		// ポーリングする
		iNode.pollData(mscl::MipTypes::CLASS_ESTFILTER, fields);

		// ポーリングしたパケットを処理する
		packets = iNode.getDataPackets();
		for(mscl::MipDataPackets::iterator itPacket = packets.begin(); itPacket != packets.end(); itPacket++)
		{
			// データを処理する
			data = itPacket->data();
			for(mscl::MipDataPoints::iterator itData = data.begin(); itData != data.end(); itData++)
			{
				if(itData->field() == mscl::MipTypes::ChannelField::CH_FIELD_ESTFILTER_ESTIMATED_LINEAR_ACCEL)
				{
					// X軸方向の加速度を取得する
					if(itData->qualifier() == mscl::MipTypes::ChannelQualifier::CH_X)
					{
						m_fEstLinearAccelX = itData->as_float();
					}
					// Y軸方向の加速度を取得する
					else if(itData->qualifier() == mscl::MipTypes::ChannelQualifier::CH_Y)
					{
						m_fEstLinearAccelY = itData->as_float();
					}
					// Z軸方向の加速度を取得する
					else if(itData->qualifier() == mscl::MipTypes::ChannelQualifier::CH_Z)
					{
						m_fEstLinearAccelZ = itData->as_float();
					}
				}
			}
		}
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}

	return true;
}

float IMU_GX5_25_Capture::GetEstLinearAccelX(void)
{
	if(m_pConnection == nullptr)
	{
		return 0.0;
	}

	return m_fEstLinearAccelX;
}

float IMU_GX5_25_Capture::GetEstLinearAccelY(void)
{
	if(m_pConnection == nullptr)
	{
		return 0.0;
	}

	return m_fEstLinearAccelY;
}

float IMU_GX5_25_Capture::GetEstLinearAccelZ(void)
{
	if(m_pConnection == nullptr)
	{
		return 0.0;
	}

	return m_fEstLinearAccelZ;
}

bool IMU_GX5_25_Capture::PollEstEulerAngles(void)
{
	mscl::MipTypes::MipChannelFields fields;
	mscl::MipDataPackets packets;
	mscl::MipDataPoints data;

	if(m_pConnection == nullptr)
	{
		return false;
	}

	try
	{
		// 通信ノードを作成する
		mscl::InertialNode iNode(*m_pConnection);

		// ポーリング対象データを登録する
		fields.push_back(mscl::MipTypes::ChannelField::CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_EULER);

		// ポーリングする
		iNode.pollData(mscl::MipTypes::CLASS_ESTFILTER, fields);

		// ポーリングしたパケットを処理する
		packets = iNode.getDataPackets();
		for(mscl::MipDataPackets::iterator itPacket = packets.begin(); itPacket != packets.end(); itPacket++)
		{
			// データを処理する
			data = itPacket->data();
			for(mscl::MipDataPoints::iterator itData = data.begin(); itData != data.end(); itData++)
			{
				if(itData->field() == mscl::MipTypes::ChannelField::CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_EULER)
				{
					// 姿勢ロールを取得する
					if(itData->qualifier() == mscl::MipTypes::ChannelQualifier::CH_ROLL)
					{
						m_fEstEulerAnglesR = itData->as_float();
					}
					// 姿勢ピッチを取得する
					else if(itData->qualifier() == mscl::MipTypes::ChannelQualifier::CH_PITCH)
					{
						m_fEstEulerAnglesP = itData->as_float();
					}
					// 姿勢ヨーを取得する
					else if(itData->qualifier() == mscl::MipTypes::ChannelQualifier::CH_YAW)
					{
						m_fEstEulerAnglesY = itData->as_float();
					}
				}
			}
		}
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}

	return true;
}

float IMU_GX5_25_Capture::GetEstEulerAnglesR(void)
{
	if(m_pConnection == nullptr)
	{
		return 0.0f;
	}

	return m_fEstEulerAnglesR;
}

float IMU_GX5_25_Capture::GetEstEulerAnglesP(void)
{
	if(m_pConnection == nullptr)
	{
		return 0.0f;
	}

	return m_fEstEulerAnglesP;
}

float IMU_GX5_25_Capture::GetEstEulerAnglesY(void)
{
	if(m_pConnection == nullptr)
	{
		return 0.0f;
	}

	return m_fEstEulerAnglesY;
}
