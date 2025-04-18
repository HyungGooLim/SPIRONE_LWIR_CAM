/*******************************************************************************
**
**    File NAME: lensdefs.h
**
**      AUTHOR:  Ron Torchia
**
**      CREATED: 2/12/2009
**  
**      DESCRIPTION: 
**
**      HISTORY:  2/12/2009 RJT - Initial Draft 
**
** Copyright 2009 FLIR Systems - Commercial Vision Systems
*******************************************************************************/
#ifndef _LENS_DEFS_H_ 
   #define _LENS_DEFS_H_
/******************************************************************************/
/** INCLUDE FILES                                                            **/
/******************************************************************************/
/* Lens Control Interface
**
** The following are the command IDs for the Lens Interface
** 
*/
/* GET commands range 0x100 - 0x1FF
*/
   #define LENS_GET_LENS_EXTENTS                0x100
   #define LENS_GET_VERSION                     0x101
   #define LENS_GET_UPTIME                      0x102
   #define LENS_GET_TEMPERATURE                 0x103
   #define LENS_GET_POSITION                    0x104
   #define LENS_GET_STATUS                      0x105
   #define LENS_GET_CURRENT_FOV                 0x106
   #define LENS_GET_BIT_STATUS                  0x107
   #define LENS_GET_FOV_INFINITY_FOCUS          0x108
   #define LENS_GET_EEPROM_BLOCK                0x109
   #define LENS_GET_REPORT_STATUS_MODE          0x10A   /* kNOWN eeprom VALUE*/

/* SET commands range 0x200 - 0x2FF
*/
   #define LENS_SET_POSITION                    0x200
   #define LENS_SELECT_FOV                      0x201
   #define LENS_SET_BIT_REQUEST                 0x202
   #define LENS_SET_NUC_REQUEST                 0x203
   #define LENS_SET_FOV_INFINITY_POSITION       0x204
   #define LENS_SET_EEPROM_BLOCK                0x205
   #define LENS_SET_REPORT_STATUS_MODE          0x206

/* USER commands range 0x300 - 0x3FF
*/
   #define LENS_ZOOM_START_MOVING_IN            0x300
   #define LENS_ZOOM_START_MOVING_OUT           0x301
   #define LENS_ZOOM_STOP_MOVING                0x302
   #define LENS_FOCUS_START_MOVING_IN           0x303
   #define LENS_FOCUS_START_MOVING_OUT          0x304
   #define LENS_FOCUS_STOP_MOVING               0x305


/* Temmek Lens Command Parameter Limits
*/
   #define _LENS_MIN_ZOOM_POSITION              0
   #define _LENS_MAX_ZOOM_POSITION              32000

   #define _LENS_MIN_FOCUS_POSITION             0
   #define _LENS_MAX_FOCUS_POSITION             32000

   #define _LENS_MIN_MOVEMENT_MODE              1
   #define _LENS_MAX_MOVEMENT_MODE              2

   #define _LENS_MIN_FOV_INDEX                  1
   #define _LENS_MAX_FOV_INDEX                  5

   #define _LENS_MIN_FOV_INFINITY_FLAG          1
   #define _LENS_MAX_FOV_INFINITY_FLAG          2

   #define _LENS_MIN_EEPROM_START_ADDRESS       0x000A
   #define _LENS_MAX_EEPROM_START_ADDRESS       0x0132

   #define _LENS_MIN_NUC_REQUEST_FLAG           0
   #define _LENS_MAX_NUC_REQUEST_FLAG           1

   #define _LENS_MIN_STATUS_REPORT_MODE         0
   #define _LENS_MAX_STATUS_REPORT_MODE         2

   #define _LENS_MIN_POWER_ON_BIT_MODE          0
   #define _LENS_MAX_POWER_ON_BIT_MODE          1

/******************************************************************************/
/** EXPORTED PUBLIC DATA                                                     **/
/******************************************************************************/

/******************************************************************************/
/** EXPORTED PUBLIC FUNCTIONS                                                **/
/******************************************************************************/

#endif  /* _LENS_DEFS_H_ */
