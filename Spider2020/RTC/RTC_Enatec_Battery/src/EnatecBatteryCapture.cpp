// -*- C++ -*-
/*!
 * @file EnatecBatteryCapture.h
 * @brief エナテック製バッテリの情報の取得クラス
 * @author C.Saito
 * @date 2019/05/30
 */

#include "EnatecBatteryCapture.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/time.h>
#include <termios.h>
#include <unistd.h>

/*! @name シリアル通信設定
 *	シリアル通信のバッファサイズ及びレスポンスの待ち時間
 */
/*  @{ */
#define SEND_BUFF_MAX	(2)			/*!< シリアル通信の送信バッファサイズ	*/
#define RECV_BUFF_MAX	(16)		/*!< シリアル通信の受信バッファサイズ	*/
#define RECV_WAIT 		(0.1)		/*!< シリアル通信の応答待ち [s]			*/
/* @} */

EnatecBatteryCapture::EnatecBatteryCapture()
	: m_fd(-1)
{
}

EnatecBatteryCapture::~EnatecBatteryCapture()
{
	// シリアルポートを閉じる
	Close();
}

bool EnatecBatteryCapture::Open(const std::string &sDeviceName)
{
	termios stTermios = {0};
	int iRet = 0;

	// 多重オープンを防止する
	if(m_fd != -1)
	{
		printf("open(%s) is failed\n", sDeviceName.c_str());
		return false;
	}

	do
	{
		// デバイスを開く
		m_fd = open(sDeviceName.c_str(), O_RDWR);
		if(m_fd == -1)
		{
			printf("open(%s) is failed\n", sDeviceName.c_str());
			break;
		}

		// シリアル通信の属性を決定する
		stTermios.c_cflag |= B4800;		// データ伝送速度: 4800bps
		stTermios.c_cflag |= CREAD;		// 受信有効
		stTermios.c_cflag |= CLOCAL;	// ローカルライン（モデム制御なし）
		stTermios.c_cflag |= CS8;		// データビット: 8bit
		stTermios.c_cflag |= 0;			// ストップビット: 1bit
		stTermios.c_cflag |= 0;			// パリティビット: なし
		cfmakeraw(&stTermios);			// バイナリモードオプション追加
		stTermios.c_cc[VMIN] = 0;		// 非カノニカル読み込み時の最小文字数（MIN）
		stTermios.c_cc[VTIME] = 1;		// 非カノニカル読み込み時のタイムアウト時間(単位:1/10秒)

		// シリアル通信の入出力バッファをクリアする
		iRet = tcflush(m_fd, TCIFLUSH);
		if(iRet == -1)
		{
			printf("tcflush is failed\n");
			break;
		}

		// シリアル通信の属性を設定する
		iRet = tcsetattr(m_fd, TCSANOW, &stTermios);
		if(iRet == -1)
		{
			printf("tcsetattr is failed\n");
			break;
		}

		// 正常終了
		return true;
	}
	while(0);

	// シリアルポートを閉じる
	Close();

	// 異常終了
	return false;
}

void EnatecBatteryCapture::Close()
{
	if(m_fd != -1)
	{
		// デバイスを閉じる
		close(m_fd);
		m_fd = -1;
	}
}

std::string EnatecBatteryCapture::GetMaker(void)
{
	BYTE btStatusBuff[9+1] = {0};		// 製造会社名のステータス: 9byte
	bool bRet = false;

	// 製造会社名を取得する
	bRet = SendAndRecv(0x03, btStatusBuff, 9);
	if(!bRet)
	{
		return "";
	}

	return (char*)btStatusBuff;
}

BYTE EnatecBatteryCapture::GetCapacityRatio(void)
{
	BYTE btStatus = 0x00;		// 残存容量比のステータス: 1byte
	bool bRet = false;

	// 残存容量比率を取得する
	bRet = SendAndRecv(0x07, &btStatus, 1);
	if(!bRet)
	{
		return 0xFF;
	}

	return btStatus;
}

bool EnatecBatteryCapture::SendAndRecv(BYTE btCmd, BYTE *pbtStatusBuff, BYTE btStatusBuffSize)
{
	BYTE btSendBuff[SEND_BUFF_MAX] = {0};
	BYTE btRecvBuff[RECV_BUFF_MAX] = {0};
	BYTE btCheckSum = 0;
	struct timeval stOldTime = {0};
	struct timeval stNowTime = {0};
	int iSize = 0;
	int i = 0;

	// 引数をチェックする
	if((pbtStatusBuff == NULL) || (btStatusBuffSize == 0))
	{
		printf("parameter is not valid\n");
		return false;
	}

	// デバイスのオープンをチェックする
	if(m_fd == -1)
	{
		printf("device is not opened\n");
		return false;
	}

	// 要求コマンドを作成する
	btSendBuff[0] = 0xAA;		// 識別ヘッダ
	btSendBuff[1] = btCmd;		// コマンド

	// 要求を送信する
	iSize = write(m_fd, btSendBuff, sizeof(btSendBuff));
	if(iSize != sizeof(btSendBuff))
	{
		printf("write is failed\n");
		return false;
	}

	// 受信文字数を初期化する
	iSize = 0;

	// 開始時刻を取得する
	gettimeofday(&stOldTime, NULL);

	do
	{
		// 応答を受信する
		iSize += read(m_fd, &btRecvBuff[iSize], sizeof(btRecvBuff) - iSize);

		// 期待データ数を受信したらループを抜ける
		// 期待データ数: ヘッダ＋コマンド＋ステータス＋チェックサム
		if(iSize == (btStatusBuffSize + 3))
		{
			break;
		}

		// 現在時刻を取得する
		gettimeofday(&stNowTime, NULL);

		// シリアル通信の応答待ちをチェックする
		if((((double)(stOldTime.tv_sec)+(double)(stOldTime.tv_usec)*0.001*0.001) + RECV_WAIT) <= ((double)(stNowTime.tv_sec)+(double)(stNowTime.tv_usec)*0.001*0.001))
		{
			printf("read is timeout\n");
			return false;
		}
	}
	while(1);

	// チェックサムを求める
	for(i = 2; i < (iSize-1); i++)
	{
		btCheckSum |= btRecvBuff[i];
	}

	// 応答の内容を検証する(識別ヘッダ)
	if(btSendBuff[0] != btRecvBuff[0])
	{
		printf("header is not matched\n");
		return false;
	}

	// 応答の内容を検証する(コマンド)
	if(btSendBuff[1] != btRecvBuff[1])
	{
		printf("command is not matched\n");
		return false;
	}

	// 応答の内容を検証する(チェックサム)
	if(btCheckSum != btRecvBuff[iSize - 1])
	{
		printf("checksum is not matched\n");
		return false;
	}

	// ステータスをコピーする
	for(i = 0; i < btStatusBuffSize; i++)
	{
		pbtStatusBuff[i] = btRecvBuff[2 + i];
	}

	// 正常終了
	return true;
}
