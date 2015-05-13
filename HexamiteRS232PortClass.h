/******************************************************************************/
/** \file       HexamiteRS232PortClass.h
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
/* Define to prevent recursive inclusion --------------------------------------*/
#ifndef HEXAMITERS232PORTCLASS_H_
#define HEXAMITERS232PORTCLASS_H_
/* Imports Header Files*/
/* Imports Library */
#include <QObject>



/* Class Constant Declaration--------------------------------------------------*/
/* Comport */
#define BAUDRATE_RS232 256000
#define DATA_BITS_RS232 '8'
#define PARITY_RS232 'N'
#define STOP_BITS_RS232 '1'
#define ULTRASONIC_COM_TRANSMIT_ITEM_SIZE 30

/* Commands to turn on and off our synchronizer */
#define OUR_SYNCHRONYSER_ON 	"M2&s2$"
#define OUR_SYNCHRONYSER_OFF	"M2&%"
/* Class Type declaration -----------------------------------------------------*/
/* Class Data declaration -----------------------------------------------------*/
/* Class definition -----------------------------------------------------------*/
class HexamiteRS232Port : public QObject
{
    Q_OBJECT

	private:
	int iPortNumber;
	std::string strAllLastUnfilteredData;


	public:
	HexamiteRS232Port(int iNewPortNumber);
	void changeHexamiteRS232Port(int iNewPortNumber);
	void getHexamiteData(std::string* strDataRx1, std::string* strDataRx2, std::string* strDataRx3);
	void sendHexamiteData(std::string strDataTx);
	void turnHexamiteUsbSynchronizerOn(void);
	void turnHexamiteUsbSynchronizerOff(void);
	void getAllLastUnfilteredHexamiteData(std::string* strUnfilteredData);
	virtual ~HexamiteRS232Port();
};

#endif /* HEXAMITERS232PORTCLASS_H_ */
