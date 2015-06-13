Rapid Shutdown Daemon for Raspberry Pi 
======================================

ラズパイのGPIOに接続したボタンからシャットダウンを行うデーモンです。

ボタンは長押しとかではありません。押した瞬間に `shutdown -h now` します。当然キャンセルできません。

ビルドとセットアップ
--------------------

以下を実行してビルドして自動起動のデーモン __shutdownd__ を設定します。

```bash
git clone https://github.com/takamin/RapidShutdown.git
cd button-down
./init-submodules.sh
mkdir build
cd build
cmake ..
make
cd ..
./setupdatemon.sh
```

配線図
------

* この図のラズパイは Model B(R2) です。他のモデルの場合は、ピン配置が違うかもしれませんので気をつけてください。
* GPIOの25を入力ポートとして使用しています。他のポートに変更する場合は、[shutdownd.c](shutdownd.c)を直接書き換えてください。
* とりあえずブレッドボードとタクトスイッチを使っていますが、なければGPIOの25とGNDをショートさせてもシャットダウンします。
* GNDはどのGNDでもかまいません。よく見ると25番のとなりにGNDがありますね。ここに直接付けられるスイッチがあれば良いですね。

![GPIOの25番にスイッチを接続。もう一方の端子はGNDへ。](https://raw.githubusercontent.com/takamin/RapidShutdown/master/breadboard.png "ブレッドボード配線図")



その他
------

### サブモジュール

以下のサブモジュールを使用しています。

* [daemonize](https://github.com/takamin/daemonize) - Raspberry Pi デーモン化ライブラリ
* [WiringPi](https://github.com/takamin/WiringPi) - Gordon's Arduino wiring-like WiringPi Library for the Raspberry Pi (LGPLv3)


LICENSE
-------

MIT LICENSEで公開します。ただし、WiringPi は LGPLv3である事に注意してください。

```
The MIT License (MIT)

Copyright (c) 2015 Koji Takami

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
