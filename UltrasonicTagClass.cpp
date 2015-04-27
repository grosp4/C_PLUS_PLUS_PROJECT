/******************************************************************************/
/** \file       UltrasonicTagClass.cpp
 *  \brief		Includes all Data and Methods to get the Position of the
 *  			according Tag
 *******************************************************************************
 *
 *  \class   	Ultrasonic Tag
 *
 *  \brief    	Includes all Data and Methods to get the Position of the
 *  			according Tag
 *
 *  \authors    jeggy1
 *
 *  \date       14.04.2015
 *
 *  \remark     Last Modification
 *               \li jeggy1, 14.04.2015 , Created
 *
 ******************************************************************************/

/* Imports Header Files*/
#include "UltrasonicTagClass.hpp"

/* Imports Library */
#include <string>
#include <iostream>
#include <sstream>


/* Define and initialize Class attribute*/
int  UltrasonicTagClass::iTeamStartPosition = TeamRight;

/*******************************************************************************
 *  Constructor :    UltrasonicTagClass()
 ******************************************************************************/
/** \brief        Constructor of the Class UltrasonicTag
 *
 *  \author		  Yves Jegge
 *
 *  \return       None
 *
 ******************************************************************************/
UltrasonicTagClass::UltrasonicTagClass(std::string const& sNewTagID)
: sTAG_ID(sNewTagID)
{

}

/*******************************************************************************
 *  Method :      checkSerialMessage()
 ******************************************************************************/
/** \brief        Check the incoming USART-String to get out the three
 * 				  necessitate distances of the Tag. If there are three
 * 				  valid distances, set the return flag.
 *
 *  \author		  Yves Jegge
 *
 *  \param		  sSerialMessage Pointer to the SerialMessage
 *
 *  \return       1 = If calculation is possible
 *  			  0 = If calculation is impossible
 *
 ******************************************************************************/
int UltrasonicTagClass::checkSerialMessage(std::string const& sSerialMessage1, std::string const& sSerialMessage2, std::string const& sSerialMessage3)
{
	/* -------------------------------------------------
	* -- Check Ultrasonoic String if Tag to Receiver  --
	* --------------------------------------------------*/
	this->getDistance(sSerialMessage1, ULTRASONIC_ID_RECEIVER1, &iDistance1);
	this->getDistance(sSerialMessage1, ULTRASONIC_ID_RECEIVER2, &iDistance2);
	this->getDistance(sSerialMessage1, ULTRASONIC_ID_RECEIVER3, &iDistance3);
	this->getDistance(sSerialMessage2, ULTRASONIC_ID_RECEIVER1, &iDistance1);
	this->getDistance(sSerialMessage2, ULTRASONIC_ID_RECEIVER2, &iDistance2);
	this->getDistance(sSerialMessage2, ULTRASONIC_ID_RECEIVER3, &iDistance3);
	this->getDistance(sSerialMessage3, ULTRASONIC_ID_RECEIVER1, &iDistance1);
	this->getDistance(sSerialMessage3, ULTRASONIC_ID_RECEIVER2, &iDistance2);
	this->getDistance(sSerialMessage3, ULTRASONIC_ID_RECEIVER3, &iDistance3);

	/* -------------------------------------------------------
	* -- Define  if calculation of the Position is possible --
	* --------------------------------------------------------*/
	if ((iDistance1 != 0) && (iDistance2 != 0) && (iDistance3 != 0))
	{
	 return(1);
	}
	else
	{
	 return(0);
	}
}
/*******************************************************************************
 *  Method :      getDistance()
 ******************************************************************************/
/** \brief		 reads out the Distance from one Receiver to one Tag
 *
 *  \author		 Yves Jegge
 *
 *  \param		 sSerialMessage Pointer to USART Message
 *  \param 		 sRecID Pointer to Receiver ID
 *  \param 		 pDistance Distance from RecID to TagID
 *
 ******************************************************************************/
void UltrasonicTagClass::getDistance(std::string const& sSerialMessage, std::string const& sRecID, int *pDistance)
{
	/* Define local Variable */
	std::string sFilterString;
	int iCalcualtedDistance = 0;

	/* create the Filterstring */
	sFilterString = sRecID + " " + sTAG_ID + " " + "A";

	/* Searching for Filterstring in USART-String */
	if(sSerialMessage.find(sFilterString) == 0)
	{
		/* read out the Position of the Distance into the aDistanceString */
		std::string sDistanceString(sSerialMessage, sFilterString.size(), (sSerialMessage.size()-sFilterString.size()));

		/* Convert the read out distance into a integer  */
		std::istringstream(sDistanceString) >> iCalcualtedDistance;

		if ((iCalcualtedDistance > 10) && (iCalcualtedDistance < 3700))
		{
			*pDistance = iCalcualtedDistance;
		}
	}
}


/*******************************************************************************
 *  Method :      calculatePosition()
 ******************************************************************************/
/** \brief		  Calculate the actually position of the Tag. Return the
 * 				  X-Position and Y-Position of the Tag. Attention: Calculation is
 * 				  only possible if there is are all distances available. Therfore
 * 				  check before return Flag of checkUSARTString
 *
 *  \author		  Yves Jegge
 *
 *  \param		 iXPosition Pointer to X-Position of the Tag
 *  \param 		 iYPosition Pointer to Y-Position of the Tag
 *
 ******************************************************************************/
void UltrasonicTagClass::calculatePosition()
{
	/* --------------------------
	* -- Define local variable --
	* ---------------------------*/
	int iX_Rec1 = 0, iY_Rec1 = 0;
	int iX_Rec2 = 0, iY_Rec2 = 0;
	int iX_Rec3 = 0, iY_Rec3 = 0;
    int iY_PositionTemp = 0, iX_PositionTemp = 0;

	int idetd = 0;
	double dtmp  = 0;
	int ixn[2][2]	  = { { 0, 0 }, { 0, 0 } };
	int iyn[2][2]	  = { { 0, 0 }, { 0, 0 } };
	double dd[2][2]	  = { { 0, 0 }, { 0, 0 } };
	double dx[2][2]   = { { 0, 0 }, { 0, 0 } };
	double d64y[2][2] = { { 0, 0 }, { 0, 0 } };

	/* -----------------------------
	* -- Check for start Position --
	* ------------------------------*/
	if (iTeamStartPosition == TeamRight)
	{
		iX_Rec1 = X_RECEIVER_MIDDLE_RIGHT;
		iY_Rec1 = Y_RECEIVER_MIDDLE_RIGHT;
		iX_Rec2 = X_RECEIVER_BOTTOM_LEFT;
		iY_Rec2 = Y_RECEIVER_BOTTOM_LEFT;
		iX_Rec3 = X_RECEIVER_TOP_LEFT;
		iY_Rec3 = Y_RECEIVER_TOP_LEFT;
	}
	else if (iTeamStartPosition == TeamLeft)
	{
		iX_Rec1 = X_RECEIVER_MIDDLE_LEFT;
		iY_Rec1 = Y_RECEIVER_MIDDLE_LEFT;
		iX_Rec2 = X_RECEIVER_TOP_RIGHT;
		iY_Rec2 = Y_RECEIVER_TOP_RIGHT;
		iX_Rec3 = X_RECEIVER_BOTTOM_RIGHT;
		iY_Rec3 = Y_RECEIVER_BOTTOM_RIGHT;
	}

	/* ---------------------------
	* -- Calculate new position --
	* ----------------------------*/
	ixn[0][0] = (int) ((iDistance1 * iDistance1) - (iDistance2 * iDistance2)) - ((iX_Rec1 * iX_Rec1) - (iX_Rec2 * iX_Rec2)) - ((iY_Rec1 * iY_Rec1) - (iY_Rec2 * iY_Rec2));
	ixn[1][0] = (int) ((iDistance1 * iDistance1) - (iDistance3 * iDistance3)) - ((iX_Rec1 * iX_Rec1) - (iX_Rec3 * iX_Rec3)) - ((iY_Rec1 * iY_Rec1) - (iY_Rec3 * iY_Rec3));
	ixn[0][1] = 2 * (iY_Rec2 - iY_Rec1);
	ixn[1][1] = 2 * (iY_Rec3 - iY_Rec1);

	dd[0][0] = 2 * (iX_Rec2 - iX_Rec1);
	dd[1][0] = 2 * (iX_Rec3 - iX_Rec1);
	dd[0][1] = 2 * (iY_Rec2 - iY_Rec1);
	dd[1][1] = 2 * (iY_Rec3 - iY_Rec1);

	iyn[0][0] = dd[0][0];
	iyn[1][0] = dd[1][0];
	iyn[0][1] = ixn[0][0];
	iyn[1][1] = ixn[1][0];

	/* Inverse of the 2D-Matrix d */
	idetd = dd[0][0] * dd[1][1] - dd[0][1] * dd[1][0];
	dtmp = dd[0][0];
	dd[0][0] = dd[1][1] * 1 / idetd;
	dd[1][1] = dtmp * 1 / idetd;
	dd[0][1] = -dd[0][1] * 1 / idetd;
	dd[1][0] = -dd[1][0] * 1 / idetd;

	/* multiply the Matrix ixn with d */
	dx[0][0] = ixn[0][0] * dd[0][0] + ixn[0][1] * dd[1][0];
	dx[0][1] = ixn[0][0] * dd[0][1] + ixn[0][1] * dd[1][1];
	dx[1][0] = ixn[1][0] * dd[0][0] + ixn[1][1] * dd[1][0];
	dx[1][1] = ixn[1][0] * dd[0][1] + ixn[1][1] * dd[1][1];

	/* calculate the x-Axis */
    iX_PositionTemp = dx[0][0] * dx[1][1] - dx[0][1] * dx[1][0];

	/* multiply the Matrix iyn with d */
	d64y[0][0] = iyn[0][0] * dd[0][0] + iyn[0][1] * dd[1][0];
	d64y[0][1] = iyn[0][0] * dd[0][1] + iyn[0][1] * dd[1][1];
	d64y[1][0] = iyn[1][0] * dd[0][0] + iyn[1][1] * dd[1][0];
	d64y[1][1] = iyn[1][0] * dd[0][1] + iyn[1][1] * dd[1][1];
	/* calculate the y-Axis */
    iY_PositionTemp = d64y[0][0] * d64y[1][1] - d64y[0][1] * d64y[1][0];

    /* check if new position out of the playing Table */
    if((iX_PositionTemp >= 0) && (iX_PositionTemp <= GLOBALS_PLAY_TABLE_WIDTH) && (iY_PositionTemp >= 0) && (iY_PositionTemp <= GLOBALS_PLAY_TABLE_HEIGHT))
    {
        iX_Position = iX_PositionTemp;
        iY_Position = iY_PositionTemp;
    }

	/* ----------------------------
	* -- Reset Distance Variable --
	* -----------------------------*/
	iDistance1 = iDistance2 = iDistance3 = 0;
}


/**
 * @}
 */
