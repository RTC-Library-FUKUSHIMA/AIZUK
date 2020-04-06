// -*- C++ -*-
/*!
 * @file  RTC_Spider2020_Crawler.h
 * @brief Spider2020の台車制御RTC
 * @date  $Date$
 *
 * $Id$
 */

#ifndef RTC_SPIDER2020_CRAWLER_H
#define RTC_SPIDER2020_CRAWLER_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">
#include "BasicDataTypeStub.h"
#include "ExtendedDataTypesStub.h"

// </rtc-template>

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

#include <sys/time.h>

#include "FlipperAngleWrapper.h"
#include "FlipperPwmWrapper.h"
#include "ModeWrapper.h"
#include "MotorLoadWrapper.h"

#include "MainMotorProcessor.h"
#include "SubMotorProcessor.h"

/*!
 * @class RTC_Spider2020_Crawler
 * @brief Spider2020の台車制御RTC
 *
 */
class RTC_Spider2020_Crawler
  : public RTC::DataFlowComponentBase
{
public:
	/*!
	 * @brief constructor
	 * @param manager Maneger Object
	 */
	RTC_Spider2020_Crawler(RTC::Manager* manager);

	/*!
	 * @brief destructor
	 */
	~RTC_Spider2020_Crawler();

	// <rtc-template block="public_attribute">

	// </rtc-template>

	// <rtc-template block="public_operation">

	// </rtc-template>

	/***
	 *
	 * The initialize action (on CREATED->ALIVE transition)
	 *
	 * @return RTC::ReturnCode_t
	 * 
	 * 
	 */
	virtual RTC::ReturnCode_t onInitialize();

	/***
	 *
	 * The finalize action (on ALIVE->END transition)
	 *
	 * @return RTC::ReturnCode_t
	 * 
	 * 
	 */
	// virtual RTC::ReturnCode_t onFinalize();

	/***
	 *
	 * The startup action when ExecutionContext startup
	 *
	 * @param ec_id target ExecutionContext Id
	 *
	 * @return RTC::ReturnCode_t
	 * 
	 * 
	 */
	// virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);

	/***
	 *
	 * The shutdown action when ExecutionContext stop
	 *
	 * @param ec_id target ExecutionContext Id
	 *
	 * @return RTC::ReturnCode_t
	 * 
	 * 
	 */
	// virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);

	/***
	 *
	 * The activated action (Active state entry action)
	 *
	 * @param ec_id target ExecutionContext Id
	 *
	 * @return RTC::ReturnCode_t
	 * 
	 * 
	 */
	virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

	/***
	 *
	 * The deactivated action (Active state exit action)
	 *
	 * @param ec_id target ExecutionContext Id
	 *
	 * @return RTC::ReturnCode_t
	 * 
	 * 
	 */
	virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

	/***
	 *
	 * The execution action that is invoked periodically
	 *
	 * @param ec_id target ExecutionContext Id
	 *
	 * @return RTC::ReturnCode_t
	 * 
	 * 
	 */
	virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

	/***
	 *
	 * The aborting action when main logic error occurred.
	 *
	 * @param ec_id target ExecutionContext Id
	 *
	 * @return RTC::ReturnCode_t
	 * 
	 * 
	 */
	// virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);

	/***
	 *
	 * The error action in ERROR state
	 *
	 * @param ec_id target ExecutionContext Id
	 *
	 * @return RTC::ReturnCode_t
	 * 
	 * 
	 */
	// virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

	/***
	 *
	 * The reset action that is invoked resetting
	 *
	 * @param ec_id target ExecutionContext Id
	 *
	 * @return RTC::ReturnCode_t
	 * 
	 * 
	 */
	// virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);

	/***
	 *
	 * The state update action that is invoked after onExecute() action
	 *
	 * @param ec_id target ExecutionContext Id
	 *
	 * @return RTC::ReturnCode_t
	 * 
	 * 
	 */
	// virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

	/***
	 *
	 * The action that is invoked when execution context's rate is changed
	 *
	 * @param ec_id target ExecutionContext Id
	 *
	 * @return RTC::ReturnCode_t
	 * 
	 * 
	 */
	// virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);

	/*!
	 * 動作状態をポートから読み込む
	 * @method ReadMode
	 * @return なし
	 */
	void ReadMode(void);

	/*!
	 * ２次元の速度をポートから読み込む
	 * @method ReadVelocity2D
	 * @return なし
	 */
	void ReadVelocity2D(void);

	/*!
	 * フリッパーのPWM指令をポートから読み込む
	 * @method ReadFlipperPwm
	 * @return なし
	 */
	void ReadFlipperPwm(void);

	/*!
	 * 外部観測した３次元の姿勢をポートから読み込む
	 * @method ReadOrientation3D
	 * @return なし
	 */
	void ReadOrientation3D(void);

	/*!
	 * オドメトリによる３次元の位置姿勢をポートに出力する
	 * @method WritePose3D
	 * @return なし
	 */
	void WritePose3D(void);

	/*!
	 * ２次元の速度をポートに出力する
	 * @method WriteVelocity2D
	 * @return なし
	 */
	void WriteVelocity2D(void);

	/*!
	 * フリッパーの角度をポートに出力する
	 * @method WriteVelocity2D
	 * @return なし
	 */
	void WriteFlipperAngle(void);

	/*!
	 * モータの負荷をポートに出力する
	 * @method WriteMotorLoad
	 * @return なし
	 */
	void WriteMotorLoad(void);

	/*!
	 * フリッパーの角度を読み込む
	 * @method LoadFlipperAngle
	 * @return なし
	 * @note 保存先: ~/.FlipperAngle.txt
	 */
	void LoadFlipperAngle(void);

	/*!
	 * フリッパーの角度を保存する
	 * @method SaveFlipperAngle
	 * @return なし
	 * @note 保存先: ~/.FlipperAngle.txt
	 */
	void SaveFlipperAngle(void);

protected:
	// <rtc-template block="protected_attribute">

	// </rtc-template>

	// <rtc-template block="protected_operation">

	// </rtc-template>

	// Configuration variable declaration
	// <rtc-template block="config_declare">
	/*!
	 * Wheel Radius
	 * - Name: メインクローラの車輪半径 WHEEL_RADIUS
	 * - DefaultValue: 0.0769
	 * - Unit: [m]
	 */
	double m_WHEEL_RADIUS;
	/*!
	 * Pulley Radius
	 * - Name: フリッパーのプーリ半径 PULLEY_RADIUS
	 * - DefaultValue: 0.0486
	 * - Unit: [m]
	 */
	double m_PULLEY_RADIUS;
	/*!
	 * Turning Radius
	 * - Name: 旋回半径 TURNING_RADIUS
	 * - DefaultValue: 0.0938
	 * - Unit: [m]
	 */
	double m_TURNING_RADIUS;
	/*!
	 * メインモータを制御するマイコンのデバイス名
	 * - Name: メインモータのデバイス名 SH1_DEVICE_NAME
	 * - DefaultValue: /dev/ttyUSB0
	 */
	std::string m_SH1_DEVICE_NAME;
	/*!
	 * 前方サブモータを制御するマイコンのデバイス名
	 * - Name: 前方サブモータのデバイス名 SH2_DEVICE_NAME
	 * - DefaultValue: /dev/ttyUSB1
	 */
	std::string m_SH2_DEVICE_NAME;
	/*!
	 * 後方サブモータを制御するマイコンのデバイス名
	 * - Name: 後方サブモータのデバイス名 SH3_DEVICE_NAME
	 * - DefaultValue: /dev/ttyUSB2
	 */
	std::string m_SH3_DEVICE_NAME;
	/*!
	 * メインモータを制御するマイコンとの伝送速度
	 * - Name: メインモータの伝送速度 SH1_BAUDRATE
	 * - DefaultValue: B38400
	 */
	std::string m_SH1_BAUDRATE;
	/*!
	 * 前方サブモータを制御するマイコンとの伝送速度
	 * - Name: 前方サブモータの伝送速度 SH2_BAUDRATE
	 * - DefaultValue: B38400
	 */
	std::string m_SH2_BAUDRATE;
	/*!
	 * 後方サブモータを制御するマイコンとの伝送速度
	 * - Name: 後方サブモータの伝送速度 SH3_BAUDRATE
	 * - DefaultValue: B38400
	 */
	std::string m_SH3_BAUDRATE;
	/*!
	 * メインモータのPID速度制御の比例ゲイン
	 * - Name: メインモータの比例ゲイン MAIN_MOTOR_KP
	 * - DefaultValue: 0.42
	 */
	double m_MAIN_MOTOR_KP;
	/*!
	 * メインモータのPID速度制御の積分ゲイン
	 * - Name: メインモータの積分ゲイン MAIN_MOTOR_KI
	 * - DefaultValue: 4.00
	 */
	double m_MAIN_MOTOR_KI;
	/*!
	 * メインモータのPID速度制御の微分ゲイン
	 * - Name: メインモータの微分ゲイン MAIN_MOTOR_KD
	 * - DefaultValue: 0.02
	 */
	double m_MAIN_MOTOR_KD;
	/*!
	 * オドメトリの並進距離を実測に近づけるための係数
	 * - Name: 並進係数 VX_GAIN
	 * - DefaultValue: 1.000
	 */
	double m_VX_GAIN;
	/*!
	 * オドメトリの旋回を実測に近づけるための係数
	 * - Name: 旋回係数 VA_GAIN
	 * - DefaultValue: 1.000
	 */
	double m_VA_GAIN;
	/*!
	 * 1000 = 500(パルス) x 2(逓倍) ※位相計数モード4
	 * - Name: メインモータのパルス数 MAIN_MOTOR_PULSE
	 * - DefaultValue: 1000
	 */
	long int m_MAIN_MOTOR_PULSE;
	/*!
	 * メインモータの減速比
	 * - Name: メインモータの減速比 MAIN_MOTOR_GEAR_RATIO
	 * - DefaultValue: 243
	 */
	double m_MAIN_MOTOR_GEAR_RATIO;
	/*!
	 * 512 = 256(パルス) x 2(逓倍) ※位相計数モード4
	 * - Name: サブモータのパルス数 SUB_MOTOR_PULSE
	 * - DefaultValue: 512
	 */
	long int m_SUB_MOTOR_PULSE;
	/*!
	 * サブモータの減速比
	 * - Name: サブモータの減速比 SUB_MOTOR_GEAR_RATIO
	 * - DefaultValue: 1080.0
	 */
	double m_SUB_MOTOR_GEAR_RATIO;
	/*!
	 * 右メインモータの回転方向(1:正回転、-1:負回転)
	 * - Name: 右メインモータの回転方向 R_MAIN_MOTOR_DIRECTION
	 * - DefaultValue: 1
	 */
	long int m_R_MAIN_MOTOR_DIRECTION;
	/*!
	 * 左メインモータの回転方向(1:正回転、-1:負回転)
	 * - Name: 左メインモータの回転方向 L_MAIN_MOTOR_DIRECTION
	 * - DefaultValue: 1
	 */
	long int m_L_MAIN_MOTOR_DIRECTION;
	/*!
	 * 右前方モータの回転方向(1:正回転、-1:負回転)
	 * - Name: 右前方モータの回転方向 R_FRONT_SUB_MOTOR_DIRECTION
	 * - DefaultValue: 1
	 */
	long int m_R_FRONT_SUB_MOTOR_DIRECTION;
	/*!
	 * 左前方モータの回転方向(1:正回転、-1:負回転)
	 * - Name: 右前方モータの回転方向 L_FRONT_SUB_MOTOR_DIRECTION
	 * - DefaultValue: 1
	 */
	long int m_L_FRONT_SUB_MOTOR_DIRECTION;
	/*!
	 * 右後方モータの回転方向(1:正回転、-1:負回転)
	 * - Name: 右後方モータの回転方向 R_BACK_SUB_MOTOR_DIRECTION
	 * - DefaultValue: 1
	 */
	long int m_R_BACK_SUB_MOTOR_DIRECTION;
	/*!
	 * 左後方モータの回転方向(1:正回転、-1:負回転)
	 * - Name: 左後方モータの回転方向 L_BACK_SUB_MOTOR_DIRECTION
	 * - DefaultValue: 1
	 */
	long int m_L_BACK_SUB_MOTOR_DIRECTION;
	/*!
	 * メインモータの電圧値をモータ負荷に変換するゲイン
	 * - Name: メインモータのモータ負荷のゲイン MAIN_MOTOR_LOAD_GAIN
	 * - DefaultValue: 7.5
	 */
	double m_MAIN_MOTOR_LOAD_GAIN;
	/*!
	 * メインモータの電圧値の基準値
	 * - Name: メインモータのモータ負荷の基準電圧 MAIN_MOTOR_LOAD_BASE
	 * - DefaultValue: 2.0
	 */
	double m_MAIN_MOTOR_LOAD_BASE;
	/*!
	 * サブモータの電圧値をモータ負荷に変換するゲイン
	 * - Name: サブモータのモータ負荷のゲイン SUB_MOTOR_LOAD_GAIN
	 * - DefaultValue: 7.5
	 */
	double m_SUB_MOTOR_LOAD_GAIN;
	/*!
	 * サブモータの電圧値の基準値
	 * - Name: サブモータのモータ負荷の基準電圧 SUB_MOTOR_LOAD_BASE
	 * - DefaultValue: 2.0
	 */
	double m_SUB_MOTOR_LOAD_BASE;
	/*!
	 * 入力ポートへ指定時間以上新しい入力がなければ、
	 * 暴走を回避するため入力データのクリアなどを実施する。
	 * - Name: フェイルセーフ時間 FAILSAFE_SEC
	 * - DefaultValue: 1.0
	 */
	double m_FAILSAFE_SEC;
	/*!
	 * 0: オドメトリの処理に外部観測した３次元の姿勢を使用しない。
	 * 1: オドメトリの処理に外部観測した３次元の姿勢を使用する。
	 * - Name: 外部観測した３次元の姿勢 USE_ORIENTATION3D_IN
	 * - DefaultValue: 0
	 */
	long int m_USE_ORIENTATION3D_IN;

	// </rtc-template>

	// DataInPort declaration
	// <rtc-template block="inport_declare">
	RTC::TimedLongSeq m_Mode_In;
	/*!
	 * 動作指令の状態
	 * - Type: TimedLongSeq
	 * - Number: 6
	 */
	RTC::InPort<RTC::TimedLongSeq> m_Mode_InIn;
	RTC::TimedVelocity2D m_Velocity2D_In;
	/*!
	 * ２次元の速度
	 * - Type: TimedVelocity2D
	 */
	RTC::InPort<RTC::TimedVelocity2D> m_Velocity2D_InIn;
	RTC::TimedLongSeq m_FlipperPwm_In;
	/*!
	 * フリッパーのPWM指令
	 * - Type: TimedLongSeq
	 * - Number: 4
	 */
	RTC::InPort<RTC::TimedLongSeq> m_FlipperPwm_InIn;
	RTC::TimedOrientation3D m_Orientation3D_In;
	/*!
	 * 外部観測した３次元の姿勢
	 * - Type: TimedOrientation3D
	 */
	RTC::InPort<RTC::TimedOrientation3D> m_Orientation3D_InIn;

	// </rtc-template>


	// DataOutPort declaration
	// <rtc-template block="outport_declare">
	RTC::TimedPose3D m_Pose3D_Out;
	/*!
	 * オドメトリによる３次元の位置・姿勢
	 * - Type: TimedPose3D
	 * - Unit: [m,rad]
	 */
	RTC::OutPort<RTC::TimedPose3D> m_Pose3D_OutOut;
	RTC::TimedVelocity2D m_Velocity2D_Out;
	/*!
	 * ２次元の速度
	 * - Type: TimedVelocity2D
	 */
	RTC::OutPort<RTC::TimedVelocity2D> m_Velocity2D_OutOut;
	RTC::TimedDoubleSeq m_FlipperAngle_Out;
	/*!
	 * フリッパーの角度
	 * - Type: TimedDoubleSeq
	 * - Number: 4
	 * - Semantics: [0]: 右前
	 *              [1]: 左前
	 *              [2]: 右後
	 *              [3]: 左後
	 */
	RTC::OutPort<RTC::TimedDoubleSeq> m_FlipperAngle_OutOut;
	RTC::TimedDoubleSeq m_MotorLoad_Out;
	/*!
	 * 各モータの負荷
	 * - Type: TimedDoubleSeq
	 * - Number: 6
	 * - Semantics: [0]: 右メインモータ
	 *              [1]: 左メインモータ
	 *              [2]: 右前方サブモータ
	 *              [3]: 左前方サブモータ
	 *              [4]: 右後方サブモータ
	 *              [5]: 左後方サブモータ
	 * - Unit: [A]
	 */
	RTC::OutPort<RTC::TimedDoubleSeq> m_MotorLoad_OutOut;

	// </rtc-template>

	// CORBA Port declaration
	// <rtc-template block="corbaport_declare">

	// </rtc-template>

	// Service declaration
	// <rtc-template block="service_declare">

	// </rtc-template>

	// Consumer declaration
	// <rtc-template block="consumer_declare">

	// </rtc-template>

private:
	// <rtc-template block="private_attribute">

	// </rtc-template>

	// <rtc-template block="private_operation">

	// </rtc-template>

	ModeWrapper m_Mode_InWrap;						/*!< m_Mode_Inのラッパークラス			*/
	FlipperPwmWrapper m_FlipperPwm_InWrap;			/*!< m_FlipperPwm_Inのラッパークラス	*/
	FlipperAngleWrapper m_FlipperAngle_OutWrap;		/*!< m_FlipperAngle_Outのラッパークラス	*/
	MotorLoadWrapper m_MotorLoad_OutWrap;			/*!< m_MotorLoad_Outのラッパークラス	*/

	MainMotorProcessor m_MainMotorProcessor;		/*!< メインモータの情報処理クラス		*/
	SubMotorProcessor m_FrontSubMotorProcessor;		/*!< 前方サブモータの情報処理クラス		*/
	SubMotorProcessor m_BackSubMotorProcessor;		/*!< 後方サブモータの情報処理クラス		*/

	struct timeval m_stTimeval;						/*!< 実行時刻							*/

	struct timeval m_stModeReadTime;				/*!< m_Mode_Inの入力時刻				*/
	struct timeval m_stVelocity2DReadTime;			/*!< m_Velocity2D_Inの入力時刻			*/
	struct timeval m_stFlipperPwmReadTime;			/*!< m_FlipperPwm_Inの入力時刻			*/

	long m_lRollCycle;								/*!< 外部観測した姿勢(ロール)の周回数	*/
	long m_lPitchCycle;								/*!< 外部観測した姿勢(ピッチ)の周回数	*/
	long m_lYawCycle;								/*!< 外部観測した姿勢(ヨー)の周回数		*/

};


extern "C"
{
	DLL_EXPORT void RTC_Spider2020_CrawlerInit(RTC::Manager* manager);
};

#endif // RTC_SPIDER2020_CRAWLER_H
