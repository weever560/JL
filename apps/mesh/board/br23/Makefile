
# make 编译并下载
# make VERBOSE=1 显示编译详细过程
# make clean 清除编译临时文件
# 注意： Linux 下编译方式：
# 1. 从 http://pkgman.jieliapp.com/doc/all 处找到下载链接
# 2. 下载后，解压到 /opt/jieli 目录下，保证
#   /opt/jieli/common/bin/clang 存在（注意目录层次）
# 3. 确认 ulimit -n 的结果足够大（建议大于8096），否则链接可能会因为打开文件太多而失败
#   可以通过 ulimit -n 8096 来设置一个较大的值

# 工具路径设置
ifeq ($(OS), Windows_NT)
# Windows 下工具链位置
TOOL_DIR := C:/JL/pi32/bin
CC    := clang.exe
CXX   := clang.exe
LD    := pi32v2-lto-wrapper.exe
AR    := pi32v2-lto-ar.exe
MKDIR := mkdir_win -p
RM    := rm -rf

SYS_LIB_DIR := C:/JL/pi32/pi32v2-lib/r3
SYS_INC_DIR := C:/JL/pi32/pi32v2-include
EXT_CFLAGS  := # Windows 下不需要 -D__SHELL__

## 后处理脚本
FIXBAT          := ..\..\..\..\tools\utils\fixbat.exe # 用于处理 utf8->gbk 编码问题
POST_SCRIPT     := ..\..\..\..\cpu\br23\tools\download.bat
RUN_POST_SCRIPT := $(POST_SCRIPT)
else
# Linux 下工具链位置
TOOL_DIR := /opt/jieli/pi32v2/bin
CC    := clang
CXX   := clang++
LD    := lto-wrapper
AR    := lto-ar
MKDIR := mkdir -p
RM    := rm -rf

SYS_LIB_DIR := $(TOOL_DIR)/../lib/r3
SYS_INC_DIR := $(TOOL_DIR)/../include
EXT_CFLAGS  := -D__SHELL__ # Linux 下需要这个保证正确处理 download.c

## 后处理脚本
FIXBAT          := touch # Linux下不需要处理 bat 编码问题
POST_SCRIPT     := ../../../../cpu/br23/tools/download.sh
RUN_POST_SCRIPT := bash $(POST_SCRIPT)
endif

CC  := $(TOOL_DIR)/$(CC)
CXX := $(TOOL_DIR)/$(CXX)
LD  := $(TOOL_DIR)/$(LD)
AR  := $(TOOL_DIR)/$(AR)
# 输出文件设置
OUT_ELF   := ../../../../cpu/br23/tools/sdk.elf
OBJ_FILE  := $(OUT_ELF).objs.txt
# 编译路径设置
BUILD_DIR := objs
# 工程路径前缀
ROOT_PREFIX := ../../../..

# 编译参数设置
CFLAGS := \
	-target pi32v2 \
	-mcpu=r3 \
	-integrated-as \
	-flto \
	-Wuninitialized \
	-Wno-invalid-noreturn \
	-fno-common \
	-integrated-as \
	-Oz \
	-g \
	-flto \
	-fallow-pointer-null \
	-fprefer-gnu-section \
	-Wno-shift-negative-value \
	-Wundef \
	-Wframe-larger-than=256 \
	-Wincompatible-pointer-types \
	-Wreturn-type \
	-Wimplicit-function-declaration \
	-fms-extensions \
	-w \


# 宏定义
DEFINES := \
	-DSUPPORT_MS_EXTENSIONS \
	-DCONFIG_RELEASE_ENABLE \
	-DCONFIG_CPU_BR23 \
	-DCONFIG_EQ_SUPPORT_ASYNC \
	-DCONFIG_MIXER_CYCLIC \
	-DCONFIG_FREE_RTOS_ENABLE \
	-DCONFIG_DNS_ENABLE \
	-DCONFIG_MMU_ENABLE \
	-DCONFIG_SBC_CODEC_HW \
	-DCONFIG_MSBC_CODEC_HW \
	-DCONFIG_AEC_M=640 \
	-DCONFIG_AUDIO_ONCHIP \
	-DCONFIG_MEDIA_DEVELOP_ENABLE \
	-D__GCC_PI32V2__ \
	-DCONFIG_NEW_ECC_ENABLE \
	-DEVENT_HANDLER_NUM_CONFIG=2 \
	-DEVENT_TOUCH_ENABLE_CONFIG=0 \
	-DEVENT_POOL_SIZE_CONFIG=256 \
	-DCONFIG_EVENT_KEY_MAP_ENABLE=0 \
	-DTIMER_POOL_NUM_CONFIG=10 \
	-DAPP_ASYNC_POOL_NUM_CONFIG=0 \
	-DVFS_ENABLE=1 \
	-DUSE_SDFILE_NEW=1 \
	-DVFS_FILE_POOL_NUM_CONFIG=0 \
	-DSDFILE_VERSION=0x020000 \
	-DVM_MAX_SIZE_CONFIG=16*1024 \
	-DVM_ITEM_MAX_NUM=128 \
	-DCONFIG_TWS_ENABLE \
	-DCONFIG_MESH_CASE_ENABLE \
	-DCONFIG_TRANSFER_ENABLE \
	-DCONFIG_LITE_AEC_ENABLE=0 \
	-DCONFIG_LITE_AUDIO \
	-DCONFIG_LMP_RESET_ENABLE \
	-DCONFIG_LMP_REFRESH_ENCRYPTION_KEY_ENABLE \
	-DCONFIG_LINK_DISTURB_SCAN_ENABLE=0 \
	-DCONFIG_BTCTRLER_TASK_DEL_ENABLE \
	-DCONFIG_UPDATA_ENABLE \
	-DCONFIG_OTA_UPDATA_ENABLE \
	-DCONFIG_ITEM_FORMAT_VM \
	-DTCFG_APP_BT_EN=1 \
	-DUSB_PC_NO_APP_MODE \
	-D__LD__ \


DEFINES += $(EXT_CFLAGS) # 额外的一些定义

# 头文件搜索路径
INCLUDES := \
	-I../../../../include_lib \
	-I../../../../include_lib/driver \
	-I../../../../include_lib/driver/device \
	-I../../../../include_lib/driver/cpu/br23 \
	-I../../../../include_lib/system \
	-I../../../../include_lib/system/generic \
	-I../../../../include_lib/system/device \
	-I../../../../include_lib/system/fs \
	-I../../../../include_lib/system/ui \
	-I../../../../include_lib/btctrler \
	-I../../../../include_lib/btctrler/port/br23 \
	-I../../../../include_lib/update \
	-I../../../../include_lib/agreement \
	-I../../../../include_lib/btstack/third_party/common \
	-I../../../../include_lib/btstack/third_party/rcsp \
	-I../../../../include_lib/media/media_develop \
	-I../../../../include_lib/media/media_develop/media \
	-I../../../../include_lib/media/media_develop/media/cpu/br23 \
	-I../../../../include_lib/media/media_develop/media/cpu/br23/asm \
	-I../../../../apps/mesh/board/br23 \
	-I../../../../apps/mesh/include \
	-I../../../../apps/common \
	-I../../../../apps/common/include \
	-I../../../../apps/common/config/include \
	-I../../../../apps/common/third_party_profile/common \
	-I../../../../apps/common/third_party_profile/jieli/JL_rcsp/rcsp_updata \
	-I../../../../apps/common/third_party_profile/jieli/JL_rcsp \
	-I../../../../apps/common/third_party_profile/jieli \
	-I../../../../include_lib/system/os/FreeRTOS \
	-I../../../../include_lib/btstack \
	-I../../../../apps/common/audio \
	-I../../../../cpu/br23/audio_dec \
	-I../../../../cpu/br23/audio_enc \
	-I../../../../cpu/br23 \
	-I../../../../apps/common/third_party_profile \
	-I../../../../apps/common/third_party_profile/sig_mesh \
	-I../../../../apps/common/third_party_profile/sig_mesh/tinycrypt/include \
	-I../../../../apps/common/third_party_profile/sig_mesh/adaptation \
	-I../../../../apps/mesh/api \
	-I$(SYS_INC_DIR) \


# 需要编译的 .c 文件
c_SRC_FILES := \
	../../../../apps/common/audio/audio_utils.c \
	../../../../apps/common/audio/decode/decode.c \
	../../../../apps/common/audio/sine_make.c \
	../../../../apps/common/bt_common/bt_test_api.c \
	../../../../apps/common/debug/debug.c \
	../../../../apps/common/device/key/adkey.c \
	../../../../apps/common/device/key/iokey.c \
	../../../../apps/common/device/key/key_driver.c \
	../../../../apps/common/third_party_profile/common/custom_cfg.c \
	../../../../apps/common/third_party_profile/jieli/JL_rcsp/rcsp_bluetooth.c \
	../../../../apps/common/third_party_profile/jieli/JL_rcsp/rcsp_updata/rcsp_ch_loader_download.c \
	../../../../apps/common/third_party_profile/jieli/JL_rcsp/rcsp_updata/rcsp_user_update.c \
	../../../../apps/common/third_party_profile/sig_mesh/access.c \
	../../../../apps/common/third_party_profile/sig_mesh/adaptation/ble_core/adv_core.c \
	../../../../apps/common/third_party_profile/sig_mesh/adaptation/ble_core/gatt_core.c \
	../../../../apps/common/third_party_profile/sig_mesh/adaptation/ble_core/hci_core.c \
	../../../../apps/common/third_party_profile/sig_mesh/adaptation/ble_core/scan_core.c \
	../../../../apps/common/third_party_profile/sig_mesh/adaptation/kernel/atomic_c.c \
	../../../../apps/common/third_party_profile/sig_mesh/adaptation/kernel/kernel_work.c \
	../../../../apps/common/third_party_profile/sig_mesh/adaptation/storage.c \
	../../../../apps/common/third_party_profile/sig_mesh/adaptation/utils.c \
	../../../../apps/common/third_party_profile/sig_mesh/adv.c \
	../../../../apps/common/third_party_profile/sig_mesh/api/sig_mesh_api.c \
	../../../../apps/common/third_party_profile/sig_mesh/beacon.c \
	../../../../apps/common/third_party_profile/sig_mesh/cdb.c \
	../../../../apps/common/third_party_profile/sig_mesh/cfg_cli.c \
	../../../../apps/common/third_party_profile/sig_mesh/cfg_srv.c \
	../../../../apps/common/third_party_profile/sig_mesh/crypto.c \
	../../../../apps/common/third_party_profile/sig_mesh/friend.c \
	../../../../apps/common/third_party_profile/sig_mesh/health_cli.c \
	../../../../apps/common/third_party_profile/sig_mesh/health_srv.c \
	../../../../apps/common/third_party_profile/sig_mesh/lpn.c \
	../../../../apps/common/third_party_profile/sig_mesh/main.c \
	../../../../apps/common/third_party_profile/sig_mesh/net.c \
	../../../../apps/common/third_party_profile/sig_mesh/net/buf.c \
	../../../../apps/common/third_party_profile/sig_mesh/prov.c \
	../../../../apps/common/third_party_profile/sig_mesh/proxy.c \
	../../../../apps/common/third_party_profile/sig_mesh/settings.c \
	../../../../apps/common/third_party_profile/sig_mesh/tinycrypt/source/aes_encrypt.c \
	../../../../apps/common/third_party_profile/sig_mesh/tinycrypt/source/cmac_mode.c \
	../../../../apps/common/third_party_profile/sig_mesh/tinycrypt/source/utils.c \
	../../../../apps/common/third_party_profile/sig_mesh/transport.c \
	../../../../apps/common/update/testbox_update.c \
	../../../../apps/common/update/update.c \
	../../../../apps/mesh/MshMDL/generic_level_srv.c \
	../../../../apps/mesh/MshMDL/generic_onoff_cli.c \
	../../../../apps/mesh/MshMDL/generic_onoff_srv.c \
	../../../../apps/mesh/MshMDL/generic_power_onoff_srv.c \
	../../../../apps/mesh/MshMDL/lightness_srv.c \
	../../../../apps/mesh/api/mesh_config_common.c \
	../../../../apps/mesh/api/model_api.c \
	../../../../apps/mesh/api/unix_timestamp.c \
	../../../../apps/mesh/app_idle.c \
	../../../../apps/mesh/app_main.c \
	../../../../apps/mesh/app_mesh.c \
	../../../../apps/mesh/audio_codec_demo.c \
	../../../../apps/mesh/board/br23/board_ac635n_demo.c \
	../../../../apps/mesh/demo_dec_frame_play.c \
	../../../../apps/mesh/examples/AliGenie_fan.c \
	../../../../apps/mesh/examples/AliGenie_light.c \
	../../../../apps/mesh/examples/AliGenie_socket.c \
	../../../../apps/mesh/examples/TUYA_light.c \
	../../../../apps/mesh/examples/generic_onoff_client.c \
	../../../../apps/mesh/examples/generic_onoff_server.c \
	../../../../apps/mesh/examples/light_lightness_server.c \
	../../../../apps/mesh/examples/vendor_client.c \
	../../../../apps/mesh/examples/vendor_server.c \
	../../../../apps/mesh/lib_config/lib_btctrler_config.c \
	../../../../apps/mesh/lib_config/lib_btstack_config.c \
	../../../../apps/mesh/lib_config/lib_driver_config.c \
	../../../../apps/mesh/lib_config/lib_media_config.c \
	../../../../apps/mesh/lib_config/lib_profile_config.c \
	../../../../apps/mesh/lib_config/lib_system_config.c \
	../../../../apps/mesh/lib_config/lib_update_config.c \
	../../../../apps/mesh/log_config.c \
	../../../../apps/mesh/user_cfg.c \
	../../../../apps/mesh/version.c \
	../../../../cpu/br23/adc_api.c \
	../../../../cpu/br23/audio_common/app_audio.c \
	../../../../cpu/br23/audio_dec/audio_dec.c \
	../../../../cpu/br23/audio_dec/audio_dec_tone.c \
	../../../../cpu/br23/audio_dec/tone_player.c \
	../../../../cpu/br23/audio_enc/audio_adc_demo.c \
	../../../../cpu/br23/audio_enc/audio_enc.c \
	../../../../cpu/br23/audio_enc/audio_mic_codec.c \
	../../../../cpu/br23/charge.c \
	../../../../cpu/br23/chargestore.c \
	../../../../cpu/br23/clock_manager.c \
	../../../../cpu/br23/ctmu.c \
	../../../../cpu/br23/handshake_timer.c \
	../../../../cpu/br23/iic_eeprom_test.c \
	../../../../cpu/br23/iic_hw.c \
	../../../../cpu/br23/iic_slave_test.c \
	../../../../cpu/br23/iic_soft.c \
	../../../../cpu/br23/irflt.c \
	../../../../cpu/br23/led_spi.c \
	../../../../cpu/br23/ledc_test.c \
	../../../../cpu/br23/mcpwm.c \
	../../../../cpu/br23/pap.c \
	../../../../cpu/br23/plcnt.c \
	../../../../cpu/br23/port_wkup.c \
	../../../../cpu/br23/pwm_led.c \
	../../../../cpu/br23/setup.c \
	../../../../cpu/br23/spi.c \
	../../../../cpu/br23/spi_test.c \
	../../../../cpu/br23/uart_dev.c \
	../../../../cpu/br23/uart_test.c \


# 需要编译的 .S 文件
S_SRC_FILES :=


# 需要编译的 .s 文件
s_SRC_FILES :=


# 需要编译的 .cpp 文件
cpp_SRC_FILES :=


# 链接参数
LFLAGS := \
	--plugin-opt=-pi32v2-always-use-itblock=false \
	--plugin-opt=-enable-ipra=true \
	--plugin-opt=-pi32v2-merge-max-offset=4096 \
	--plugin-opt=-pi32v2-enable-simd=true \
	--plugin-opt=mcpu=r3 \
	--plugin-opt=-global-merge-on-const \
	--plugin-opt=-inline-threshold=5 \
	--plugin-opt=-inline-max-allocated-size=32 \
	--plugin-opt=-inline-normal-into-special-section=true \
	--plugin-opt=-dont-used-symbol-list=malloc,free,sprintf,printf,puts,putchar \
	--plugin-opt=save-temps \
	--plugin-opt=-pi32v2-enable-rep-memop \
	--plugin-opt=-warn-stack-size=256 \
	--sort-common \
	--dont-complain-call-overflow \
	--plugin-opt=-used-symbol-file=../../../../cpu/br23/sdk_used_list.used \
	--gc-sections \
	--start-group \
	../../../../cpu/br23/liba/cpu.a \
	../../../../cpu/br23/liba/system.a \
	../../../../cpu/br23/liba/btstack.a \
	../../../../cpu/br23/liba/btctrler.a \
	../../../../cpu/br23/liba/crypto_toolbox_Osize.a \
	../../../../cpu/br23/liba/rcsp_stack.a \
	../../../../cpu/br23/liba/agreement.a \
	../../../../cpu/br23/liba/JL_Phone_Call.a \
	../../../../cpu/br23/liba/math.a \
	../../../../cpu/br23/liba/media.a \
	../../../../cpu/br23/liba/media_app.a \
	../../../../cpu/br23/liba/opus_enc_lib.a \
	../../../../cpu/br23/liba/speex_enc_lib.a \
	../../../../cpu/br23/liba/bfilterfun_lib.a \
	../../../../cpu/br23/liba/wtg_dec_lib.a \
	../../../../cpu/br23/liba/wav_dec_lib.a \
	../../../../cpu/br23/liba/wtgv2_dec_lib.a \
	../../../../cpu/br23/liba/lib_adpcm_ima_code.a \
	../../../../cpu/br23/liba/lib_adpcm_code.a \
	../../../../cpu/br23/liba/lc3_codec_lib.a \
	../../../../cpu/br23/liba/lib_midi_dec.a \
	../../../../cpu/br23/liba/update.a \
	--end-group \
	-T../../../../cpu/br23/sdk.ld \
	-M=../../../../cpu/br23/tools/sdk.map \
	--plugin-opt=mcpu=r3 \
	--plugin-opt=-mattr=+fprev1 \


LIBPATHS := \
	-L$(SYS_LIB_DIR) \


LIBS := \
	$(SYS_LIB_DIR)/libm.a \
	$(SYS_LIB_DIR)/libc.a \
	$(SYS_LIB_DIR)/libm.a \
	$(SYS_LIB_DIR)/libcompiler-rt.a \



c_OBJS    := $(c_SRC_FILES:%.c=%.c.o)
S_OBJS    := $(S_SRC_FILES:%.S=%.S.o)
s_OBJS    := $(s_SRC_FILES:%.s=%.s.o)
cpp_OBJS  := $(cpp_SRC_FILES:%.cpp=%.cpp.o)

OBJS      := $(c_OBJS) $(S_OBJS) $(s_OBJS) $(cpp_OBJS)
DEP_FILES := $(OBJS:%.o=%.d)


OBJS      := $(addprefix $(BUILD_DIR)/, $(OBJS:$(ROOT_PREFIX)/%=%))
DEP_FILES := $(addprefix $(BUILD_DIR)/, $(DEP_FILES:$(ROOT_PREFIX)/%=%))


VERBOSE ?= 0
ifeq ($(VERBOSE), 1)
QUITE :=
else
QUITE := @
endif

# 一些旧的 make 不支持 file 函数，需要 make 的时候指定 LINK_AT=0 make
LINK_AT ?= 1

.PHONY: all clean pre_build

all: pre_build $(OUT_ELF)
	$(info +POST-BUILD)
	$(QUITE) $(RUN_POST_SCRIPT) sdk

pre_build:
	$(info +PRE-BUILD)
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -E -P ../../../../cpu/br23/sdk_used_list.c -o ../../../../cpu/br23/sdk_used_list.used
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -E -P ../../../../cpu/br23/sdk_ld.c -o ../../../../cpu/br23/sdk.ld
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -E -P ../../../../cpu/br23/tools/download.c -o $(POST_SCRIPT)
	$(QUITE) $(FIXBAT) $(POST_SCRIPT)
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -E -P ../../../../cpu/br23/tools/isd_config_rule.c -o ../../../../cpu/br23/tools/isd_config.ini

clean:
	$(QUITE) $(RM) $(OUT_ELF)
	$(QUITE) $(RM) $(BUILD_DIR)



ifeq ($(LINK_AT), 1)
$(OUT_ELF): $(OBJS)
	$(info +LINK $@)
	$(shell $(MKDIR) $(@D))
	$(file >$(OBJ_FILE), $(OBJS))
	$(QUITE) $(LD) -o $(OUT_ELF) @$(OBJ_FILE) $(LFLAGS) $(LIBPATHS) $(LIBS)
else
$(OUT_ELF): $(OBJS)
	$(info +LINK $@)
	$(shell $(MKDIR) $(@D))
	$(QUITE) $(LD) -o $(OUT_ELF) $(OBJS) $(LFLAGS) $(LIBPATHS) $(LIBS)
endif


$(BUILD_DIR)/%.c.o : $(ROOT_PREFIX)/%.c
	$(info +CC $<)
	@$(MKDIR) $(@D)
	@$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -MM -MT "$@" $< -o $(@:.o=.d)
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/%.S.o : $(ROOT_PREFIX)/%.S
	$(info +AS $<)
	@$(MKDIR) $(@D)
	@$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -MM -MT "$@" $< -o $(@:.o=.d)
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/%.s.o : $(ROOT_PREFIX)/%.s
	$(info +AS $<)
	@$(MKDIR) $(@D)
	@$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -MM -MT "$@" $< -o $(@:.o=.d)
	$(QUITE) $(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/%.cpp.o : $(ROOT_PREFIX)/%.cpp
	$(info +CXX $<)
	@$(MKDIR) $(@D)
	@$(CXX) $(CFLAGS) $(DEFINES) $(INCLUDES) -MM -MT "$@" $< -o $(@:.o=.d)
	$(QUITE) $(CXX) $(CFLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

-include $(DEP_FILES)
