// -*- C++ -*-
/*!
 * @file  RTC_Spider2020_Log.h
 * @brief Spider2020 ログ出力RTC
 * @date  $Date$
 *
 * $Id$
 */

#ifndef RTC_SPIDER2020_LOG_H
#define RTC_SPIDER2020_LOG_H

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

#include "ArmAngularWrapper.h"
#include "ArmCurrentWrapper.h"
#include "AxisWrapper.h"
#include "ButtonWrapper.h"
#include "FingerStatusWrapper.h"
#include "FlipperAngleWrapper.h"
#include "ModeWrapper.h"
#include "MotorLoadWrapper.h"

/*!
 * @class RTC_Spider2020_Log
 * @brief Spider2020 ログ出力RTC
 *
 */
class RTC_Spider2020_Log
  : public RTC::DataFlowComponentBase
{
public:
	/*!
	 * @brief constructor
	 * @param manager Maneger Object
	 */
	RTC_Spider2020_Log(RTC::Manager* manager);

	/*!
	 * @brief destructor
	 */
	~RTC_Spider2020_Log();

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
	 * 現在の日時を取得する
	 * 書式: YYYY-MM-DD hh:mm:ss.uuuuuu
	 * @method GetDateTimeString
	 * @return 日時の文字列
	 */
	std::string GetDateTimeString(void);

	/*!
	 * ロボット識別子のヘッダーをログファイルに出力する
	 * @method OutputRobotIDHeaders
	 * @return なし
	 */
	void OutputRobotIDHeaders(void);

	/*!
	 * ロボット識別子をログファイルとポートに書き込む
	 * @method WriteRobotID
	 * @return なし
	 */
	void WriteRobotID(void);

	/*!
	 * ３次元の位置姿勢のヘッダーをログファイルに出力する
	 * @method OutputPose3DHeaders
	 * @return なし
	 */
	void OutputPose3DHeaders(void);

	/*!
	 * ３次元の位置姿勢をポートから読み込む
	 * @method ReadPose3D
	 * @return なし
	 */
	void ReadPose3D(void);

	/*!
	 * ３次元の位置姿勢をログファイルとポートに書き込む
	 * @method WritePose3D
	 * @return なし
	 */
	void WritePose3D(void);

	/*!
	 * モータの負荷のヘッダーをログファイルに出力する
	 * @method OutputMotorLoadHeaders
	 * @return なし
	 */
	void OutputMotorLoadHeaders(void);

	/*!
	 * モータの負荷をポートから読み込む
	 * @method ReadMotorLoad
	 * @return なし
	 */
	void ReadMotorLoad(void);

	/*!
	 * モータの負荷をログファイルとポートに書き込む
	 * @method WriteMotorLoad
	 * @return なし
	 */
	void WriteMotorLoad(void);

	/*!
	 * フリッパーの角度のヘッダーをログファイルに出力する
	 * @method OutputFlipperAngleHeaders
	 * @return なし
	 */
	void OutputFlipperAngleHeaders(void);

	/*!
	 * フリッパーの角度をポートから読み込む
	 * @method ReadFlipperAngle
	 * @return なし
	 */
	void ReadFlipperAngle(void);

	/*!
	 * フリッパーの角度をログファイルとポートに書き込む
	 * @method WriteFlipperAngle
	 * @return なし
	 */
	void WriteFlipperAngle(void);

	/*!
	 * ３次元の姿勢(IMU)のヘッダーをログファイルに出力する
	 * @method OutputIMUOrientation3DHeaders
	 * @return なし
	 */
	void OutputIMUOrientation3DHeaders(void);

	/*!
	 * ３次元の姿勢(IMU)をポートから読み込む
	 * @method ReadIMUOrientation3D
	 * @return なし
	 */
	void ReadIMUOrientation3D(void);

	/*!
	 * ３次元の姿勢(IMU)をログファイルとポートに書き込む
	 * @method WriteIMUOrientation3D
	 * @return なし
	 */
	void WriteIMUOrientation3D(void);

	/*!
	 * メインクローラの速度のヘッダーをログファイルに出力する
	 * @method OutputVelocity2DHeaders
	 * @return なし
	 */
	void OutputVelocity2DHeaders(void);

	/*!
	 * メインクローラの速度をポートから読み込む
	 * @method ReadVelocity2D
	 * @return なし
	 */
	void ReadVelocity2D(void);

	/*!
	 * メインクローラの速度をログファイルとポートに書き込む
	 * @method WriteVelocity2D
	 * @return なし
	 */
	void WriteVelocity2D(void);

	/*!
	 * ゲームコントローラのバッテリ残容量比のヘッダーをログファイルに出力する
	 * @method OutputGCCapacityRatioHeaders
	 * @return なし
	 */
	void OutputGCCapacityRatioHeaders(void);

	/*!
	 * ゲームコントローラのバッテリ残容量比をポートから読み込む
	 * @method ReadGCCapacityRatio
	 * @return なし
	 */
	void ReadGCCapacityRatio(void);

	/*!
	 * ゲームコントローラのバッテリ残容量比をログファイルとポートに書き込む
	 * @method WriteGCCapacityRatio
	 * @return なし
	 */
	void WriteGCCapacityRatio(void);

	/*!
	 * ゲームコントローラの軸キーの入力具合のヘッダーをログファイルに出力する
	 * @method OutputGCAxisHeaders
	 * @return なし
	 */
	void OutputGCAxisHeaders(void);

	/*!
	 * ゲームコントローラの軸キーの入力具合をポートから読み込む
	 * @method ReadGCAxis
	 * @return なし
	 */
	void ReadGCAxis(void);

	/*!
	 * ゲームコントローラの軸キーの入力具合をログファイルとポートに書き込む
	 * @method WriteGCAxis
	 * @return なし
	 */
	void WriteGCAxis(void);

	/*!
	 * ゲームコントローラのボタンの押下状態のヘッダーをログファイルに出力する
	 * @method OutputGCButtonHeaders
	 * @return なし
	 */
	void OutputGCButtonHeaders(void);

	/*!
	 * ゲームコントローラのボタンの押下状態をポートから読み込む
	 * @method ReadGCButton
	 * @return なし
	 */
	void ReadGCButton(void);

	/*!
	 * ゲームコントローラのボタンの押下状態をログファイルとポートに書き込む
	 * @method WriteGCButton
	 * @return なし
	 */
	void WriteGCButton(void);

	/*!
	 * メインバッテリのバッテリ残容量比のヘッダーをログファイルに出力する
	 * @method OutputMainCapacityRatioHeaders
	 * @return なし
	 */
	void OutputMainCapacityRatioHeaders(void);

	/*!
	 * メインバッテリのバッテリ残容量比をポートから読み込む
	 * @method ReadMainCapacityRatio
	 * @return なし
	 */
	void ReadMainCapacityRatio(void);

	/*!
	 * メインバッテリのバッテリ残容量比をログファイルとポートに書き込む
	 * @method WriteMainCapacityRatio
	 * @return なし
	 */
	void WriteMainCapacityRatio(void);

	/*!
	 * 動作指令の状態のヘッダーをログファイルに出力する
	 * @method OutputModeHeaders
	 * @return なし
	 */
	void OutputModeHeaders(void);

	/*!
	 * 動作指令の状態をポートから読み込む
	 * @method ReadMode
	 * @return なし
	 */
	void ReadMode(void);

	/*!
	 * 動作指令の状態をログファイルとポートに書き込む
	 * @method WriteMode
	 * @return なし
	 */
	void WriteMode(void);

	/*!
	 * Jaco2アーム(１本目)の３次元の位置姿勢のヘッダーをログファイルに出力する
	 * @method OutputArm1Pose3DHeaders
	 * @return なし
	 */
	void OutputArm1Pose3DHeaders(void);

	/*!
	 * Jaco2アーム(１本目)の３次元の位置姿勢をポートから読み込む
	 * @method ReadArm1Pose3D
	 * @return なし
	 */
	void ReadArm1Pose3D(void);

	/*!
	 * Jaco2アーム(１本目)の３次元の位置姿勢をログファイルとポートに書き込む
	 * @method WriteArm1Pose3D
	 * @return なし
	 */
	void WriteArm1Pose3D(void);

	/*!
	 * Jaco2アーム(１本目)の腕の角度のヘッダーをログファイルに出力する
	 * @method OutputArm1AngularHeaders
	 * @return なし
	 */
	void OutputArm1AngularHeaders(void);

	/*!
	 * Jaco2アーム(１本目)の腕の角度をポートから読み込む
	 * @method ReadArm1Angular
	 * @return なし
	 */
	void ReadArm1Angular(void);

	/*!
	 *  Jaco2アーム(１本目)の腕の角度をログファイルとポートに書き込む
	 * @method WriteArm1Angular
	 * @return なし
	 */
	void WriteArm1Angular(void);

	/*!
	 * Jaco2アーム(１本目)の指の開閉具合のヘッダーをログファイルに出力する
	 * @method OutputArm1FingerHeaders
	 * @return なし
	 */
	void OutputArm1FingerHeaders(void);

	/*!
	 * Jaco2アーム(１本目)の指の開閉具合をポートから読み込む
	 * @method ReadArm1Finger
	 * @return なし
	 */
	void ReadArm1Finger(void);

	/*!
	 *  Jaco2アーム(１本目)の指の開閉具合をログファイルとポートに書き込む
	 * @method WriteArm1Finger
	 * @return なし
	 */
	void WriteArm1Finger(void);

	/*!
	 * Jaco2アーム(１本目)のモータ負荷のヘッダーをログファイルに出力する
	 * @method OutputArm1CurrentHeaders
	 * @return なし
	 */
	void OutputArm1CurrentHeaders(void);

	/*!
	 * Jaco2アーム(１本目)のモータ負荷をポートから読み込む
	 * @method ReadArm1Current
	 * @return なし
	 */
	void ReadArm1Current(void);

	/*!
	 *  Jaco2アーム(１本目)の指の開閉具合をログファイルとポートに書き込む
	 * @method WriteArm1Current
	 * @return なし
	 */
	void WriteArm1Current(void);

protected:
	// <rtc-template block="protected_attribute">

	// </rtc-template>

	// <rtc-template block="protected_operation">

	// </rtc-template>

	// Configuration variable declaration
	// <rtc-template block="config_declare">
	/*!
	 * ロボット識別子
	 * - Name:  ID
	 * - DefaultValue: spider2020
	 */
	std::string m_ID;

	// </rtc-template>

	// DataInPort declaration
	// <rtc-template block="inport_declare">
	RTC::TimedPose3D m_Pose3D_In;
	/*!
	 * ３次元の位置姿勢
	 * - Type: TimedPose3D
	 * - Number: 1
	 * - Unit: [m,rad]
	 */
	RTC::InPort<RTC::TimedPose3D> m_Pose3D_InIn;
	RTC::TimedDoubleSeq m_MotorLoad_In;
	/*!
	 * モータの負荷
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
	RTC::InPort<RTC::TimedDoubleSeq> m_MotorLoad_InIn;
	RTC::TimedDoubleSeq m_FlipperAngle_In;
	/*!
	 * フリッパーの角度
	 * - Type: TimedDoubleSeq
	 * - Number: 4
	 * - Semantics: [0]: 右前方フリッパー
	 *              [1]: 左前方フリッパー
	 *              [2]: 右後方フリッパー
	 *              [3]: 左後方フリッパー
	 * - Unit: [rad]
	 */
	RTC::InPort<RTC::TimedDoubleSeq> m_FlipperAngle_InIn;
	RTC::TimedOrientation3D m_IMU_Orientation3D_In;
	/*!
	 * ３次元の姿勢
	 * （IMU）
	 * - Type: TimedOrientation3D
	 * - Number: 1
	 * - Unit: [rad]
	 */
	RTC::InPort<RTC::TimedOrientation3D> m_IMU_Orientation3D_InIn;
	RTC::TimedVelocity2D m_Velocity2D_In;
	/*!
	 * メインクローラの速度
	 * - Type: TimedVelocity2D
	 * - Number: 1
	 * - Unit: [m/s,m/s,rad/s]
	 */
	RTC::InPort<RTC::TimedVelocity2D> m_Velocity2D_InIn;
	RTC::TimedDouble m_GCCapacityRatio_In;
	/*!
	 * DualShock4コントローラのバッテリ残容量比
	 * - Type: TimedDouble
	 * - Unit: [%]
	 */
	RTC::InPort<RTC::TimedDouble> m_GCCapacityRatio_InIn;
	RTC::TimedDoubleSeq m_GCAxis_In;
	/*!
	 * DualShock4コントローラの軸キーの入力具合
	 * - Type: TimedDoubleSeq
	 */
	RTC::InPort<RTC::TimedDoubleSeq> m_GCAxis_InIn;
	RTC::TimedULong m_GCButton_In;
	/*!
	 * DualShock4コントローラのボタンの押下状態
	 * - Type: TimedULong
	 */
	RTC::InPort<RTC::TimedULong> m_GCButton_InIn;
	RTC::TimedDouble m_MainCapacityRatio_In;
	/*!
	 * メインバッテリのバッテリ残存容量比
	 * - Type: TimedDouble
	 * - Unit: [%]
	 */
	RTC::InPort<RTC::TimedDouble> m_MainCapacityRatio_InIn;
	RTC::TimedLongSeq m_Mode_In;
	/*!
	 * 動作指令の状態
	 * - Type: TimedLongSeq
	 * - Number: 6
	 */
	RTC::InPort<RTC::TimedLongSeq> m_Mode_InIn;
	RTC::TimedPose3D m_Arm1Pose3D_In;
	/*!
	 * Arm1の位置姿勢
	 * （ロボット座標系）
	 * - Type: TimedPose3D
	 * - Number: 1
	 * - Unit: [m,rad]
	 */
	RTC::InPort<RTC::TimedPose3D> m_Arm1Pose3D_InIn;
	RTC::TimedDoubleSeq m_Arm1Angular_In;
	/*!
	 * Arm1の腕の角度
	 * - Type: TimedDoubleSeq
	 * - Number: 6
	 * - Semantics: [0]: 1軸目
	 *              [1]: 2軸目
	 *              [2]: 3軸目
	 *              [3]: 4軸目
	 *              [4]: 5軸目
	 *              [5]: 6軸目
	 * - Unit: [rad]
	 */
	RTC::InPort<RTC::TimedDoubleSeq> m_Arm1Angular_InIn;
	RTC::TimedLongSeq m_Arm1Finger_In;
	/*!
	 * Arm1の指の開閉具合
	 * - Type: TimedLongSeq
	 * - Number: 3
	 * - Semantics: [0]: 親指
	 *              [1]: 差指
	 *              [2]: 中指
	 * - Unit: [u]
	 */
	RTC::InPort<RTC::TimedLongSeq> m_Arm1Finger_InIn;
	RTC::TimedDoubleSeq m_Arm1Current_In;
	/*!
	 * Arm1のモータ負荷
	 * - Type: TimedDoubleSeq
	 * - Number: 9
	 * - Semantics: [0]: 腕の1軸目
	 *              [1]: 腕の2軸目
	 *              [2]: 腕の3軸目
	 *              [3]: 腕の4軸目
	 *              [4]: 腕の5軸目
	 *              [5]: 腕の6軸目
	 *              [6]: 親指
	 *              [7]: 差指
	 *              [8]: 中指
	 * - Unit: [A]
	 */
	RTC::InPort<RTC::TimedDoubleSeq> m_Arm1Current_InIn;

	// </rtc-template>


	// DataOutPort declaration
	// <rtc-template block="outport_declare">
	RTC::TimedString m_RobotID_Out;
	/*!
	 * ロボット識別子
	 * - Type: TimedString
	 * - Number: 1
	 */
	RTC::OutPort<RTC::TimedString> m_RobotID_OutOut;
	RTC::TimedPose3D m_Pose3D_Out;
	/*!
	 * ３次元の位置姿勢
	 * - Type: TimedPose3D
	 * - Number: 1
	 * - Unit: [m,rad]
	 */
	RTC::OutPort<RTC::TimedPose3D> m_Pose3D_OutOut;
	RTC::TimedDoubleSeq m_MotorLoad_Out;
	/*!
	 * モータの負荷
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
	RTC::TimedDoubleSeq m_FlipperAngle_Out;
	/*!
	 * フリッパーの角度
	 * - Type: TimedDoubleSeq
	 * - Number: 4
	 * - Semantics: [0]: 右前方サブモータ
	 *              [1]: 左前方サブモータ
	 *              [2]: 右後方サブモータ
	 *              [3]: 左後方サブモータ
	 * - Unit: [rad]
	 */
	RTC::OutPort<RTC::TimedDoubleSeq> m_FlipperAngle_OutOut;
	RTC::TimedOrientation3D m_IMU_Orientation3D_Out;
	/*!
	 * ３次元の姿勢
	 * （IMU）
	 * - Type: TimedOrientation3D
	 * - Number: 1
	 * - Unit: [rad]
	 */
	RTC::OutPort<RTC::TimedOrientation3D> m_IMU_Orientation3D_OutOut;
	RTC::TimedVelocity2D m_Velocity2D_Out;
	/*!
	 * メインクローラの速度
	 * - Type: TimedVelocity2D
	 * - Number: 1
	 * - Unit: [m/s,m/s,rad/s]
	 */
	RTC::OutPort<RTC::TimedVelocity2D> m_Velocity2D_OutOut;
	RTC::TimedDouble m_GCCapacityRatio_Out;
	/*!
	 * DualShock4コントローラのバッテリ残容量比
	 * - Type: TimedDouble
	 * - Unit: [%]
	 */
	RTC::OutPort<RTC::TimedDouble> m_GCCapacityRatio_OutOut;
	RTC::TimedDoubleSeq m_GCAxis_Out;
	/*!
	 * DualShock4コントローラの軸キーの入力具合
	 * - Type: TimedDoubleSeq
	 */
	RTC::OutPort<RTC::TimedDoubleSeq> m_GCAxis_OutOut;
	RTC::TimedULong m_GCButton_Out;
	/*!
	 * DualShock4コントローラのボタンの押下状態
	 * - Type: TimedULong
	 */
	RTC::OutPort<RTC::TimedULong> m_GCButton_OutOut;
	RTC::TimedDouble m_MainCapacityRatio_Out;
	/*!
	 * メインバッテリのバッテリ残存容量比
	 * - Type: TimedDouble
	 * - Unit: [%]
	 */
	RTC::OutPort<RTC::TimedDouble> m_MainCapacityRatio_OutOut;
	RTC::TimedLongSeq m_Mode_Out;
	/*!
	 * 動作指令の状態
	 * - Type: TimedLongSeq
	 * - Number: 6
	 */
	RTC::OutPort<RTC::TimedLongSeq> m_Mode_OutOut;
	RTC::TimedPose3D m_Arm1Pose3D_Out;
	/*!
	 * Arm1の位置姿勢
	 * （ロボット座標系）
	 * - Type: TimedPose3D
	 * - Number: 1
	 * - Unit: [m,rad]
	 */
	RTC::OutPort<RTC::TimedPose3D> m_Arm1Pose3D_OutOut;
	RTC::TimedDoubleSeq m_Arm1Angular_Out;
	/*!
	 * Arm1の腕の角度
	 * - Type: TimedDoubleSeq
	 * - Number: 6
	 * - Semantics: [0]: 1軸目
	 *              [1]: 2軸目
	 *              [2]: 3軸目
	 *              [3]: 4軸目
	 *              [4]: 5軸目
	 *              [5]: 6軸目
	 * - Unit: [rad]
	 */
	RTC::OutPort<RTC::TimedDoubleSeq> m_Arm1Angular_OutOut;
	RTC::TimedLongSeq m_Arm1Finger_Out;
	/*!
	 * Arm1の指の開閉具合
	 * - Type: TimedLongSeq
	 * - Number: 3
	 * - Semantics: [0]: 親指
	 *              [1]: 差指
	 *              [2]: 中指
	 * - Unit: [u]
	 */
	RTC::OutPort<RTC::TimedLongSeq> m_Arm1Finger_OutOut;
	RTC::TimedDoubleSeq m_Arm1Current_Out;
	/*!
	 * Arm1のモータ負荷
	 * - Type: TimedDoubleSeq
	 * - Number: 9
	 * - Semantics: [0]: 腕の1軸目
	 *              [1]: 腕の2軸目
	 *              [2]: 腕の3軸目
	 *              [3]: 腕の4軸目
	 *              [4]: 腕の5軸目
	 *              [5]: 腕の6軸目
	 *              [6]: 親指
	 *              [7]: 差指
	 *              [8]: 中指
	 * - Unit: [A]
	 */
	RTC::OutPort<RTC::TimedDoubleSeq> m_Arm1Current_OutOut;

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

	MotorLoadWrapper m_MotorLoad_InWrap;			/*!< m_MotorLoad_Inのラッパークラス		*/
	FlipperAngleWrapper m_FlipperAngle_InWrap;		/*!< m_FlipperAngle_Inのラッパークラス	*/
	ModeWrapper m_Mode_InWrap;						/*!< m_Mode_Inのラッパークラス			*/
	AxisWrapper m_GCAxis_InWrap;					/*!< m_GCAxis_Inのラッパークラス		*/
	ButtonWrapper m_GCButton_InWrap;				/*!< m_GCButton_Inのラッパークラス		*/
	ArmAngularWrapper m_Arm1Angular_InWrap;		/*!< m_Arm1Angular_Inのラッパークラス	*/
	FingerStatusWrapper m_Arm1Finger_InWrap;		/*!< m_Arm1Finger_Inのラッパークラス	*/
	ArmCurrentWrapper m_Arm1Current_InWrap;		/*!< m_Arm1Current_Inのラッパークラス	*/

	MotorLoadWrapper m_MotorLoad_OutWrap;			/*!< m_MotorLoad_Outのラッパークラス	*/
	FlipperAngleWrapper m_FlipperAngle_OutWrap;		/*!< m_FlipperAngle_Outのラッパークラス	*/
	ModeWrapper m_Mode_OutWrap;						/*!< m_Mode_Outのラッパークラス			*/
	AxisWrapper m_GCAxis_OutWrap;					/*!< m_GCAxis_Outのラッパークラス		*/
	ButtonWrapper m_GCButton_OutWrap;				/*!< m_GCButton_Outのラッパークラス		*/
	ArmAngularWrapper m_Arm1Angular_OutWrap;		/*!< m_Arm1Angular_Outのラッパークラス	*/
	FingerStatusWrapper m_Arm1Finger_OutWrap;		/*!< m_Arm1Finger_Outのラッパークラス	*/
	ArmCurrentWrapper m_Arm1Current_OutWrap;		/*!< m_Arm1Current_Outのラッパークラス	*/

	std::ofstream m_Logout_Robot;					/*!< ロボットログファイル出力用			*/

};


extern "C"
{
	DLL_EXPORT void RTC_Spider2020_LogInit(RTC::Manager* manager);
};

#endif // RTC_SPIDER2020_LOG_H
