@echo off

cd %~dp0

rem copy ..\..\uboot.boot .
rem copy ..\..\ota.bin .
rem copy ..\..\ota_all.bin .
rem copy ..\..\ota_nor.bin .

copy ..\..\script.ver .
copy ..\..\tone.cfg .
copy ..\..\br23loader.bin .
copy ..\..\user_api.bin .

cd ..\..\ui_resource
copy *.* ..\download\watch

cd %~dp0

cd ..\..\ui_upgrade
copy *.* ..\download\watch\ui_upgrade
cd %~dp0


..\..\json_to_res.exe json.txt
..\..\md5sum.exe app.bin md5.bin
set /p "themd5=" < "md5.bin"


..\..\packres.exe -keep-suffix-case JL.sty JL.res JL.str -n res -o JL
..\..\packres.exe -keep-suffix-case sidebar.sty sidebar.res sidebar.str sidebar.tab -n res -o sidebar
..\..\packres.exe -keep-suffix-case watch.sty watch.res watch.str watch.view watch.json watch.anim watch.tab -n res -o watch
..\..\packres.exe -keep-suffix-case watch1.sty watch1.res watch1.str watch1.view watch1.json -n res -o watch1
..\..\packres.exe -keep-suffix-case watch2.sty watch2.res watch2.str watch2.view watch2.json -n res -o watch2
..\..\packres.exe -keep-suffix-case watch3.sty watch3.res watch3.str watch3.view watch3.json -n res -o watch3
..\..\packres.exe -keep-suffix-case watch4.sty watch4.res watch4.str watch4.view watch4.json -n res -o watch4
..\..\packres.exe -keep-suffix-case watch5.sty watch5.res watch5.str watch5.view watch5.json -n res -o watch5
..\..\packres.exe -keep-suffix-case F_ASCII.PIX F_GB2312.PIX F_GB2312.TAB ascii.res -n res -o font



..\..\fat_comm.exe -pad-backup -out new_res.bin -image-size 10 -filelist JL sidebar watch watch1 watch2 watch3 watch4 watch5 font -remove-empty -remove-bpb
del /Q res.ori\*
del upgrade.zip
move JL res.ori\JL
move watch? res.ori\
move font res.ori\font
::fat_comm.exe -out new_res.bin -image-size 10 -filelist uires -remove-empty -remove-bpb

..\..\packres.exe -n res -o res.bin new_res.bin 0 -normal

..\..\isd_download.exe ..\..\isd_config.ini -tonorflash -dev br23 -boot 0x12000 -div8 -wait 300 -uboot ..\..\uboot.boot -app ..\..\app.bin ..\..\cfg_tool.bin -res tone.cfg ui_upgrade config.dat md5.bin -ex_flash res.bin -ex_api_bin user_api.bin


:: ui_upgrade  : ����flash ��������
:: config.dat : app apk ͼƬ
:: md5.bin  :  ������������Ҫ
:: user_api.bin   :  uboot ��������
:: res.bin   : ui ��Դ

::ex_flash : ���ص����flash

:: -format all
::-reboot 2500

  

@rem ɾ����ʱ�ļ�-format all
if exist *.mp3 del *.mp3 
if exist *.PIX del *.PIX
if exist *.TAB del *.TAB
if exist *.res del *.res
if exist *.sty del *.sty
if exist *.str del *.str
if exist *.view del *.view
if exist *.json del *.json

@rem add ver to jl_isd.fw
@rem generate upgrade file
..\..\fw_add.exe -noenc -fw jl_isd.fw  -add ..\..\ota_all.bin -name ota.bin -type 100 -out jl_isd_all.fw
..\..\fw_add.exe -noenc -fw jl_isd.fw  -add ..\..\ota_nor.bin -name ota.bin -type 100 -out jl_isd_nor.fw
@rem add ver to jl_isd.fw
..\..\fw_add.exe -noenc -fw jl_isd_all.fw -add script.ver -out jl_isd_all.fw
..\..\fw_add.exe -noenc -fw jl_isd_nor.fw -add script.ver -out jl_isd_nor.fw

..\..\ufw_maker.exe -fw_to_ufw jl_isd_all.fw
..\..\ufw_maker.exe -fw_to_ufw jl_isd_nor.fw

copy jl_isd_all.ufw update_%themd5%.ufw
copy jl_isd_nor.ufw nor_update.ufw
copy jl_isd_all.fw jl_isd.fw
del jl_isd_all.ufw jl_isd_nor.ufw jl_isd_all.fw jl_isd_nor.fw

..\..\zip.exe -r upgrade.zip res.ori update_%themd5%.ufw

@REM ���������ļ������ļ�
::ufw_maker.exe -chip AC800X %ADD_KEY% -output config.ufw -res bt_cfg.cfg

::IF EXIST jl_695x.bin del jl_695x.bin 


@rem ��������˵��
@rem -format vm        //����VM ����
@rem -format cfg       //����BT CFG ����
@rem -format 0x3f0-2   //��ʾ�ӵ� 0x3f0 �� sector ��ʼ�������� 2 �� sector(��һ������Ϊ16���ƻ�10���ƶ��ɣ��ڶ�������������10����)

ping /n 2 127.1>null
IF EXIST null del null
