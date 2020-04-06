 /** GiraffeViewer アプリケーション コンフィグ
  * @namespace */
export const GiraffeViewerConfig = {

    /** WebSocket プロトコル ( location.protocol == "https:" ? "wss" : "ws" )
	 * @type {String} */
	WEBSOCKET_PROTO: location.protocol == "https:" ? "wss" : "ws",
	/** WebSocket ホスト名 ( location.hostname || "lcoalhost" )
	 * @type {String} */
	WEBSOCKET_HOST: location.hostname || "lcoalhost",
	/** WebSocket ポート番号 ( location.protocol == "https:" ? 8443 : 8080 )
	 * @type {Number} */
	WEBSOCKET_PORT: location.protocol == "https:" ? 8443 : 8080,
	
	/** 表示パネル 幅
	 * @type {Number} */
	PANEL_WIDTH: 504,
	/** 表示パネル 高さ
	 * @type {Number} */
	PANEL_HEIGHT: 294,
	/** BODY 幅
	 * @type {Number} */
	BODY_WIDTH: 504 * 3 + 10, // 1522
	
	/** 画面ズーム 比率 最小値
	 * @type {Number} */
	ZOOM_RATIO_MIN: 0.5,
	
	/** 画面フェード 継続時間 (ms)
	 * @type {Number} */
	FADE_DURATION: 1000, // ms

	/** データ 未受信時 ラベル
	 * @type {String} */
	DATA_EMPTY_LABEL: "-",

	/** RTC 入力ポート別 パラメータ
	 * @type {Object} */
	PORT_PARAMS: {
		MainCapacityRatio_In: {panel: $("#CapacityRatio")},
		Mode_In:              {panel: $("#Mode")},
		Pose3D_In:            {panel: $("#Pose3D")},
		Velocity2D_In:        {panel: $("#Velocity2D")},
		FlipperAngle_In:      {panel: $("#FlipperAngle")},
		MotorLoad_In:         {panel: $("#MotorLoad")},
		GCCapacityRatio_In:   {panel: $("#CapacityRatio")},
	},
	
	/** バッテリーゲージ オプション
	 * @type {Object} */
	BATTERY_GAUGE_OPTIONS: {
		common: {
			batteryColor:    "#2d2", // Green
			backgroundColor: "#aaa",
			textColor:       "#000",
			maxWidth:        150,
		},
		levels: {
			20: {
				batteryColor:    "#d22", // Red
			},
			80: {
				batteryColor:    "#ef4", // Yellow
			},
		},
	},

	/** 速度ゲージ オプション
	 * @type {Object} */
    VELOCITY2D_GAUGE_OPTIONS: {
		common: {
			width: 200,
			height: 200,

            colorPlate: "#000",

            colorTitle: "#fff",
            fontTitleSize: 28,

            colorMajorTicks: "#fff",
			colorMinorTicks: "#eee",
			colorNumbers: "#fff",
            fontNumbersSize: 28,

            colorUnits: "#fff",
			fontUnitsSize: 28,

            fontValueSize: 28,
            colorValueBoxBackground: "#eee",

            borders: false,

			animation: false, // 何故か針が時々変な向きを示すので無効化
            animationDuration: 100,
			animationRule: "linear",
		},
		vx : {
			units: "m/s",
			minValue: -0.2,
			maxValue: 0.2,
            valueInt: 1,
            valueDec: 3,
			majorTicks: [-0.20, -0.15, -0.10, -0.05, 0.00, 0.05, 0.10, 0.15, 0.20],
			minorTicks: 5,
			highlights: [],
		},
		va : {
			units: "deg/s",
			minValue: -180,
			maxValue: 180,
            valueInt: 1,
			valueDec: 1,
			majorTicks: [-180, -135, -90, -45, 0, 45, 90, 135, 180],
			minorTicks: 3,
			highlights: [],
		},
	},

	/** メッセージ ボックス セレクタ
	 * @type {String} */
	MESSAGE_BOX_SELECTOR: "#message",
	/** ローディング パネル セレクタ
	 * @type {String} */
	LOADING_PANEL_SELECTOR: "#loading",
};