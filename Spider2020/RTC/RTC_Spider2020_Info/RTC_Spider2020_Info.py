#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

"""
 @file RTC_Spider2020_Info.py
 @brief Spider2020ビューア用のWebSocketサーバRTC
 @date $Date$


"""
import sys
import time
sys.path.append(".")

import os
import json
import threading
from websocket_server import WebsocketServer
WebsocketServer.allow_reuse_address = True

RTC_DIR = os.path.abspath(os.path.dirname(__file__))
VIEWER_CONFIG_FILE = RTC_DIR+"/viewer/config.rtc.json"

# Import RTM module
import RTC
import OpenRTM_aist


# Import Service implementation class
# <rtc-template block="service_impl">

# </rtc-template>

# Import Service stub modules
# <rtc-template block="consumer_import">
# </rtc-template>


# This module's spesification
# <rtc-template block="module_spec">
rtc_spider2020_info_spec = ["implementation_id", "RTC_Spider2020_Info",
		 "type_name",         "RTC_Spider2020_Info",
		 "description",       "Spider2020ビューア用のWebSocketサーバRTC",
		 "version",           "1.0.0",
		 "vendor",            "AIZUK",
		 "category",          "Viewer",
		 "activity_type",     "STATIC",
		 "max_instance",      "1",
		 "language",          "Python",
		 "lang_type",         "SCRIPT",
		 "conf.default.WEBSOCKET_PORT", "8080",
		 "conf.default.WEBSOCKET_HOST", "0.0.0.0",

		 "conf.__widget__.WEBSOCKET_PORT", "text",
		 "conf.__widget__.WEBSOCKET_HOST", "text",

         "conf.__type__.WEBSOCKET_PORT", "int",
         "conf.__type__.WEBSOCKET_HOST", "string",

		 ""]
# </rtc-template>

##
# @class RTC_Spider2020_Info
# @brief Spider2020ビューア用のWebSocketサーバRTC
#
#
class RTC_Spider2020_Info(OpenRTM_aist.DataFlowComponentBase):

	##
	# @brief constructor
	# @param manager Maneger Object
	#
	def __init__(self, manager):
		OpenRTM_aist.DataFlowComponentBase.__init__(self, manager)

		self._d_GCCapacityRatio_In = OpenRTM_aist.instantiateDataType(RTC.TimedDouble)
		"""
		ゲームコントローラのバッテリ残容量比
		 - Unit: [%]
		"""
		self._GCCapacityRatio_InIn = OpenRTM_aist.InPort("GCCapacityRatio_In", self._d_GCCapacityRatio_In)
		self._d_MainCapacityRatio_In = OpenRTM_aist.instantiateDataType(RTC.TimedDouble)
		"""
		メインバッテリのバッテリ残容量比
		 - Unit: [%]
		"""
		self._MainCapacityRatio_InIn = OpenRTM_aist.InPort("MainCapacityRatio_In", self._d_MainCapacityRatio_In)
		self._d_Mode_In = OpenRTM_aist.instantiateDataType(RTC.TimedLongSeq)
		"""
		動作指令の状態
		 - Number: 6
		 - Semantics: [0]: 操作モード
		              [1]: 走行操作 速度レベル
		              [2]: 走行操作 最大速度フラグ
		              [3]: 走行モード フリッパーの選択状態
		              [4]: 走行モード フリッパーの動作状態
		              [5]: 走行モード 台車の位置姿勢のクリア
		"""
		self._Mode_InIn = OpenRTM_aist.InPort("Mode_In", self._d_Mode_In)
		self._d_Pose3D_In = OpenRTM_aist.instantiateDataType(RTC.TimedPose3D)
		"""
		３次元の位置・姿勢
		 - Unit: 位置:[m], 姿勢:[rad]
		"""
		self._Pose3D_InIn = OpenRTM_aist.InPort("Pose3D_In", self._d_Pose3D_In)
		self._d_Velocity2D_In = OpenRTM_aist.instantiateDataType(RTC.TimedVelocity2D)
		"""
		メインクローラの速度
		 - Unit: [m/s]
		"""
		self._Velocity2D_InIn = OpenRTM_aist.InPort("Velocity2D_In", self._d_Velocity2D_In)
		self._d_FlipperAngle_In = OpenRTM_aist.instantiateDataType(RTC.TimedDoubleSeq)
		"""
		フリッパーの角度
		 - Number: 4
		 - Semantics: [0]: 右前方フリッパー
		              [1]: 左前方フリッパー
		              [2]: 右後方フリッパー
		              [3]: 左後方フリッパー
		 - Unit: [rad]
		"""
		self._FlipperAngle_InIn = OpenRTM_aist.InPort("FlipperAngle_In", self._d_FlipperAngle_In)
		self._d_MotorLoad_In = OpenRTM_aist.instantiateDataType(RTC.TimedDoubleSeq)
		"""
		モータの負荷
		 - Number: 6
		 - Semantics: [0]: 右メインモータ
		              [1]: 左メインモータ
		              [2]: 右前方サブモータ
		              [3]: 左前方サブモータ
		              [4]: 右後方サブモータ
		              [5]: 左後方サブモータ
		 - Unit: [A]
		"""
		self._MotorLoad_InIn = OpenRTM_aist.InPort("MotorLoad_In", self._d_MotorLoad_In)
		self._d_Arm1Pose3D_In = OpenRTM_aist.instantiateDataType(RTC.TimedPose3D)
		"""
		アーム1の３次元の位置・姿勢
		(ロボット座標系)
		 - Unit: 位置:[m], 姿勢:[rad]
		"""
		self._Arm1Pose3D_InIn = OpenRTM_aist.InPort("Arm1Pose3D_In", self._d_Arm1Pose3D_In)
		self._d_Arm1Angular_In = OpenRTM_aist.instantiateDataType(RTC.TimedDoubleSeq)
		"""
		アーム1の腕の角度
		 - Semantics: [0]: 1軸目
		              [1]: 2軸目
		              [2]: 3軸目
		              [3]: 4軸目
		              [4]: 5軸目
		              [5]: 6軸目
		 - Unit: [rad]
		"""
		self._Arm1Angular_InIn = OpenRTM_aist.InPort("Arm1Angular_In", self._d_Arm1Angular_In)
		self._d_Arm1Finger_In = OpenRTM_aist.instantiateDataType(RTC.TimedLongSeq)
		"""
		アーム1の指の開閉具合
		 - Semantics: [0]: 親指
		              [1]: 差指
		              [2]: 中指
		 - Unit: [u] (独自単位)
		"""
		self._Arm1Finger_InIn = OpenRTM_aist.InPort("Arm1Finger_In", self._d_Arm1Finger_In)
		self._d_Arm1Current_In = OpenRTM_aist.instantiateDataType(RTC.TimedDoubleSeq)
		"""
		アーム1のモータ負荷
		 - Semantics: [0]: 1軸目
		              [1]: 2軸目
		              [2]: 3軸目
		              [3]: 4軸目
		              [4]: 5軸目
		              [5]: 6軸目
		              [6]: 親指
		              [7]: 差指
		              [8]: 中指
		 - Unit: [A]
		"""
		self._Arm1Current_InIn = OpenRTM_aist.InPort("Arm1Current_In", self._d_Arm1Current_In)





		# initialize of configuration-data.
		# <rtc-template block="init_conf_param">
		"""
		WebSocket 待受ポート番号
		 - Name:  WEBSOCKET_PORT
		 - DefaultValue: 8080
		"""
		self._WEBSOCKET_PORT = [8080]
		"""
		WebSocket 待受アドレス
		 - Name:  WEBSOCKET_HOST
		 - DefaultValue: 0.0.0.0
		"""
		self._WEBSOCKET_HOST = ['0.0.0.0']

		# </rtc-template>



	##
	#
	# The initialize action (on CREATED->ALIVE transition)
	# formaer rtc_init_entry()
	#
	# @return RTC::ReturnCode_t
	#
	#
	def onInitialize(self):
		# Bind variables and configuration variable
		self.bindParameter("WEBSOCKET_PORT", self._WEBSOCKET_PORT, "8080")
		self.bindParameter("WEBSOCKET_HOST", self._WEBSOCKET_HOST, "0.0.0.0")

		# Set InPort buffers
		self.addInPort("GCCapacityRatio_In",self._GCCapacityRatio_InIn)
		self.addInPort("MainCapacityRatio_In",self._MainCapacityRatio_InIn)
		self.addInPort("Mode_In",self._Mode_InIn)
		self.addInPort("Pose3D_In",self._Pose3D_InIn)
		self.addInPort("Velocity2D_In",self._Velocity2D_InIn)
		self.addInPort("FlipperAngle_In",self._FlipperAngle_InIn)
		self.addInPort("MotorLoad_In",self._MotorLoad_InIn)
		self.addInPort("Arm1Pose3D_In",self._Arm1Pose3D_InIn)
		self.addInPort("Arm1Angular_In",self._Arm1Angular_InIn)
		self.addInPort("Arm1Finger_In",self._Arm1Finger_InIn)
		self.addInPort("Arm1Current_In",self._Arm1Current_InIn)

		# Set OutPort buffers

		# Set service provider to Ports

		# Set service consumers to Ports

		# Set CORBA Service Ports

		return RTC.RTC_OK

	##
	#
	# The finalize action (on ALIVE->END transition)
	# formaer rtc_exiting_entry()
	#
	# @return RTC::ReturnCode_t

	#
	def onFinalize(self):

		return RTC.RTC_OK

	###
	##
	## The startup action when ExecutionContext startup
	## former rtc_starting_entry()
	##
	## @param ec_id target ExecutionContext Id
	##
	## @return RTC::ReturnCode_t
	##
	##
	#def onStartup(self, ec_id):
	#
	#	return RTC.RTC_OK

	###
	##
	## The shutdown action when ExecutionContext stop
	## former rtc_stopping_entry()
	##
	## @param ec_id target ExecutionContext Id
	##
	## @return RTC::ReturnCode_t
	##
	##
	#def onShutdown(self, ec_id):
	#
	#	return RTC.RTC_OK

	##
	#
	# The activated action (Active state entry action)
	# former rtc_active_entry()
	#
	# @param ec_id target ExecutionContext Id
	#
	# @return RTC::ReturnCode_t
	#
	#
	def onActivated(self, ec_id):
		# ビューアーの設定ファイルを生成
		config = {
			"WEBSOCKET_PORT": self._WEBSOCKET_PORT[0],
		}
		with open(VIEWER_CONFIG_FILE, mode="w") as f:
			json.dump(config, f, ensure_ascii=False, indent=2, separators=(",", ": "))

		#def ws_on_message(client, server, message):
		#	server.send_message_to_all(message)
		#	return

		# WebSocket サーバーを起動
		self.ws_server = WebsocketServer(self._WEBSOCKET_PORT[0], host=self._WEBSOCKET_HOST[0])
		#self.ws_server.set_fn_message_received(ws_on_message)
		self.ws_thread = threading.Thread(target=self.ws_server.run_forever)
		self.ws_thread.start()

		return RTC.RTC_OK

	##
	#
	# The deactivated action (Active state exit action)
	# former rtc_active_exit()
	#
	# @param ec_id target ExecutionContext Id
	#
	# @return RTC::ReturnCode_t
	#
	#
	def onDeactivated(self, ec_id):
		# WebSocket サーバーを終了
		self.ws_server.shutdown()
		self.ws_server.server_close()

		return RTC.RTC_OK

	##
	#
	# The execution action that is invoked periodically
	# former rtc_active_do()
	#
	# @param ec_id target ExecutionContext Id
	#
	# @return RTC::ReturnCode_t
	#
	#
	def onExecute(self, ec_id):
		# 入力ポートに入ってきたデータを WebSocket クライアントに転送する
		for port in self._inports:
			port_name = port._name
			port_type = port._value.__class__.__name__

			if port.isNew():
				port_in = port.read()
				time = port_in.tm.sec + port_in.tm.nsec * (10**-9)

				if port_type in ["TimedDouble", "TimedLongSeq", "TimedDoubleSeq"]:
					data = port_in.data
				elif port_type == "TimedPose3D":
					position = port_in.data.position
					orientation = port_in.data.orientation
					data = {
						"position": {"x": position.x, "y": position.y, "z": position.z},
						"orientation": {"r": orientation.r, "p": orientation.p, "y": orientation.y},
					}
				elif port_type == "TimedVelocity2D":
					velocity = port_in.data
					data = {"vx": velocity.vx, "vy": velocity.vy, "va": velocity.va}

				js_data = json.dumps({port_name: {"tm": time, "data": data}})
				self.ws_server.send_message_to_all(js_data)
				#print(js_data)

		return RTC.RTC_OK

	###
	##
	## The aborting action when main logic error occurred.
	## former rtc_aborting_entry()
	##
	## @param ec_id target ExecutionContext Id
	##
	## @return RTC::ReturnCode_t
	##
	##
	#def onAborting(self, ec_id):
	#
	#	return RTC.RTC_OK

	###
	##
	## The error action in ERROR state
	## former rtc_error_do()
	##
	## @param ec_id target ExecutionContext Id
	##
	## @return RTC::ReturnCode_t
	##
	##
	#def onError(self, ec_id):
	#
	#	return RTC.RTC_OK

	###
	##
	## The reset action that is invoked resetting
	## This is same but different the former rtc_init_entry()
	##
	## @param ec_id target ExecutionContext Id
	##
	## @return RTC::ReturnCode_t
	##
	##
	#def onReset(self, ec_id):
	#
	#	return RTC.RTC_OK

	###
	##
	## The state update action that is invoked after onExecute() action
	## no corresponding operation exists in OpenRTm-aist-0.2.0
	##
	## @param ec_id target ExecutionContext Id
	##
	## @return RTC::ReturnCode_t
	##

	##
	#def onStateUpdate(self, ec_id):
	#
	#	return RTC.RTC_OK

	###
	##
	## The action that is invoked when execution context's rate is changed
	## no corresponding operation exists in OpenRTm-aist-0.2.0
	##
	## @param ec_id target ExecutionContext Id
	##
	## @return RTC::ReturnCode_t
	##
	##
	#def onRateChanged(self, ec_id):
	#
	#	return RTC.RTC_OK




def RTC_Spider2020_InfoInit(manager):
    profile = OpenRTM_aist.Properties(defaults_str=rtc_spider2020_info_spec)
    manager.registerFactory(profile,
                            RTC_Spider2020_Info,
                            OpenRTM_aist.Delete)

def MyModuleInit(manager):
    RTC_Spider2020_InfoInit(manager)

    # Create a component
    comp = manager.createComponent("RTC_Spider2020_Info")

def main():
	mgr = OpenRTM_aist.Manager.init(sys.argv)
	mgr.setModuleInitProc(MyModuleInit)
	mgr.activateManager()
	mgr.runManager()

if __name__ == "__main__":
	main()

