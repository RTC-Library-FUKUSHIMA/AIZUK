// -*- C++ -*-
/*!
 * @file  RTC_IMU_GX5_25.cpp
 * @brief LORD製の3DM-GX5-25から姿勢情報を取得する
 * @date $Date$
 *
 * $Id$
 */

#include "RTC_IMU_GX5_25.h"
#include <Eigen/Geometry>

#define DEG_TO_RAD(x)	((M_PI/180)*(x))
#define RAD_TO_DEG(x)	((180/M_PI)*(x))

#define TIMEVAL_DIFF(x1,x2)	(((double)x1.tv_sec + (double)x1.tv_usec/1000000.0) - ((double)x2.tv_sec + (double)x2.tv_usec/1000000.0))

// Module specification
// <rtc-template block="module_spec">
static const char* rtc_imu_gx5_25_spec[] =
{
	"implementation_id", "RTC_IMU_GX5_25",
	"type_name",         "RTC_IMU_GX5_25",
	"description",       "LORD製の3DM-GX5-25から姿勢情報を取得する",
	"version",           "1.0.0",
	"vendor",            "AIZUK",
	"category",          "Sensor",
	"activity_type",     "PERIODIC",
	"kind",              "DataFlowComponent",
	"max_instance",      "1",
	"language",          "C++",
	"lang_type",         "compile",

	// Configuration variables
	"conf.default.DEVICE_NAME", "/dev/ttyACM0",
	"conf.default.X_ROTATION", "0.0",
	"conf.default.Y_ROTATION", "0.0",
	"conf.default.Z_ROTATION", "0.0",

	// Widget
	"conf.__widget__.DEVICE_NAME", "text",
	"conf.__widget__.X_ROTATION", "text",
	"conf.__widget__.Y_ROTATION", "text",
	"conf.__widget__.Z_ROTATION", "text",

	// Constraints
	"conf.__type__.DEVICE_NAME", "string",
	"conf.__type__.X_ROTATION", "double",
	"conf.__type__.Y_ROTATION", "double",
	"conf.__type__.Z_ROTATION", "double",

	""
};
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RTC_IMU_GX5_25::RTC_IMU_GX5_25(RTC::Manager* manager)
	// <rtc-template block="initializer">
	: RTC::DataFlowComponentBase(manager)
	, m_ResetFilter_InIn("ResetFilter_In", m_ResetFilter_In)
	, m_Acceleration3D_OutOut("Acceleration3D_Out", m_Acceleration3D_Out)
	, m_Orientation3D_OutOut("Orientation3D_Out", m_Orientation3D_Out)

	// </rtc-template>
{
}

/*!
 * @brief destructor
 */
RTC_IMU_GX5_25::~RTC_IMU_GX5_25()
{
}

RTC::ReturnCode_t RTC_IMU_GX5_25::onInitialize()
{
	// Registration: InPort/OutPort/Service
	// <rtc-template block="registration">
	// Set InPort buffers
	addInPort("ResetFilter_In", m_ResetFilter_InIn);

	// Set OutPort buffer
	addOutPort("Acceleration3D_Out", m_Acceleration3D_OutOut);
	addOutPort("Orientation3D_Out", m_Orientation3D_OutOut);

	// Set service provider to Ports

	// Set service consumers to Ports

	// Set CORBA Service Ports

	// </rtc-template>

	// <rtc-template block="bind_config">
	// Bind variables and configuration variable
	bindParameter("DEVICE_NAME", m_DEVICE_NAME, "/dev/ttyACM0");
	bindParameter("X_ROTATION", m_X_ROTATION, "0.0");
	bindParameter("Y_ROTATION", m_Y_ROTATION, "0.0");
	bindParameter("Z_ROTATION", m_Z_ROTATION, "0.0");
	// </rtc-template>

	// フィルタリセットの入力を初期化する
	m_ResetFilter_In.data = 0;

	// ロボットの座標系に合わせた３軸の加速度の出力を初期化する
	m_Acceleration3D_Out.data.ax = 0.0;
	m_Acceleration3D_Out.data.ay = 0.0;
	m_Acceleration3D_Out.data.az = 0.0;

	// ロボットの座標系に合わせた３次元の姿勢の出力を初期化する
	m_Orientation3D_Out.data.r = 0.0;
	m_Orientation3D_Out.data.p = 0.0;
	m_Orientation3D_Out.data.y = 0.0;

	// 前回のフィルタリセット指令を初期化する
	m_lLastResetFilter = 0;

	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RTC_IMU_GX5_25::onFinalize()
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_IMU_GX5_25::onStartup(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_IMU_GX5_25::onShutdown(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t RTC_IMU_GX5_25::onActivated(RTC::UniqueId ec_id)
{
	// シリアルポートを開く
	m_IMUCapture.Open(m_DEVICE_NAME);

	// Estimationフィルタをリセットする
	m_IMUCapture.ResetEstFilter();

	// Estimationフィルタを初期化する
	m_IMUCapture.InitEstFilter(0.0, 0.0, 0.0);

	return RTC::RTC_OK;
}

RTC::ReturnCode_t RTC_IMU_GX5_25::onDeactivated(RTC::UniqueId ec_id)
{
	// シリアルポートを閉じる
	m_IMUCapture.Close();

	return RTC::RTC_OK;
}

RTC::ReturnCode_t RTC_IMU_GX5_25::onExecute(RTC::UniqueId ec_id)
{
	// リセットフィルタ指令をポートから読み込む
	ReadResetFilter();

	// フィルタをリセットする場合
	if((m_lLastResetFilter != 1) && (m_ResetFilter_In.data == 1))
	{
		// Estimationフィルタをリセットする
		m_IMUCapture.ResetEstFilter();

		// Estimationフィルタを初期化する
		m_IMUCapture.InitEstFilter(0.0, 0.0, 0.0);
	}
	// フィルタをリセットしない場合
	else
	{
		// ESTFILTERの加速度をポーリングする
		m_IMUCapture.PollEstLinearAccel();

		// ESTFILTERのオイラー角をポーリングする
		m_IMUCapture.PollEstEulerAngles();
	}
	m_lLastResetFilter = m_ResetFilter_In.data;

	// ３軸の加速度をポートに出力する
	WriteAcceleration3D();

	// ３次元の姿勢をポートに出力する
	WriteOrientation3D();

	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RTC_IMU_GX5_25::onAborting(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_IMU_GX5_25::onError(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_IMU_GX5_25::onReset(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_IMU_GX5_25::onStateUpdate(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_IMU_GX5_25::onRateChanged(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

void RTC_IMU_GX5_25::ReadResetFilter(void)
{
	// リセットフィルタ指令を更新する
	if(m_ResetFilter_InIn.isNew())
	{
		// 次のデータを読み込む
		m_ResetFilter_InIn.read();
	}
}

void RTC_IMU_GX5_25::WriteAcceleration3D(void)
{
	double dLinearAccelX = 0.0;
	double dLinearAccelY = 0.0;
	double dLinearAccelZ = 0.0;
	Eigen::Vector3d vec(3);

	// IMUの加速度を取得する
	dLinearAccelX = m_IMUCapture.GetEstLinearAccelX();
	dLinearAccelY = m_IMUCapture.GetEstLinearAccelY();
	dLinearAccelZ = m_IMUCapture.GetEstLinearAccelZ();

	// IMU座標系の加速度をロボット座標系の加速度に変換する
	vec = Eigen::AngleAxisd(DEG_TO_RAD(m_Z_ROTATION), Eigen::Vector3d::UnitZ())
	    * Eigen::AngleAxisd(DEG_TO_RAD(m_Y_ROTATION), Eigen::Vector3d::UnitY())
	    * Eigen::AngleAxisd(DEG_TO_RAD(m_X_ROTATION), Eigen::Vector3d::UnitX())
		* Eigen::Vector3d(dLinearAccelX, dLinearAccelY, dLinearAccelZ);

	// ロボット座標系の加速度を出力データに設定する
	m_Acceleration3D_Out.data.ax = vec(0);
	m_Acceleration3D_Out.data.ay = vec(1);
	m_Acceleration3D_Out.data.az = vec(2);

	// ロボット座標系の加速度をポートに出力する
	setTimestamp(m_Acceleration3D_Out);
	m_Acceleration3D_OutOut.write();
}

void RTC_IMU_GX5_25::WriteOrientation3D(void)
{
	double dEulerAngleR = 0.0;
	double dEulerAngleP = 0.0;
	double dEulerAngleY = 0.0;
	Eigen::Vector3d vec(3);

	// IMUの加速度を取得する
	dEulerAngleR = m_IMUCapture.GetEstEulerAnglesR();
	dEulerAngleP = m_IMUCapture.GetEstEulerAnglesP();
	dEulerAngleY = m_IMUCapture.GetEstEulerAnglesY();

	// IMU座標系のオイラー角をロボット座標系のオイラー角に変換する
	vec = Eigen::AngleAxisd(DEG_TO_RAD(m_Z_ROTATION), Eigen::Vector3d::UnitZ())
	    * Eigen::AngleAxisd(DEG_TO_RAD(m_Y_ROTATION), Eigen::Vector3d::UnitY())
	    * Eigen::AngleAxisd(DEG_TO_RAD(m_X_ROTATION), Eigen::Vector3d::UnitX())
		* Eigen::Vector3d(dEulerAngleR, dEulerAngleP, dEulerAngleY);

	// ロボット座標系のオイラー角を出力データに設定する
	m_Orientation3D_Out.data.r = vec(0);
	m_Orientation3D_Out.data.p = vec(1);
	m_Orientation3D_Out.data.y = vec(2);

	// ロボット座標系の加速度をポートに出力する
	setTimestamp(m_Orientation3D_Out);
	m_Orientation3D_OutOut.write();
}


extern "C"
{
	void RTC_IMU_GX5_25Init(RTC::Manager* manager)
	{
		coil::Properties profile(rtc_imu_gx5_25_spec);
		manager->registerFactory(profile, RTC::Create<RTC_IMU_GX5_25>, RTC::Delete<RTC_IMU_GX5_25>);
	}
};
