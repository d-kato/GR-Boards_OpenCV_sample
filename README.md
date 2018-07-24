# GR-Boards_OpenCV_sample
GR-PEACH、および、GR-LYCHEEで動作するサンプルプログラムです。  
本サンプルはMbedオンラインコンパイラでは使用できません。  
OpenCVライブラリがGCC_ARMコンパイラにのみ対応しているため、Mbed CLI環境などでコンパイラにGCC_ARMを指定してご利用ください。  
GR-LYCHEEの開発環境については、[GR-LYCHEE用オフライン開発環境の手順](https://developer.mbed.org/users/dkato/notebook/offline-development-lychee-langja/)を参照ください。


## 概要
OpenCVを使った顔検出サンプルです。
「xml\lbpcascade_frontalface.xml」をSDカード(もしくはUSBメモリ)に保存しておきます。このファイルは顔検出に必要なモデルファイルです。  
保存したSDカードをGR-Boardに接続し、リセットボタンを押してください。  
認識結果はprintfで表示されます。


USB0にUSBケーブルを接続してPC用アプリ [DisplayApp](https://developer.mbed.org/users/dkato/code/DisplayApp/)でカメラ映像が表示できます。(認識結果はDisplay App上には表示されません)

～参考ページ～  
[がじぇっとるねさすコミュニティ GR-LYCHEE OpenCV](http://japan.renesasrulz.com/gr_user_forum_japanese/f/gr-lychee/4208/gr-lychee-opencv)
