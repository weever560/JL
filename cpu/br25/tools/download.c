// *INDENT-OFF*
#include "app_config.h"

#ifdef __SHELL__

##!/bin/sh
${OBJDUMP} -D -address-mask=0x1ffffff -print-dbg $1.elf > $1.lst
${OBJCOPY} -O binary -j .text $1.elf text.bin
${OBJCOPY} -O binary -j .data $1.elf data.bin
${OBJCOPY} -O binary -j .data_code $1.elf data_code.bin

${OBJCOPY} -O binary -j .overlay_aec $1.elf aeco.bin
${OBJCOPY} -O binary -j .overlay_wav $1.elf wavo.bin
${OBJCOPY} -O binary -j .overlay_ape $1.elf apeo.bin
${OBJCOPY} -O binary -j .overlay_flac $1.elf flaco.bin
${OBJCOPY} -O binary -j .overlay_m4a $1.elf m4ao.bin
${OBJCOPY} -O binary -j .overlay_amr $1.elf amro.bin
${OBJCOPY} -O binary -j .overlay_dts $1.elf dtso.bin
${OBJCOPY} -O binary -j .overlay_fm $1.elf fmo.bin
${OBJCOPY} -O binary -j .overlay_mp3 $1.elf mp3o.bin
${OBJCOPY} -O binary -j .overlay_wma $1.elf wmao.bin



/opt/utils/remove_tailing_zeros -i aeco.bin -o aec.bin -mark ff
/opt/utils/remove_tailing_zeros -i wavo.bin -o wav.bin -mark ff
/opt/utils/remove_tailing_zeros -i apeo.bin -o ape.bin -mark ff
/opt/utils/remove_tailing_zeros -i flaco.bin -o flac.bin -mark ff
/opt/utils/remove_tailing_zeros -i m4ao.bin -o m4a.bin -mark ff
/opt/utils/remove_tailing_zeros -i amro.bin -o amr.bin -mark ff
/opt/utils/remove_tailing_zeros -i dtso.bin -o dts.bin -mark ff
/opt/utils/remove_tailing_zeros -i fmo.bin -o fm.bin -mark ff
/opt/utils/remove_tailing_zeros -i mp3o.bin -o mp3.bin -mark ff
/opt/utils/remove_tailing_zeros -i wmao.bin -o wma.bin -mark ff


bank_files=
for i in $(seq 0 20)
do
    ${OBJCOPY} -O binary -j .overlay_bank$i $1.elf bank$i.bin
    if [ ! -s bank$i.bin ]
    then
        break
    fi
    bank_files=$bank_files"bank$i.bin 0x0 "
done
echo $bank_files


${OBJDUMP} -section-headers -address-mask=0x1ffffff $1.elf
${OBJSIZEDUMP} -lite -skip-zero -enable-dbg-info $1.elf | sort -k 1 >  symbol_tbl.txt

cat text.bin data.bin data_code.bin \
	aec.bin \
	wav.bin \
	ape.bin \
	flac.bin \
	m4a.bin \
	amr.bin \
	dts.bin \
	fm.bin \
	mp3.bin \
	wma.bin \
	bank.bin \
	> app.bin

/opt/utils/strip-ini -i isd_config.ini -o isd_config.ini

files="app.bin ${CPU}loader.* uboot* ota*.bin isd_config.ini isd_download.exe fw_add.exe ufw_maker.exe"

host-client -project ${NICKNAME}$2 -f ${files} $1.elf

#else


rem @echo off

@echo *****************************************************************
@echo 			SDK BR25
@echo *****************************************************************
@echo %date%

cd %~dp0


set OBJDUMP=C:\JL\pi32\bin\llvm-objdump.exe
set OBJCOPY=C:\JL\pi32\bin\llvm-objcopy.exe
set ELFFILE=sdk.elf

REM %OBJDUMP% -D -address-mask=0x1ffffff -print-dbg $1.elf > $1.lst
%OBJCOPY% -O binary -j .text %ELFFILE% text.bin
%OBJCOPY% -O binary -j .data %ELFFILE% data.bin
%OBJCOPY% -O binary -j .data_code %ELFFILE% data_code.bin


%OBJCOPY% -O binary -j .overlay_aec %ELFFILE% aeco.bin
%OBJCOPY% -O binary -j .overlay_wav %ELFFILE% wavo.bin
%OBJCOPY% -O binary -j .overlay_ape %ELFFILE% apeo.bin
%OBJCOPY% -O binary -j .overlay_flac %ELFFILE% flaco.bin
%OBJCOPY% -O binary -j .overlay_m4a %ELFFILE% m4ao.bin
%OBJCOPY% -O binary -j .overlay_amr %ELFFILE% amro.bin
%OBJCOPY% -O binary -j .overlay_dts %ELFFILE% dtso.bin
%OBJCOPY% -O binary -j .overlay_fm %ELFFILE% fmo.bin
%OBJCOPY% -O binary -j .overlay_mp3 %ELFFILE% mp3o.bin
%OBJCOPY% -O binary -j .overlay_wma %ELFFILE% wmao.bin


remove_tailing_zeros -i aeco.bin -o aec.bin -mark ff
remove_tailing_zeros -i wavo.bin -o wav.bin -mark ff
remove_tailing_zeros -i apeo.bin -o ape.bin -mark ff
remove_tailing_zeros -i flaco.bin -o flac.bin -mark ff
remove_tailing_zeros -i m4ao.bin -o m4a.bin -mark ff
remove_tailing_zeros -i amro.bin -o amr.bin -mark ff
remove_tailing_zeros -i dtso.bin -o dts.bin -mark ff
remove_tailing_zeros -i fmo.bin -o fm.bin -mark ff
remove_tailing_zeros -i mp3o.bin -o mp3.bin -mark ff
remove_tailing_zeros -i wmao.bin -o wma.bin -mark ff

bankfiles=
for /L %%i in (0,1,20) do (
 %OBJCOPY% -O binary -j .overlay_bank%%i %INELF% bank%%i.bin
 set bankfiles=!bankfiles! bank%%i.bin 0x0
)

echo %bank_files
%LZ4_PACKET% -dict text.bin -input common.bin 0 %bankfiles% -o bank.bin

%OBJDUMP% -section-headers -address-mask=0x1ffffff %ELFFILE%
%OBJDUMP% -t %ELFFILE% >  symbol_tbl.txt

copy /b text.bin+data.bin+data_code.bin+aec.bin+wav.bin+ape.bin+flac.bin+m4a.bin+amr.bin+dts.bin+fm.bin+mp3.bin+wma.bin+bank.bin app.bin

#ifdef CONFIG_WATCH_CASE_ENABLE
call download/watch/download.bat
#elif defined(CONFIG_SOUNDBOX_CASE_ENABLE)
#if (CONFIG_APP_BT_ENABLE == 0)
call download/soundbox/download.bat
#else
call download/soundbox/download_app_ota.bat
#endif //APP_BT_ENABLE
#elif defined(CONFIG_EARPHONE_CASE_ENABLE)
call download/earphone/download.bat
#elif defined(CONFIG_HID_CASE_ENABLE) ||defined(CONFIG_SPP_AND_LE_CASE_ENABLE)||defined(CONFIG_MESH_CASE_ENABLE)||defined(CONFIG_DONGLE_CASE_ENABLE)    //数传
call download/data_trans/download.bat
#else
//to do other case
#endif  //endif app_case

#endif

