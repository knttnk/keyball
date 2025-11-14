# https://github.com/Yowkees/keyball/discussions/124
# を参考にする

# qmk msys を起動し
# qmk setup -H /t/Windows/home/qmk_firmware
# を実行してホームを変更する．

# キーマップを変更したときは，viaに保存されているキーマップを消すために
# escがあるキーを押しながら両方のキーボードを接続して，設定をリセットする．

# qmk msysを起動してこれを実行する
KeymapFolder=mykeymap
QmkHome="/t/Windows/home/qmk_firmware"
ThisDir="/c/Users/kenta/Syncthing/Scripts/keyboards/keyball"

# qmk firmware をダウンロード
git clone https://github.com/qmk/qmk_firmware.git --depth 1 --recurse-submodules --shallow-submodules -b 0.22.14 $QmkHome

# QMKの中にこのディレクトリへのリンクを作成
cd $QmkHome/keyboards
rm -rf keyball
ln -s $ThisDir/qmk_firmware/keyboards/keyball keyball

# ビルド
cd $QmkHome
make SKIP_GIT=yes keyball/keyball61:$KeymapFolder
