#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Server.h"
#include "UdpServer.h"
#include <QTimer>
#include <QFile>
#include <QDir>
#include <QPixmap>
#include <QThread>
#include <QImageReader>

#define ASCII_O 48
#define MSG_LENGHT_CHR_COUNT 3
#define STATUS_MSG_LEN 2
#define MAX_SEND_RECEIVE 350

class Server : public QMainWindow
{
    Q_OBJECT

public:
    Server(QWidget *parent = Q_NULLPTR);
	~Server();
public slots:
	void CheckNewMsg();

private:
	// Attribute..
    Ui::ServerClass ui;
	UdpServer udpServer;
	QTimer* timer;
	QByteArray *image;
	QFile *imageFile;
	QString imageName;

	int imageCount;
	long int index;

	// Functions.
	void CharArrToInt(char* input, int& output);
	void SendConfirmationMsg();
	void ShowImages();
};
