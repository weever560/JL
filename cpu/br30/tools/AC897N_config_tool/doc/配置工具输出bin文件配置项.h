//bin�ļ�������ݽṹ����

//���ñ���ID = 0x00, 0x0001, len = 0x3C

//key_msg, ID = 606, CFG_KEY_MSG_ID, 0x8189, len  = 0x3C = 60
typedef struct _KEY_MSG {
    u8 short_msg;     //�̰���Ϣ
    u8 long_msg;      //������Ϣ
    u8 hold_msg;      //hold ��Ϣ
    u8 up_msg;        //̧����Ϣ
    u8 double_msg;    //˫����Ϣ
    u8 triple_msg;    //������Ϣ
} KEY_MSG;

typedef struct __KEY_MSG {
    KEY_MSG key_msg[KEY_NUM];  //KEY_NUMָ��user_cfg.lua�ļ����õ�num
};


//audio, ID = 524, CFG_AUDIO_ID, 0x8301, len = 0x04
typedef struct _AUDIO_CONFIG {
    u8 sw;
    u8 max_sys_vol;         //���ϵͳ����
    u8 default_vol;         //����Ĭ������
    u8 tone_vol;            //��ʾ������, Ϊ0����ϵͳ����
} AUDIO_CFG;

//charge, ID = 535, CFG_CHARGE_ID, 0x85C1, 0x05
typedef struct __CHARGE_CONFIG {
    u8 sw;                  //����
	u8 poweron_en;          //֧�ֿ������
    u8 full_v;              //������ѹ
	u8 full_c;              //��������
	u8 charge_c;            //������
} CHARGE_CONFIG;


//��������
//mac: ID: 102, CFG_BT_MAC_ADDR, 0x4BC1, len = 0x06
typedef struct __BLUE_MAC {
    u8 mac[6];
} BLUE_MAC_CFG;


//rf_power: ID: 601, CFG_BT_RF_POWER_ID, 0x8601, len = 0x01
typedef struct __BLUE_RF_POWER {
    u8 rf_power;
} RF_POWER_CFG;

//name: ID: 101, CFG_BT_NAME, 0x4B81, len = 32 * 20 = 0x0294 = 660
typedef struct __BLUE_NAME {
    u8 name[32];
} BLUE_NAME_CFG;

//aec_cfg: ID: 604, CFG_AEC_ID, 0x8681, len = 0x14 = 20
//aec_cfg: 
typedef struct __AEC_CONFIG { 
    u8 mic_again;           //DAC����,default:3(0~14)
    u8 dac_again;           //MIC����,default:22(0~31)
    u8 aec_mode;            //AECģʽ,default:advance(diable(0), reduce(1), advance(2))
    u8 ul_eq_en;            //����EQʹ��,default:enable(disable(0), enable(1))
    /*AGC*/ 
    float fade_gain;        //�Ŵ󲽽�default: 0.9f(0.1 ~ 5 dB)
    float ndt_max_gain;     //���˽����Ŵ�����,default: 12.f(0 ~ 24 dB)
    float ndt_min_gain;     //���˽����Ŵ�����,default: 0.f(-20 ~ 24 dB)
    float ndt_speech_thr;   //���˽����Ŵ���ֵ,default: -50.f(-70 ~ -40 dB)
    float dt_max_gain;      //˫�˽����Ŵ�����,default: 12.f(0 ~ 24 dB)
    float dt_min_gain;      //˫�˽����Ŵ�����,default: 0.f(-20 ~ 24 dB)
    float dt_speech_thr;    //˫�˽����Ŵ���ֵ,default: -40.f(-70 ~ -40 dB)
    float echo_present_thr; //����˫�˽�����ֵ,default:-70.f(-70 ~ -40 dB)
    /*AEC*/ 
    float aec_dt_aggress;   //ԭ������׷�ٵȼ�, default: 1.0f(1 ~ 5)
    float aec_refengthr;    //������������ο�ֵ, default: -70.0f(-90 ~ -60 dB)
    /*ES*/ 
    float es_aggress_factor;    //����ǰ����̬ѹ��,ԽСԽǿ,default: -3.0f(-1 ~ -5)
    float es_min_suppress;      //�����󼶶�̬ѹ��,Խ��Խǿ,default: 4.f(0 ~ 10)
    /*ANS*/ 
    float ans_aggress; //����ǰ����̬ѹ��,Խ��Խǿdefault: 1.25f(1 ~ 2)
    float ans_suppress; //�����󼶶�̬ѹ��,ԽСԽǿdefault: 0.04f(0 ~ 1)
} _GNU_PACKED_ AEC_CONFIG;

//tws_pair_code: ID: 602, CFG_TWS_PAIR_CODE_ID, 0x8781, len = 0x02
typedef struct __TWS_PAIR_CODE {
    u16 tws_pair_code;
} TWS_PAIR_CODE_CFG;

//status: ID: 605, CFG_UI_TONE_STATUS_ID, 0x8701, len = 0x1D = 29
typedef struct __STATUS {
    u8 charge_start;    //��ʼ���
    u8 charge_full;     //������
    u8 power_on;        //����
    u8 power_off;       //�ػ�
    u8 lowpower;        //�͵�
    u8 max_vol;         //�������
    u8 phone_in;        //����
    u8 phone_out;       //ȥ��
    u8 phone_activ;     //ͨ����
    u8 bt_init_ok;      //������ʼ�����
    u8 bt_connect_ok;   //�������ӳɹ�
    u8 bt_disconnect;   //�����Ͽ�
    u8 tws_connect_ok;   //�������ӳɹ�
    u8 tws_disconnect;   //�����Ͽ�
} _GNU_PACKED_ STATUS;

typedef struct __STATUS_CONFIG {
    u8 status_sw;
    STATUS led;    //led status
    STATUS tone;   //tone status
} STATUS_CONFIG_CFG;



//MIC����ݷ�����Ҫ���ã�Ӱ��MIC��ƫ�õ�ѹ
//[1]:16K
//[2]:7.5K
//[3]:5.1K 
//[4]:6.8K
//[5]:4.7K
//[6]:3.5K
//[7]:2.9K
//[8]:3K
//[9]:2.5K
//[10]:2.1K
//[11]:1.9K
//[12]:2K
//[13]:1.8K
//[14]:1.6K
//[15]:1.5K
//[16]:1K
//[31]:0.6K
//MIC_TYPE, ID: 537, CFG_MIC_TYPE_ID, 0x89C1, len = 0x03
typedef struct __MIC_TYPE_SEL {
    u8 mic_capless; //MIC����ݷ���
    u8 mic_bias_res;    //MIC����ݷ�����Ҫ���ã�Ӱ��MIC��ƫ�õ�ѹ 1:16K 2:7.5K 3:5.1K 4:6.8K 5:4.7K 6:3.5K 7:2.9K  8:3K  9:2.5K 10:2.1K 11:1.9K  12:2K  13:1.8K 14:1.6K  15:1.5K 16:1K 31:0.6K
    u8 mic_ldo_vsel;//00:2.3v 01:2.5v 10:2.7v 11:3.0v
} MIC_TYPE_SEL;

//LOWPOWER_VOLTAGE, ID: 536, CFG_LOWPOWER_VOLTAGE_ID, 0x, len = 0x04
typedef struct __LOWPOWER_VOLTAGE {
    u16 tone_voltage;       //�͵����ѵ�ѹ, Ĭ��340->3.4V
    u16 power_off_voltage;  //�͵�ػ���ѹ, Ĭ��330->3.3V
} LOWPOWER_VOLTAGE;

//AUTO_OFF_TIME, ID: 603, CFG_AUTO_OFF_TIME_ID, 0x, len = 0x01
typedef struct __AUTO_OFF_TIME {
    u8 auto_off_time;  //û�������Զ��ػ�ʱ��, ��λ������, Ĭ��3����
} AUTO_OFF_TIME;

//LRC_CFG, ID: 607, CFG_LRC_ID, 0x, len = 0x09
typedef struct __LRC_CONFIG {
    u16 lrc_ws_inc;
    u16 lrc_ws_init;
    u16 btosc_ws_inc;
    u16 btosc_ws_init;
    u8 lrc_change_mode;
} _GNU_PACKED_ LRC_CONFIG;

//BLE_CFG, ID: 608, CFG_BLE_ID, 0x, len = 0x0
typedef struct __BLE_CONFIG {
    u8 ble_cfg_en;      //ble������Ч��־
    u8 ble_name[32];    //ble������
    u8 ble_rf_power;    //ble���书��
    u8 ble_addr_en;     //ble ��ַ��Ч��־
    u8 ble_addr[6];     //ble��ַ, ��ble_addr_sw = 1; ����Ч
} _GNU_PACKED_ BLE_CONFIG;

