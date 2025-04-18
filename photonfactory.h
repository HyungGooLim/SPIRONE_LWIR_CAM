#ifndef _PHOTONFACTORY_H_
#define _PHOTONFACTORY_H_
#ifdef __cplusplus
extern "C"
{
#endif

/* enums and typedefs that should not be exposed in photondefs.h */

typedef enum cam_gain_cmd
{
    CALC_FRAME_DIFF             = 0,
    CALC_GAIN_FRAME             = 1,
    FIND_BAD_PIXELS             = 2,
    SET_FRAME_VALUE             = 3
} CAM_GAIN_CMD;

typedef enum VideoSmoothing
{
    VIDEO_SMOOTHING_OFF = 0,
    VIDEO_SMOOTHING_ON  = 1
} PHOTON_VIDEO_SMOOTHING;

typedef enum SymbolColor
{
    SYMBOLS_WHITE_BLACK = 0, 
    SYMBOLS_OVERBRIGHT  = 1, 
    SYMBOLS_OFF         = 2, 
    SYMBOLS_YELLOW      = 3, 
    SYMBOLS_RED         = 4, 
    SYMBOLS_MAGENTA     = 5, 
    SYMBOLS_BLUE        = 6, 
    SYMBOLS_CYAN        = 7,
    SYMBOLS_GREEN       = 8 
} PHOTON_SYMBOL_COLOR;

typedef enum CamFamily
{
    CAM_TYPE_UNKNOWN = 0,
    CAM_TYPE_UL3     = 1, 
    CAM_TYPE_AUTOCAM = 2,
    CAM_TYPE_FLIR    = 3,
    CAM_TYPE_WIDEEYE = 4,
    CAM_TYPE_MSA     = 5,
    CAM_TYPE_BULLARD = 6
} PHOTON_CAM_FAMILY;

typedef enum CaseTemp
{
    CASE_TEMP_DEGx10      = 0,
    CASE_TEMP_COUNTS      = 1,
    CASE_TEMP_LENS_COUNTS = 2
} PHOTON_CASE_TEMP;

typedef enum DataSource
{
    DATA_SOURCE_FPGA     = 0, 
    DATA_SOURCE_ON_CHIP  = 1, 
    DATA_SOURCE_0FF_CHIP = 2, 
    DATA_SOURCE_LG_0     = 3, 
    DATA_SOURCE_LG_1     = 4, 
    DATA_SOURCE_LG_2     = 5, 
    DATA_SOURCE_LG_3     = 6 
} PHOTON_DATA_SOURCE;


typedef enum CalFlag
{
    DO_NOT_READ_CAL = 0,
    READ_CAL        = 1
} PHOTON_CAL_FLAG;

typedef enum GetSet
{
    GET_DATA          = 0,
    SET_AND_SAVE_DATA = 1,
    SET_DATA          = 2
} PHOTON_GET_SET;

//typedef enum FlashError
//{
//    FLASH_ERASE_ERROR = -1,
//    FLASH_WRITE_ERROR = -2 
//} PHOTON_FLASH_ERROR;

typedef enum SecurityOptions
{
    PASSWORD_REQ_MASK    = 1,  /*!<  */
    TAMPER_PROTECT_MASK  = 2,  /*!<  */
    FACTORY_LOCKOUT_MASK = 4   /*!<  */
} PHOTON_SECURITY_OPTIONS;


typedef enum FPA25UCommand
{
    FPA25U_SP_A        = 0 ,
    FPA25U_LVDP        = 0 ,
    FPA25U_RA          = 1 ,
    FPA25U_RM          = 2 ,
    FPA25U_RCA         = 3 ,
    FPA25U_ORA         = 4 ,
    FPA25U_IMA         = 5 ,
    FPA25U_ISA         = 6 ,
    FPA25U_IAA         = 7 ,
    FPA25U_FPA25U_ICA  = 8 ,
    FPA25U_ITA         = 9 ,
    FPA25U_ILA         = 10,
    FPA25U_CLA         = 11,
    FPA25U_FPA25U_IRA  = 12,
    FPA25U_REFEN       = 13,
    FPA25U_RMPG        = 14,
    FPA25U_ATEMP       = 15,
    FPA25U_GTEMP       = 16,
    FPA25U_DPEN        = 17,
    FPA25U_TST         = 18,
    FPA25U_UP          = 19,
    FPA25U_INTRLCD     = 20,
    FPA25U_FIELD       = 21,
    FPA25U_BR_AMP      = 22,
    FPA25U_BR_TP       = 23,
    FPA25U_BS_RS       = 24,
    FPA25U_BS_LT       = 25,
    FPA25U_VET         = 26,
    FPA25U_SP_D        = 27,
    FPA25U_VREFA       = 27,
    FPA25U_LVRP        = 28,
    FPA25U_LVDSDT      = 29,
    FPA25U_LVDSD       = 30,
    FPA25U_BLIND8      = 31
} CAM_FPA25U_COMMAND;

typedef enum factory_command{
    //  Factory commands
    FPGA_SOFT_RESET             =   100,
    CAMERA_SERIAL               =   101,
    CAMERA_OPTIONS              =   103,
    GET_CLIP_HIST_SUM           =   105,
    //Omega Compatiblity
    GET_PSEUDO_GAIN             =   107,
    PSEUDO_GAIN                 =   108,
    //Omega Compatiblity
    GET_PLATEAU_VALUE           =   109,
    LENS_4_CAL                  =   110,
    LENS_ID                     =   111,
    CAL_FLAG                    =   113,
    NORMALIZATION_TARGET        =   115,
    GAIN_SWITCH_VALUES          =   118,
    SHUTTER_MOTOR_TIME          =   119,
    //Omega Compatibility
    GET_SHUTTER_MOTOR_TIME      =   120,
    VIDEO_SMOOTHING             =   122,
    CAL_DATE_STAMP              =   123,
    SHUTTER_TEMP_DELTA          =   124,
    COMMAND_WORD                =   126,
    //Omega Compatiblity
    READ_COMMAND_WORD           =   127,
    SET_FPGA_STATE              =   128,
    NORMALIZE_OFFSET_DAC        =   129,
    //TRANSFER_FRAME              =   130,
    CALC_GAIN                   =   131,
    DRAM_EXISTS                 =   132,
    GET_BAD_PIXEL_COUNT         =   134,
    PIXEL_GAIN                  =   135,
    GET_INT_START               =   144,
    GET_INT_TIME                =   145,
    GET_TEMP_BIAS               =   146,
    GET_HI_OFFSET               =   147,
    GET_LO_OFFSET               =   148,
    GET_GBL_GAIN                =   149,
    GET_VIDEO_MODE              =   150,
    GET_TEST_MODE               =   151,
    GET_DET_PROTECT             =   152,
    GET_VET_ADDR                =   153,
    GET_MSTR_RESET              =   154,
    GET_CLK_DELAY               =   155,
    GET_BCOMP_ENABLE            =   156,

    SET_INT_START               =   160,
    SET_INT_TIME                =   161,
    SET_TEMP_BIAS               =   162,
    SET_HI_OFFSET               =   163,
    SET_LO_OFFSET               =   164,
    SET_GBL_GAIN                =   165,
    SET_VIDEO_MODE              =   166,
    SET_TEST_MODE               =   167,
    TEMP_VOLTAGE_CAL            =   168,
    HUMIDITY_THRESHOLD          =   169,
    FPA_PARAMS                  =   170,
    SET_CLK_DELAY               =   171,
    SET_BCOMP_ENABLE            =   172,
    SCAN_TEMP_BIAS              =   175,
    READ_TEMP_BIAS_SCAN         =   176,
    //CORRECTION_MASK             =   177,
    
    NOISE_LEVEL                 =   178,
    
    SET_SECURITY_LEVEL          =   180,
    GET_SECURITY_LEVEL          =   181,
    GET_FLUX_FROM_TEMP          =   182,
    GET_TEMP_FROM_FLUX          =   183,
    CASE_TEMP_CORRECTION        =   184,
    RELATIVE_RESPONSE_CONSTANTS =   185,
    NUC_TABLE_RESPONSE_CONSTANTS=   186,

    DATA_SOURCE_SELECT          =   189,
    ERASE_NUC_TABLE             =   190,
    WRITE_ONCHIP_TABLE          =   191,
    WRITE_GAIN_TABLE            =   192,
    WRITE_LAGRANGE_TABLE        =   193,
    WRITE_NUC_HEADER            =   194,
    WRITE_STATIC_HEADER         =   195,
   
    WRITE_FACTORY_HEADER        =   199,
    MIN_PIXEL_GAIN              =   200,
    MAX_PIXEL_GAIN              =   201,
    SET_GLOBAL_GDAC             =   202,
    SET_GLOBAL_BDAC             =   203,
    SET_GLOBAL_ODAC             =   204,
    INIT_RDAC                   =   205,
    FINAL_RDAC                  =   206,
    BOLO_COMP_ACQUIRE           =   207,
    //Omega compatibility
    GET_R_EXTERNAL              =   208,
    R_EXTERNAL                  =   209,
    READ_MEMORY                 =   210,
    WRITE_MEMORY                =   211,
    ERASE_FLASH_BLOCK           =   212,
    GET_PROGRAM_ADDRESS         =   213,
    GET_NUC_ADDRESS             =   214,
    INITIAL_REXT                =   215,
    FINAL_REXT                  =   216,
    GET_BEST_REXT               =   217,
    RDAC_4_REXT_CAL             =   218,
    BAD_PIXEL_LIMITS            =   220,
    GLOBAL_BAD_PIXEL_LIMITS     =   221,
    NOISY_PIXEL_TEST            =   222,
    SLOW_PIXEL_TEST             =   223,
    GLOBAL_BAD_PIXEL_COUNT      =   224,
    BAD_PIXEL_NUMBER            =   225,
	 VIDEO_RATE                  =   228,
    RESPONSIVITY_ATTENUATION    =   229,
    WRITE_DRAM_NUC              =   230,
    READ_DRAM_NUC               =   231,
    NOISE_FILTER_COUNTS         =   232,
    SET_FRAME_RATE              =   233,
    SET_INTEGRATION_MODE        =   234,
    
    /* pulled functions not used in photon SDK from photondefs.h */
    SYMBOL_COLOR            = 26,
    GET_CONTRAST            = 22,     /* Omega Compatibility */  
    GET_BRIGHTNESS          = 23,     /* Omega Compatibility */
    GET_BRIGHTNESS_BIAS     = 25,     /* Omega Compatibility */
    //LENS_NUMBER             = 30,
    //GET_ISOTHERM_THRESHOLDS = 36,     /* Omega Compatibility */
    GET_FFC_PERIOD          = 38,     /* Omega Compatibility */
    GET_FFC_TEMP_DELTA      = 39,     /* Omega Compatibility */
    //GET_LENS_ID             = 40,     /* Omega Compatibility */
    GET_SET_MAX_AGC_GAIN    = 64,     /* Omega Compatibility */
    SET_ENCRYPTION_PASSWORD = 65,
    GET_ENCRYPTION_SEED     = 66,    
    GET_VIDEO_ARRAY_OFFSET  = 69,     /* Omega Compatibility */
    READ_FPA_TEMP           = 72,
    RADIOMETRIC_DATA        = 73,
    TEMP_SENSE_BIAS         = 74,
    READ_ROW_DATA           = 80,    
    DISABLE_FACTORY_LOCKOUT = 99,
    NUC_TABLE_LOAD          = 116,
    NUC_TABLE_SELECT        = 117
} PHOTON_FACTORY_COMMAND;

/* Frame command types */
typedef enum FrameCommand
{ 
    FRAME_PLAYBACK      = 0x0100,
    FRAME_MASK          = 0x00FF,
    FRAME_TYPE_MASK     = 0xFF00,

    VIDEO_CAPTURE_TAG   = 0x0000,
    ONCHIP_CAPTURE_TAG  = 0x0200,
    GAIN_CAPTURE_TAG    = 0x0400,

    VIDEO_PLAYBACK_TAG  = VIDEO_CAPTURE_TAG  | FRAME_PLAYBACK,
    ONCHIP_PLAYBACK_TAG = ONCHIP_CAPTURE_TAG | FRAME_PLAYBACK,
    GAIN_PLAYBACK_TAG   = GAIN_CAPTURE_TAG   | FRAME_PLAYBACK,

} FRAME_COMMAND;

#ifdef __cplusplus
}
#endif
#endif /*_PHOTONFACTORY_H_*/
