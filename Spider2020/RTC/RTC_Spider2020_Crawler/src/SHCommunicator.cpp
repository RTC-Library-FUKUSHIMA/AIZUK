#include "SHCommunicator.h"
#include <fcntl.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

/*! @name シリアル通信設定
 *	シリアル通信の文字バッファサイズ
 */
/*  @{ */
#define SEND_BUFF_MAX	(256)		/*!< シリアル通信の送信文字バッファサイズ	*/
#define RECV_BUFF_MAX	(256)		/*!< シリアル通信の受信文字バッファサイズ	*/
/* @} */

SHCommunicator::SHCommunicator()
	: m_fd(-1)
{
}

SHCommunicator::~SHCommunicator()
{
	// シリアルポートをクローズする
	Close();
}

bool SHCommunicator::Open(const std::string &sDeviceName, const std::string &sBaudrate)
{
	termios stTermios = {0};
	int iRet = 0;

	// 多重オープンを防止する
	if(IsOpen())
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
		if(sBaudrate.compare("B9600") == 0)
		{
			stTermios.c_cflag |= B9600;
		}
		else if(sBaudrate.compare("B19200") == 0)
		{
			stTermios.c_cflag |= B19200;
		}
		else if(sBaudrate.compare("B38400") == 0)
		{
			stTermios.c_cflag |= B38400;
		}
		else if(sBaudrate.compare("B57600") == 0)
		{
			stTermios.c_cflag |= B57600;
		}
		else
		{
			printf("open is failed\n");
			break;
		}
		stTermios.c_cflag |= CREAD;		// 受信有効
		stTermios.c_cflag |= CLOCAL;	// ローカルライン（モデム制御なし）
		stTermios.c_cflag |= CS8;		// データビット: 8bit
		stTermios.c_cflag |= CRTSCTS;	// RTS/CTSフロー制御有効
		stTermios.c_cflag |= 0;			// ストップビット: 1bit
		stTermios.c_cflag |= 0;			// パリティビット: なし
		stTermios.c_iflag |= IGNPAR;	// フレームエラー及びパリティエラーを無視
		stTermios.c_iflag |= ICRNL;		// キャリッジリターンを無視

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

	// シリアルポートをクローズする
	Close();

	// 異常終了
	return false;
}

bool SHCommunicator::IsOpen(void)
{
	return (m_fd != -1);
}

void SHCommunicator::Close()
{
	if(m_fd != -1)
	{
		// デバイスをクローズする
		close(m_fd);
		m_fd = -1;
	}
}

bool SHCommunicator::Send(const std::string &sData)
{
	int iSize = 0;

	// シリアルポートのオープン状態をチェックする
	if(!IsOpen())
	{
		printf("device is not opened\n");
		return false;
	}

	// データ長をチェックする
	if(SEND_BUFF_MAX <= sData.length())
	{
		printf("data length is too long\n");
		return false;
	}

	// 文字列を送信する
	iSize = write(m_fd, (void*)sData.c_str(), sData.length());
	if(iSize != sData.length())
	{
		printf("write is failed\n");
		return false;
	}

	// 正常終了
	return true;
}

std::string SHCommunicator::Recv(void)
{
	std::string sData;
	int iSize = 0;

	// シリアルポートのオープン状態をチェックする
	if(!IsOpen())
	{
		printf("device is not opened\n");
		return sData;
	}

	// 受信文字列格納バッファを確保する
	sData.resize(RECV_BUFF_MAX, '\0');

	// 応答を受信する
	iSize = read(m_fd, (void*)sData.c_str(), sData.length());

	// NULL終端までで文字列を再構成する
	sData = sData.c_str();

	return sData;
}
