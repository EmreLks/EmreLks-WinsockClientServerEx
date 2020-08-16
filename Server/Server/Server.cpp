#include "Server.h"


Server::Server(QWidget *parent) : QMainWindow(parent)
{
	bool result = true;
    ui.setupUi(this);
	image = new QByteArray();

	index = 0;
	imageCount = 0;
	timer = new QTimer(this);

	connect(timer, SIGNAL(timeout() ), this, SLOT(CheckNewMsg() ) );

	ui.imgsTabWidget->removeTab(0);
	ui.imgsTabWidget->removeTab(0);

	result = udpServer.InitWinsock();
	if (result == false)
	{
		ui.infoLabel->setText("Winsock Init Error");
	}
	else
	{
		udpServer.SetupClient(AF_INET, "127.0.0.1", 8001);
		
		result = udpServer.CreateSocket(AF_INET);

		if (result == false)
		{
			ui.infoLabel->setText("Socket Create Error");
		}
		else
		{
			result = udpServer.Bind();

			if (result == false)
			{
				ui.infoLabel->setText("Binding Error");
			}
			else
			{
				timer->start(10);
			}
		}

	}
}

Server::~Server()
{
	udpServer.CloseSocket();
	udpServer.CleanWinSock();
}

void Server::CheckNewMsg()
{
	this->repaint();
	char buffer[400];
	memset(buffer, 0, sizeof(buffer) );
	
	// Receive data.
	bool result = false;
	result = udpServer.RecvData(buffer, 400);
	if (result == false)
	{
		ui.infoLabel->setText("Msg Receive Error");
	}
	else
	{
		// if incoming data is status message.
		if (buffer[0] == 'S' && buffer[1] == 'T')
		{
			index = 0;
			image->clear();
			SendConfirmationMsg();
		}
		else
		{
			//int msgSize = strlen(buffer) - MSG_LENGHT_CHR_COUNT;
			int msgSizeInfo = 0;

			CharArrToInt(buffer, msgSizeInfo);

			//if (msgSize == msgSizeInfo)
		    
			for (int i = index; i < index + msgSizeInfo; i++)
			{
				image->append(buffer[i - index + 3]);
			}
			// end of the loop.
				
			// last part.	
			if (msgSizeInfo < MAX_SEND_RECEIVE)
			{
				imageCount = imageCount + 1;
				imageName = QString("D://") + QString::number(imageCount) + ".jpeg";
				imageFile = new QFile(imageName);
				imageFile->open(QIODevice::WriteOnly);
				imageFile->write(*image, image->size() );
				imageFile->flush();
				imageFile->close();

				SendConfirmationMsg();

				ShowImages();
			}
			else
			{
				SendConfirmationMsg();
			}

			
		}
	}
}

void Server::CharArrToInt(char* input, int& output)
{
	output = (input[2] - 48) + (input[1] - 48) * 10 + (input[0] - 48) * 100;
}

void Server::SendConfirmationMsg()
{
	char statusMsg[STATUS_MSG_LEN];
	memset(statusMsg, 0, sizeof(statusMsg) );

	statusMsg[0] = 'O'; statusMsg[1] = 'K';
	udpServer.SendData(statusMsg, STATUS_MSG_LEN);
}

void Server::ShowImages()
{
	QString fileName = imageFile->fileName();
	QPixmap pixmap(imageName);
	QLabel* imlabel = new QLabel(ui.imgsTabWidget);
	imlabel->setPixmap(pixmap);
	imlabel->show();
	ui.imgsTabWidget->insertTab(imageCount, imlabel, QString("Image ") + QString::number(imageCount));
	ui.imgsTabWidget->setCurrentIndex(ui.imgsTabWidget->count() - 1);
}
