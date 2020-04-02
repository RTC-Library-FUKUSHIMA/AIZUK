// -*- C++ -*-
/*!
 * @file  RTC_Spider2020_Log.cpp
 * @brief Spider2020 ログ出力RTC
 * @date $Date$
 *
 * $Id$
 */

#include "RTC_Spider2020_Log.h"
#include <float.h>
#include <stdint.h>
#include <sys/stat.h>

// ログファイル
#define LOG_DIR			("LOGS")			// ログフォルダ名
#define LOG_DIR_MODE	(0775)				// ログフォルダパーミッション
#define LOG_FILE		("Spider2020_Log")	// ログファイル名
#define LOG_FILE_EXT	("csv")				// ログファイル拡張子

// CSVの区切り文字
#define CSV_DIV (",")		// カンマ文字

// ダミー値
#define DUMMY_DBL_VALUE		(1.79769e+308)	// (≒DUMMY_DBL_VALUE)
#define DUMMY_LONG_VALUE	(2147483647)	// (=DUMMY_LONG_VALUE)

// Module specification
// <rtc-template block="module_spec">
static const char* rtc_spider2020_log_spec[] =
{
	"implementation_id", "RTC_Spider2020_Log",
	"type_name",         "RTC_Spider2020_Log",
	"description",       "Spider2020 ログ出力RTC",
	"version",           "2.0.0",
	"vendor",            "AIZUK",
	"category",          "Controller",
	"activity_type",     "PERIODIC",
	"kind",              "DataFlowComponent",
	"max_instance",      "1",
	"language",          "C++",
	"lang_type",         "compile",

	// Configuration variables
	"conf.default.ID", "spider2020",

	// Widget
	"conf.__widget__.ID", "text",

	// Constraints
	"conf.__type__.ID", "string",

	""
};
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RTC_Spider2020_Log::RTC_Spider2020_Log(RTC::Manager* manager)
	// <rtc-template block="initializer">
	: RTC::DataFlowComponentBase(manager)
	, m_Pose3D_InIn("Pose3D_In", m_Pose3D_In)
	, m_MotorLoad_InIn("MotorLoad_In", m_MotorLoad_In)
	, m_FlipperAngle_InIn("FlipperAngle_In", m_FlipperAngle_In)
	, m_IMU_Orientation3D_InIn("IMU_Orientation3D_In", m_IMU_Orientation3D_In)
	, m_Velocity2D_InIn("Velocity2D_In", m_Velocity2D_In)
	, m_GCCapacityRatio_InIn("GCCapacityRatio_In", m_GCCapacityRatio_In)
	, m_GCAxis_InIn("GCAxis_In", m_GCAxis_In)
	, m_GCButton_InIn("GCButton_In", m_GCButton_In)
	, m_MainCapacityRatio_InIn("MainCapacityRatio_In", m_MainCapacityRatio_In)
	, m_Mode_InIn("Mode_In", m_Mode_In)
	, m_Arm1Pose3D_InIn("Arm1Pose3D_In", m_Arm1Pose3D_In)
	, m_Arm1Angular_InIn("Arm1Angular_In", m_Arm1Angular_In)
	, m_Arm1Finger_InIn("Arm1Finger_In", m_Arm1Finger_In)
	, m_Arm1Current_InIn("Arm1Current_In", m_Arm1Current_In)
	, m_RobotID_OutOut("RobotID_Out", m_RobotID_Out)
	, m_Pose3D_OutOut("Pose3D_Out", m_Pose3D_Out)
	, m_MotorLoad_OutOut("MotorLoad_Out", m_MotorLoad_Out)
	, m_FlipperAngle_OutOut("FlipperAngle_Out", m_FlipperAngle_Out)
	, m_IMU_Orientation3D_OutOut("IMU_Orientation3D_Out", m_IMU_Orientation3D_Out)
	, m_Velocity2D_OutOut("Velocity2D_Out", m_Velocity2D_Out)
	, m_GCCapacityRatio_OutOut("GCCapacityRatio_Out", m_GCCapacityRatio_Out)
	, m_GCAxis_OutOut("GCAxis_Out", m_GCAxis_Out)
	, m_GCButton_OutOut("GCButton_Out", m_GCButton_Out)
	, m_MainCapacityRatio_OutOut("MainCapacityRatio_Out", m_MainCapacityRatio_Out)
	, m_Mode_OutOut("Mode_Out", m_Mode_Out)
	, m_Arm1Pose3D_OutOut("Arm1Pose3D_Out", m_Arm1Pose3D_Out)
	, m_Arm1Angular_OutOut("Arm1Angular_Out", m_Arm1Angular_Out)
	, m_Arm1Finger_OutOut("Arm1Finger_Out", m_Arm1Finger_Out)
	, m_Arm1Current_OutOut("Arm1Current_Out", m_Arm1Current_Out)

	// </rtc-template>
	, m_MotorLoad_InWrap(m_MotorLoad_In)
	, m_FlipperAngle_InWrap(m_FlipperAngle_In)
	, m_Mode_InWrap(m_Mode_In)
	, m_GCAxis_InWrap(m_GCAxis_In)
	, m_GCButton_InWrap(m_GCButton_In)
	, m_Arm1Angular_InWrap(m_Arm1Angular_In)
	, m_Arm1Finger_InWrap(m_Arm1Finger_In)
	, m_Arm1Current_InWrap(m_Arm1Current_In)
	, m_MotorLoad_OutWrap(m_MotorLoad_Out)
	, m_FlipperAngle_OutWrap(m_FlipperAngle_Out)
	, m_Mode_OutWrap(m_Mode_Out)
	, m_GCAxis_OutWrap(m_GCAxis_Out)
	, m_GCButton_OutWrap(m_GCButton_Out)
	, m_Arm1Angular_OutWrap(m_Arm1Angular_Out)
	, m_Arm1Finger_OutWrap(m_Arm1Finger_Out)
	, m_Arm1Current_OutWrap(m_Arm1Current_Out)
{
}

/*!
 * @brief destructor
 */
RTC_Spider2020_Log::~RTC_Spider2020_Log()
{
}

RTC::ReturnCode_t RTC_Spider2020_Log::onInitialize()
{
	// Registration: InPort/OutPort/Service
	// <rtc-template block="registration">
	// Set InPort buffers
	addInPort("Pose3D_In", m_Pose3D_InIn);
	addInPort("MotorLoad_In", m_MotorLoad_InIn);
	addInPort("FlipperAngle_In", m_FlipperAngle_InIn);
	addInPort("IMU_Orientation3D_In", m_IMU_Orientation3D_InIn);
	addInPort("Velocity2D_In", m_Velocity2D_InIn);
	addInPort("GCCapacityRatio_In", m_GCCapacityRatio_InIn);
	addInPort("GCAxis_In", m_GCAxis_InIn);
	addInPort("GCButton_In", m_GCButton_InIn);
	addInPort("MainCapacityRatio_In", m_MainCapacityRatio_InIn);
	addInPort("Mode_In", m_Mode_InIn);
	addInPort("Arm1Pose3D_In", m_Arm1Pose3D_InIn);
	addInPort("Arm1Angular_In", m_Arm1Angular_InIn);
	addInPort("Arm1Finger_In", m_Arm1Finger_InIn);
	addInPort("Arm1Current_In", m_Arm1Current_InIn);

	// Set OutPort buffer
	addOutPort("RobotID_Out", m_RobotID_OutOut);
	addOutPort("Pose3D_Out", m_Pose3D_OutOut);
	addOutPort("MotorLoad_Out", m_MotorLoad_OutOut);
	addOutPort("FlipperAngle_Out", m_FlipperAngle_OutOut);
	addOutPort("IMU_Orientation3D_Out", m_IMU_Orientation3D_OutOut);
	addOutPort("Velocity2D_Out", m_Velocity2D_OutOut);
	addOutPort("GCCapacityRatio_Out", m_GCCapacityRatio_OutOut);
	addOutPort("GCAxis_Out", m_GCAxis_OutOut);
	addOutPort("GCButton_Out", m_GCButton_OutOut);
	addOutPort("MainCapacityRatio_Out", m_MainCapacityRatio_OutOut);
	addOutPort("Mode_Out", m_Mode_OutOut);
	addOutPort("Arm1Pose3D_Out", m_Arm1Pose3D_OutOut);
	addOutPort("Arm1Angular_Out", m_Arm1Angular_OutOut);
	addOutPort("Arm1Finger_Out", m_Arm1Finger_OutOut);
	addOutPort("Arm1Current_Out", m_Arm1Current_OutOut);

	// Set service provider to Ports

	// Set service consumers to Ports

	// Set CORBA Service Ports

	// </rtc-template>

	// <rtc-template block="bind_config">
	// Bind variables and configuration variable
	bindParameter("ID", m_ID, "spider2020");
	// </rtc-template>

	// モータの負荷の入力を初期化する
	m_MotorLoad_InWrap.InitData();

	// フリッパーの角度の入力を初期化する
	m_FlipperAngle_InWrap.InitData();

	// 動作指令の状態の入力を初期化する
	m_Mode_InWrap.InitData();

	// 軸キーの入力具合の入力を初期化する
	m_GCAxis_InWrap.InitData();

	// ボタンの押下状態の入力を初期化する
	m_GCButton_InWrap.InitData();

	// Jaco2アーム(１本目)の腕の角度の入力を初期化する
	m_Arm1Angular_InWrap.InitData();

	// Jaco2アーム(１本目)の指の開閉具合の出力を初期化する
	m_Arm1Finger_InWrap.InitData();

	// Jaco2アーム(１本目)のモータ負荷の出力を初期化する
	m_Arm1Current_InWrap.InitData();

	// モータの負荷の出力を初期化する
	m_MotorLoad_OutWrap.InitData();

	// フリッパーの角度の出力を初期化する
	m_FlipperAngle_OutWrap.InitData();

	// 動作指令の状態の出力を初期化する
	m_Mode_OutWrap.InitData();

	// 軸キーの入力具合の出力を初期化する
	m_GCAxis_OutWrap.InitData();

	// ボタンの押下状態の出力を初期化する
	m_GCButton_OutWrap.InitData();

	// Jaco2アーム(１本目)の腕の角度の出力を初期化する
	m_Arm1Angular_OutWrap.InitData();

	// Jaco2アーム(１本目)の指の開閉具合の出力を初期化する
	m_Arm1Finger_OutWrap.InitData();

	// Jaco2アーム(１本目)のモータ負荷の出力を初期化する
	m_Arm1Current_OutWrap.InitData();

	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RTC_Spider2020_Log::onFinalize()
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Log::onStartup(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Log::onShutdown(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

RTC::ReturnCode_t RTC_Spider2020_Log::onActivated(RTC::UniqueId ec_id)
{
	struct timeval myTime;
	struct tm *time_st = NULL;
	char str[512] = {0};
	int i = 0;

	// ログファイル出力ディレクトリを作成する
	mkdir(LOG_DIR, LOG_DIR_MODE);

	// 現在時刻を取得してログファイル名を作成する
	gettimeofday(&myTime, NULL);
	time_st = localtime(&myTime.tv_sec);
	sprintf(str, "%s/%s_%04d%02d%02d%02d%02d%02d.%s",
		LOG_DIR,
		LOG_FILE,
		time_st->tm_year + 1900,
		time_st->tm_mon + 1,
		time_st->tm_mday,
		time_st->tm_hour,
		time_st->tm_min,
		time_st->tm_sec,
	 	LOG_FILE_EXT);

	// ログファイルを開く
	m_Logout_Robot.open(str, std::ios::out);

	// 浮動小数点数型の小数点を常に出力する
	m_Logout_Robot << std::showpoint;

	// ロボット識別子のヘッダーをログファイルに出力する
	OutputRobotIDHeaders();

	// ３次元の位置姿勢のヘッダーをログファイルに出力する
	OutputPose3DHeaders();

	// モータの負荷のヘッダーをログファイルに出力する
	OutputMotorLoadHeaders();

	// フリッパーの角度のヘッダーをログファイルに出力する
	OutputFlipperAngleHeaders();

	// ３次元の姿勢(IMU)のヘッダーをログファイルに出力する
	OutputIMUOrientation3DHeaders();

	// メインクローラの速度のヘッダーをログファイルに出力する
	OutputVelocity2DHeaders();

	// ゲームコントローラのバッテリ残容量比のヘッダーをログファイルに出力する
	OutputGCCapacityRatioHeaders();

	// ゲームコントローラの軸キーの入力具合のヘッダーをログファイルに出力する
	OutputGCAxisHeaders();

	// ゲームコントローラのボタンの押下状態のヘッダーをログファイルに出力する
	OutputGCButtonHeaders();

	// メインバッテリのバッテリ残容量比のヘッダーをログファイルに出力する
	OutputMainCapacityRatioHeaders();

	// 動作指令の状態のヘッダーをログファイルに出力する
	OutputModeHeaders();

	// Jaco2アーム(１本目)の３次元の位置姿勢のヘッダーをログファイルに出力する
	OutputArm1Pose3DHeaders();

	// Jaco2アーム(１本目)の腕の角度のヘッダーをログファイルに出力する
	OutputArm1AngularHeaders();

	// Jaco2アーム(１本目)の指の開閉具合のヘッダーをログファイルに出力する
	OutputArm1FingerHeaders();

	// Jaco2アーム(１本目)のモータ負荷のヘッダーをログファイルに出力する
	OutputArm1CurrentHeaders();

	// ログファイルに改行を出力する
	m_Logout_Robot << std::endl;

	// ３次元の位置姿勢の入力値を初期化する
	m_Pose3D_In.data.position.x = DUMMY_DBL_VALUE;
	m_Pose3D_In.data.position.y = DUMMY_DBL_VALUE;
	m_Pose3D_In.data.position.z = DUMMY_DBL_VALUE;
	m_Pose3D_In.data.orientation.r = DUMMY_DBL_VALUE;
	m_Pose3D_In.data.orientation.p = DUMMY_DBL_VALUE;
	m_Pose3D_In.data.orientation.y = DUMMY_DBL_VALUE;

	// モータの負荷の入力値を初期化する
	for(i = 0; i < m_MotorLoad_In.data.length(); i++)
	{
		m_MotorLoad_In.data[i] = DUMMY_DBL_VALUE;
	}

	// フリッパーの角度の入力値を初期化する
	for(i = 0; i < m_FlipperAngle_In.data.length(); i++)
	{
		m_FlipperAngle_In.data[i] = DUMMY_DBL_VALUE;
	}

	// ３次元の姿勢(IMU)の入力値を初期化する
	m_IMU_Orientation3D_In.data.r = DUMMY_DBL_VALUE;
	m_IMU_Orientation3D_In.data.p = DUMMY_DBL_VALUE;
	m_IMU_Orientation3D_In.data.y = DUMMY_DBL_VALUE;

	// メインクローラの速度の入力値を初期化する
	m_Velocity2D_In.data.vx = DUMMY_DBL_VALUE;
	m_Velocity2D_In.data.vy = DUMMY_DBL_VALUE;
	m_Velocity2D_In.data.va = DUMMY_DBL_VALUE;

	// ゲームコントローラのバッテリ残容量比の入力値を初期化する
	m_GCCapacityRatio_In.data = DUMMY_DBL_VALUE;

	// ゲームコントローラの軸キーの入力具合のヘッダーをログファイルに出力する
	for(i = 0; i < m_GCAxis_In.data.length(); i++)
	{
		m_GCAxis_In.data[i] = DUMMY_DBL_VALUE;
	}

	// ゲームコントローラのボタンの押下状態のヘッダーをログファイルに出力する
	m_GCButton_In.data = DUMMY_LONG_VALUE;

	// メインバッテリのバッテリ残容量比の入力値を初期化する
	m_MainCapacityRatio_In.data = DUMMY_DBL_VALUE;

	// 動作指令の状態の入力値を初期化する
	for(i = 0; i < m_Mode_In.data.length(); i++)
	{
		m_Mode_In.data[i] = DUMMY_LONG_VALUE;
	}

	// Jaco2アーム(１本目)の３次元の位置姿勢の入力値を初期化する
	m_Arm1Pose3D_In.data.position.x = DUMMY_DBL_VALUE;
	m_Arm1Pose3D_In.data.position.y = DUMMY_DBL_VALUE;
	m_Arm1Pose3D_In.data.position.z = DUMMY_DBL_VALUE;
	m_Arm1Pose3D_In.data.orientation.r = DUMMY_DBL_VALUE;
	m_Arm1Pose3D_In.data.orientation.p = DUMMY_DBL_VALUE;
	m_Arm1Pose3D_In.data.orientation.y = DUMMY_DBL_VALUE;

	// Jaco2アーム(１本目)の腕の角度の入力値を初期化する
	for(i = 0; i < m_Arm1Angular_In.data.length(); i++)
	{
		m_Arm1Angular_In.data[i] = DUMMY_DBL_VALUE;
	}

	// Jaco2アーム(１本目)の指の開閉具合の入力値を初期化する
	for(i = 0; i < m_Arm1Finger_In.data.length(); i++)
	{
		m_Arm1Finger_In.data[i] = DUMMY_LONG_VALUE;
	}

	// Jaco2アーム(１本目)のモータ負荷の入力値を初期化する
	for(i = 0; i < m_Arm1Current_In.data.length(); i++)
	{
		m_Arm1Current_In.data[i] = DUMMY_DBL_VALUE;
	}

	return RTC::RTC_OK;
}

RTC::ReturnCode_t RTC_Spider2020_Log::onDeactivated(RTC::UniqueId ec_id)
{
	// ログファイルを閉じる
	m_Logout_Robot.close();

	return RTC::RTC_OK;
}

RTC::ReturnCode_t RTC_Spider2020_Log::onExecute(RTC::UniqueId ec_id)
{
	// ３次元の位置姿勢をポートから読み込む
	ReadPose3D();

	// モータの負荷をポートから読み込む
	ReadMotorLoad();

	// フリッパーの角度をポートから読み込む
	ReadFlipperAngle();

	// ３次元の姿勢(IMU)をポートから読み込む
	ReadIMUOrientation3D();

	// メインクローラの速度をポートから読み込む
	ReadVelocity2D();

	// ゲームコントローラのバッテリ残容量比をポートから読み込む
	ReadGCCapacityRatio();

	// ゲームコントローラの軸キーの入力具合をポートから読み込む
	ReadGCAxis();

	// ゲームコントローラのボタンの押下状態をポートから読み込む
	ReadGCButton();

	// メインバッテリのバッテリ残容量比をポートから読み込む
	ReadMainCapacityRatio();

	// 動作指令の状態をポートから読み込む
	ReadMode();

	// Jaco2アーム(１本目)の３次元の位置姿勢をポートから読み込む
	ReadArm1Pose3D();

	// Jaco2アーム(１本目)の腕の角度をポートから読み込む
	ReadArm1Angular();

	// Jaco2アーム(１本目)の指の開閉具合をポートから読み込む
	ReadArm1Finger();

	// Jaco2アーム(１本目)のモータ負荷をポートから読み込む
	ReadArm1Current();

	// ロボット識別子をログファイルとポートに書き込む
	WriteRobotID();

	// ３次元の位置姿勢をログファイルとポートに書き込む
	WritePose3D();

	// モータの負荷をログファイルとポートに書き込む
	WriteMotorLoad();

	// フリッパーの角度をログファイルとポートに書き込む
	WriteFlipperAngle();

	// ３次元の姿勢をログファイルとポートに書き込む
	WriteIMUOrientation3D();

	// メインクローラの速度をログファイルとポートに書き込む
	WriteVelocity2D();

	// ゲームコントローラのバッテリ残容量比をログファイルとポートに書き込む
	WriteGCCapacityRatio();

	// ゲームコントローラの軸キーの入力具合をログファイルとポートに書き込む
	WriteGCAxis();

	// ゲームコントローラのボタンの押下状態をログファイルとポートに書き込む
	WriteGCButton();

	// メインバッテリのバッテリ残容量比をログファイルとポートに書き込む
	WriteMainCapacityRatio();

	// 動作指令の状態をログファイルとポートに書き込む
	WriteMode();

	// Jaco2アーム(１本目)の３次元の位置姿勢をログファイルとポートに書き込む
	WriteArm1Pose3D();

	// Jaco2アーム(１本目)の腕の角度をログファイルとポートに書き込む
	WriteArm1Angular();

	// Jaco2アーム(１本目)の指の開閉具合をログファイルとポートに書き込む
	WriteArm1Finger();

	// Jaco2アーム(１本目)のモータ負荷をログファイルとポートに書き込む
	WriteArm1Current();

	// ログファイルに改行を出力する
	m_Logout_Robot << std::endl;

	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RTC_Spider2020_Log::onAborting(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Log::onError(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Log::onReset(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Log::onStateUpdate(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RTC_Spider2020_Log::onRateChanged(RTC::UniqueId ec_id)
{
	return RTC::RTC_OK;
}
*/

std::string RTC_Spider2020_Log::GetDateTimeString(void)
{
	struct timeval ti = {0};
	struct tm *time_st = NULL;
	char time_str[512] = {0};

	// 日時文字列を作成する
	gettimeofday(&ti, NULL);
	time_st = localtime(&ti.tv_sec);
	sprintf(time_str, "%d-%02d-%02d %02d:%02d:%02d.%06ld", time_st->tm_year + 1900, time_st->tm_mon + 1, time_st->tm_mday, time_st->tm_hour, time_st->tm_min, time_st->tm_sec, ti.tv_usec);

	return time_str;
}

void RTC_Spider2020_Log::OutputRobotIDHeaders(void)
{
	m_Logout_Robot << "robot_id";
	m_Logout_Robot << CSV_DIV << "robot_id_datetime";
}

void RTC_Spider2020_Log::WriteRobotID(void)
{
	char ID[512] = {0};

	// ロボット識別子を設定する
	m_ID.copy(ID, m_ID.size());
	m_RobotID_Out.data = CORBA::string_dup(ID);

	// ログファイルに出力する
	m_Logout_Robot << m_RobotID_Out.data;
	m_Logout_Robot << CSV_DIV << GetDateTimeString();

	// OutPortに出力する
	setTimestamp(m_RobotID_Out);
	m_RobotID_OutOut.write();
}

void RTC_Spider2020_Log::OutputPose3DHeaders(void)
{
	m_Logout_Robot << CSV_DIV << "pose3d";
	m_Logout_Robot << CSV_DIV << "pose3d_datetime";
	m_Logout_Robot << CSV_DIV << "pose3d_x";
	m_Logout_Robot << CSV_DIV << "pose3d_y";
	m_Logout_Robot << CSV_DIV << "pose3d_z";
	m_Logout_Robot << CSV_DIV << "pose3d_roll";
	m_Logout_Robot << CSV_DIV << "pose3d_pitch";
	m_Logout_Robot << CSV_DIV << "pose3d_yaw";
}

void RTC_Spider2020_Log::ReadPose3D(void)
{
	// ３次元の位置姿勢を更新する
	if(m_Pose3D_InIn.isNew())
	{
		// 入力データを読み込む
		m_Pose3D_InIn.read();
	}
}

void RTC_Spider2020_Log::WritePose3D(void)
{
	// 出力データを更新する
	m_Pose3D_Out = m_Pose3D_In;

	// ログファイルに出力する
	m_Logout_Robot << CSV_DIV;
	m_Logout_Robot << CSV_DIV << GetDateTimeString();
	m_Logout_Robot << CSV_DIV << m_Pose3D_Out.data.position.x;
	m_Logout_Robot << CSV_DIV << m_Pose3D_Out.data.position.y;
	m_Logout_Robot << CSV_DIV << m_Pose3D_Out.data.position.z;
	m_Logout_Robot << CSV_DIV << m_Pose3D_Out.data.orientation.r;
	m_Logout_Robot << CSV_DIV << m_Pose3D_Out.data.orientation.p;
	m_Logout_Robot << CSV_DIV << m_Pose3D_Out.data.orientation.y;

	// OutPortに出力する
	setTimestamp(m_Pose3D_Out);
	m_Pose3D_OutOut.write();
}

void RTC_Spider2020_Log::OutputMotorLoadHeaders(void)
{
	m_Logout_Robot << CSV_DIV << "motor_load";
	m_Logout_Robot << CSV_DIV << "motor_load_datetime";
	m_Logout_Robot << CSV_DIV << "motor_load_main_r";
	m_Logout_Robot << CSV_DIV << "motor_load_main_l";
	m_Logout_Robot << CSV_DIV << "motor_load_sub_fr";
	m_Logout_Robot << CSV_DIV << "motor_load_sub_fl";
	m_Logout_Robot << CSV_DIV << "motor_load_sub_br";
	m_Logout_Robot << CSV_DIV << "motor_load_sub_bl";
}

void RTC_Spider2020_Log::ReadMotorLoad(void)
{
	// モータの負荷を更新する
	if(m_MotorLoad_InIn.isNew())
	{
		// 入力データを読み込む
		m_MotorLoad_InIn.read();
	}
}

void RTC_Spider2020_Log::WriteMotorLoad(void)
{
	// 出力データを更新する
	m_MotorLoad_Out = m_MotorLoad_In;

	// ログファイルに出力する
	m_Logout_Robot << CSV_DIV;
	m_Logout_Robot << CSV_DIV << GetDateTimeString();
	m_Logout_Robot << CSV_DIV << m_MotorLoad_OutWrap.GetRightMotorLoad();
	m_Logout_Robot << CSV_DIV << m_MotorLoad_OutWrap.GetLeftMotorLoad();
	m_Logout_Robot << CSV_DIV << m_MotorLoad_OutWrap.GetFrontRightMotorLoad();
	m_Logout_Robot << CSV_DIV << m_MotorLoad_OutWrap.GetFrontLeftMotorLoad();
	m_Logout_Robot << CSV_DIV << m_MotorLoad_OutWrap.GetBackRightMotorLoad();
	m_Logout_Robot << CSV_DIV << m_MotorLoad_OutWrap.GetBackLeftMotorLoad();

	// OutPortに出力する
	m_MotorLoad_OutWrap.SetTimestamp();
	m_MotorLoad_OutOut.write();
}

void RTC_Spider2020_Log::OutputFlipperAngleHeaders(void)
{
	m_Logout_Robot << CSV_DIV << "flipper_angle";
	m_Logout_Robot << CSV_DIV << "flipper_angle_datetime";
	m_Logout_Robot << CSV_DIV << "flipper_angle_fr";
	m_Logout_Robot << CSV_DIV << "flipper_angle_fl";
	m_Logout_Robot << CSV_DIV << "flipper_angle_br";
	m_Logout_Robot << CSV_DIV << "flipper_angle_bl";
}

void RTC_Spider2020_Log::ReadFlipperAngle(void)
{
	// フリッパーの角度を更新する
	if(m_FlipperAngle_InIn.isNew())
	{
		// 入力データを読み込む
		m_FlipperAngle_InIn.read();
	}
}

void RTC_Spider2020_Log::WriteFlipperAngle(void)
{
	// 出力データを更新する
	m_FlipperAngle_Out = m_FlipperAngle_In;

	// ログファイルに出力する
	m_Logout_Robot << CSV_DIV;
	m_Logout_Robot << CSV_DIV << GetDateTimeString();
	m_Logout_Robot << CSV_DIV << m_FlipperAngle_OutWrap.GetFrontRightAngle();
	m_Logout_Robot << CSV_DIV << m_FlipperAngle_OutWrap.GetFrontLeftAngle();
	m_Logout_Robot << CSV_DIV << m_FlipperAngle_OutWrap.GetBackRightAngle();
	m_Logout_Robot << CSV_DIV << m_FlipperAngle_OutWrap.GetBackLeftAngle();

	// OutPortに出力する
	m_FlipperAngle_OutWrap.SetTimestamp();
	m_FlipperAngle_OutOut.write();
}

void RTC_Spider2020_Log::OutputIMUOrientation3DHeaders(void)
{
	m_Logout_Robot << CSV_DIV << "imu_orientation3d";
	m_Logout_Robot << CSV_DIV << "imu_orientation3d_datetime";
	m_Logout_Robot << CSV_DIV << "imu_orientation3d_roll";
	m_Logout_Robot << CSV_DIV << "imu_orientation3d_pitch";
	m_Logout_Robot << CSV_DIV << "imu_orientation3d_yaw";
}

void RTC_Spider2020_Log::ReadIMUOrientation3D(void)
{
	// ３次元の姿勢(IMU)を更新する
	if(m_IMU_Orientation3D_InIn.isNew())
	{
		// 入力データを読み込む
		m_IMU_Orientation3D_InIn.read();
	}
}

void RTC_Spider2020_Log::WriteIMUOrientation3D(void)
{
	// 出力データを更新する
	m_IMU_Orientation3D_Out = m_IMU_Orientation3D_In;

	// ログファイルに出力する
	m_Logout_Robot << CSV_DIV;
	m_Logout_Robot << CSV_DIV << GetDateTimeString();
	m_Logout_Robot << CSV_DIV << m_IMU_Orientation3D_Out.data.r;
	m_Logout_Robot << CSV_DIV << m_IMU_Orientation3D_Out.data.p;
	m_Logout_Robot << CSV_DIV << m_IMU_Orientation3D_Out.data.y;

	// OutPortに出力する
	setTimestamp(m_IMU_Orientation3D_Out);
	m_IMU_Orientation3D_OutOut.write();
}

void RTC_Spider2020_Log::OutputVelocity2DHeaders(void)
{
	m_Logout_Robot << CSV_DIV << "velocity2d";
	m_Logout_Robot << CSV_DIV << "velocity2d_dateimte";
	m_Logout_Robot << CSV_DIV << "velocity2d_vx";
	m_Logout_Robot << CSV_DIV << "velocity2d_vy";
	m_Logout_Robot << CSV_DIV << "velocity2d_va";
}

void RTC_Spider2020_Log::ReadVelocity2D(void)
{
	// メインクローラの速度を更新する
	if(m_Velocity2D_InIn.isNew())
	{
		// 入力データを読み込む
		m_Velocity2D_InIn.read();
	}
}

void RTC_Spider2020_Log::WriteVelocity2D(void)
{
	// 出力データを更新する
	m_Velocity2D_Out = m_Velocity2D_In;

	// ログファイルに出力する
	m_Logout_Robot << CSV_DIV;
	m_Logout_Robot << CSV_DIV << GetDateTimeString();
	m_Logout_Robot << CSV_DIV << m_Velocity2D_Out.data.vx;
	m_Logout_Robot << CSV_DIV << m_Velocity2D_Out.data.vy;
	m_Logout_Robot << CSV_DIV << m_Velocity2D_Out.data.va;

	// OutPortに出力する
	setTimestamp(m_Velocity2D_Out);
	m_Velocity2D_OutOut.write();
}

void RTC_Spider2020_Log::OutputGCCapacityRatioHeaders(void)
{
	m_Logout_Robot << CSV_DIV << "gc_capacity_ratio";
	m_Logout_Robot << CSV_DIV << "gc_capacity_ratio_datetime";
	m_Logout_Robot << CSV_DIV << "gc_capacity_ratio_val";
}

void RTC_Spider2020_Log::ReadGCCapacityRatio(void)
{
	// ゲームコントローラのバッテリ残容量比を更新する
	if(m_GCCapacityRatio_InIn.isNew())
	{
		// 入力データを読み込む
		m_GCCapacityRatio_InIn.read();
	}
}

void RTC_Spider2020_Log::WriteGCCapacityRatio(void)
{
	// 出力データを更新する
	m_GCCapacityRatio_Out = m_GCCapacityRatio_In;

	// ログファイルに出力する
	m_Logout_Robot << CSV_DIV;
	m_Logout_Robot << CSV_DIV << GetDateTimeString();
	m_Logout_Robot << CSV_DIV << m_GCCapacityRatio_Out.data;

	// OutPortに出力する
	setTimestamp(m_GCCapacityRatio_Out);
	m_GCCapacityRatio_OutOut.write();
}

void RTC_Spider2020_Log::OutputGCAxisHeaders(void)
{
	m_Logout_Robot << CSV_DIV << "gc_axis";
	m_Logout_Robot << CSV_DIV << "gc_axis_datetime";
	m_Logout_Robot << CSV_DIV << "gc_axis_direction_h";
	m_Logout_Robot << CSV_DIV << "gc_axis_direction_v";
	m_Logout_Robot << CSV_DIV << "gc_axis_lstick_h";
	m_Logout_Robot << CSV_DIV << "gc_axis_lstick_v";
	m_Logout_Robot << CSV_DIV << "gc_axis_rstick_h";
	m_Logout_Robot << CSV_DIV << "gc_axis_rstick_v";
	m_Logout_Robot << CSV_DIV << "gc_axis_l2";
	m_Logout_Robot << CSV_DIV << "gc_axis_r2";
}

void RTC_Spider2020_Log::ReadGCAxis(void)
{
	// ゲームコントローラの軸キーの入力具合を更新する
	if(m_GCAxis_InIn.isNew())
	{
		// 入力データを読み込む
		m_GCAxis_InIn.read();
	}
}

void RTC_Spider2020_Log::WriteGCAxis(void)
{
	// 出力データを更新する
	m_GCAxis_Out = m_GCAxis_In;

	// ログファイルに出力する
	m_Logout_Robot << CSV_DIV;
	m_Logout_Robot << CSV_DIV << GetDateTimeString();
	m_Logout_Robot << CSV_DIV << m_GCAxis_OutWrap.GetDirHorizontal();
	m_Logout_Robot << CSV_DIV << m_GCAxis_OutWrap.GetDirVertical();
	m_Logout_Robot << CSV_DIV << m_GCAxis_OutWrap.GetLStickHorizontal();
	m_Logout_Robot << CSV_DIV << m_GCAxis_OutWrap.GetLStickVertical();
	m_Logout_Robot << CSV_DIV << m_GCAxis_OutWrap.GetRStickHorizontal();
	m_Logout_Robot << CSV_DIV << m_GCAxis_OutWrap.GetRStickVertical();
	m_Logout_Robot << CSV_DIV << m_GCAxis_OutWrap.GetL2();
	m_Logout_Robot << CSV_DIV << m_GCAxis_OutWrap.GetR2();

	// OutPortに出力する
	m_GCAxis_OutWrap.SetTimestamp();
	m_GCAxis_OutOut.write();
}

void RTC_Spider2020_Log::OutputGCButtonHeaders(void)
{
	m_Logout_Robot << CSV_DIV << "gc_button";
	m_Logout_Robot << CSV_DIV << "gc_button_datetime";
	m_Logout_Robot << CSV_DIV << "gc_button_square";
	m_Logout_Robot << CSV_DIV << "gc_button_cross";
	m_Logout_Robot << CSV_DIV << "gc_button_circle";
	m_Logout_Robot << CSV_DIV << "gc_button_triangle";
	m_Logout_Robot << CSV_DIV << "gc_button_l1";
	m_Logout_Robot << CSV_DIV << "gc_button_r1";
	m_Logout_Robot << CSV_DIV << "gc_button_l2";
	m_Logout_Robot << CSV_DIV << "gc_button_r2";
	m_Logout_Robot << CSV_DIV << "gc_button_share";
	m_Logout_Robot << CSV_DIV << "gc_button_options";
	m_Logout_Robot << CSV_DIV << "gc_button_l3";
	m_Logout_Robot << CSV_DIV << "gc_button_r3";
	m_Logout_Robot << CSV_DIV << "gc_button_ps";
	m_Logout_Robot << CSV_DIV << "gc_button_touch";
}

void RTC_Spider2020_Log::ReadGCButton(void)
{
	// ゲームコントローラのボタンの押下状態を更新する
	if(m_GCButton_InIn.isNew())
	{
		// 入力データを読み込む
		m_GCButton_InIn.read();
	}
}

void RTC_Spider2020_Log::WriteGCButton(void)
{
	// 出力データを更新する
	m_GCButton_Out = m_GCButton_In;

	// ログファイルに出力する
	m_Logout_Robot << CSV_DIV;
	m_Logout_Robot << CSV_DIV << GetDateTimeString();
	m_Logout_Robot << CSV_DIV << ((m_GCButton_Out.data != DUMMY_LONG_VALUE) ? m_GCButton_OutWrap.GetSquare() : DUMMY_LONG_VALUE);
	m_Logout_Robot << CSV_DIV << ((m_GCButton_Out.data != DUMMY_LONG_VALUE) ? m_GCButton_OutWrap.GetCross() : DUMMY_LONG_VALUE);
	m_Logout_Robot << CSV_DIV << ((m_GCButton_Out.data != DUMMY_LONG_VALUE) ? m_GCButton_OutWrap.GetCircle() : DUMMY_LONG_VALUE);
	m_Logout_Robot << CSV_DIV << ((m_GCButton_Out.data != DUMMY_LONG_VALUE) ? m_GCButton_OutWrap.GetTriangle() : DUMMY_LONG_VALUE);
	m_Logout_Robot << CSV_DIV << ((m_GCButton_Out.data != DUMMY_LONG_VALUE) ? m_GCButton_OutWrap.GetL1() : DUMMY_LONG_VALUE);
	m_Logout_Robot << CSV_DIV << ((m_GCButton_Out.data != DUMMY_LONG_VALUE) ? m_GCButton_OutWrap.GetR1() : DUMMY_LONG_VALUE);
	m_Logout_Robot << CSV_DIV << ((m_GCButton_Out.data != DUMMY_LONG_VALUE) ? m_GCButton_OutWrap.GetL2() : DUMMY_LONG_VALUE);
	m_Logout_Robot << CSV_DIV << ((m_GCButton_Out.data != DUMMY_LONG_VALUE) ? m_GCButton_OutWrap.GetR2() : DUMMY_LONG_VALUE);
	m_Logout_Robot << CSV_DIV << ((m_GCButton_Out.data != DUMMY_LONG_VALUE) ? m_GCButton_OutWrap.GetShare() : DUMMY_LONG_VALUE);
	m_Logout_Robot << CSV_DIV << ((m_GCButton_Out.data != DUMMY_LONG_VALUE) ? m_GCButton_OutWrap.GetOptions() : DUMMY_LONG_VALUE);
	m_Logout_Robot << CSV_DIV << ((m_GCButton_Out.data != DUMMY_LONG_VALUE) ? m_GCButton_OutWrap.GetL3() : DUMMY_LONG_VALUE);
	m_Logout_Robot << CSV_DIV << ((m_GCButton_Out.data != DUMMY_LONG_VALUE) ? m_GCButton_OutWrap.GetR3() : DUMMY_LONG_VALUE);
	m_Logout_Robot << CSV_DIV << ((m_GCButton_Out.data != DUMMY_LONG_VALUE) ? m_GCButton_OutWrap.GetPS() : DUMMY_LONG_VALUE);
	m_Logout_Robot << CSV_DIV << ((m_GCButton_Out.data != DUMMY_LONG_VALUE) ? m_GCButton_OutWrap.GetTouch() : DUMMY_LONG_VALUE);

	// OutPortに出力する
	m_GCButton_OutWrap.SetTimestamp();
	m_GCButton_OutOut.write();
}

void RTC_Spider2020_Log::OutputMainCapacityRatioHeaders(void)
{
	if(m_Logout_Robot.good())
	{
		m_Logout_Robot << CSV_DIV << "main_capacity_ratio";
		m_Logout_Robot << CSV_DIV << "main_capacity_ratio_datetime";
		m_Logout_Robot << CSV_DIV << "main_capacity_ratio_val";
	}
}

void RTC_Spider2020_Log::ReadMainCapacityRatio(void)
{
	// メインバッテリのバッテリ残容量比を更新する
	if(m_MainCapacityRatio_InIn.isNew())
	{
		// 入力データを読み込む
		m_MainCapacityRatio_InIn.read();
	}
}

void RTC_Spider2020_Log::WriteMainCapacityRatio(void)
{
	// 出力データを更新する
	m_MainCapacityRatio_Out = m_MainCapacityRatio_In;

	// ログファイルに出力する
	m_Logout_Robot << CSV_DIV;
	m_Logout_Robot << CSV_DIV << GetDateTimeString();
	m_Logout_Robot << CSV_DIV << m_MainCapacityRatio_Out.data;

	// OutPortに出力する
	setTimestamp(m_MainCapacityRatio_Out);
	m_MainCapacityRatio_OutOut.write();
}

void RTC_Spider2020_Log::OutputModeHeaders(void)
{
	m_Logout_Robot << CSV_DIV << "mode";
	m_Logout_Robot << CSV_DIV << "mode_datetime";
	m_Logout_Robot << CSV_DIV << "mode_action";
	m_Logout_Robot << CSV_DIV << "mode_speed_level";
	m_Logout_Robot << CSV_DIV << "mode_speed_max";
	m_Logout_Robot << CSV_DIV << "mode_flipper_select_fr";
	m_Logout_Robot << CSV_DIV << "mode_flipper_select_fl";
	m_Logout_Robot << CSV_DIV << "mode_flipper_select_br";
	m_Logout_Robot << CSV_DIV << "mode_flipper_select_bl";
	m_Logout_Robot << CSV_DIV << "mode_flipper_action";
	m_Logout_Robot << CSV_DIV << "mode_pose_clear";
}

void RTC_Spider2020_Log::ReadMode(void)
{
	// 動作指令の状態を更新する
	if(m_Mode_InIn.isNew())
	{
		// 入力データを読み込む
		m_Mode_InIn.read();
	}
}

void RTC_Spider2020_Log::WriteMode(void)
{
	// 出力データを更新する
	m_Mode_Out = m_Mode_In;

	// ログファイルに出力する
	m_Logout_Robot << CSV_DIV;
	m_Logout_Robot << CSV_DIV << GetDateTimeString();
	m_Logout_Robot << CSV_DIV << m_Mode_OutWrap.GetControl();
	m_Logout_Robot << CSV_DIV << m_Mode_OutWrap.GetSpeedLevel();
	m_Logout_Robot << CSV_DIV << m_Mode_OutWrap.GetSpeedMax();
	m_Logout_Robot << CSV_DIV << ((m_Mode_OutWrap.GetFlipperStatus() != DUMMY_LONG_VALUE) ? m_Mode_OutWrap.GetFrontRightFlipperSelect() : DUMMY_LONG_VALUE);
	m_Logout_Robot << CSV_DIV << ((m_Mode_OutWrap.GetFlipperStatus() != DUMMY_LONG_VALUE) ? m_Mode_OutWrap.GetFrontLeftFlipperSelect() : DUMMY_LONG_VALUE);
	m_Logout_Robot << CSV_DIV << ((m_Mode_OutWrap.GetFlipperStatus() != DUMMY_LONG_VALUE) ? m_Mode_OutWrap.GetBackRightFlipperSelect() : DUMMY_LONG_VALUE);
	m_Logout_Robot << CSV_DIV << ((m_Mode_OutWrap.GetFlipperStatus() != DUMMY_LONG_VALUE) ? m_Mode_OutWrap.GetBackLeftFlipperSelect() : DUMMY_LONG_VALUE);
	m_Logout_Robot << CSV_DIV << m_Mode_OutWrap.GetFlipperStatus();
	m_Logout_Robot << CSV_DIV << m_Mode_OutWrap.GetCrawlerPoseClear();

	// OutPortに出力する
	m_Mode_OutWrap.SetTimestamp();
	m_Mode_OutOut.write();
}

void RTC_Spider2020_Log::OutputArm1Pose3DHeaders(void)
{
	m_Logout_Robot << CSV_DIV << "arm1_pose3d";
	m_Logout_Robot << CSV_DIV << "arm1_pose3d_datetime";
	m_Logout_Robot << CSV_DIV << "arm1_pose3d_x";
	m_Logout_Robot << CSV_DIV << "arm1_pose3d_y";
	m_Logout_Robot << CSV_DIV << "arm1_pose3d_z";
	m_Logout_Robot << CSV_DIV << "arm1_pose3d_roll";
	m_Logout_Robot << CSV_DIV << "arm1_pose3d_pitch";
	m_Logout_Robot << CSV_DIV << "arm1_pose3d_yaw";
}

void RTC_Spider2020_Log::ReadArm1Pose3D(void)
{
	// Arm1の位置姿勢（ロボット座標系）を更新する
	if(m_Arm1Pose3D_InIn.isNew())
	{
		// 入力データを読み込む
		m_Arm1Pose3D_InIn.read();
	}
}

void RTC_Spider2020_Log::WriteArm1Pose3D(void)
{
	// 出力データを更新する
	m_Arm1Pose3D_Out = m_Arm1Pose3D_In;

	// ログファイルに出力する
	m_Logout_Robot << CSV_DIV;
	m_Logout_Robot << CSV_DIV << GetDateTimeString();
	m_Logout_Robot << CSV_DIV << m_Arm1Pose3D_Out.data.position.x;
	m_Logout_Robot << CSV_DIV << m_Arm1Pose3D_Out.data.position.y;
	m_Logout_Robot << CSV_DIV << m_Arm1Pose3D_Out.data.position.z;
	m_Logout_Robot << CSV_DIV << m_Arm1Pose3D_Out.data.orientation.r;
	m_Logout_Robot << CSV_DIV << m_Arm1Pose3D_Out.data.orientation.p;
	m_Logout_Robot << CSV_DIV << m_Arm1Pose3D_Out.data.orientation.y;

	// OutPortに出力する
	setTimestamp(m_Arm1Pose3D_Out);
	m_Arm1Pose3D_OutOut.write();
}

void RTC_Spider2020_Log::OutputArm1AngularHeaders(void)
{
	m_Logout_Robot << CSV_DIV << "arm1_angular";
	m_Logout_Robot << CSV_DIV << "arm1_angular_datetime";
	m_Logout_Robot << CSV_DIV << "arm1_angular_angular1";
	m_Logout_Robot << CSV_DIV << "arm1_angular_angular2";
	m_Logout_Robot << CSV_DIV << "arm1_angular_angular3";
	m_Logout_Robot << CSV_DIV << "arm1_angular_angular4";
	m_Logout_Robot << CSV_DIV << "arm1_angular_angular5";
	m_Logout_Robot << CSV_DIV << "arm1_angular_angular6";
}

void RTC_Spider2020_Log::ReadArm1Angular(void)
{
	// Arm1の腕の角度を更新する
	if(m_Arm1Angular_InIn.isNew())
	{
		// 入力データを読み込む
		m_Arm1Angular_InIn.read();
	}
}

void RTC_Spider2020_Log::WriteArm1Angular(void)
{
	// 出力データを更新する
	m_Arm1Angular_Out = m_Arm1Angular_In;

	// ログファイルに出力する
	m_Logout_Robot << CSV_DIV;
	m_Logout_Robot << CSV_DIV << GetDateTimeString();
	m_Logout_Robot << CSV_DIV << m_Arm1Angular_OutWrap.GetShoulderAngular();
	m_Logout_Robot << CSV_DIV << m_Arm1Angular_OutWrap.GetArmAngular();
	m_Logout_Robot << CSV_DIV << m_Arm1Angular_OutWrap.GetForearmAngular();
	m_Logout_Robot << CSV_DIV << m_Arm1Angular_OutWrap.GetWrist1Angular();
	m_Logout_Robot << CSV_DIV << m_Arm1Angular_OutWrap.GetWrist2Angular();
	m_Logout_Robot << CSV_DIV << m_Arm1Angular_OutWrap.GetHandAngular();

	// OutPortに出力する
	m_Arm1Angular_OutWrap.SetTimestamp();
	m_Arm1Angular_OutOut.write();
}

void RTC_Spider2020_Log::OutputArm1FingerHeaders(void)
{
	m_Logout_Robot << CSV_DIV << "arm1_finger";
	m_Logout_Robot << CSV_DIV << "arm1_finger_datetime";
	m_Logout_Robot << CSV_DIV << "arm1_finger_finger1";
	m_Logout_Robot << CSV_DIV << "arm1_finger_finger2";
	m_Logout_Robot << CSV_DIV << "arm1_finger_finger3";
}

void RTC_Spider2020_Log::ReadArm1Finger(void)
{
	// Arm1の指の開閉具合を更新する
	if(m_Arm1Finger_InIn.isNew())
	{
		// 入力データを読み込む
		m_Arm1Finger_InIn.read();
	}
}

void RTC_Spider2020_Log::WriteArm1Finger(void)
{
	// 出力データを更新する
	m_Arm1Finger_Out = m_Arm1Finger_In;

	// ログファイルに出力する
	m_Logout_Robot << CSV_DIV;
	m_Logout_Robot << CSV_DIV << GetDateTimeString();
	m_Logout_Robot << CSV_DIV << m_Arm1Finger_OutWrap.GetThumbStatus();
	m_Logout_Robot << CSV_DIV << m_Arm1Finger_OutWrap.GetIndexFingerStatus();
	m_Logout_Robot << CSV_DIV << m_Arm1Finger_OutWrap.GetMiddleFingerStatus();

	// OutPortに出力する
	m_Arm1Finger_OutWrap.SetTimestamp();
	m_Arm1Finger_OutOut.write();
}

void RTC_Spider2020_Log::OutputArm1CurrentHeaders(void)
{
	m_Logout_Robot << CSV_DIV << "arm1_current";
	m_Logout_Robot << CSV_DIV << "arm1_current_datetime";
	m_Logout_Robot << CSV_DIV << "arm1_current_angular1";
	m_Logout_Robot << CSV_DIV << "arm1_current_angular2";
	m_Logout_Robot << CSV_DIV << "arm1_current_angular3";
	m_Logout_Robot << CSV_DIV << "arm1_current_angular4";
	m_Logout_Robot << CSV_DIV << "arm1_current_angular5";
	m_Logout_Robot << CSV_DIV << "arm1_current_angular6";
	m_Logout_Robot << CSV_DIV << "arm1_current_finger1";
	m_Logout_Robot << CSV_DIV << "arm1_current_finger2";
	m_Logout_Robot << CSV_DIV << "arm1_current_finger3";
}

void RTC_Spider2020_Log::ReadArm1Current(void)
{
	// Arm1のモータ負荷を更新する
	if(m_Arm1Current_InIn.isNew())
	{
		// 入力データを読み込む
		m_Arm1Current_InIn.read();
	}
}

void RTC_Spider2020_Log::WriteArm1Current(void)
{
	// 出力データを更新する
	m_Arm1Current_Out = m_Arm1Current_In;

	// ログファイルに出力する
	m_Logout_Robot << CSV_DIV;
	m_Logout_Robot << CSV_DIV << GetDateTimeString();
	m_Logout_Robot << CSV_DIV << m_Arm1Current_OutWrap.GetShoulderCurrent();
	m_Logout_Robot << CSV_DIV << m_Arm1Current_OutWrap.GetArmCurrent();
	m_Logout_Robot << CSV_DIV << m_Arm1Current_OutWrap.GetForearmCurrent();
	m_Logout_Robot << CSV_DIV << m_Arm1Current_OutWrap.GetWrist1Current();
	m_Logout_Robot << CSV_DIV << m_Arm1Current_OutWrap.GetWrist2Current();
	m_Logout_Robot << CSV_DIV << m_Arm1Current_OutWrap.GetHandCurrent();
	m_Logout_Robot << CSV_DIV << m_Arm1Current_OutWrap.GetThumbCurrent();
	m_Logout_Robot << CSV_DIV << m_Arm1Current_OutWrap.GetIndexFingerCurrent();
	m_Logout_Robot << CSV_DIV << m_Arm1Current_OutWrap.GetMiddleFingerCurrent();

	// OutPortに出力する
	m_Arm1Current_OutWrap.SetTimestamp();
	m_Arm1Current_OutOut.write();
}


extern "C"
{
	void RTC_Spider2020_LogInit(RTC::Manager* manager)
	{
		coil::Properties profile(rtc_spider2020_log_spec);
		manager->registerFactory(profile, RTC::Create<RTC_Spider2020_Log>, RTC::Delete<RTC_Spider2020_Log>);
	}
};
