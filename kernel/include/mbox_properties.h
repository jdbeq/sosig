#ifndef MBOX_PROPERTIES_H
#define MBOX_PROPERITES_H

typedef enum {
    /* Videocore */
    TAG_GET_FIRMWARE_VERSION = 0x10000,

    /* Hardware */
    TAG_GET_BOARD_MODEL = 0x10001,
    TAG_GET_BOARD_REVISION = 0x10002,
    TAG_GET_BOARD_MAC_ADDRESS = 0x10003,
    TAG_GET_BOARD_SERIAL = 0x10004,
    TAG_GET_ARM_MEMORY = 0x10005,
    TAG_GET_VC_MEMORY = 0x10006,
    TAG_GET_CLOCKS = 0x10007,

    /* Clocks */
    TAG_GET_CLOCK_STATE = 0x30001,
    TAG_SET_CLOCK_STATE = 0x38001,
    TAG_GET_CLOCK_RATE = 0x30002,
    TAG_SET_CLOCK_RATE = 0x38002,
    TAG_GET_MAX_CLOCK_RATE = 0x30004,
    TAG_GET_MIN_CLOCK_RATE = 0x30007,
    TAG_GET_TURBO = 0x30009,
    TAG_SET_TURBO = 0x38009,

	/* Memory */
    TAG_ALLOCATE_MEMORY = 0x3000C,
    TAG_LOCK_MEMORY = 0x3000D,
    TAG_UNLOCK_MEMORY = 0x3000E,
    TAG_RELEASE_MEMORY = 0x3000F,
    TAG_EXECUTE_CODE = 0x30010,
    TAG_GET_DISPMANX_MEM_HANDLE = 0x30014,
    TAG_GET_EDID_BLOCK = 0x30020,
    
        /* Command Line */
    TAG_GET_COMMAND_LINE = 0x50001,

    /* DMA Management */
    TAG_GET_DMA_CHANNELS = 0x60001,

    /* Framebuffer */
    TAG_ALLOCATE_BUFFER = 0x40001,
    TAG_RELEASE_BUFFER = 0x48001,
    TAG_BLANK_SCREEN = 0x40002,
    TAG_GET_PHYSICAL_SIZE = 0x40003,
    TAG_TEST_PHYSICAL_SIZE = 0x44003,
    TAG_SET_PHYSICAL_SIZE = 0x48003,
    TAG_GET_VIRTUAL_SIZE = 0x40004,
    TAG_TEST_VIRTUAL_SIZE = 0x44004,
    TAG_SET_VIRTUAL_SIZE = 0x48004,
    TAG_GET_DEPTH = 0x40005,
    TAG_TEST_DEPTH = 0x44005,
    TAG_SET_DEPTH = 0x48005,
    TAG_GET_PIXEL_ORDER = 0x40006,
    TAG_TEST_PIXEL_ORDER = 0x44006,
    TAG_SET_PIXEL_ORDER = 0x48006,
    TAG_GET_ALPHA_MODE = 0x40007,
    TAG_TEST_ALPHA_MODE = 0x44007,
    TAG_SET_ALPHA_MODE = 0x48007,
    TAG_GET_PITCH = 0x40008,
    TAG_GET_VIRTUAL_OFFSET = 0x40009,
    TAG_TEST_VIRTUAL_OFFSET = 0x44009,
    TAG_SET_VIRTUAL_OFFSET = 0x48009,
    TAG_GET_OVERSCAN = 0x4000A,
    TAG_TEST_OVERSCAN = 0x4400A,
    TAG_SET_OVERSCAN = 0x4800A,
    TAG_GET_PALETTE = 0x4000B,
    TAG_TEST_PALETTE = 0x4400B,
    TAG_SET_PALETTE = 0x4800B,
    TAG_SET_CURSOR_INFO = 0x8011,
    TAG_SET_CURSOR_STATE = 0x8010

    } mb_tag;

typedef enum {
    TAG_STATE_REQUEST = 0,
    TAG_STATE_RESPONSE = 1,
    } tag_state;
    
typedef enum {
    PT_OSIZE = 0,
    PT_OREQUEST_OR_RESPONSE = 1,
    } tag_buffer_offset;

typedef enum {
    T_OIDENT = 0,
    T_OVALUE_SIZE = 1,
    T_ORESPONSE = 2,
    T_OVALUE = 3,
    } tag_offset;

typedef struct {
    int tag;
    int byte_length;
    union {
        int value_32;
        unsigned char buffer_8[256];
        int buffer_32[64];
    } data;
    } mbox_property_t;

typedef enum {
    TAG_CLOCK_RESERVED = 0x0,
    TAG_CLOCK_EMMC = 0x1,
    TAG_CLOCK_UART = 0x2,
    TAG_CLOCK_ARM = 0x3,
    TAG_CLOCK_CORE = 0x4,
    TAG_CLOCK_V3D = 0x5,
    TAG_CLOCK_H264 = 0x6,
    TAG_CLOCK_ISP = 0x7,
    TAG_CLOCK_SDRAM = 0x8,
    TAG_CLOCK_PIXEL = 0x9,
    TAG_CLOCK_PWM = 0xA,
    TAG_CLOCK_HEVC = 0xB,
    TAG_CLOCK_EMMC2 = 0xC,
    TAG_CLOCK_M2MC = 0xD,
    TAG_CLOCK_PIX_BVB = 0xE
    } tag_clock_id_t;

void property_init( void );
void property_add_tag( mb_tag tag, ... );
mbox_property_t* property_get( mb_tag tag );

#endif
