/******************************************************************************/

/** \file       UltrasonicTagClass.hpp
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
/* Define to prevent recursive inclusion --------------------------------------*/
#ifndef ULTRASONIC_TAG_CLASS_HPP
#define ULTRASONIC_TAG_CLASS_HPP

/* Imports Library */
#include <string>

/* Class Constant Declaration--------------------------------------------------*/
/* Define Coordinate System for Left Team */
#define X_RECEIVER_TOP_LEFT			( -60 )		/*!< X-Position Receiver Top Left */
#define Y_RECEIVER_TOP_LEFT			( -60 )		/*!< Y-Position Receiver Top Left */
#define X_RECEIVER_MIDDLE_RIGHT		( 3060 ) 	/*!< X-Position Receiver Middle Right */
#define Y_RECEIVER_MIDDLE_RIGHT		( 1000 )	/*!< Y-Position Receiver Middle Right */
#define X_RECEIVER_BOTTOM_LEFT		( -60 )		/*!< X-Position Receiver Bottom Left */
#define Y_RECEIVER_BOTTOM_LEFT		( 2060 )	/*!< Y-Position Receiver Bottom Left */

/* Define Coordinate System for Right Team */
#define X_RECEIVER_TOP_RIGHT		( 3060 )	/*!< X-Position Receiver Top Right */
#define Y_RECEIVER_TOP_RIGHT		( -60 )		/*!< Y-Position Receiver Top Right */
#define X_RECEIVER_MIDDLE_LEFT		( -60 )		/*!< X-Position Receiver Middle Left */
#define Y_RECEIVER_MIDDLE_LEFT		( 1000 )	/*!< Y-Position Receiver Middle Left */
#define X_RECEIVER_BOTTOM_RIGHT		( 3060 )	/*!< X-Position Receiver Bottom Right */
#define Y_RECEIVER_BOTTOM_RIGHT		( 2060 )	/*!< Y-Position Receiver Bottom Right */

/* ID's of the Receivers */
#define ULTRASONIC_ID_RECEIVER1		"R41"		/*!< ID's Receiver 1, Team Right: Middle Right / Team Left: Middle Left*/
#define ULTRASONIC_ID_RECEIVER2		"R42"		/*!< ID's Receiver 2, Team Right: Bottom Left  / Team Left: Top Right */
#define ULTRASONIC_ID_RECEIVER3		"R43"		/*!< ID's Receiver 3, Team Right: Top Left     / Team Left: Bottom Right */

/* Class Type declaration -----------------------------------------------------*/
enum Team
{
	TeamRight = 0, TeamLeft = 1
};
/* Class Data declaration -----------------------------------------------------*/
/* Class definition -----------------------------------------------------------*/
class UltrasonicTagClass
{
	/*  -- Private Methods/Data -- */
   private:
   void getDistance(std::string const& sSerialMessage, std::string const& sRecID, int *pDistance);	/*!<  Method to get the Distance out of the USART-String */
   std::string sTAG_ID;											/*!<  ID of the used Tag */
   int iDistance1, iDistance2, iDistance3;						/*!<  Distance from each Receiver to Tag */
   int iX_Position, iY_Position;								/*!<  Position of the Tag */
   static int iTeamStartPosition;								/*!<  Class attribute for StartPosition to get the calculation*/

   /* -- Public Methods/Data -- */
   public:
   UltrasonicTagClass(std::string const& sNewTagID);  			/*!<  Constructor of Class UltrasonicTag*/
   void calculatePosition();									/*!<  Method to get the Position of the Tag */
   int checkSerialMessage(std::string const& sSerialMessage1, std::string const& sSerialMessage2, std::string const& sSerialMessage3);	/*!<  Method to get the Distance out of the USART String */
   int getX_Position(void) {return(iX_Position);};				/*!<  get Method for Position*/
   int getY_Position(void) {return(iY_Position);};				/*!<  get Method for Position*/
   static void setTeamStartPosition(int iStartPosition) {iTeamStartPosition = iStartPosition;};	/*!<  Set Method for  TeamStartPosition*/
   };

#endif	/*ULTRASONIC_TAG_CLASS_HPP*/
/**
 * @}
 */
