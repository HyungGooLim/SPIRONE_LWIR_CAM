/*******************************************************************************
**
**    File NAME: CooledCoreControlDefs.h
**
**      AUTHOR:  David Dart
**
**      CREATED: 3/11/2009
**  
**      DESCRIPTION: Contains Interfaces to the Cooled Core Commands
**
**      HISTORY:  3/11/2009 DWD - Initial Draft 
**
** Copyright 2008 FLIR Systems - Commercial Vision Systems
*******************************************************************************/
#ifndef _COOLED_CORE_CONTROL_H_ 
   #define _COOLED_CORE_CONTROL_H_
/******************************************************************************/
/** INCLUDE FILES                                                            **/
/******************************************************************************/

/* Photon Command Interface for Cooled Core
*/
#define CALC_GAIN						131
#define SET_INT_TIME					161
#define R_EXTERNAL						209
#define SET_FRAME_RATE					233
#define SET_INTEGRATION_MODE			234

/* Cooled Core Command Interface
**
** The following are the command IDs for the Cooled Core Command Interface
** 
*/
/* GET commands range 0x100 - 0x1FF
*/
   #define COOLED_CORE_GET_MAX_PIXEL_VALUE_LIMIT            0x100    /* Bad Pixel Detection Parameter */
   #define COOLED_CORE_GET_MIN_PIXEL_VALUE_LIMIT            0x101    /* Bad Pixel Detection Parameter */   
   #define COOLED_CORE_GET_MAX_PIXEL_GAIN_LIMIT             0x102    /* Bad Pixel Detection Parameter */
   #define COOLED_CORE_GET_MIN_PIXEL_GAIN_LIMIT             0x103    /* Bad Pixel Detection Parameter */

   #define COOLED_CORE_GET_BAD_PIXEL_DETECTION_RESULTS      0x104    /* Bad Pixel Detection Results */

   #define COOLED_CORE_GET_SCENE_MEAN_INTENSITY             0x105    /* Scene intensity */

   #define COOLED_CORE_GET_AUTO_FOCUS_ENABLE                0x106    /* Auto Focus Enable */ 
   #define COOLED_CORE_GET_AUTO_FOCUS_ROI                   0x107    /* Auto Focus ROI */
   #define COOLED_CORE_GET_AUTO_FOCUS_METRIC_RESULT         0x108    /* Auto Focus Gradient Metric Result */
   #define COOLED_CORE_GET_AUTO_FOCUS_METRIC_THRESHOLD      0x109    /* Auto Focus Gradient Metric Threshold */

   #define COOLED_CORE_GET_AUTO_FOCUS_BUMP_AMOUNT           0x10A    /* Auto Focus Bump */

   #define COOLED_CORE_GET_ACTIVE_NUC                       0x10B    /* Returns the active NUC table number */

   #define COOLED_CORE_GET_CAL_STATUS                       0x10C    /* Calibration Status: Ready, Busy */

   #define COOLED_CORE_GET_PIXEL_GAIN                       0x10D    /* Calibration Status: Ready, Busy */

/* SET commands range 0x200 - 0x2FF
*/
   #define COOLED_CORE_SET_MAX_PIXEL_VALUE_LIMIT            0x200    /* Bad Pixel Detection Parameter */
   #define COOLED_CORE_SET_MIN_PIXEL_VALUE_LIMIT            0x201    /* Bad Pixel Detection Parameter */
   #define COOLED_CORE_SET_MAX_PIXEL_GAIN_LIMIT             0x202    /* Bad Pixel Detection Parameter */
   #define COOLED_CORE_SET_MIN_PIXEL_GAIN_LIMIT             0x203    /* Bad Pixel Detection Parameter */

   #define COOLED_CORE_SET_AUTO_FOCUS_ENABLE                0x204    /* Auto Focus Enable */ 
   #define COOLED_CORE_SET_AUTO_FOCUS_ROI                   0x205    /* Auto Focus ROI */
   #define COOLED_CORE_SET_AUTO_FOCUS_METRIC_THRESHOLD      0x206    /* Auto Focus Gradient Metric Threshold */

   #define COOLED_CORE_SET_AUTO_FOCUS_BUMP_AMOUNT           0x207    /* Auto Focus Bump */

   #define COOLED_CORE_SET_ACTIVE_NUC                       0x208    /* Selects (loads) the active NUC table */

   #define COOLED_CORE_SET_PIXEL_GAIN                       0x209    /* Selects (loads) the active NUC table */

/* USER commands range 0x300 - 0x3FF
*/
//#define COOLED_CORE_            0x300



/* Cooled Core Command Parameter Limits
*/
   #define COOLED_CORE_LIMIT_MIN_PIXEL_VALUE_LIMIT          0
   #define COOLED_CORE_LIMIT_MAX_PIXEL_VALUE_LIMIT          0x3FFF   /* 16383 - 14-bit ADC */

/******************************************************************************/
/** EXPORTED PUBLIC DATA                                                     **/
/******************************************************************************/

/******************************************************************************/
/** EXPORTED PUBLIC FUNCTIONS                                                **/
/******************************************************************************/

#endif  /* _COOLED_CORE_CONTROL_H_ */
