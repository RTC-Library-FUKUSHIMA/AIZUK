// -*- C++ -*-
/*!
 * @file  RTC_Single_Jaco2.cpp
 * @brief １本のJaco2アームを速度指令で制御する
 * @date $Date$
 *
 * $Id$
 */

#include "RTC_Single_Jaco2.h"
#include <dlfcn.h>
#include <math.h>

#include </opt/JACO2_SDK/API/Kinova.API.CommLayerUbuntu.h>
#include </opt/JACO2_SDK/API/KinovaTypes.h>

#define RAD (M_PI/180)

// timeval構造体の差を計算する(x1-x2)
#define TIMEVAL_DIFF(x1,x2)	(((double)x1.tv_sec + (double)x1.tv_usec/1000000.0) - ((double)x2.tv_sec + (double)x2.tv_usec/1000000.0))

int result;

//Handle for the library's command layer.
void * commandLayer_handle;
//Function pointers to the functions we need
int Device_NUM;
int (*ARM_InitAPI)();
int (*ARM_SendBasicTrajectory)(TrajectoryPoint command);
int (*ARM_GetDevices)(KinovaDevice devices[MAX_KINOVA_DEVICE], int &result);
int (*ARM_SetActiveDevice)(KinovaDevice device);
int (*ARM_MoveHome)();
int (*ARM_InitFingers)();
int (*ARM_GetCartesianPosition)(CartesianPosition &);
int (*ARM_GetAngularPosition)(AngularPosition &);
int (*ARM_GetAngularCurrent)(AngularPosition &Response);
int (*ARM_GetGeneralInformations)(GeneralInformations &);

// Module specification
// <rtc-template block="module_spec">
static const char* rtc_single_jaco2_spec[] =
{
	"implementation_id", "RTC_Single_Jaco2",
	"type_name",         "RTC_Single_Jaco2",
	"description",       "１本のJaco2アームを速度指令で制御する",
	"version",           "1.0.0",
	"vendor",            "AIZUK",
	"category",          "Controller",
	"activity_type",     "PERIODIC",
	"kind",              "DataFlowComponent",
	"max_instance",      "1",
	"language",          "C++",
	"lang_type",         "compile",

	// Configuration variables
	"conf.default.FAILSAFE_SEC", "1.0",
	"conf.default.OUT_SEC", "0.2",

	// Widget
	"conf.__widget__.FAILSAFE_SEC", "text",
	"conf.__widget__.OUT_SEC", "text",

	// Constraints
	"conf.__type__.FAILSAFE_SEC", "double",
	"conf.__type__.OUT_SEC", "double",

	""
};
// </rtc-template>

RTC_Single_Jaco2::RTC_Single_Jaco2(RTC::Manager* manager)
	// <rtc-template block="initializer">
	: RTC::DataFlowComponentBase(manager)
	, m_PoseDelta_InIn("PoseDelta_In", m_PoseDelta_In)
	, m_FingerDelta_InIn("FingerDelta_In", m_FingerDelta_In)
	, m_Home_InIn("Home_In", m_Home_In)
	, m_Pose3D_OutOut("Pose3D_Out", m_Pose3D_Out)
	, m_Angular_OutOut("Angular_Out", m_Angular_Out)
	, m_Finger_OutOut("Finger_Out", m_Finger_Out)
	, m_Current_OutOut("Current_Out", m_Current_Out)

	// </rtc-template>
	, m_FingerDelta_InWrap(m_FingerDelta_In)
	, m_Angular_OutWrap(m_Angular_Out)
	, m_Current_OutWrap(m_Current_Out)
	, m_Finger_OutWrap(m_Finger_Out)
	, m_stPoseDeltaReadTime({0})
	, m_stFingerDeltaReadTime({0})
	, m_stInfoWriteTime({0})
{
}

RTC_Single_Jaco2::~RTC_Single_Jaco2()
{
}

RTC::ReturnCode_t RTC_Single_Jaco2::onInitialize()
{
	// Registration: InPort/OutPort/Service
	// <rtc-template block="registration">
	// Set InPort buffers
	addInPort("PoseDelta_In", m_PoseDelta_InIn);
	addInPort("FingerDelta_In", m_FingerDelta_InIn);
	addInPort("Home_In", m_Home_InIn);

	// Set OutPort buffer
	addOutPort("Pose3D_Out", m_Pose3D_OutOut);
	addOutPort("Angular_Out", m_Angular_OutOut);
	addOutPort("Finger_Out", m_Finger_OutOut);
	addOutPort("Current_Out", m_Current_OutOut);

	// Set service provider to Ports

	// Set service consumers to Ports

	// Set CORBA Service Ports

	// </rtc-template>

	// <rtc-template block="bind_config">
	// Bind variables and configuration variable
	bindParameter("FAILSAFE_SEC", m_FAILSAFE_SEC, "1.0");
	bindParameter("OUT_SEC", m_OUT_SEC, "0.2");
	// </rtc-template>

	// 手先位置姿勢の変位速度の入力を初期化する
	m_PoseDelta_In.data.position.x = 0.0;
	m_PoseDelta_In.data.position.y = 0.0;
	m_PoseDelta_In.data.position.z = 0.0;
	m_PoseDelta_In.data.orientation.r = 0.0;
	m_PoseDelta_In.data.orientation.p = 0.0;
	m_PoseDelta_In.data.orientation.y = 0.0;

	// 指の開閉具合の変位速度の入力を初期化する
	m_FingerDelta_InWrap.InitData();

	// 初期姿勢遷移指令の入力を初期化する
	m_Home_In.data = 0;

	// 手先位置姿勢の出力を初期化する
	m_Pose3D_Out.data.position.x = 0.0;
	m_Pose3D_Out.data.position.y = 0.0;
	m_Pose3D_Out.data.position.z = 0.0;
	m_Pose3D_Out.data.orientation.r = 0.0;
	m_Pose3D_Out.data.orientation.p = 0.0;
	m_Pose3D_Out.data.orientation.y = 0.0;

	// 腕の角度の出力を初期化する
	m_Angular_OutWrap.InitData();

	// 指の開閉具合の出力を初期化する
	m_Finger_OutWrap.InitData();

	// モータ負荷の出力を初期化する
	m_Current_OutWrap.InitData();

	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RTC_Single_Jaco2::onFinalize()
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Single_Jaco2::onStartup(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Single_Jaco2::onShutdown(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t RTC_Single_Jaco2::onActivated(RTC::UniqueId ec_id)
{
	KinovaDevice list[MAX_KINOVA_DEVICE];

	// KinovaAPIライブラリを読み込む
	commandLayer_handle = dlopen("Kinova.API.USBCommandLayerUbuntu.so",RTLD_NOW|RTLD_GLOBAL);

	// 初期化APIの関数アドレスを取得する
	ARM_InitAPI = (int (*)()) dlsym(commandLayer_handle,"InitAPI");

	// ホームポジション移動APIの関数アドレスを取得する
	ARM_MoveHome = (int (*)()) dlsym(commandLayer_handle,"MoveHome");

	// 角度制御モード設定APIの関数アドレスを取得する
	ARM_InitFingers = (int (*)()) dlsym(commandLayer_handle,"InitFingers");

	// デバイス一覧取得APIの関数アドレスを取得する
	ARM_GetDevices = (int (*)(KinovaDevice devices[MAX_KINOVA_DEVICE], int &result)) dlsym(commandLayer_handle,"GetDevices");

	// カレントデバイス設定APIの関数アドレスを取得する
	ARM_SetActiveDevice = (int (*)(KinovaDevice devices)) dlsym(commandLayer_handle,"SetActiveDevice");

	// 手先位置姿勢設定APIの関数アドレスを取得する
	ARM_SendBasicTrajectory = (int (*)(TrajectoryPoint)) dlsym(commandLayer_handle,"SendBasicTrajectory");

	// 手先位置姿勢取得APIの関数アドレスを取得する
	ARM_GetCartesianPosition = (int (*)(CartesianPosition &)) dlsym(commandLayer_handle,"GetCartesianPosition");

	// 全てのアクチュエータの角度取得APIの関数アドレスを取得する
	ARM_GetAngularPosition = (int (*)(AngularPosition &)) dlsym(commandLayer_handle,"GetAngularPosition");

	// 全てのアクチュエータの負荷取得APIの関数アドレスを取得する
	ARM_GetAngularCurrent = (int (*)(AngularPosition &Response)) dlsym(commandLayer_handle,"GetAngularCurrent");

	// ロボットアームの汎用情報取得APIの関数アドレスを取得する
	ARM_GetGeneralInformations = (int (*)(GeneralInformations &)) dlsym(commandLayer_handle,"GetGeneralInformations");

	if((ARM_InitAPI == NULL)
	|| (ARM_MoveHome == NULL)
	|| (ARM_InitFingers == NULL)
	|| (ARM_GetDevices == NULL)
	|| (ARM_SetActiveDevice == NULL)
	|| (ARM_SendBasicTrajectory == NULL)
	|| (ARM_GetCartesianPosition == NULL)
	|| (ARM_GetAngularPosition == NULL)
	|| (ARM_GetAngularCurrent == NULL)
	|| (ARM_GetGeneralInformations == NULL))
	{
		std::cout << "Init Fail" << std::endl;
		return RTC::RTC_ERROR;
	}
	else
	{
		std::cout << "Init" << std::endl;
		result = ARM_InitAPI();
		Device_NUM = ARM_GetDevices(list, result);
		std::cout << "Device NUM: " << Device_NUM << std::endl;

		// Jaco2アーム未検出の場合、初期化は失敗
		if(Device_NUM < 1)
		{
			std::cout << "device is not detected" << std::endl;
			return RTC::RTC_ERROR;
		}
	}

	// Jaco2アームを初期姿勢に設定する
	ARM_SetActiveDevice(list[0]);
	ARM_InitFingers();
	ARM_MoveHome();

	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RTC_Single_Jaco2::onDeactivated(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t RTC_Single_Jaco2::onExecute(RTC::UniqueId ec_id)
{
	KinovaDevice list[MAX_KINOVA_DEVICE];
	TrajectoryPoint TargetPoint;
	struct timeval ti = {0};

	// 手先位置姿勢の変位速度をポートから読み込む
	ReadPoseDelta();

	// 指の開閉具合の変位速度をポートから読み込む
	ReadFingerDelta();

	// 初期姿勢遷移指令をポートから読み込む
	ReadHome();

	// Jaco2アームのデバイスリストを取得する
	Device_NUM = ARM_GetDevices(list, result);

	// １本目のJaco2アームをカレント設定する
	ARM_SetActiveDevice(list[0]);

	// 初期姿勢に戻す場合
	if(m_Home_In.data == 1)
	{
		ARM_MoveHome();
	}
	// 姿勢制御を処理する場合
	else
	{
		// 手先位置姿勢設定の構造体初期化
		TargetPoint.InitStruct();

		// 手先位置姿勢設定の制御方法を速度制御に設定
		TargetPoint.Position.Type = CARTESIAN_VELOCITY;

		// 手先位置姿勢設定の手先位置姿勢の速度を設定
		TargetPoint.Position.CartesianPosition.X = m_PoseDelta_In.data.position.x;
		TargetPoint.Position.CartesianPosition.Y = m_PoseDelta_In.data.position.y;
		TargetPoint.Position.CartesianPosition.Z = m_PoseDelta_In.data.position.z;
		TargetPoint.Position.CartesianPosition.ThetaX = m_PoseDelta_In.data.orientation.r;
		TargetPoint.Position.CartesianPosition.ThetaY = m_PoseDelta_In.data.orientation.p;
		TargetPoint.Position.CartesianPosition.ThetaZ = m_PoseDelta_In.data.orientation.y;

		// 手先位置姿勢設定の指先の速度を設定
		TargetPoint.Position.Fingers.Finger1 = m_FingerDelta_InWrap.GetThumbDelta();
		TargetPoint.Position.Fingers.Finger2 = m_FingerDelta_InWrap.GetIndexFingerDelta();
		TargetPoint.Position.Fingers.Finger3 = m_FingerDelta_InWrap.GetMiddleFingerDelta();

		// １本目のJaco2アームの手先位置姿勢を設定する
		ARM_SendBasicTrajectory(TargetPoint);
	}

	// 現在の時刻を取得する
	gettimeofday(&ti, NULL);

	// 前回の出力時間からOUT_SEC経過していれば情報を出力する
	if(m_OUT_SEC <= TIMEVAL_DIFF(ti,m_stInfoWriteTime))
	{
		// 書き込み時刻を更新する
		m_stInfoWriteTime = ti;

		// 手先位置姿勢ををポートに出力する
		WritePose3D();

		// 腕の角度をポートに出力する
		WriteAngular();

		// 指の開閉具合をポートに出力する
		WriteFinger();

		// モータ負荷をポートに出力する
		WriteCurrent();
	}

	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RTC_Single_Jaco2::onAborting(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Single_Jaco2::onError(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Single_Jaco2::onReset(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Single_Jaco2::onStateUpdate(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Single_Jaco2::onRateChanged(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

void RTC_Single_Jaco2::ReadPoseDelta(void)
{
	struct timeval ti = {0};

	// 現在の時刻を取得する
	gettimeofday(&ti, NULL);

	// 手先位置姿勢の変位速度を更新する
	if(m_PoseDelta_InIn.isNew())
	{
		// 読み込み時刻を更新する
		m_stPoseDeltaReadTime = ti;

		// 次のデータを読み込む
		m_PoseDelta_InIn.read();
	}
	else
	{
		if(m_FAILSAFE_SEC <= TIMEVAL_DIFF(ti,m_stPoseDeltaReadTime))
		{
			// 手先位置姿勢の変位速度の入力を初期化する(暴走回避)
			m_PoseDelta_In.data.position.x = 0.0;
			m_PoseDelta_In.data.position.y = 0.0;
			m_PoseDelta_In.data.position.z = 0.0;
			m_PoseDelta_In.data.orientation.r = 0.0;
			m_PoseDelta_In.data.orientation.p = 0.0;
			m_PoseDelta_In.data.orientation.y = 0.0;
		}
	}
}

void RTC_Single_Jaco2::ReadFingerDelta(void)
{
	struct timeval ti = {0};

	// 現在の時刻を取得する
	gettimeofday(&ti, NULL);

	// 指の開閉具合の変位速度を更新する
	if(m_FingerDelta_InIn.isNew())
	{
		// 読み込み時刻を更新する
		m_stFingerDeltaReadTime = ti;

		// 次のデータを読み込む
		m_FingerDelta_InIn.read();
	}
	else
	{
		if(m_FAILSAFE_SEC <= TIMEVAL_DIFF(ti,m_stFingerDeltaReadTime))
		{
			// 指の開閉具合の変位速度の入力を初期化する(暴走回避)
			m_FingerDelta_InWrap.InitData();
		}
	}
}

void RTC_Single_Jaco2::ReadHome(void)
{
	// 初期姿勢遷移指令を更新する
	if(m_Home_InIn.isNew())
	{
		// 次のデータを読み込む
		m_Home_InIn.read();
	}
}

void RTC_Single_Jaco2::WritePose3D(void)
{
	CartesianPosition getPosition;

	// 手先位置姿勢を取得する
	ARM_GetCartesianPosition(getPosition);

	// 出力データを更新する
	m_Pose3D_Out.data.position.x = getPosition.Coordinates.X;
	m_Pose3D_Out.data.position.y = getPosition.Coordinates.Y;
	m_Pose3D_Out.data.position.z = getPosition.Coordinates.Z;
	m_Pose3D_Out.data.orientation.p = getPosition.Coordinates.ThetaX;
	m_Pose3D_Out.data.orientation.r = getPosition.Coordinates.ThetaY;
	m_Pose3D_Out.data.orientation.y = getPosition.Coordinates.ThetaZ;

	// ポートに書き込む
	setTimestamp(m_Pose3D_Out);
	m_Pose3D_OutOut.write();
}

void RTC_Single_Jaco2::WriteAngular(void)
{
	AngularPosition CurrentData;

	// 腕の角度を取得する
	ARM_GetAngularPosition(CurrentData);

	// 腕の角度を更新する
	m_Angular_OutWrap.SetShoulderAngular(CurrentData.Actuators.Actuator1*RAD);
	m_Angular_OutWrap.SetArmAngular(CurrentData.Actuators.Actuator2*RAD);
	m_Angular_OutWrap.SetForearmAngular(CurrentData.Actuators.Actuator3*RAD);
	m_Angular_OutWrap.SetWrist1Angular(CurrentData.Actuators.Actuator4*RAD);
	m_Angular_OutWrap.SetWrist2Angular(CurrentData.Actuators.Actuator5*RAD);
	m_Angular_OutWrap.SetHandAngular(CurrentData.Actuators.Actuator6*RAD);

	// ポートに書き込む
	m_Angular_OutWrap.SetTimestamp();
	m_Angular_OutOut.write();
}

void RTC_Single_Jaco2::WriteFinger(void)
{
	AngularPosition CurrentData;

	// 指の開閉具合を取得する
	ARM_GetAngularPosition(CurrentData);

	// 指の開閉具合を更新する
	m_Finger_OutWrap.SetThumbStatus(CurrentData.Fingers.Finger1);
	m_Finger_OutWrap.SetIndexFingerStatus(CurrentData.Fingers.Finger2);
	m_Finger_OutWrap.SetMiddleFingerStatus(CurrentData.Fingers.Finger3);

	// ポートに書き込む
	m_Finger_OutWrap.SetTimestamp();
	m_Finger_OutOut.write();
}

void RTC_Single_Jaco2::WriteCurrent(void)
{
	AngularPosition CurrentData;

	// モータ負荷を取得する
	ARM_GetAngularPosition(CurrentData);

	// モータ負荷を更新する
	m_Current_OutWrap.SetShoulderCurrent(CurrentData.Actuators.Actuator1);
	m_Current_OutWrap.SetArmCurrent(CurrentData.Actuators.Actuator2);
	m_Current_OutWrap.SetForearmCurrent(CurrentData.Actuators.Actuator3);
	m_Current_OutWrap.SetWrist1Current(CurrentData.Actuators.Actuator4);
	m_Current_OutWrap.SetWrist2Current(CurrentData.Actuators.Actuator5);
	m_Current_OutWrap.SetHandCurrent(CurrentData.Actuators.Actuator6);
	m_Current_OutWrap.SetThumbCurrent(CurrentData.Fingers.Finger1);
	m_Current_OutWrap.SetIndexFingerCurrent(CurrentData.Fingers.Finger2);
	m_Current_OutWrap.SetMiddleFingerCurrent(CurrentData.Fingers.Finger3);

	// ポートに書き込む
	m_Current_OutWrap.SetTimestamp();
	m_Current_OutOut.write();
}


extern "C"
{
	void RTC_Single_Jaco2Init(RTC::Manager* manager)
	{
		coil::Properties profile(rtc_single_jaco2_spec);
		manager->registerFactory(profile, RTC::Create<RTC_Single_Jaco2>, RTC::Delete<RTC_Single_Jaco2>);
	}
};
