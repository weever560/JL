#ifndef _AUDIO_CONFIG_H_
#define _AUDIO_CONFIG_H_

#include "generic/typedef.h"
#include "app_config.h"

#define AUDIO_MIXER_LEN			(128 * 4 * 2)

/*解码任务cpu占用率跟踪*/
#define TCFG_AUDIO_DECODER_OCCUPY_TRACE		1

#if BT_SUPPORT_MUSIC_VOL_SYNC
#define TCFG_MAX_VOL_PROMPT						 0
#else
#define TCFG_MAX_VOL_PROMPT						 1
#endif

/*
 *该配置适用于没有音量按键的产品，防止打开音量同步之后
 *连接支持音量同步的设备，将音量调小过后，连接不支持音
 *量同步的设备，音量没有恢复，导致音量小的问题
 *默认是没有音量同步的，将音量设置到最大值，可以在vol_sync.c
 *该宏里面修改相应的设置。
 */
#define TCFG_VOL_RESET_WHEN_NO_SUPPORT_VOL_SYNC	 0	//不支持音量同步的设备默认最大音量

/*
 *省电容mic偏置电压自动调整(因为校准需要时间，所以有不同的方式)
 *1、烧完程序（完全更新，包括配置区）开机校准一次
 *2、上电复位的时候都校准,即断电重新上电就会校准是否有偏差(默认)
 *3、每次开机都校准，不管有没有断过电，即校准流程每次都跑
 */
#define MC_BIAS_ADJUST_DISABLE		0	//省电容mic偏置校准关闭
#define MC_BIAS_ADJUST_ONE			1	//省电容mic偏置只校准一次（跟dac trim一样）
#define MC_BIAS_ADJUST_POWER_ON		2	//省电容mic偏置每次上电复位都校准(Power_On_Reset)
#define MC_BIAS_ADJUST_ALWAYS		3	//省电容mic偏置每次开机都校准(包括上电复位和其他复位)

#if TCFG_MIC_CAPLESS_ENABLE
#define TCFG_MC_BIAS_AUTO_ADJUST	MC_BIAS_ADJUST_POWER_ON
#define TCFG_MC_CONVERGE_TRACE		0	//省电容mic收敛值跟踪
#else
#define TCFG_MC_BIAS_AUTO_ADJUST	MC_BIAS_ADJUST_DISABLE
#define TCFG_MC_CONVERGE_TRACE		0	//省电容mic收敛值跟踪
#endif/*TCFG_MIC_CAPLESS_ENABLE*/
#define TCFG_MC_MIC_ONLINE_CHECK_EN	0	//省电容mic在线检测
/*
 *省电容mic收敛步进限制
 *0:自适应步进调整, >0:收敛步进最大值
 *注：当mic的模拟增益或者数字增益很大的时候，mic_capless模式收敛过程,
 *变化的电压放大后，可能会听到哒哒声，这个时候就可以限制住这个收敛步进
 *让收敛平缓进行(前提是预收敛成功的情况下)
 */
#define TCFG_MC_DTB_STEP_LIMIT		15  //最大收敛步进值

#if TCFG_USER_BLE_ENABLE
#define TCFG_AEC_SIMPLEX			0  //通话单工模式配置
#else
#define TCFG_AEC_SIMPLEX			0  //通话单工模式配置
#endif

#define TCFG_ESCO_PLC				1	//通话丢包修复
#define TCFG_DIG_PHASE_INVERTER_EN	1  //数字反相器，用来矫正DAC的输出相位

#ifdef CONFIG_SOUNDBOX_FLASH_256K
#define TCFG_ESCO_LIMITER			0  	//通话近端限幅器
#else
#define TCFG_ESCO_LIMITER			0  	//通话近端限幅器
#endif
#define TCFG_ESCO_NOISEGATE			0  	//通话近端噪声门限

/*
 *[模拟音量]最大等级配置
 *比如配置30，则表示0~30，总共31等级
 */
#if (TCFG_AUDIO_DAC_CONNECT_MODE == DAC_OUTPUT_MONO_LR_DIFF || \
     TCFG_AUDIO_DAC_CONNECT_MODE == DAC_OUTPUT_DUAL_LR_DIFF)
#define MAX_ANA_VOL             (21)
#else
#define MAX_ANA_VOL             (30)
#endif/*TCFG_AUDIO_DAC_CONNECT_MODE*/

/*
 *[联合音量]最大等级配置
 *和联合音量等级的数组大小 (combined_vol_list)关联
 *比如配置30，则表示0~30，总共31等级
 */
#define MAX_COM_VOL             (30)

/*
 *[数字音量]最大等级配置
 *比如配置30，则表示0~30，总共31等级
 */
#define MAX_DIG_VOL             (100)

#define MAX_DIG_GR_VOL          (30)//数字音量组的最大值

#if ((SYS_VOL_TYPE == VOL_TYPE_DIGITAL) || (SYS_VOL_TYPE == VOL_TYPE_DIGITAL_HW))
#define SYS_MAX_VOL             MAX_DIG_VOL
#elif (SYS_VOL_TYPE == VOL_TYPE_ANALOG)
#define SYS_MAX_VOL             MAX_ANA_VOL
#elif (SYS_VOL_TYPE == VOL_TYPE_AD)
#define SYS_MAX_VOL             MAX_COM_VOL
#elif (SYS_VOL_TYPE == VOL_TYPE_DIGGROUP)
#define SYS_MAX_VOL             MAX_DIG_GR_VOL
#else
#error "SYS_VOL_TYPE define error"
#endif


#define SYS_DEFAULT_VOL         	0//(SYS_MAX_VOL/2)
#define SYS_DEFAULT_TONE_VOL    	10//(SYS_MAX_VOL)
#define SYS_DEFAULT_SIN_VOL     	17

#define APP_AUDIO_STATE_IDLE        0
#define APP_AUDIO_STATE_MUSIC       1
#define APP_AUDIO_STATE_CALL        2
#define APP_AUDIO_STATE_WTONE       3
#define APP_AUDIO_STATE_LINEIN      4
#define APP_AUDIO_CURRENT_STATE     5

#define APP_AUDIO_MAX_STATE    (APP_AUDIO_CURRENT_STATE + 1)


#ifdef TCFG_IIS_ENABLE

#define AUDIO_OUTPUT_ONLY_IIS \
    (TCFG_IIS_ENABLE && TCFG_IIS_OUTPUT_EN && AUDIO_OUTPUT_WAY == AUDIO_OUTPUT_WAY_IIS)
#define AUDIO_OUTPUT_DAC_AND_IIS \
    (AUDIO_OUTPUT_WAY == AUDIO_OUTPUT_WAY_DAC_IIS && TCFG_IIS_ENABLE && TCFG_IIS_OUTPUT_EN)

#else

#define AUDIO_OUTPUT_ONLY_IIS   0
#define AUDIO_OUTPUT_DAC_AND_IIS (AUDIO_OUTPUT_WAY == AUDIO_OUTPUT_WAY_DAC_IIS)

#endif

#define AUDIO_OUTPUT_INCLUDE_IIS (AUDIO_OUTPUT_ONLY_IIS || AUDIO_OUTPUT_DAC_AND_IIS)
#define AUDIO_OUTPUT_ONLY_DAC          (AUDIO_OUTPUT_WAY == AUDIO_OUTPUT_WAY_DAC)
#define AUDIO_OUTPUT_INCLUDE_DAC       ((AUDIO_OUTPUT_WAY == AUDIO_OUTPUT_WAY_DAC) \
               || (AUDIO_OUTPUT_WAY == AUDIO_OUTPUT_WAY_BT) \
               || (AUDIO_OUTPUT_WAY == AUDIO_OUTPUT_WAY_DONGLE) \
               || (AUDIO_OUTPUT_DAC_AND_IIS))

#define AUDIO_OUTPUT_INCLUDE_BT 	((defined(AUDIO_OUTPUT_WAY)) && (AUDIO_OUTPUT_WAY == AUDIO_OUTPUT_WAY_BT)) \
    						    || ((defined(AUDIO_OUT_WAY_TYPE)) && (AUDIO_OUT_WAY_TYPE & AUDIO_WAY_TYPE_BT))

#define AUDIO_OUTPUT_INCLUDE_FM 	((defined(AUDIO_OUTPUT_WAY)) && (AUDIO_OUTPUT_WAY == AUDIO_OUTPUT_WAY_FM)) \
    						    || ((defined(AUDIO_OUT_WAY_TYPE)) && (AUDIO_OUT_WAY_TYPE & AUDIO_WAY_TYPE_FM))


u8 get_max_sys_vol(void);
u8 get_tone_vol(void);

void app_audio_output_init(void);
void app_audio_output_sync_buff_init(void *sync_buff, int len);
int app_audio_output_channel_set(u8 output);
int app_audio_output_channel_get(void);
int app_audio_output_mode_set(u8 output);
int app_audio_output_mode_get(void);
int app_audio_output_write(void *buf, int len);
int app_audio_output_samplerate_select(u32 sample_rate, u8 high);
int app_audio_output_samplerate_set(int sample_rate);
int app_audio_output_samplerate_get(void);
int app_audio_output_start(void);
int app_audio_output_stop(void);
int app_audio_output_reset(u32 msecs);
int app_audio_output_state_get(void);
void app_audio_output_ch_mute(u8 ch, u8 mute);
int app_audio_output_ch_analog_gain_set(u8 ch, u8 again);
int app_audio_output_ch_digital_gain_set(u8 ch, u32 dgain);
int app_audio_output_get_cur_buf_points(void);
s8 app_audio_get_volume(u8 state);
void app_audio_set_volume(u8 state, s8 volume, u8 fade);
void app_audio_volume_up(u8 value);
void app_audio_volume_down(u8 value);
void app_audio_state_switch(u8 state, s16 max_volume);
void app_audio_mute(u8 value);
s16 app_audio_get_max_volume(void);
void app_audio_state_switch(u8 state, s16 max_volume);
void app_audio_state_exit(u8 state);
u8 app_audio_get_state(void);
void volume_up_down_direct(s8 value);
void app_audio_volume_init(void);
void app_audio_set_digital_volume(s16 volume);
void dac_trim_hook(u8 pos);
void audio_combined_vol_init(u8 cfg_en);
void audio_volume_list_init(u8 cfg_en);


void *app_audio_alloc_use_buff(int use_len);
void app_audio_release_use_buff(void *buf);

int audio_output_buf_time(void);
int audio_output_dev_is_working(void);
int audio_output_sync_start(void);
int audio_output_sync_stop(void);

void app_set_sys_vol(s16 vol_l, s16  vol_r);
void app_set_max_vol(s16 vol);

u32 phone_call_eq_open();
int eq_mode_sw();
int mic_test_start();
int mic_test_stop();

void dac_power_on(void);
void dac_power_off(void);


void audio_adda_dump(void); //打印所有的dac,adc寄存器
void audio_adda_gain_dump(void);//打印所有adc,dac的增益
#endif/*_AUDIO_CONFIG_H_*/
