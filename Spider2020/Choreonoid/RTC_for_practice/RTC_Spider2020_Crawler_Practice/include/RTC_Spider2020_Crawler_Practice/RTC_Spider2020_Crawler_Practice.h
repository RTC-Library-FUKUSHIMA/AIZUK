// -*- C++ -*-
/*!
 * @file  RTC_Spider2020_Crawler_Practice.h
 * @brief Spider2020 コレオノイドモデルの台車制御RTC
 * @date  $Date$
 *
 * $Id$
 */

#ifndef RTC_SPIDER2020_CRAWLER_PRACTICE_H
#define RTC_SPIDER2020_CRAWLER_PRACTICE_H

#include <cnoid/BodyIoRTC>
#include <cnoid/EigenUtil>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">
#include "ExtendedDataTypesStub.h"
#include "BasicDataTypeStub.h"

// </rtc-template>

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

#include "FlipperPwmWrapper.h"

using namespace cnoid;

/*!
 * @enum 列挙子
 * リンクデータのインデクサ
 */
enum LINK_t
{
	LINK_CHASSIS,					/*!< シャーシ						*/
	LINK_FR_FLIPPER,				/*!< 右前方フリッパー				*/
	LINK_FL_FLIPPER,				/*!< 左前方フリッパー				*/
	LINK_BR_FLIPPER,				/*!< 右後方フリッパー				*/
	LINK_BL_FLIPPER,				/*!< 左後方フリッパー				*/
	LINK_R_BELT,					/*!< 右メインベルト					*/
	LINK_L_BELT,					/*!< 左メインベルト					*/
	LINK_FR_SUB_BELT,				/*!< 右前方サブベルト				*/
	LINK_FL_SUB_BELT,				/*!< 左前方サブベルト				*/
	LINK_BR_SUB_BELT,				/*!< 右後方サブベルト				*/
	LINK_BL_SUB_BELT,				/*!< 左後方サブベルト				*/
	LINK_R_BELT_SPROCKET,			/*!< 右メインベルトスプロケット		*/
	LINK_L_BELT_SPROCKET,			/*!< 左メインベルトスプロケット		*/
	LINK_FR_SUB_BELT_SPROCKET,		/*!< 右前方サブベルトスプロケット	*/
	LINK_FL_SUB_BELT_SPROCKET,		/*!< 左前方サブベルトスプロケット	*/
	LINK_BR_SUB_BELT_SPROCKET,		/*!< 右後方サブベルトスプロケット	*/
	LINK_BL_SUB_BELT_SPROCKET,		/*!< 左後方サブベルトスプロケット	*/
	LINK_NUM,						/*!< リンクデータの数				*/
};

/*!
 * @enum 列挙子
 * 関節データのインデクサ
 */
enum JOINT_t
{
	JOINT_FR_FLIPPER,	/*!< 右前方フリッパー	*/
	JOINT_FL_FLIPPER,	/*!< 左前方フリッパー	*/
	JOINT_BR_FLIPPER,	/*!< 右後方フリッパー	*/
	JOINT_BL_FLIPPER,	/*!< 左後方フリッパー	*/
	JOINT_NUM,			/*!< 関節データの数		*/
};

/*!
 * @class RTC_Spider2020_Crawler_Practice
 * @brief Spider2020 コレオノイドモデルの台車制御RTC
 *
 */
class RTC_Spider2020_Crawler_Practice
  : public BodyIoRTC
{
public:
	/*!
	 * @brief constructor
	 * @param manager Maneger Object
	 */
	RTC_Spider2020_Crawler_Practice(RTC::Manager* manager);

	/*!
	 * @brief destructor
	 */
	~RTC_Spider2020_Crawler_Practice();

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
	virtual RTC::ReturnCode_t onInitialize(Body* body) override;

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
	// virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

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
	// virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

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
	 * シミュレーションの開始処理
	 * @method initializeSimulation
	 * @param io IOオブジェクトのポインタ
	 * @retval true 正常終了
	 * @retval false 異常終了
	 */
	virtual bool initializeSimulation(ControllerIO* io) override;

	/*!
	 * シミュレーションの出力ポートへの書込処理
	 * @method inputFromSimulator
	 * @return なし
	 */
	virtual void inputFromSimulator() override;

	/*!
	 * シミュレーションの入力ポートからの読込処理
	 * @method outputToSimulator
	 * @return なし
	 */
	virtual void outputToSimulator() override;

	/*!
	 * シミュレーションの終了処理
	 * @method stopSimulation
	 * @return なし
	 */
	virtual void stopSimulation() override;

	/*!
	 * ２次元の速度をポートから読み込む
	 * @method ReadVelocity2D
	 * @return なし
	 */
	void ReadVelocity2D(void);

	/*!
	 * ２次元の速度をリンクに書き込む
	 * @method WriteVelocity2D
	 * @return なし
	 */
	void WriteVelocity2D(void);

	/*!
	 * フリッパーのPWM指令をポートから読み込む
	 * @method ReadFlipperPwm
	 * @return なし
	 */
	void ReadFlipperPwm(void);

	/*!
	 * フリッパーのPWM指令をリンクに書き込む
	 * @method WriteFlipperPwm
	 * @return なし
	 */
	void WriteFlipperPwm(void);

	/*!
	 * PWM指令からモータの回転数を求め、目標角度を対象にトルクでPD制御する
	 * @method FlipperPwm
	 * @param iJointIndex 関節データのインデクサ
	 * @param lPwm PWM指令
	 */
	void FlipperPwm(int iJointIndex, long lPwm);

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
	 * Turning Radius
	 * - Name: 旋回半径 TURNING_RADIUS
	 * - DefaultValue: 0.0938
	 * - Unit: [m]
	 */
	double m_TURNING_RADIUS;
	/*!
	 * メインモータの最大連続トルク
	 * - Name: トルク MAIN_MOTOR_TORQUE
	 * - DefaultValue: 405e-3
	 * - Unit: [Nm]
	 */
	double m_MAIN_MOTOR_TORQUE;
	/*!
	 * メインモータの無負荷回転数
	 * - Name: 回転数 MAIN_MOTOR_RPM
	 * - DefaultValue: 5950
	 * - Unit: [rpm]
	 */
	long int m_MAIN_MOTOR_RPM;
	/*!
	 * メインモータのトルク勾配
	 * - Name: トルク勾配 MAIN_MOTOR_GRADIENT
	 * - DefaultValue: 0.668e+3
	 * - Unit: [rpm/Nm]
	 */
	double m_MAIN_MOTOR_GRADIENT;
	/*!
	 * メインモータの減速比
	 * - Name: 減速比 MAIN_MOTOR_GEAR_RATIO
	 * - DefaultValue: 243
	 */
	double m_MAIN_MOTOR_GEAR_RATIO;
	/*!
	 * サブモータの最大連続トルク
	 * - Name: トルク SUB_MOTOR_TORQUE
	 * - DefaultValue: 105e-3
	 * - Unit: [Nm]
	 */
	double m_SUB_MOTOR_TORQUE;
	/*!
	 * サブモータの無負荷回転数
	 * - Name: 回転数 SUB_MOTOR_RPM
	 * - DefaultValue: 7750
	 * - Unit: [rpm]
	 */
	long int m_SUB_MOTOR_RPM;
	/*!
	 * サブモータのトルク勾配
	 * - Name: トルク勾配 SUB_MOTOR_GRADIENT
	 * - DefaultValue: 6.54e+3
	 * - Unit: [rpm/Nm]
	 */
	double m_SUB_MOTOR_GRADIENT;
	/*!
	 * サブモータの減速比
	 * - Name: 減速比 SUB_MOTOR_GEAR_RATIO
	 * - DefaultValue: 1080
	 */
	double m_SUB_MOTOR_GEAR_RATIO;
	/*!
	 * 入力ポートへ指定時間以上新しい入力がなければ、
	 * 暴走を回避するため入力データのクリアなどを実施する。
	 * - Name: フェイルセーフ時間 FAILSAFE_SEC
	 * - DefaultValue: 1.0
	 */
	double m_FAILSAFE_SEC;

	// </rtc-template>

	// DataInPort declaration
	// <rtc-template block="inport_declare">
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

	// </rtc-template>


	// DataOutPort declaration
	// <rtc-template block="outport_declare">

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

	FlipperPwmWrapper m_FlipperPwm_InWrap;			/*!< m_FlipperPwm_Inのラッパークラス	*/

	Link*		m_cnoid_Link[LINK_NUM];				/*!< コレオノイドモデルのリンク			*/
	double		m_cnoid_RefAngle[JOINT_NUM];		/*!< コレオノイドモデルの目標関節角度	*/
	double		m_cnoid_MotorAngle[JOINT_NUM];		/*!< サブモータの角度					*/
	double		m_cnoid_TimeStep;					/*!< シミュレーションの周期				*/

	bool		m_bPseudoContinuousTrack;			/*!< 無限軌道の判別フラグ				*/

	struct timeval m_stVelocity2DReadTime;			/*!< m_Velocity2D_Inの入力時刻			*/
	struct timeval m_stFlipperPwmReadTime;			/*!< m_FlipperPwm_Inの入力時刻			*/

};


extern "C"
{
	DLL_EXPORT void RTC_Spider2020_Crawler_PracticeInit(RTC::Manager* manager);
};

#endif // RTC_SPIDER2020_CRAWLER_PRACTICE_H
