# https://github.com/Yowkees/keyball/discussions/124
# を参考にする

# qmk msys を起動し
# qmk setup -H /t/Windows/home/qmk_firmware
# を実行してホームを変更する．

# キーマップを変更したときは，viaに保存されているキーマップを消すために
# escがあるキーを押しながら両方のキーボードを接続して，設定をリセットする．

# qmk msysを起動してこれを実行する
KeymapFolder=mykeymap
rm T:/Windows/home/qmk_firmware/keyboards/keyball/ -r
rm T:/Windows/home/qmk_firmware/.build/ -r

cd G:/マイドライブ/utils/Scripts/keyboards/keyball
cp qmk_firmware/keyboards/keyball T:/Windows/home/qmk_firmware/keyboards -r
qmk compile -j 4 -kb keyball/keyball61 -km $KeymapFolder
cp T:/Windows/home/qmk_firmware/.build/keyball_keyball61_$KeymapFolder.hex keyball61_$KeymapFolder.hex
