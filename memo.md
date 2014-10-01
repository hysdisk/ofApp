ofpath
------------------
###円弧を描きたい
* arc
* setCircleResolution
* setStrokeWidth
* setStrokeColor
* setFilled
* close
* draw

#### 準備
* 円弧の解像度を設定 -> setCircleResolution
* 線を描画しない -> setStrokeWidth,setStrokeColor
* 塗りつぶさない -> setFilled

#### 描画
1. 外円を描画する -> arc(中心座標XY,直径XY,開始角度,終了角度)
2. close
3. 内円を描画する -> arc(中心座標XY,直径XY,開始角度,終了角度)
4. close
5. draw  

これで外円を内円で繰り抜いた描画になる

#### 疑問点

* 描画が遅い
* 描画レートが早くなる？とポリゴン欠けが発生する時がある。

ofMesh
------
### 描画モード
![primitives_new.gif (GIF 画像, 870x367 px)](http://www.creativeapplications.net/wp-content/uploads/2011/03/primitives_new.gif "primitives_new.gif (GIF 画像, 870x367 px)")

### 円弧を描きたい
