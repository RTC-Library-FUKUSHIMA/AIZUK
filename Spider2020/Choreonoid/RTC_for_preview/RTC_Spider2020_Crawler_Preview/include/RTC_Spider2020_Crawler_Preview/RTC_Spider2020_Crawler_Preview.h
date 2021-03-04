// -*- C++ -*-
/*!
 * @file  RTC_Spider2020_Crawler_Preview.h
 * @brief Spider2020 コレオノイドモデルの台車プレビューRTC
 * @date  $Date$
 *
 * $Id$
 */

#ifndef RTC_SPIDER2020_CRAWLER_PREVIEW_H
#define RTC_SPIDER2020_CRAWLER_PREVIEW_H

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

#include "FlipperAngleWrapper.h"

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
	LINK_NUM,						/*!< リンクデータの数				*/
};

/*!
 * @class RTC_Spider2020_Crawler_Preview
 * @brief Spider2020 コレオノイドモデルの台車プレビューRTC
 *
 */
class RTC_Spider2020_Crawler_Preview
  : public BodyIoRTC
{
public:
	/*!
	 * @brief constructor
	 * @param manager Maneger Object
	 */
	RTC_Spider2020_Crawler_Preview(RTC::Manager* manager);

	/*!
	 * @brief destructor
	 */
	~RTC_Spider2020_Crawler_Preview();

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


protected:
	// <rtc-template block="protected_attribute">

	// </rtc-template>

	// <rtc-template block="protected_operation">

	// </rtc-template>

	// Configuration variable declaration
	// <rtc-template block="config_declare">
	/*!
	 * シャーシのZ座標
	 * - Name: Z座標 CHASSIS_Z
	 * - DefaultValue: 0.0081
	 * - Unit: [m]
	 */
	double m_CHASSIS_Z;

	// </rtc-template>

	// DataInPort declaration
	// <rtc-template block="inport_declare">
	RTC::TimedPose3D m_Pose3D_In;
	/*!
	 * ３次元の位置・姿勢
	 * - Type: TimedPose3D
	 * - Number: 1
	 * - Unit: [m,rad]
	 */
	RTC::InPort<RTC::TimedPose3D> m_Pose3D_InIn;
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


	FlipperAngleWrapper m_FlipperAngle_InWrap;		/*!< m_FlipperAngle_Inのラッパークラス	*/

	Link*		m_cnoid_Link[LINK_NUM];				/*!< コレオノイドモデルのリンク			*/

};


extern "C"
{
	DLL_EXPORT void RTC_Spider2020_Crawler_PreviewInit(RTC::Manager* manager);
};

#endif // RTC_SPIDER2020_CRAWLER_PREVIEW_H
