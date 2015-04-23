/******************************************************************************/
/** \file       HexamiteRS232PortClass.cpp
 *  \brief      Include all methods for generating a RS232-Port to communicate with Hexamite System
 *******************************************************************************
 *
 *  \class   	HexamiteRS232Port
 *
 *  \brief      Include all methods for generating a RS232-Port to communicate with Hexamite System
 *
 *  \authors    sches24
 *
 *  \date       02.04.2015
 *
 *  \remark     Last Modification
 *               \li sches24, 02.04.2015, Created
 *

 *
 ******************************************************************************/
/*
 *  method:
 *
 *@{
 ******************************************************************************/


//
#include<iostream>
#include<sstream>
#include<string>
#include<cstring>
#include<windows.h>
#include<iomanip>
#include "HexamiteRS232PortClass.h"
#include "rs232.h"


/*******************************************************************************
 *  Constructor :    HexamiteRS232Port()
 ******************************************************************************/
/** \brief        Constructor for HexamiteRS232Port
 *
 *  \return  	  None
 *
 ******************************************************************************/
HexamiteRS232Port::HexamiteRS232Port(int iNewPortNumber)
{
	iPortNumber = iNewPortNumber - 1;  // -1 because of the library

	/* Open RS232-Port */
	char mode[]={DATA_BITS_RS232,PARITY_RS232, STOP_BITS_RS232,0};

	if(RS232_OpenComport(iPortNumber, BAUDRATE_RS232, mode))
	{
		std::cout << "Can not open the port!!!" << std::endl;
	}
}


/*******************************************************************************
 *  Deconstructor :    HexamiteRS232Port()
 ******************************************************************************/
/** \brief        Deconstructor for HexamiteRS232Port
 *
 *  \return  	  None
 *
 ******************************************************************************/
HexamiteRS232Port::~HexamiteRS232Port()
{
	/* Close Port */
	RS232_CloseComport(iPortNumber);
}


/*******************************************************************************
 *  Method:       changeHexamiteRS232Port()
 ******************************************************************************/
/** \brief        Change port number
 *
 *  \param		  iNewPortNumber  Number of new Com-Port
 *
 *  \return  	  None
 *
 ******************************************************************************/
void HexamiteRS232Port::changeHexamiteRS232Port(int iNewPortNumber)
{
	/* Close old RS232-Port */
	RS232_CloseComport(iPortNumber);

	/* Change port number */
	iPortNumber = iNewPortNumber - 1; // -1 because of the library

	/* Open new RS232-Port */
	char mode[]={DATA_BITS_RS232,PARITY_RS232, STOP_BITS_RS232,0};

	if(RS232_OpenComport(iPortNumber, BAUDRATE_RS232, mode))
	{
		std::cout << "Can not open the port!!!" << std::endl;
	}
}



/*******************************************************************************
 *  Method :      getHexamiteData()
 ******************************************************************************/
/** \brief        Get data from RS232-Port
 *
 *  \param		  strDataRx1  Data from RS232-Port line 1
 *  \param		  strDataRx1  Data from RS232-Port line 2
 *  \param		  strDataRx1  Data from RS232-Port line 3
 *
 *  \return  	  None
 *
 ******************************************************************************/
void HexamiteRS232Port::getHexamiteData(std::string* strDataRx1, std::string* strDataRx2, std::string* strDataRx3)
{
	/* Intern variable */
	int iNReceivedBytes = 0;
	unsigned char cDataRxTemp[30] = {0};
	unsigned char cDataRx1[100] = {0};
	unsigned char cDataRx2[100] = {0};
	unsigned char cDataRx3[100] = {0};
	unsigned char cReceivedCharacter;
	int iXDedected = false;
	int iCharacterCounter = 0;
	int iNumberOfLine = 0;
	int iNumberOfColumn = 0;
	int iMaxWaitForX = 1000;

	while(1)
	{
		/* Receive message */
		iNReceivedBytes = RS232_PollComport(iPortNumber, cDataRxTemp, sizeof(cDataRxTemp));

		/* Store all data */
		strAllLastUnfilteredData += (char *)cDataRxTemp;

		/* Clear buffer, when too big */
		if(strAllLastUnfilteredData.length() > 100000)
		{
			strAllLastUnfilteredData.clear();
		}

		/* Works with only with one charactor */
		for(iCharacterCounter = 0; iCharacterCounter < iNReceivedBytes; iCharacterCounter++)
		{
			cReceivedCharacter = cDataRxTemp[iCharacterCounter];

			/* Wait until an X is dedected */
			if(cReceivedCharacter == 'X')
			{
				iXDedected = true;
				iNumberOfLine = 0;
				iNumberOfColumn = 0;
			}

			/* When T detected, then wait until X again */
			else if((cReceivedCharacter == 'T') && (iXDedected == true) && (iNumberOfLine < 4))
			{
				iXDedected = false;
			}

			/* Works only if X was dedected */
			else if(iXDedected == true)
			{

				switch(iNumberOfLine)
				{
					/* Line 0 -> we dont need this line */
					case 0:
					{
						break;
					}

					/* Line 1 -> we write it in cDataRx1 */
					case 1:
					{
						cDataRx1[iNumberOfColumn] = cReceivedCharacter;
						break;
					}

					/* Line 2 -> we write it in cDataRx2 */
					case 2:
					{
						cDataRx2[iNumberOfColumn] = cReceivedCharacter;
						break;
					}

					/* Line 3 -> we write it in cDataRx3 */
					case 3:
					{
						cDataRx3[iNumberOfColumn] = cReceivedCharacter;
						break;
					}

					default:
					{


						break;
					}
				}

				/* Increment number of lines if /r dedected */
				if(cReceivedCharacter == '\r')
				{
					iNumberOfLine++;
					iNumberOfColumn = 0;

					/* Line 4 -> finish with reading */
					if(iNumberOfLine > 3)
					{
						// Only correct, if all Strings have an A on the 8th position
						if((cDataRx1[8] == 'A') && (cDataRx2[8] == 'A') && (cDataRx3[8] == 'A'))
						{
							*strDataRx1 = (char *)cDataRx1;
							*strDataRx2 = (char *)cDataRx2;
							*strDataRx3 = (char *)cDataRx3;
							return;
						}
						else
						{
							iXDedected = false;
						}
					}
				}
				else
				{
					/* Change column */
					iNumberOfColumn++;
				}



			}
		}

		/* If the duration of waiting is to long, then send empty string back */
		if(iMaxWaitForX == 0)
		{
			cDataRx1[0] = '\0';
			cDataRx2[0] = '\0';
			cDataRx3[0] = '\0';
			*strDataRx1 = (char *)cDataRx1;
			*strDataRx2 = (char *)cDataRx2;
			*strDataRx3 = (char *)cDataRx3;
			return;
		}
		else
		{
			iMaxWaitForX--;
			//Wait 1ms
			Sleep(1);
		}
	}
}


/*******************************************************************************
 *  Method :      sendHexamiteData()
 ******************************************************************************/
/** \brief        Send data to RS232-Port
 *
 *  \param		  strDataTx  Data for RS232-Port
 *
 *  \return  	  None
 *
 ******************************************************************************/
void HexamiteRS232Port::sendHexamiteData(std::string strDataTx)
{

	/* Define local Variable */
	int iTxDataLength = strDataTx.length();
	int iCheckSumCounter = 0;
	int iConvertCounter = 0;

	int iCheckSum = 0;
	char cDataTxTemp[iTxDataLength];
	char cDataTx[ULTRASONIC_COM_TRANSMIT_ITEM_SIZE + 6] = {0};
	std::strcpy(cDataTxTemp, strDataTx.c_str());
	std::ostringstream streamHx;


	if (iTxDataLength > ULTRASONIC_COM_TRANSMIT_ITEM_SIZE)
	{
		std::cout << "Transmit data for RS232 too long" << std::endl;
	}
	else
	{
		for (iCheckSumCounter = 0; iCheckSumCounter < iTxDataLength; iCheckSumCounter++)
		{
			iCheckSum += (cDataTxTemp[iCheckSumCounter]);
		}

		/* Create string to send */
		strDataTx += "/";

		/* Append hex checksum */
		streamHx << std::hex << iCheckSum;


		std::string strHx( streamHx.str() );

		/* Convert small letters to big */
		while (strHx[iConvertCounter] != '\0')
		{
			if (strHx[iConvertCounter] >= 97)
			{
				strHx[iConvertCounter] = strHx[iConvertCounter] - 32;
			}
			iConvertCounter++;
		}

		strDataTx += strHx;

		/* Append CR */
		strDataTx += "\r\0";

		/* Send message */
		strcpy(cDataTx, strDataTx.c_str());
		RS232_SendBuf(iPortNumber, (unsigned char *)cDataTx, strDataTx.length());
		std::cout << strDataTx << std::endl;

	}


	strDataTx.clear();

}


/*******************************************************************************
 *  Method:       turnHexamiteUsbSynchronizerOn()
 ******************************************************************************/
/** \brief        Turn the hexamite usb synchronizer on
 *
 *
 *  \return  	  None
 *
 ******************************************************************************/
void HexamiteRS232Port::turnHexamiteUsbSynchronizerOn(void)
{
	/* Turn our usb synchronizer on */
	sendHexamiteData(OUR_SYNCHRONYSER_ON);
}



/*******************************************************************************
 *  Method:       turnHexamiteUsbSynchronizerOff()
 ******************************************************************************/
/** \brief        Turn the hexamite usb synchronizer off
 *
 *
 *  \return  	  None
 *
 ******************************************************************************/
void HexamiteRS232Port::turnHexamiteUsbSynchronizerOff(void)
{
	/* Turn our usb synchronizer off */
	sendHexamiteData(OUR_SYNCHRONYSER_OFF);
}


/*******************************************************************************
 *  Method:       getAllLastUnfilteredHexamiteData()
 ******************************************************************************/
/** \brief        Get all last unfiltered data from Hexamite system.
 *
 *
 *  \return  	  None
 *
 ******************************************************************************/
void HexamiteRS232Port::getAllLastUnfilteredHexamiteData(std::string* strUnfilteredData)
{
	/* Take all unfiltered data */
	*strUnfilteredData = strAllLastUnfilteredData;

	/* Clear buffer */
	strAllLastUnfilteredData.clear();
}
