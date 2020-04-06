// -*- C++ -*-
/*!
 * @file  RTC_Spider2020_Motion.h
 * @brief ロボットの動作指令を生成する
 * @date  $Date$
 *
 * $Id$
 */

#ifndef RTC_SPIDER2020_MOTION_H
#define RTC_SPIDER2020_MOTION_H

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

#include "AxisWrapper.h"
#include "ButtonWrapper.h"
#include "FingerDeltaWrapper.h"
#include "FlipperPwmWrapper.h"
#include "ModeWrapper.h"

/*!
 * @class RTC_Spider2020_Motion
 * @brief ロボットの動作指令を生成する
 *
 */
class RTC_Spider2020_Motion
  : public RTC::DataFlowComponentBase
{
public:
	/*!
	 * @brief constructor
	 * @param manager Maneger Object
	 */
	RTC_Spider2020_Motion(RTC::Manager* manager);

	/*!
	 * @brief destructor
	 */
	~RTC_Spider2020_Motion();

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
	// virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

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
	 * 軸キーの入力具合をポートから読み込む
	 * @method ReadAxis
	 * @return なし
	 */
	void ReadAxis(void);

	/*!
	 * ボタンの押下状態をポートから読み込む
	 * @method ReadButton
	 * @return なし
	 */
	void ReadButton(void);

	/*!
	 * 動作指令の状態を更新してポートに出力する
	 * @method WriteMode
	 * @return なし
	 */
	void WriteMode(void);

	/*!
	 * 走行モードの動作指令を生成してポートに出力する
	 * @method WriteCrawlerMotion
	 * @return なし
	 */
	void WriteCrawlerMotion(void);

	/*!
	 * IMUのフィルタリセット指令の状態を更新してポートに出力する
	 * @method WriteResetIMU
	 * @return なし
	 */
	void WriteResetIMU(void);

	/*!
	 * アームモードの動作指令を生成してポートに出力する
	 * @method WriteArmMotion
	 * @return なし
	 */
	void WriteArmMotion(void);


protected:
	// <rtc-template block="protected_attribute">

	// </rtc-template>

	// <rtc-template block="protected_operation">

	// </rtc-template>

	// Configuration variable declaration
	// <rtc-template block="config_declare">
	/*!
	 *
	 * - Name: 並進ゲイン VELOCITY_GAIN
	 * - DefaultValue: 0.15
	 */
	double m_VELOCITY_GAIN;
	/*!
	 *
	 * - Name: 旋回ゲイン OMEGA_GAIN
	 * - DefaultValue: 0.785
	 */
	double m_OMEGA_GAIN;
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
	RTC::TimedDoubleSeq m_Axis_In;
	/*!
	 * DualShock4コントローラの軸キーの入力具合
	 * - Type: TimedDoubleSeq
	 * - Number: 8
	 */
	RTC::InPort<RTC::TimedDoubleSeq> m_Axis_InIn;
	RTC::TimedULong m_Button_In;
	/*!
	 * DualShock4コントローラのボタンの押下状態
	 * - Type: TimedULong
	 * - Number: 14
	 */
	RTC::InPort<RTC::TimedULong> m_Button_InIn;

	// </rtc-template>


	// DataOutPort declaration
	// <rtc-template block="outport_declare">
	RTC::TimedLongSeq m_Mode_Out;
	/*!
	 * 動作指令の状態
	 * - Type: TimedLongSeq
	 * - Number: 9
	 */
	RTC::OutPort<RTC::TimedLongSeq> m_Mode_OutOut;
	RTC::TimedVelocity2D m_Velocity2D_Out;
	/*!
	 * ２次元の速度
	 * - Type: TimedVelocity2D
	 */
	RTC::OutPort<RTC::TimedVelocity2D> m_Velocity2D_OutOut;
	RTC::TimedLongSeq m_FlipperPwm_Out;
	/*!
	 * フリッパーのPWM指令
	 * - Type: TimedLongSeq
	 * - Number: 4
	 */
	RTC::OutPort<RTC::TimedLongSeq> m_FlipperPwm_OutOut;
	RTC::TimedLong m_ResetIMU_Out;
	/*!
	 * IMUのフィルタリセット指令
	 * - Type: TimedLong
	 * - Number: 1
	 * - Semantics: 0: フィルタをリセットする
	 *              1: フィルタをリセットしない
	 */
	RTC::OutPort<RTC::TimedLong> m_ResetIMU_OutOut;

	RTC::TimedPose3D m_Arm1PoseDelta_Out;
	/*!
	 * Jaco2アーム（１本目）の手先位置姿勢の変位速度
	 * - Type: TimedPose3D
	 */
	RTC::OutPort<RTC::TimedPose3D> m_Arm1PoseDelta_OutOut;
	RTC::TimedLongSeq m_Arm1FingerDelta_Out;
	/*!
	 * Jaco2アーム（１本目）の指の開閉具合の変位速度
	 * - Type: TimedLongSeq
	 */
	RTC::OutPort<RTC::TimedLongSeq> m_Arm1FingerDelta_OutOut;
	RTC::TimedLong m_Arm1Home_Out;
	/*!
	 * Jaco2アーム（１本目）の初期姿勢遷移指令
	 * - Type: TimedLong
	 * - Number: 3
	 */
	RTC::OutPort<RTC::TimedLong> m_Arm1Home_OutOut;

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

	RTC::TimedDoubleSeq m_OldAxis_In;					/*!< 前回の軸キーの入力具合				*/
	RTC::TimedULong m_OldButton_In;						/*!< 前回のボタンの押下状態				*/

	AxisWrapper m_Axis_InWrap;							/*!< m_Axis_Inのラッパークラス			*/
	AxisWrapper m_OldAxis_InWrap;						/*!< m_OldAxis_Inのラッパークラス		*/
	ButtonWrapper m_Button_InWrap;						/*!< m_Button_Inのラッパークラス		*/
	ButtonWrapper m_OldButton_InWrap;					/*!< m_OldButton_Inのラッパークラス		*/
	ModeWrapper m_Mode_OutWrap;							/*!< m_Mode_Outのラッパークラス			*/
	FlipperPwmWrapper m_FlipperPwm_OutWrap;				/*!< m_FlipperPwm_Outのラッパークラス	*/
	FingerDeltaWrapper m_Arm1FingerDelta_OutWrap;		/*!< m_FingerDelta_Outのラッパークラス	*/

	struct timeval m_stAxisReadTime;					/*!< m_Axis_Inの入力時刻				*/
	struct timeval m_stButtonReadTime;					/*!< m_Button_Inの入力時刻				*/

};


extern "C"
{
	DLL_EXPORT void RTC_Spider2020_MotionInit(RTC::Manager* manager);
};

#endif // RTC_SPIDER2020_MOTION_H
