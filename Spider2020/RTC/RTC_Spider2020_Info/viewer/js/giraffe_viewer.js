import {GiraffeViewerConfig} from "./giraffe_viewer_config.js";
import {GiraffeInfoClient} from "./giraffe_info_client.js";

var $s; // スタティック変数参照用

 /** GiraffeViewer アプリケーション クラス */
export class GiraffeViewer {

	/** コンストラクタ */
	constructor() {
		$s = this.constructor; // スタティック変数参照用
		
		this.batteryGauges = {};
		this.velocityGauges = {};

		var wsURL = $s.WEBSOCKET_PROTO+"://"+$s.WEBSOCKET_HOST+":"+$s.WEBSOCKET_PORT;
		var dataHandlers = this._defineDataHandlers();

		this.info = new GiraffeInfoClient(wsURL, {
			// 接続開始時
			onConnect: () => {
				var messageBox = $($s.MESSAGE_BOX_SELECTOR);
				messageBox.html("サーバーに接続しています...");
				messageBox.fadeIn($s.FADE_DURATION);
			},
			// 接続完了時
			onConnected: () => {
				var messageBox = $($s.MESSAGE_BOX_SELECTOR);
				var loadingPanel = $($s.LOADING_PANEL_SELECTOR);
				messageBox.html(messageBox.html()+" 接続が完了しました。");
				messageBox.fadeOut($s.FADE_DURATION, () => messageBox.html(""));
				loadingPanel.fadeOut($s.FADE_DURATION);		
			},
			// 切断時
			onDisconnected: () => {
				var messageBox = $($s.MESSAGE_BOX_SELECTOR);
				var loadingPanel = $($s.LOADING_PANEL_SELECTOR);
				messageBox.html("サーバーから切断されました。再接続しています...");
				messageBox.fadeIn($s.FADE_DURATION);
				loadingPanel.fadeIn($s.FADE_DURATION);
			},
			// 再接続開始時
			onReconnect: () => {
			},
			// データ受信時
			onReceived: (port, input, lastInput) => {
				// データが前回と同じ値の場合は処理しない
				if (lastInput && JSON.stringify(input.data) == JSON.stringify(lastInput.data)) return;
				var handler = dataHandlers[port];
				if (handler) {
					handler(port, input.data, $s.PORT_PARAMS[port]);
				}
			},
		});
	}

	/** アプリケーションを開始する。 */
	start() {
		if (this.info.start()) {
			// Velocity2D_In: 10ms 間隔でターゲット値に向かって更新
			setInterval(() => {
				$.each(this.velocityGauges, (key, gauge) => {
					if (gauge.value == gauge.targetValue) return;
					if (Math.abs(gauge.value - gauge.targetValue) < 0.001)
						gauge.value = gauge.targetValue;
					else
						gauge.value = (gauge.value * 0.9 + gauge.targetValue * 0.1);
				});
			}, 10);
			return true;
		} else {
			return false;
		}

	}

	/**
	 * デバッグモードを有効化/無効化する。
	 * @param  {Boolean} enable=null true で有効化、false で無効化、省略時はトグル動作
	 */
	debugMode(enable = null) {
		if (this.panelOriginalStyle == null)
			this.panelOriginalStyle = {paddingBottom: $(".panel").css("paddingBottom")};
		if (enable == false || (enable == null && this.info.options.debug)) {
			// デバッグモード 無効化
			if (this.info.ws.readyState != WebSocket.OPEN) $("#loading").fadeIn();
			$(".panel").animate(this.panelOriginalStyle);
			$(".debug").fadeOut(() => {
				this.setScreenZoom();
			});
			this.info.options.debug = false;
		} else {
			// デバッグモード 有効化
			$("#loading").fadeOut();
			$(".panel").animate({paddingBottom: "30px"});
			$(".debug").fadeIn(() => {
				this.setScreenZoom();
			}).css("display", "flex");
			this.info.options.debug = true;
		}
	}
	
	/** 表示パネルの初期化を行う。 */
	initializePanels() {
		var portInitializers = this._definePortInitializer();

		$.each($s.PORT_PARAMS, (port, params) => {
			var init = portInitializers[port];
			if (init) {
				// デバッグ編集欄を追加
				var debugBox = params.panel.find(".debug");
				if (debugBox.length == 0) {
					debugBox = $('<div class="debug flexbox"></div>');
					debugBox.keydown((e) => {
						if (e.keyCode == 13) this.info.data(eval("("+e.target.value+")"));
					});
					params.panel.append(debugBox);
				}
				debugBox.append('<input class="edit '+port+'" type="text">');

				// 初期化関数を実行
				init(port, params);
			}
		});

		// フルスクリーンボタンを追加
		var button = $('<ul class="button"></ul>');
		button.append('<li class="fullscreen"></li>');
		$(".panel h3").after(button);

		// データ未受信時ラベルを設定
		$(".data").text($s.DATA_EMPTY_LABEL);	
	}

	/** 画面のズーム比率を設定する。 */
	setScreenZoom() {
		if ($(document.body).css("zoom") == 1) {
			// 初回のみ実行
			$(document.body).css("width", $s.BODY_WIDTH).css("opacity", 1);
		}
		if (document.fullscreen) {
			// フルスクリーン有効時
			var zoomRatio = 1;
		} else {
			// フルスクリーン解除時
			var zoomRatioWidth = $(window).width() / $s.BODY_WIDTH;
			var zoomRatioHeight = $(window).height() / $(document.body).height();
			var zoomRatio = Math.min(zoomRatioWidth, zoomRatioHeight);
			if (zoomRatio < $s.ZOOM_RATIO_MIN) zoomRatio = $s.ZOOM_RATIO_MIN;
			this._resizeVelocity2DGauge(zoomRatio);
		}
console.log(zoomRatioWidth, zoomRatioHeight, zoomRatio);
		$(document.body).css("zoom", zoomRatio);
	}
	
	/** 表示パネルのズーム比率を設定する。 */
	setPanelZoom() {
		var panel = document.fullscreenElement;
		if (document.fullscreen) {
			// フルスクリーン有効時
			var zoomRatio = Math.min($(window).width() / $s.PANEL_WIDTH, $(window).height() / $s.PANEL_HEIGHT);
			$(panel).css("zoom", zoomRatio);
			if (panel.id == "Velocity2D") this._resizeVelocity2DGauge(zoomRatio);
		} else {
			// フルスクリーン解除時
			$(".panel").css("zoom", 1);
		}
	}
	
	/** イベントハンドラーを設定する。 */
	setEventHandlers() {
		// Ctrl+Shift を押しながらタイトルクリックでデバッグモード
		$(".title h1").click((e) => e.ctrlKey && e.shiftKey && this.debugMode());

		// フルスクリーン設定
		var fullScreenCallback = (e) => {
			if (document.fullscreen)
				document.exitFullscreen();
			else
				$(e.target).parents(".panel")[0].requestFullscreen();
		};
		$(".panel li.fullscreen").click(fullScreenCallback);
		$(".panel h3").dblclick(fullScreenCallback);
		$(document).bind("fullscreenchange", (e) => {
			console.log("fullscreenchange");
			this.setPanelZoom();
			this.setScreenZoom();
		});

		// ウィンドウ リサイズ設定
		$(window).on("resize", (e) => {
			console.log("window_resize");
			this.setScreenZoom();
		});

	}
	
	/**
	 * 速度ゲージのサイズを変更する。
	 * @private
	 * @param {Number} zoomRatio ズーム比率
	 */
	_resizeVelocity2DGauge(zoomRatio) {
		var v2dCanvas = $("#Velocity2D canvas");
		var v2dGaugeOptions = $s.VELOCITY2D_GAUGE_OPTIONS.common;
		var v2dZoomWidth = v2dGaugeOptions.width * zoomRatio;
		var v2dZoomHeight = v2dGaugeOptions.height * zoomRatio;
		v2dCanvas.css("zoom", 1 / zoomRatio);
		$.each(this.velocityGauges, (key, gauge) => {
			gauge.update({width: v2dZoomWidth, height: v2dZoomHeight});
		});
	}

	/**
	 * デバッグ編集欄に値を設定する。
	 * @private
	 * @param {String} port RTC 入力ポート名
	 * @param {Number|Object} data 入力データ
	 */
	_setDebugEditValue(port, data) {
		var obj = {[port]: {data: data}};
		$(".debug .edit."+port).val(JSON.stringify(obj).replace(/\"([^(\")"]+)\":/g,"$1:"));
	}

	/**
	 * 角度をラジアンから度に変換する。
	 * @private
	 * @param {Number} angle 角度 (ラジアン)
	 * @param {Number} base 基底
	 */
	_angle(angle, base = 1) {
        return Math.round(angle * 180 / Math.PI / base) * base;
    }

	/**
	 * 各 RTC 入力ポートに対応する初期化関数を定義する。
	 * @private
	 */
	_definePortInitializer() {
		var init = {};

		// initialize GCCapacityRatio_In
		init.GCCapacityRatio_In = (port, params) => {
			this.batteryGauges[port] =
				params.panel.find(".battery."+port.replace("CapacityRatio_In", "")).battery(
					$s.BATTERY_GAUGE_OPTIONS.common
				);
			this.batteryGauges[port].update($s.DATA_EMPTY_LABEL);
			this._setDebugEditValue(port, 0);
		};

		// initialize MainCapacityRatio_In
		init.MainCapacityRatio_In = init.GCCapacityRatio_In;
		
		// initialize Mode_In
		init.Mode_In = (port, params) => {
			this._setDebugEditValue(port, [0, 0, 0, 0, 0, 0]);
		};

		// initialize Pose3D_In
		init.Pose3D_In = (port, params) => {
			this._setDebugEditValue(port, {position: {x: 0, y: 0, z:0}, orientation: {r: 0, p: 0, y: 0}});
		};

		// initialize Velocity2D_In
		init.Velocity2D_In = (port, params) => {
			var gaugeOptions = $s.VELOCITY2D_GAUGE_OPTIONS;
			["vx", null, "va"].forEach((axis, i) => {
				if (!axis) return;
				var options = Object.assign({}, gaugeOptions.common, gaugeOptions[axis], {
					renderTo: params.panel.find(".velocity canvas."+axis)[0],
				});
				this.velocityGauges[axis] = new RadialGauge(options).draw();
				this.velocityGauges[axis].targetValue = 0;
			});
			this._setDebugEditValue(port, {vx: 0, vy: 0, va: 0});
		};

		// initialize FlipperAngle_In
		init.FlipperAngle_In = (port, params) => {
			this._setDebugEditValue(port, [0, 0, 0, 0]);
		};

		// initialize MotorLoad_In
		init.MotorLoad_In = (port, params) => {
			this._setDebugEditValue(port, [0, 0, 0, 0, 0, 0]);
		};

		return init;
	}

	/**
	 * 各 RTC 入力ポートに対応する受信データ処理関数を定義する。
	 * @private
	 */
	_defineDataHandlers() {
		var handlers = {};

		// data handler MainCapacityRatio_In
		handlers.MainCapacityRatio_In = (port, data, params) => {
			var gaugeOptions = $s.BATTERY_GAUGE_OPTIONS;
			var options = Object.assign({}, gaugeOptions.common);
			var gauge = this.batteryGauges[port];
			$.each(gaugeOptions.levels, (lvValue, lvOptions) => {
				if (data <= lvValue) {
					Object.assign(options, lvOptions);
					return false; // break
				}
			})
			if (data < 0) {
				gauge.update(0, options);
				gauge.update("-");
			} else {
				gauge.update(data, options);
			}
		};

		// data handler GCCapacityRatio_In
		handlers.GCCapacityRatio_In = handlers.MainCapacityRatio_In;

		// data handler Mode_In
		handlers.Mode_In = (port, data, params) => {
			["operation", "speed-level", "speed-max"].forEach((key, i) => {
				params.panel.find(".mode tr."+key+" td").removeClass("selected");
				params.panel.find(".mode tr."+key+" td").eq(data[i]).addClass("selected");
			});
			var panel = $s.PORT_PARAMS.FlipperAngle_In.panel;
			["front", "rear"].forEach((fr, i) => {
				["right", "left"].forEach((rl, j) => {
					var flipper = panel.find(".angle."+rl+" img.flipper."+fr);
					flipper.removeClass("selected up down");
					if (data[3] & (1 << (i*2+j))) {
						flipper.addClass(["selected", "up", "down"][data[4]]);
					}
				});
			});
		};

		// data handler Pose3D_In
		handlers.Pose3D_In = (port, data, params) => {
			$.each(data.position, (axis, value) => {
				params.panel.find(".position .data."+axis).text($.sprintf("%.3f", value));
			})
			$.each(data.orientation, (axis, rad) => {
				params.panel.find(".orientation."+axis+" .data").text($.sprintf("%.1f", this._angle(rad, 0.1)));
				params.panel.find(".orientation."+axis+" img").css("transform", "rotate("+(-rad)+"rad)");
			})
		};

		// data handler Velocity2D_In
		handlers.Velocity2D_In = (port, data, params) => {
			this.velocityGauges.vx.targetValue = data.vx;
			this.velocityGauges.va.targetValue = this._angle(data.va);
		};

		// data handler FlipperAngle_In
		handlers.FlipperAngle_In = (port, data, params) => {
			["front", "rear"].forEach((fr, i) => {
				["right", "left"].forEach((rl, j) => {
					var sign = (i == j) ? -1 : 1;
					params.panel.find(".angle."+rl+" .data."+fr).text($.sprintf("%.1f", this._angle(data[i*2+j])));
					params.panel.find(".angle."+rl+" img.flipper."+fr).css("transform", "rotate("+(sign*data[i*2+j])+"rad)");
				});
			});
		};

		// data handler MotorLoad_In
		handlers.MotorLoad_In = (port, data, params) => {
			["main", "front", "rear"].forEach((fr, i) => {
				["right", "left"].forEach((rl, j) => {
					params.panel.find(".load."+rl+" .data."+fr).text($.sprintf("%.3f", data[i*2+j]));
				});
			});
		};

		return handlers;
	}

	/**
	 * デバッグデータを生成する。
	 * @private
	 * @param {Number} interval=100 生成間隔
	 */
	_generateDebugData(interval = 100) {
		setInterval(() => {
			$.each({
				MainCapacityRatio_In: 0,
				Mode_In: [0 ,0 ,0 ,0 ,0 ,0],
				Pose3D_In: {position: {x: 0, y: 0, z:0}, orientation: {r: 0, p: 0, y: 0}},
				Velocity2D_In: {vx: 0, vy: 0, va: 0},
				FlipperAngle_In: [0 ,0 ,0 ,0],
				MotorLoad_In: [0 ,0 ,0 ,0 ,0 ,0],
				GCCapacityRatio_In: 0,
			}, (port, data) => {
				var date = new Date();
				var time = (date.getTime() + date.getMilliseconds()) / 1000;
				this.info.data({[port]: {tm: time, data: data}});
			});
		}, interval);
	}
}

Object.assign(GiraffeViewer, GiraffeViewerConfig);