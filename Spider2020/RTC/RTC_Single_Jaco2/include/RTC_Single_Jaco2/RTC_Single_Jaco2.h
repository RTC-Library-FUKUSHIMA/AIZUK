// -*- C++ -*-
/*!
 * @file  RTC_Single_Jaco2.h
 * @brief １本のJaco2アームを速度指令で制御する
 * @date  $Date$
 *
 * $Id$
 */

#ifndef RTC_SINGLE_JACO2_H
#define RTC_SINGLE_JACO2_H

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
#include "FingerDeltaWrapper.h"
#include "FingerStatusWrapper.h"

/*!
 * @class RTC_Single_Jaco2
 * @brief １本のJaco2アームを速度指令で制御する
 *
 */
class RTC_Single_Jaco2
  : public RTC::DataFlowComponentBase
{
public:
	/*!
	 * @brief constructor
	 * @param manager Maneger Object
	 */
	RTC_Single_Jaco2(RTC::Manager* manager);

	/*!
	 * @brief destructor
	 */
	~RTC_Single_Jaco2();

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
	 * 手先位置姿勢の変位速度をポートから読み込む
	 * @method ReadPoseDelta
	 * @return なし
	 */
	void ReadPoseDelta(void);

	/*!
	 * 指の開閉具合の変位速度をポートから読み込む
	 * @method ReadFingerDelta
	 * @return なし
	 */
	void ReadFingerDelta(void);

	/*!
	 * 初期姿勢遷移指令をポートから読み込む
	 * @method ReadHome
	 * @return なし
	 */
	void ReadHome(void);

	/*!
	 * 手先位置姿勢をポートに出力する
	 * @method WritePose3D
	 * @return なし
	 */
	void WritePose3D(void);

	/*!
	 * 腕の角度をポートに出力する
	 * @method WriteAngular
	 * @return なし
	 */
	void WriteAngular(void);

	/*!
	 * 指の開閉具合をポートに出力する
	 * @method WriteFinger
	 * @return なし
	 */
	void WriteFinger(void);

	/*!
	 * モータ負荷をポートに出力する
	 * @method WriteCurrent
	 * @return なし
	 */
	void WriteCurrent(void);

protected:
	// <rtc-template block="protected_attribute">

	// </rtc-template>

	// <rtc-template block="protected_operation">

	// </rtc-template>

	// Configuration variable declaration
	// <rtc-template block="config_declare">
	/*!
	 * 入力ポートへ指定時間以上新しい入力がなければ、
	 * 暴走を回避するため入力データのクリアなどを実施する。
	 * - Name: フェイルセーフ時間 FAILSAFE_SEC
	 * - DefaultValue: 1.0
	 */
	double m_FAILSAFE_SEC;
	/*!
	 * Jaco2アームの情報を出力する周期
	 * ※Jaco2アームから情報を取得するのに数十msかかるため、周期を短
	 * くするとアーム制御が不安定になる。
	 * - Name: OutPort出力周期 OUT_SEC
	 * - DefaultValue: 0.2
	 * - Unit: [s]
	 */
	double m_OUT_SEC;

	// </rtc-template>

	// DataInPort declaration
	// <rtc-template block="inport_declare">
	RTC::TimedPose3D m_PoseDelta_In;
	/*!
	 * 手先位置姿勢の変位速度
	 * - Type: TimedPose3D
	 * - Number: 1
	 * - Unit: [m,rad]
	 */
	RTC::InPort<RTC::TimedPose3D> m_PoseDelta_InIn;
	RTC::TimedLongSeq m_FingerDelta_In;
	/*!
	 * 指の開閉具合の変位速度
	 * - Type: TimedLongSeq
	 * - Number: 3
	 * - Semantics: [0]: 親指
	 *              [1]: 差指
	 *              [2]: 中指
	 * - Unit: [u]
	 */
	RTC::InPort<RTC::TimedLongSeq> m_FingerDelta_InIn;
	RTC::TimedLong m_Home_In;
	/*!
	 * 初期姿勢遷移指令
	 * - Type: TimedLong
	 * - Number: 1
	 */
	RTC::InPort<RTC::TimedLong> m_Home_InIn;

	// </rtc-template>


	// DataOutPort declaration
	// <rtc-template block="outport_declare">
	RTC::TimedPose3D m_Pose3D_Out;
	/*!
	 * 手先位置姿勢
	 * (ロボット座標系)
	 * - Type: TimedPose3D
	 * - Number: 1
	 * - Unit: [m,rad]
	 */
	RTC::OutPort<RTC::TimedPose3D> m_Pose3D_OutOut;
	RTC::TimedDoubleSeq m_Angular_Out;
	/*!
	 * 腕の角度
	 * - Type: TimedDoubleSeq
	 * - Number: 6
	 * - Semantics: [0]: 腕の1軸目
	 *              [1]: 腕の2軸目
	 *              [2]: 腕の3軸目
	 *              [3]: 腕の4軸目
	 *              [4]: 腕の5軸目
	 *              [5]: 腕の6軸目
	 */
	RTC::OutPort<RTC::TimedDoubleSeq> m_Angular_OutOut;
	RTC::TimedLongSeq m_Finger_Out;
	/*!
	 * 指の開閉具合
	 * - Type: TimedLongSeq
	 * - Number: 3
	 * - Semantics: [0]: 親指
	 *              [1]: 差指
	 *              [2]: 中指
	 * - Unit: [u]
	 */
	RTC::OutPort<RTC::TimedLongSeq> m_Finger_OutOut;
	RTC::TimedDoubleSeq m_Current_Out;
	/*!
	 * モータ負荷
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
	RTC::OutPort<RTC::TimedDoubleSeq> m_Current_OutOut;

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

	FingerDeltaWrapper m_FingerDelta_InWrap;	/*!< m_FingerDelta_Inのラッパークラス	*/

	ArmAngularWrapper m_Angular_OutWrap;		/*!< m_Angular_Outのラッパークラス		*/
	ArmCurrentWrapper m_Current_OutWrap;		/*!< m_Current_Outのラッパークラス		*/
	FingerStatusWrapper m_Finger_OutWrap;		/*!< m_Finger_Outのラッパークラス		*/

	struct timeval m_stPoseDeltaReadTime;		/*!< m_PoseDelta_Inの入力時刻			*/
	struct timeval m_stFingerDeltaReadTime;		/*!< m_FingerDelta_Inの入力時刻			*/

	struct timeval m_stInfoWriteTime;			/*!< 情報の出力時刻						*/

};


extern "C"
{
	DLL_EXPORT void RTC_Single_Jaco2Init(RTC::Manager* manager);
};

#endif // RTC_SINGLE_JACO2_H
