// -*- C++ -*-
/*!
 * @file  RTC_Spider2020_Crawler.cpp
 * @brief Spider2020の台車制御RTC
 * @date $Date$
 *
 * $Id$
 */

#include "RTC_Spider2020_Crawler.h"
#include "SHCommunicator.h"
#include <math.h>

#define DEG_TO_RAD(x)	((M_PI/180)*(x))
#define RAD_TO_DEG(x)	((180/M_PI)*(x))

#define FLIPPER_ANGLE_DEFAULT (DEG_TO_RAD(90))		/*!< フリッパー角度初期値		*/
#define FLIPPER_ANGLE_FILE (".FlipperAngle.txt")	/*!< フリッパー角度保存ファイル	*/

#define MOTOR_FEEDBACK_TIME (40000)		/*!< モータのフィードバックの待ち時間 */

#define CYCLE_THRESHOLD (DEG_TO_RAD(180))	/*!< 外部観測した姿勢の周回判定閾値 */

// timeval構造体の差を計算する(x1-x2)
#define TIMEVAL_DIFF(x1,x2)	(((double)x1.tv_sec + (double)x1.tv_usec/1000000.0) - ((double)x2.tv_sec + (double)x2.tv_usec/1000000.0))

// Module specification
// <rtc-template block="module_spec">
static const char* rtc_spider2020_crawler_spec[] =
{
	"implementation_id", "RTC_Spider2020_Crawler",
	"type_name",         "RTC_Spider2020_Crawler",
	"description",       "Spider2020の台車制御RTC",
	"version",           "2.0.0",
	"vendor",            "AIZUK",
	"category",          "Controller",
	"activity_type",     "PERIODIC",
	"kind",              "DataFlowComponent",
	"max_instance",      "1",
	"language",          "C++",
	"lang_type",         "compile",

	// Configuration variables
	"conf.default.WHEEL_RADIUS", "0.0769",
	"conf.default.PULLEY_RADIUS", "0.0486",
	"conf.default.TURNING_RADIUS", "0.0938",
	"conf.default.SH1_DEVICE_NAME", "/dev/ttyUSB0",
	"conf.default.SH2_DEVICE_NAME", "/dev/ttyUSB1",
	"conf.default.SH3_DEVICE_NAME", "/dev/ttyUSB2",
	"conf.default.SH1_BAUDRATE", "B38400",
	"conf.default.SH2_BAUDRATE", "B38400",
	"conf.default.SH3_BAUDRATE", "B38400",
	"conf.default.MAIN_MOTOR_KP", "0.42",
	"conf.default.MAIN_MOTOR_KI", "4.00",
	"conf.default.MAIN_MOTOR_KD", "0.02",
	"conf.default.VX_GAIN", "1.000",
	"conf.default.VA_GAIN", "1.000",
	"conf.default.MAIN_MOTOR_PULSE", "1000",
	"conf.default.MAIN_MOTOR_GEAR_RATIO", "243",
	"conf.default.SUB_MOTOR_PULSE", "512",
	"conf.default.SUB_MOTOR_GEAR_RATIO", "1080.0",
	"conf.default.R_MAIN_MOTOR_DIRECTION", "1",
	"conf.default.L_MAIN_MOTOR_DIRECTION", "1",
	"conf.default.R_FRONT_SUB_MOTOR_DIRECTION", "1",
	"conf.default.L_FRONT_SUB_MOTOR_DIRECTION", "1",
	"conf.default.R_BACK_SUB_MOTOR_DIRECTION", "1",
	"conf.default.L_BACK_SUB_MOTOR_DIRECTION", "1",
	"conf.default.MAIN_MOTOR_LOAD_GAIN", "7.5",
	"conf.default.MAIN_MOTOR_LOAD_BASE", "2.0",
	"conf.default.SUB_MOTOR_LOAD_GAIN", "7.5",
	"conf.default.SUB_MOTOR_LOAD_BASE", "2.0",
	"conf.default.FAILSAFE_SEC", "1.0",
	"conf.default.USE_ORIENTATION3D_IN", "0",

	// Widget
	"conf.__widget__.WHEEL_RADIUS", "text",
	"conf.__widget__.PULLEY_RADIUS", "text",
	"conf.__widget__.TURNING_RADIUS", "text",
	"conf.__widget__.SH1_DEVICE_NAME", "text",
	"conf.__widget__.SH2_DEVICE_NAME", "text",
	"conf.__widget__.SH3_DEVICE_NAME", "text",
	"conf.__widget__.SH1_BAUDRATE", "text",
	"conf.__widget__.SH2_BAUDRATE", "text",
	"conf.__widget__.SH3_BAUDRATE", "text",
	"conf.__widget__.MAIN_MOTOR_KP", "text",
	"conf.__widget__.MAIN_MOTOR_KI", "text",
	"conf.__widget__.MAIN_MOTOR_KD", "text",
	"conf.__widget__.VX_GAIN", "text",
	"conf.__widget__.VA_GAIN", "text",
	"conf.__widget__.MAIN_MOTOR_PULSE", "text",
	"conf.__widget__.MAIN_MOTOR_GEAR_RATIO", "text",
	"conf.__widget__.SUB_MOTOR_PULSE", "text",
	"conf.__widget__.SUB_MOTOR_GEAR_RATIO", "text",
	"conf.__widget__.R_MAIN_MOTOR_DIRECTION", "text",
	"conf.__widget__.L_MAIN_MOTOR_DIRECTION", "text",
	"conf.__widget__.R_FRONT_SUB_MOTOR_DIRECTION", "text",
	"conf.__widget__.L_FRONT_SUB_MOTOR_DIRECTION", "text",
	"conf.__widget__.R_BACK_SUB_MOTOR_DIRECTION", "text",
	"conf.__widget__.L_BACK_SUB_MOTOR_DIRECTION", "text",
	"conf.__widget__.MAIN_MOTOR_LOAD_GAIN", "text",
	"conf.__widget__.MAIN_MOTOR_LOAD_BASE", "text",
	"conf.__widget__.SUB_MOTOR_LOAD_GAIN", "text",
	"conf.__widget__.SUB_MOTOR_LOAD_BASE", "text",
	"conf.__widget__.FAILSAFE_SEC", "text",
	"conf.__widget__.USE_ORIENTATION3D_IN", "text",

	// Constraints
	"conf.__type__.WHEEL_RADIUS", "double",
	"conf.__type__.PULLEY_RADIUS", "double",
	"conf.__type__.TURNING_RADIUS", "double",
	"conf.__type__.SH1_DEVICE_NAME", "string",
	"conf.__type__.SH2_DEVICE_NAME", "string",
	"conf.__type__.SH3_DEVICE_NAME", "string",
	"conf.__type__.SH1_BAUDRATE", "string",
	"conf.__type__.SH2_BAUDRATE", "string",
	"conf.__type__.SH3_BAUDRATE", "string",
	"conf.__type__.MAIN_MOTOR_KP", "double",
	"conf.__type__.MAIN_MOTOR_KI", "double",
	"conf.__type__.MAIN_MOTOR_KD", "double",
	"conf.__type__.VX_GAIN", "double",
	"conf.__type__.VA_GAIN", "double",
	"conf.__type__.MAIN_MOTOR_PULSE", "long",
	"conf.__type__.MAIN_MOTOR_GEAR_RATIO", "double",
	"conf.__type__.SUB_MOTOR_PULSE", "long",
	"conf.__type__.SUB_MOTOR_GEAR_RATIO", "double",
	"conf.__type__.R_MAIN_MOTOR_DIRECTION", "long",
	"conf.__type__.L_MAIN_MOTOR_DIRECTION", "long",
	"conf.__type__.R_FRONT_SUB_MOTOR_DIRECTION", "long",
	"conf.__type__.L_FRONT_SUB_MOTOR_DIRECTION", "long",
	"conf.__type__.R_BACK_SUB_MOTOR_DIRECTION", "long",
	"conf.__type__.L_BACK_SUB_MOTOR_DIRECTION", "long",
	"conf.__type__.MAIN_MOTOR_LOAD_GAIN", "double",
	"conf.__type__.MAIN_MOTOR_LOAD_BASE", "double",
	"conf.__type__.SUB_MOTOR_LOAD_GAIN", "double",
	"conf.__type__.SUB_MOTOR_LOAD_BASE", "double",
	"conf.__type__.FAILSAFE_SEC", "double",
	"conf.__type__.USE_ORIENTATION3D_IN", "long",

	""
};
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RTC_Spider2020_Crawler::RTC_Spider2020_Crawler(RTC::Manager* manager)
	// <rtc-template block="initializer">
	: RTC::DataFlowComponentBase(manager)
	, m_Mode_InIn("Mode_In", m_Mode_In)
	, m_Velocity2D_InIn("Velocity2D_In", m_Velocity2D_In)
	, m_FlipperPwm_InIn("FlipperPwm_In", m_FlipperPwm_In)
	, m_Orientation3D_InIn("Orientation3D_In", m_Orientation3D_In)
	, m_Pose3D_OutOut("Pose3D_Out", m_Pose3D_Out)
	, m_Velocity2D_OutOut("Velocity2D_Out", m_Velocity2D_Out)
	, m_FlipperAngle_OutOut("FlipperAngle_Out", m_FlipperAngle_Out)
	, m_MotorLoad_OutOut("MotorLoad_Out", m_MotorLoad_Out)

	// </rtc-template>
	, m_Mode_InWrap(m_Mode_In)
	, m_FlipperPwm_InWrap(m_FlipperPwm_In)
	, m_FlipperAngle_OutWrap(m_FlipperAngle_Out)
	, m_MotorLoad_OutWrap(m_MotorLoad_Out)
	, m_stTimeval({0})
	, m_stModeReadTime({0})
	, m_stVelocity2DReadTime({0})
	, m_stFlipperPwmReadTime({0})
{
}

/*!
 * @brief destructor
 */
RTC_Spider2020_Crawler::~RTC_Spider2020_Crawler()
{
}

RTC::ReturnCode_t RTC_Spider2020_Crawler::onInitialize()
{
	// Registration: InPort/OutPort/Service
	// <rtc-template block="registration">
	// Set InPort buffers
	addInPort("Mode_In", m_Mode_InIn);
	addInPort("Velocity2D_In", m_Velocity2D_InIn);
	addInPort("FlipperPwm_In", m_FlipperPwm_InIn);
	addInPort("Orientation3D_In", m_Orientation3D_InIn);

	// Set OutPort buffer
	addOutPort("Pose3D_Out", m_Pose3D_OutOut);
	addOutPort("Velocity2D_Out", m_Velocity2D_OutOut);
	addOutPort("FlipperAngle_Out", m_FlipperAngle_OutOut);
	addOutPort("MotorLoad_Out", m_MotorLoad_OutOut);

	// Set service provider to Ports

	// Set service consumers to Ports

	// Set CORBA Service Ports

	// </rtc-template>

	// <rtc-template block="bind_config">
	// Bind variables and configuration variable
	bindParameter("WHEEL_RADIUS", m_WHEEL_RADIUS, "0.0769");
	bindParameter("PULLEY_RADIUS", m_PULLEY_RADIUS, "0.0486");
	bindParameter("TURNING_RADIUS", m_TURNING_RADIUS, "0.0938");
	bindParameter("SH1_DEVICE_NAME", m_SH1_DEVICE_NAME, "/dev/ttyUSB0");
	bindParameter("SH2_DEVICE_NAME", m_SH2_DEVICE_NAME, "/dev/ttyUSB1");
	bindParameter("SH3_DEVICE_NAME", m_SH3_DEVICE_NAME, "/dev/ttyUSB2");
	bindParameter("SH1_BAUDRATE", m_SH1_BAUDRATE, "B38400");
	bindParameter("SH2_BAUDRATE", m_SH2_BAUDRATE, "B38400");
	bindParameter("SH3_BAUDRATE", m_SH3_BAUDRATE, "B38400");
	bindParameter("MAIN_MOTOR_KP", m_MAIN_MOTOR_KP, "0.42");
	bindParameter("MAIN_MOTOR_KI", m_MAIN_MOTOR_KI, "4.00");
	bindParameter("MAIN_MOTOR_KD", m_MAIN_MOTOR_KD, "0.02");
	bindParameter("VX_GAIN", m_VX_GAIN, "1.000");
	bindParameter("VA_GAIN", m_VA_GAIN, "1.000");
	bindParameter("MAIN_MOTOR_PULSE", m_MAIN_MOTOR_PULSE, "1000");
	bindParameter("MAIN_MOTOR_GEAR_RATIO", m_MAIN_MOTOR_GEAR_RATIO, "243");
	bindParameter("SUB_MOTOR_PULSE", m_SUB_MOTOR_PULSE, "512");
	bindParameter("SUB_MOTOR_GEAR_RATIO", m_SUB_MOTOR_GEAR_RATIO, "1080.0");
	bindParameter("R_MAIN_MOTOR_DIRECTION", m_R_MAIN_MOTOR_DIRECTION, "1");
	bindParameter("L_MAIN_MOTOR_DIRECTION", m_L_MAIN_MOTOR_DIRECTION, "1");
	bindParameter("R_FRONT_SUB_MOTOR_DIRECTION", m_R_FRONT_SUB_MOTOR_DIRECTION, "1");
	bindParameter("L_FRONT_SUB_MOTOR_DIRECTION", m_L_FRONT_SUB_MOTOR_DIRECTION, "1");
	bindParameter("R_BACK_SUB_MOTOR_DIRECTION", m_R_BACK_SUB_MOTOR_DIRECTION, "1");
	bindParameter("L_BACK_SUB_MOTOR_DIRECTION", m_L_BACK_SUB_MOTOR_DIRECTION, "1");
	bindParameter("MAIN_MOTOR_LOAD_GAIN", m_MAIN_MOTOR_LOAD_GAIN, "7.5");
	bindParameter("MAIN_MOTOR_LOAD_BASE", m_MAIN_MOTOR_LOAD_BASE, "2.0");
	bindParameter("SUB_MOTOR_LOAD_GAIN", m_SUB_MOTOR_LOAD_GAIN, "7.5");
	bindParameter("SUB_MOTOR_LOAD_BASE", m_SUB_MOTOR_LOAD_BASE, "2.0");
	bindParameter("FAILSAFE_SEC", m_FAILSAFE_SEC, "1.0");
	bindParameter("USE_ORIENTATION3D_IN", m_USE_ORIENTATION3D_IN, "0");
	// </rtc-template>

	// 動作指令の状態の入力を初期化する
	m_Mode_InWrap.InitData();

	// ２次元の速度の入力を初期化する
	m_Velocity2D_In.data.vx = 0.0;
	m_Velocity2D_In.data.vy = 0.0;
	m_Velocity2D_In.data.va = 0.0;

	// フリッパーのPWM指令を初期化する
	m_FlipperPwm_InWrap.InitData();

	// 外部観測した３次元の姿勢を初期化する
	m_Orientation3D_In.data.r = 0.0;
	m_Orientation3D_In.data.p = 0.0;
	m_Orientation3D_In.data.y = 0.0;

	// オドメトリによる３次元の位置・姿勢の出力を初期化する
	m_Pose3D_Out.data.position.x = 0.0;
	m_Pose3D_Out.data.position.y = 0.0;
	m_Pose3D_Out.data.position.z = 0.0;
	m_Pose3D_Out.data.orientation.r = 0.0;
	m_Pose3D_Out.data.orientation.p = 0.0;
	m_Pose3D_Out.data.orientation.y = 0.0;

	// ２次元の速度の出力を初期化する
	m_Velocity2D_Out.data.vx = 0.0;
	m_Velocity2D_Out.data.vy = 0.0;
	m_Velocity2D_Out.data.va = 0.0;

	// フリッパーの角度を初期化する
	m_FlipperAngle_OutWrap.InitData();

	// モータの負荷を初期化する
	m_MotorLoad_OutWrap.InitData();

	// オドメトリによる３次元の位置姿勢を初期化する
	m_Pose3D_Out.data.position.x = 0.0;
	m_Pose3D_Out.data.position.y = 0.0;
	m_Pose3D_Out.data.position.z = 0.0;
	m_Pose3D_Out.data.orientation.r = 0.0;
	m_Pose3D_Out.data.orientation.p = 0.0;
	m_Pose3D_Out.data.orientation.y = 0.0;

	// メインモータのデータを初期化する
	m_MainMotorProcessor.InitData();

	// 前方サブモータのデータを初期化する
	m_FrontSubMotorProcessor.InitData();

	// 後方サブモータのデータを初期化する
	m_BackSubMotorProcessor.InitData();

	// 外部観測した姿勢の周回数を初期化する
	m_lRollCycle = 0;
	m_lPitchCycle = 0;
	m_lYawCycle = 0;

	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RTC_Spider2020_Crawler::onFinalize()
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Crawler::onStartup(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Crawler::onShutdown(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

RTC::ReturnCode_t RTC_Spider2020_Crawler::onActivated(RTC::UniqueId ec_id)
{
	// メインモータのコンフィグレーションを設定する
	m_MainMotorProcessor.SetConfig(m_TURNING_RADIUS, m_MAIN_MOTOR_KP, m_MAIN_MOTOR_KI, m_MAIN_MOTOR_KD, m_VX_GAIN, m_VA_GAIN);
	m_MainMotorProcessor.SetConfigR(m_R_MAIN_MOTOR_DIRECTION, m_MAIN_MOTOR_PULSE, m_WHEEL_RADIUS, m_MAIN_MOTOR_GEAR_RATIO, m_MAIN_MOTOR_LOAD_GAIN, m_MAIN_MOTOR_LOAD_BASE);
	m_MainMotorProcessor.SetConfigL(m_L_MAIN_MOTOR_DIRECTION, m_MAIN_MOTOR_PULSE, m_WHEEL_RADIUS, m_MAIN_MOTOR_GEAR_RATIO, m_MAIN_MOTOR_LOAD_GAIN, m_MAIN_MOTOR_LOAD_BASE);

	// 前方サブモータのコンフィグレーションを設定する
	m_FrontSubMotorProcessor.SetConfigR(m_R_FRONT_SUB_MOTOR_DIRECTION, m_SUB_MOTOR_PULSE, m_PULLEY_RADIUS, m_SUB_MOTOR_GEAR_RATIO, m_SUB_MOTOR_LOAD_GAIN, m_SUB_MOTOR_LOAD_BASE);
	m_FrontSubMotorProcessor.SetConfigL(m_L_FRONT_SUB_MOTOR_DIRECTION, m_SUB_MOTOR_PULSE, m_PULLEY_RADIUS, m_SUB_MOTOR_GEAR_RATIO, m_SUB_MOTOR_LOAD_GAIN, m_SUB_MOTOR_LOAD_BASE);

	// 後方サブモータのコンフィグレーションを設定する
	m_BackSubMotorProcessor.SetConfigR(m_R_BACK_SUB_MOTOR_DIRECTION, m_SUB_MOTOR_PULSE, m_PULLEY_RADIUS, m_SUB_MOTOR_GEAR_RATIO, m_SUB_MOTOR_LOAD_GAIN, m_SUB_MOTOR_LOAD_BASE);
	m_BackSubMotorProcessor.SetConfigL(m_L_BACK_SUB_MOTOR_DIRECTION, m_SUB_MOTOR_PULSE, m_PULLEY_RADIUS, m_SUB_MOTOR_GEAR_RATIO, m_SUB_MOTOR_LOAD_GAIN, m_SUB_MOTOR_LOAD_BASE);

	// 実行時刻を初期化する(現時刻-1周期分)
	gettimeofday(&m_stTimeval, NULL);
	if(((1.0/getExecutionRate(ec_id))*1000000) <= m_stTimeval.tv_usec)
	{
		m_stTimeval.tv_usec -= (suseconds_t)((1.0/getExecutionRate(ec_id))*1000000);
	}
	else
	{
		m_stTimeval.tv_sec -= 1;
		m_stTimeval.tv_usec += (1000000 - (suseconds_t)((1.0/getExecutionRate(ec_id))*1000000));
	}

	// フリッパーの角度を復元する
	LoadFlipperAngle();

	return RTC::RTC_OK;
}

RTC::ReturnCode_t RTC_Spider2020_Crawler::onDeactivated(RTC::UniqueId ec_id)
{
	SHCommunicator SH1Device;
	SHCommunicator SH2Device;
	SHCommunicator SH3Device;

	// メインモータのフィードバックデータを初期化する
	m_MainMotorProcessor.InitFeedbackData();

	// 前方サブモータのフィードバックデータを初期化する
	m_FrontSubMotorProcessor.InitFeedbackData();

	// 後方サブモータのフィードバックデータを初期化する
	m_BackSubMotorProcessor.InitFeedbackData();

	// メインモータを停止する
	if(SH1Device.Open(m_SH1_DEVICE_NAME, m_SH1_BAUDRATE))
	{
		SH1Device.Send(m_MainMotorProcessor.GenStopCommand());
	}

	// 前方サブモータを停止する
	if(SH2Device.Open(m_SH2_DEVICE_NAME, m_SH2_BAUDRATE))
	{
		SH2Device.Send(m_FrontSubMotorProcessor.GenStopCommand());
	}

	// 後方サブモータを停止する
	if(SH3Device.Open(m_SH3_DEVICE_NAME, m_SH3_BAUDRATE))
	{
		SH3Device.Send(m_BackSubMotorProcessor.GenStopCommand());
	}

	// モータのフィードバックを待つ
	usleep(MOTOR_FEEDBACK_TIME);

	// メインモータのフィードバックを受信して破棄する
	if(SH1Device.IsOpen())
	{
		SH1Device.Recv();
	}

	// 前方サブモータのフィードバックを受信して破棄する
	if(SH2Device.IsOpen())
	{
		SH2Device.Recv();
	}

	// 後方サブモータのフィードバックを受信して破棄する
	if(SH3Device.IsOpen())
	{
		SH3Device.Recv();
	}

	return RTC::RTC_OK;
}

RTC::ReturnCode_t RTC_Spider2020_Crawler::onExecute(RTC::UniqueId ec_id)
{
	SHCommunicator SH1Device;
	SHCommunicator SH2Device;
	SHCommunicator SH3Device;
	struct timeval ti = {0};
	double dFrequency = 0.0;

	// 実行周期を取得する
	gettimeofday(&ti, NULL);
	dFrequency = ((double)ti.tv_sec + (double)(ti.tv_usec/1000000.0)) - ((double)m_stTimeval.tv_sec + (double)(m_stTimeval.tv_usec/1000000.0));
	m_stTimeval = ti;

	// 動作状態をポートから読み込む
	ReadMode();

	// ２次元の速度をポートから読み込む
	ReadVelocity2D();

	// フリッパーのPWM指令をポートから読み込む
	ReadFlipperPwm();

	// 外部観測した３次元の姿勢をポートから読み込む
	ReadOrientation3D();

	// ３次元の位置姿勢及びフリッパーの角度の初期化ＯＮならば初期化する
	if(m_Mode_InWrap.GetCrawlerPoseClear() == ModeWrapper::CRAWLER_POSE_CLEAR_ON)
	{
		// ３次元の位置姿勢を初期化する
		m_MainMotorProcessor.SetPositionX(0.0);
		m_MainMotorProcessor.SetPositionY(0.0);
		m_MainMotorProcessor.SetPositionZ(0.0);
		m_MainMotorProcessor.SetOrientationR(0.0);
		m_MainMotorProcessor.SetOrientationP(0.0);
		m_MainMotorProcessor.SetOrientationY(0.0);

		// フリッパーの角度を初期化する
		m_FrontSubMotorProcessor.SetAngleR(FLIPPER_ANGLE_DEFAULT);
		m_FrontSubMotorProcessor.SetAngleL(FLIPPER_ANGLE_DEFAULT);
		m_BackSubMotorProcessor.SetAngleR(FLIPPER_ANGLE_DEFAULT);
		m_BackSubMotorProcessor.SetAngleL(FLIPPER_ANGLE_DEFAULT);

		// 外部観測した姿勢の周回数を初期化する
		m_lRollCycle = 0;
		m_lPitchCycle = 0;
		m_lYawCycle = 0;
	}

	// メインモータを指定速度で動かす
	if(SH1Device.Open(m_SH1_DEVICE_NAME, m_SH1_BAUDRATE))
	{
		if(!SH1Device.Send(m_MainMotorProcessor.GenMoveCommand(m_Velocity2D_In.data.vx, m_Velocity2D_In.data.vy, m_Velocity2D_In.data.va)))
		{
			printf("SH1 WRITE_ERROR!\n");
		}
	}

	// 前方サブモータを指令PWMで動かす
	if(SH2Device.Open(m_SH2_DEVICE_NAME, m_SH2_BAUDRATE))
	{
		if(!SH2Device.Send(m_FrontSubMotorProcessor.GenMoveCommand(m_FlipperPwm_InWrap.GetFrontRightPwm(),m_FlipperPwm_InWrap.GetFrontLeftPwm())))
		{
			printf("SH2 WRITE ERROR!\n");
		}
	}

	// 後方サブモータを指令PWMで動かす
	if(SH3Device.Open(m_SH3_DEVICE_NAME, m_SH3_BAUDRATE))
	{
		if(!SH3Device.Send(m_BackSubMotorProcessor.GenMoveCommand(m_FlipperPwm_InWrap.GetBackRightPwm(),m_FlipperPwm_InWrap.GetBackLeftPwm())))
		{
			printf("SH3 WRITE ERROR!\n");
		}
	}

	// モータのフィードバックを待つ
	usleep(MOTOR_FEEDBACK_TIME);

	// メインモータのフィードバックを受信する
	if(SH1Device.IsOpen())
	{
		// フィードバックを解析する
		if(!m_MainMotorProcessor.AnalyzeFeedback(dFrequency, m_Velocity2D_In.data.vx, m_Velocity2D_In.data.vy, m_Velocity2D_In.data.va, SH1Device.Recv()))
		{
			printf("SH1 READ ERROR!\n");
		}
		else
		{
			if(m_USE_ORIENTATION3D_IN)
			{
				// モータの回転及びIMUの姿勢から３次元の位置姿勢を求める
				m_MainMotorProcessor.CalcOdometry(m_Orientation3D_In.data.r + DEG_TO_RAD(360)*m_lRollCycle, m_Orientation3D_In.data.p + DEG_TO_RAD(360)*m_lPitchCycle, m_Orientation3D_In.data.y + DEG_TO_RAD(360)*m_lYawCycle, dFrequency);
			}
			else
			{
				// モータの回転から２次元の位置姿勢を求める
				m_MainMotorProcessor.CalcOdometry(dFrequency);
			}
		}
	}

	if(SH2Device.IsOpen())
	{
		// フィードバックを解析する
		if(!m_FrontSubMotorProcessor.AnalyzeFeedback(dFrequency, SH2Device.Recv()))
		{
			printf("SH2 READ ERROR!\n");
		}
	}

	if(SH3Device.IsOpen())
	{
		// フィードバックを解析する
		if(!m_BackSubMotorProcessor.AnalyzeFeedback(dFrequency, SH3Device.Recv()))
		{
			printf("SH3 READ ERROR!\n");
		}
	}

	// オドメトリによる３次元の位置姿勢をポートに出力する
	WritePose3D();

	// ２次元の速度をポートに出力する
	WriteVelocity2D();

	// フリッパーの角度をポートに出力する
	WriteFlipperAngle();

	// フリッパーの角度を保存する
	SaveFlipperAngle();

	// モータの負荷をポートに出力する
	WriteMotorLoad();

	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RTC_Spider2020_Crawler::onAborting(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Crawler::onError(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Crawler::onReset(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Crawler::onStateUpdate(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Crawler::onRateChanged(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

void RTC_Spider2020_Crawler::ReadMode(void)
{
	struct timeval ti = {0};

	// 現在の時刻を取得する
	gettimeofday(&ti, NULL);

	// 動作状態を更新する
	if(m_Mode_InIn.isNew())
	{
		// 読み込み時刻を更新する
		m_stModeReadTime = ti;

		// 次のデータを読み込む
		m_Mode_InIn.read();
	}
	else
	{
		if(m_FAILSAFE_SEC <= TIMEVAL_DIFF(ti,m_stModeReadTime))
		{
			// 最大速度フラグをＯＦＦする(暴走回避)
			m_Mode_InWrap.SetSpeedMax(ModeWrapper::SPEED_MAX_OFF);
		}
	}
}

void RTC_Spider2020_Crawler::ReadVelocity2D(void)
{
	struct timeval ti = {0};

	// 現在の時刻を取得する
	gettimeofday(&ti, NULL);

	// ２次元の速度を更新する
	if(m_Velocity2D_InIn.isNew())
	{
		// 読み込み時刻を更新する
		m_stVelocity2DReadTime = ti;

		// 次のデータを読み込む
		m_Velocity2D_InIn.read();
	}
	else
	{
		if(m_FAILSAFE_SEC <= TIMEVAL_DIFF(ti,m_stVelocity2DReadTime))
		{
			// ２次元の速度の入力を初期化する(暴走回避)
			m_Velocity2D_In.data.vx = 0.0;
			m_Velocity2D_In.data.vy = 0.0;
			m_Velocity2D_In.data.va = 0.0;
		}
	}
}

void RTC_Spider2020_Crawler::ReadFlipperPwm(void)
{
	struct timeval ti = {0};

	// 現在の時刻を取得する
	gettimeofday(&ti, NULL);

	// フリッパーのPWM指令を更新する
	if(m_FlipperPwm_InIn.isNew())
	{
		// 読み込み時刻を更新する
		m_stFlipperPwmReadTime = ti;

		// 次のデータを読み込む
		m_FlipperPwm_InIn.read();
	}
	else
	{
		if(m_FAILSAFE_SEC <= TIMEVAL_DIFF(ti,m_stFlipperPwmReadTime))
		{
			// フリッパーのPWM指令を初期化する(暴走回避)
			m_FlipperPwm_InWrap.InitData();
		}
	}
}

void RTC_Spider2020_Crawler::ReadOrientation3D(void)
{
	double dOldR = 0.0;
	double dOldP = 0.0;
	double dOldY = 0.0;
	double dDiffR = 0.0;
	double dDiffP = 0.0;
	double dDiffY = 0.0;

	// 外部観測した３次元の姿勢を更新する
	if(m_USE_ORIENTATION3D_IN)
	{
		if(m_Orientation3D_InIn.isNew())
		{
			dOldR = m_Orientation3D_In.data.r;
			dOldP = m_Orientation3D_In.data.p;
			dOldY = m_Orientation3D_In.data.y;

			// 次のデータを読み込む
			m_Orientation3D_InIn.read();

			// ロールの周回を更新する
			dDiffR = m_Orientation3D_In.data.r - dOldR;
			if(dDiffR < -CYCLE_THRESHOLD)
			{
				m_lRollCycle++;
			}
			else if(CYCLE_THRESHOLD < dDiffR)
			{
				m_lRollCycle--;
			}

			// ピッチの周回を更新する
			dDiffP = m_Orientation3D_In.data.p - dOldP;
			if(dDiffP < -CYCLE_THRESHOLD)
			{
				m_lPitchCycle++;
			}
			else if(CYCLE_THRESHOLD < dDiffP)
			{
				m_lPitchCycle--;
			}

			// ヨーの周回を更新する
			dDiffY = m_Orientation3D_In.data.y - dOldY;
			if(dDiffY < -CYCLE_THRESHOLD)
			{
				m_lYawCycle++;
			}
			else if(CYCLE_THRESHOLD < dDiffY)
			{
				m_lYawCycle--;
			}
		}
	}
}

void RTC_Spider2020_Crawler::WritePose3D(void)
{
	// オドメトリによる３次元の位置姿勢を取得する
	m_Pose3D_Out.data.position.x = m_MainMotorProcessor.GetPositionX();
	m_Pose3D_Out.data.position.y = m_MainMotorProcessor.GetPositionY();
	m_Pose3D_Out.data.position.z = m_MainMotorProcessor.GetPositionZ();
	m_Pose3D_Out.data.orientation.r = m_MainMotorProcessor.GetOrientationR();
	m_Pose3D_Out.data.orientation.p = m_MainMotorProcessor.GetOrientationP();
	m_Pose3D_Out.data.orientation.y = m_MainMotorProcessor.GetOrientationY();

	// オドメトリによる３次元の位置姿勢をポートに出力する
	setTimestamp(m_Pose3D_Out);
	m_Pose3D_OutOut.write();
}

void RTC_Spider2020_Crawler::WriteVelocity2D(void)
{
	// ２次元の速度を取得する
	m_Velocity2D_Out.data.vx = m_MainMotorProcessor.GetVx();
	m_Velocity2D_Out.data.vy = m_MainMotorProcessor.GetVy();
	m_Velocity2D_Out.data.va = m_MainMotorProcessor.GetVa();

	// ２次元の速度をポートに出力する
	setTimestamp(m_Velocity2D_Out);
	m_Velocity2D_OutOut.write();
}

void RTC_Spider2020_Crawler::WriteFlipperAngle(void)
{
	// フリッパーの角度を更新する
	m_FlipperAngle_OutWrap.SetFrontRightAngle(m_FrontSubMotorProcessor.GetAngleR());
	m_FlipperAngle_OutWrap.SetFrontLeftAngle(m_FrontSubMotorProcessor.GetAngleL());
	m_FlipperAngle_OutWrap.SetBackRightAngle(m_BackSubMotorProcessor.GetAngleR());
	m_FlipperAngle_OutWrap.SetBackLeftAngle(m_BackSubMotorProcessor.GetAngleL());

	// フリッパーの角度をポートに出力する
	m_FlipperAngle_OutWrap.SetTimestamp();
	m_FlipperAngle_OutOut.write();
}

void RTC_Spider2020_Crawler::WriteMotorLoad(void)
{
	// モータの負荷を更新する
	m_MotorLoad_OutWrap.SetRightMotorLoad(m_MainMotorProcessor.GetLoadR());
	m_MotorLoad_OutWrap.SetLeftMotorLoad(m_MainMotorProcessor.GetLoadL());
	m_MotorLoad_OutWrap.SetFrontRightMotorLoad(m_FrontSubMotorProcessor.GetLoadR());
	m_MotorLoad_OutWrap.SetFrontLeftMotorLoad(m_FrontSubMotorProcessor.GetLoadL());
	m_MotorLoad_OutWrap.SetBackRightMotorLoad(m_BackSubMotorProcessor.GetLoadR());
	m_MotorLoad_OutWrap.SetBackLeftMotorLoad(m_BackSubMotorProcessor.GetLoadL());

	// モータの負荷をポートに出力する
	m_MotorLoad_OutWrap.SetTimestamp();
	m_MotorLoad_OutOut.write();
}

void RTC_Spider2020_Crawler::LoadFlipperAngle(void)
{
	std::ifstream ifs(getenv("HOME") + std::string("/") + std::string(FLIPPER_ANGLE_FILE));
	char buff[256 + 1] = {0};
	double dFrontR = 0.0;
	double dFrontL = 0.0;
	double dBackR = 0.0;
	double dBackL = 0.0;

	if(ifs.good())
	{
		if(ifs.getline(buff, (sizeof(buff)/sizeof(buff[0])) - 1))
		{
			if(sscanf(buff, "%lf:%lf:%lf:%lf", &dFrontR, &dFrontL, &dBackR, &dBackL) == 4)
			{
				m_FrontSubMotorProcessor.SetAngleR(dFrontR);
				m_FrontSubMotorProcessor.SetAngleL(dFrontL);
				m_BackSubMotorProcessor.SetAngleR(dBackR);
				m_BackSubMotorProcessor.SetAngleL(dBackL);
				return;
			}
		}
	}
	else
	{
		printf("サブクローラ角度の保存データなし\n");
	}

	m_FrontSubMotorProcessor.SetAngleR(FLIPPER_ANGLE_DEFAULT);
	m_FrontSubMotorProcessor.SetAngleL(FLIPPER_ANGLE_DEFAULT);
	m_BackSubMotorProcessor.SetAngleR(FLIPPER_ANGLE_DEFAULT);
	m_BackSubMotorProcessor.SetAngleL(FLIPPER_ANGLE_DEFAULT);
}

void RTC_Spider2020_Crawler::SaveFlipperAngle(void)
{
	std::ofstream ofs(getenv("HOME") + std::string("/") + std::string(FLIPPER_ANGLE_FILE), std::ios::trunc);

	if(ofs.good())
	{
		ofs << 	m_FrontSubMotorProcessor.GetAngleR()
			<< ":"
			<< m_FrontSubMotorProcessor.GetAngleL()
			<< ":"
			<< m_BackSubMotorProcessor.GetAngleR()
			<< ":"
			<< m_BackSubMotorProcessor.GetAngleL()
			<< std::endl;
	}
}


extern "C"
{
	void RTC_Spider2020_CrawlerInit(RTC::Manager* manager)
	{
		coil::Properties profile(rtc_spider2020_crawler_spec);
		manager->registerFactory(profile, RTC::Create<RTC_Spider2020_Crawler>, RTC::Delete<RTC_Spider2020_Crawler>);
	}
};
