#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Client.h"
#include <qfiledialog.h>
#include "UdpClient.h"
#include <QTimer>
#define STATUS_MSG_LEN 2

class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = Q_NULLPTR);
	~Client();
	bool CheckHandshake();

public slots:
	void openFileDialog();

private:
    Ui::ClientClass ui;
	UdpClient udpClient;
	QString imageName;
	QFile image;
	long int imageSize;
	int blockDataSize;
	char buffer[400];
	char commBuffer[3];
	long int  index;
	QByteArray imgSizeByteArr;

	void IntToCharArr(int input, char* output);

	void SendConfirmationMsg();
};
