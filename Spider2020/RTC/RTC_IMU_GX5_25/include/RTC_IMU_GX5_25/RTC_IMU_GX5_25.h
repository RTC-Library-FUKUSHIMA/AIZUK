// -*- C++ -*-
/*!
 * @file  RTC_IMU_GX5_25.h
 * @brief LORD製の3DM-GX5-25から姿勢情報を取得する
 * @date  $Date$
 *
 * $Id$
 */

#ifndef RTC_IMU_GX5_25_H
#define RTC_IMU_GX5_25_H

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

#include "IMU_GX5_25_Capture.h"

/*!
 * @class RTC_IMU_GX5_25
 * @brief LORD製の3DM-GX5-25から姿勢情報を取得する
 *
 */
class RTC_IMU_GX5_25
  : public RTC::DataFlowComponentBase
{
public:
	/*!
	* @brief constructor
	* @param manager Maneger Object
	*/
	RTC_IMU_GX5_25(RTC::Manager* manager);

	/*!
	* @brief destructor
	*/
	~RTC_IMU_GX5_25();

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
	 * リセットフィルタ指令をポートから読み込む
	 * @method ReadResetFilter
	 * @return なし
	 */
	void ReadResetFilter(void);

	/*!
	 * ３軸の加速度をポートに出力する
	 * @method WriteAcceleration3D
	 * @return なし
	 */
	void WriteAcceleration3D(void);

	/*!
	 * ３次元の姿勢をポートに出力する
	 * @method WriteOrientation3D
	 * @return なし
	 */
	void WriteOrientation3D(void);


protected:
	// <rtc-template block="protected_attribute">

	// </rtc-template>

	// <rtc-template block="protected_operation">

	// </rtc-template>

	// Configuration variable declaration
	// <rtc-template block="config_declare">
	/*!
	 * 3DM-GX5-25のデバイス名
	 * - Name: デバイス名 DEVICE_NAME
	 * - DefaultValue: /dev/ttyACM0
	 */
	std::string m_DEVICE_NAME;
	/*!
	 * IMUの座標系をロボットの座標系に合わせるための回転量
	 * - Name: X軸の回転 X_ROTATION
	 * - DefaultValue: 0.0
	 * - Unit: [deg]
	 */
	double m_X_ROTATION;
	/*!
	 * IMUの座標系をロボットの座標系に合わせるための回転量
	 * - Name: Y軸の回転 Y_ROTATION
	 * - DefaultValue: 0.0
	 * - Unit: [deg]
	 */
	double m_Y_ROTATION;
	/*!
	 * IMUの座標系をロボットの座標系に合わせるための回転量
	 * - Name: Z軸の回転 Z_ROTATION
	 * - DefaultValue: 0.0
	 * - Unit: [deg]
	 */
	double m_Z_ROTATION;

	// </rtc-template>

	// DataInPort declaration
	// <rtc-template block="inport_declare">
	RTC::TimedLong m_ResetFilter_In;
	/*!
	 * フィルタをリセットする
	 * - Type: TimedLong
	 * - Number: 1
	 * - Semantics: 0: リセットしない
	 *              1: リセットする
	 */
	RTC::InPort<RTC::TimedLong> m_ResetFilter_InIn;

	// </rtc-template>


	// DataOutPort declaration
	// <rtc-template block="outport_declare">
	RTC::TimedAcceleration3D m_Acceleration3D_Out;
	/*!
	 * ロボットの座標系に合わせた３軸の加速度
	 * - Type: TimedAcceleration3D
	 * - Number: 1
	 * - Unit: [m/s^2]
	 */
	RTC::OutPort<RTC::TimedAcceleration3D> m_Acceleration3D_OutOut;
	RTC::TimedOrientation3D m_Orientation3D_Out;
	/*!
	* ロボットの座標系に合わせた３次元の姿勢
	* - Type: TimedOrientation3D
	* - Number: 1
	* - Unit: [rad]
	*/
	RTC::OutPort<RTC::TimedOrientation3D> m_Orientation3D_OutOut;

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

	IMU_GX5_25_Capture m_IMUCapture;	/*!< LORD製3DM-GX5-25の情報の取得クラス */

	long m_lLastResetFilter;			/*!< 前回のフィルタをリセット指令		*/

};


extern "C"
{
	DLL_EXPORT void RTC_IMU_GX5_25Init(RTC::Manager* manager);
};

#endif // RTC_IMU_GX5_25_H
