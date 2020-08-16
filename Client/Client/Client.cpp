#include "Client.h"
#define ASCII_O 48
#define MAX_SEND_RECEIVE 350


Client::Client(QWidget *parent)
    : QMainWindow(parent)
{
	bool result = true;
    ui.setupUi(this);

	result = udpClient.InitWinsock();
	if (result == false)
	{
		ui.infoLabel->setText("Winsock Init Error");
	}
	else
	{
		udpClient.SetupServer(AF_INET, "127.0.0.1", 8001);

		result = udpClient.CreateSocket(AF_INET);

		if (result == false)
		{
			ui.infoLabel->setText("Socket Create Error");
		}
		// else, do nothing.
	}

	
}

Client::~Client()
{
	udpClient.CloseSocket();
	udpClient.CleanWinSock();
}

void Client::openFileDialog()
{
	imageName = QFileDialog::getOpenFileName(this, "Open an Image", "D://", "(*.jpg)");
	image.setFileName(imageName);

	if (!image.open(QIODevice::ReadOnly))
	{
		ui.infoLabel->setText(imageName + " can not be opened!");
	}
	// else, do nothing.
	

	QByteArray imageByte = image.readAll();
	imageSize = 0;

	// New image sending start.
	memset(commBuffer, 0, sizeof(commBuffer) );
	commBuffer[0] = 'S'; commBuffer[1] = 'T';
	udpClient.SendData(commBuffer, 2);

	if (true == CheckHandshake())
	{
		imageSize = imageByte.size();
	}
	// else, do nothing.
	
	// Prepare data initial state.
	index = 0;
	memset(buffer, 0, sizeof(buffer));
	
	while (imageSize > 0)
	{
		if (imageSize >= MAX_SEND_RECEIVE)
		{
			blockDataSize = MAX_SEND_RECEIVE;
		}
		else
		{
			blockDataSize = imageSize;
		}

		// Fill first three byte with size of sent bytes.
		IntToCharArr(blockDataSize, buffer);

		for (int i = index; i < index + blockDataSize; i++)
		{
			buffer[i + 3 - index] = imageByte.at(i);
		}
		int sentSize = blockDataSize + 3;

		udpClient.SendData(buffer, sentSize);


		// If confirmation is received, sent new block.
		if (true == CheckHandshake() )
		{
			imageSize = imageSize - blockDataSize;
			index = index + blockDataSize;
		}
		// else, do nothing.
	}
}

bool Client::CheckHandshake()
{
	bool result = false;
	
	memset(commBuffer, 0, sizeof(commBuffer) );
	result = udpClient.RecvData(commBuffer, 2);

	if (result != false)
	{
		// Confirmation.
		if (buffer[0] == 'O' && buffer[1] == 'K')
		{
			result = true;
		}
		// else, do nothing.
	}
	// else, do nothing.

	return result;
}

void Client::IntToCharArr(int input, char* output)
{
	output[0] = 48; output[1] = 48; output[2] = 48;

	if (input > 99)
	{
		output[2] = input % 10 + 48;
		input = input / 10;
		output[1] = input % 10 + 48;
		output[0] = input / 10 + 48;
	}
	else if (input > 9)
	{
		output[2] = input % 10 + 48;
		output[1] = input / 10 + 48;
	}
	else if (input > 0)
	{
		output[2] = input % 10 + 48;
	}
}