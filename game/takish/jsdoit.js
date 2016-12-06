// forked from takish's "迷路：加速度テスト" http://jsdo.it/takish/4zHQ
// forked from takish's "迷路：pushscene test" http://jsdo.it/takish/6GGS
// forked from takish's "forked: 迷路2" http://jsdo.it/takish/9y4w
// forked from takish's "迷路2" http://jsdo.it/takish/8YY0
// forked from takish's "迷路" http://jsdo.it/takish/7n2c
// forked from takish's "forked: Avatar" http://jsdo.it/takish/aTkS

enchant();

var mode = 0;
var DEBUG = true;

window.onload=function(){
	core = new Game(320,480);
    core.rootScene.backgroundColor="#000";
    
    ////////////////////////
　// 画像リソース
    IMAGE_STATUS = 'http://jsrun.it/assets/9/S/h/3/9Sh3E.png';
    IMAGE_MAP = 'http://enchantjs.com/images/materials/map1.png';
    IMAGE_MONSTER =  'http://jsrun.it/assets/z/m/Y/v/zmYvB.gif';
    IMG_LOGO = 'http://jsrun.it/assets/n/7/3/3/n733S.png';
    IMG_CLEAR = 'http://enchantjs.com/images/materials/clear.png';
    
    core.preload(IMAGE_MAP, IMAGE_STATUS, IMAGE_MONSTER,IMG_CLEAR);
    

    ////////////////////////
    // 各種定数
    var TIP = 16;
    var CHARA_HEIGHT = 48;
    var CHARA_WIDTH = 32;

    var HEIGHT = 480;
    var WIDTH = 320;
    core.time = 0;
    
    var HP = 40;
    var MAX_HP = 40;
    var MP = 20;
    var MAX_MP = 20;
    
    var ENEMY_NUM = 0;
    var STAGE_NUM = 0;
    var MAX_STAGE = 1;
    ////////////////////////
    
    
    // プロトタイプの作成
    function Player() {
    }
    
    Player.prototype.name = "";
    Player.prototype.maxHp = MAX_HP;
    Player.prototype.maxMp = MAX_MP;
    Player.prototype.hp = HP;
    Player.prototype.mp = MP;
    
    core.onload=function(){

    var backgroundMap = new Map(TIP, TIP);
    backgroundMap.image = core.assets[IMAGE_MAP];

    backgroundMap.loadData([
    [7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7],
    [7,21,21,7,21,21,21,21,21,7,21,21,21,21,21,21,21,21,21,7],
    [7,21,21,7,21,21,21,21,21,7,21,21,21,21,21,21,21,21,21,7],
    [7,21,21,7,21,21,7,21,21,7,21,21,7,7,7,7,7,21,21,7],
    [7,21,21,7,21,21,7,21,21,7,21,21,7,21,21,21,21,21,21,7],
    [7,21,21,7,21,21,7,21,21,7,21,21,7,21,21,21,21,21,21,7],
    [7,21,21,7,21,21,7,21,21,7,21,21,7,21,21,7,7,7,7,7],
    [7,21,21,21,21,21,7,21,21,7,21,21,7,21,21,21,21,21,21,7],
    [7,21,21,21,21,21,7,21,21,7,21,21,7,21,21,21,21,21,21,7],
    [7,7,7,7,7,7,7,21,21,7,21,21,7,7,7,7,7,21,21,7],
    [7,21,21,21,21,21,21,21,21,7,21,21,7,21,21,21,21,21,21,7],
    [7,21,21,21,21,21,21,21,21,7,21,21,7,21,21,21,21,21,21,7],
    [7,21,21,7,7,7,7,7,7,7,21,21,7,21,21,7,7,7,7,7],
    [7,21,21,21,21,21,21,21,21,21,21,21,7,21,21,21,21,21,21,7],
    [7,21,21,21,21,21,21,21,21,21,21,21,7,21,21,21,21,21,21,7],
    [7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,21,21,7],
    [7,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,7],
    [7,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,7],
    [7,21,21,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7],
    [7,21,21,7,21,21,21,21,21,7,21,21,21,21,21,7,21,21,21,7],
    [7,21,21,7,21,21,21,21,21,7,21,21,21,21,21,7,21,21,21,7],
    [7,21,21,7,21,21,7,21,21,7,21,21,7,21,21,7,21,21,21,7],
    [7,21,21,21,21,21,7,21,21,21,21,21,7,21,21,21,21,21,21,7],
    [7,21,21,21,21,21,7,21,21,21,21,21,7,21,21,21,21,21,21,7],
    [7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7]
],[
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,28,28,28,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,28,29,28,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,28,28,28,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1]
]);
backgroundMap.collisionData = [
    [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
    [1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,1,0,0,1,0,0,1,0,0,1,1,1,1,1,0,0,1],
    [1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,1],
    [1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,1],
    [1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,1,1,1,1],
    [1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,1],
    [1,1,1,1,1,1,1,0,0,1,0,0,1,1,1,1,1,0,0,1],
    [1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1],
    [1,0,0,1,1,1,1,1,1,1,0,0,1,0,0,1,1,1,1,1],
    [1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1],
    [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
    [1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1],
    [1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1],
    [1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,1],
    [1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1],
    [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]
];
        
        core.rootScene.addChild(backgroundMap);

        // ガイド線を引く（開発用）
        core.createGrid = function () {

            sprite = new Sprite(WIDTH, HEIGHT);        
            surface = new Surface(WIDTH, HEIGHT);
        
            //spriteのimageにsurfaceを代入します
            sprite.image = surface;
        
            //コンテキストを取得します
            context = surface.context;
        
            //以下、HTML5のcanvasと同じように使えます
            context.beginPath();       //パスを開始
        
            //赤い線に
            //context.strokeStyle = 'rgb(192, 80, 77)'; 
            context.strokeStyle = 'rgb(2, 120, 0)'; 
            sprite.opacity = 0.2;
        
            for (i=0; i< WIDTH; i+=16) {
                    context.moveTo(i,0);	//ペンを(50,50)に移動
                    context.lineTo(i,HEIGHT);//(100,100)まで直線を描く
                    context.closePath();	//パスを終了
                    context.stroke();		//パスを描画する      
            }
            
            for (j=0; j < HEIGHT; j+= 16) {
                    context.moveTo(0,j);	//ペンを(50,50)に移動
                    context.lineTo(WIDTH,j);//(100,100)まで直線を描く
                    context.closePath();	//パスを終了
                    context.stroke();		//パスを描画する
            }
        
            return sprite;
        };
 
        
        if (DEBUG) {
            //シーンにサーフェスを追加する
            core.rootScene.addChild(core.createGrid()); 
        }

        // ステータスエリアの表示

        core.createStatus = function (){
            var sprite = new Sprite(WIDTH, 80);        
            var surface = new Surface(WIDTH, 80);
            
            // canvas 描画
            surface.draw(core.assets[IMAGE_STATUS], 0, 0);
            sprite.image = surface; // サーフェスを画像としてセット
             //シーンにサーフェスを追加する
             sprite.y = 400;

            return sprite;
        };
        
        core.rootScene.addChild(core.createStatus()); 
        

        
         if (DEBUG) { 
            // 足あと用エリアの追加
            var ashi_area = new Sprite(WIDTH, HEIGHT);
            var ashi_surf = new Surface(WIDTH, HEIGHT);
            // context.drawImage(image, sx, sy, sw, sh, dx, dy, dw, dh)
            // imageの(sx,sy)地点からsw分の幅,sh分の高さの画像を(dx,dy）地点のdw幅,dh高さの領域へコピー。
           // ashi_surf.draw(core.assets[IMAGE_STATUS], 0, 84, 16, 16, 0, 0, 16, 16);
             ashi_area.image = ashi_surf; 
            core.rootScene.addChild(ashi_area);
        }
        
        // バーチャルパッドはmode 1以上
        if (mode >= 1) {
            var pad = new Pad();
            pad.x = 0;
            pad.y = 380;
            core.rootScene.addChild(pad);
        }
        
        ///////////////////////////
        // グローバルラベル表記
        // 
        ////////////////////
        // ステータスラベル
        var lvLabel = new Label('1');
        lvLabel.font = "18px 'Consolas', 'Monaco', 'ＭＳ ゴシック'";

        lvLabel.x = 40;
        lvLabel.y = 430;
        lvLabel.color = '#FFF';
        core.rootScene.addChild(lvLabel);

        var hpLabel = new Label(HP);
        hpLabel.font = "18px 'Consolas', 'Monaco', 'ＭＳ ゴシック'";
        hpLabel.x = 40;
        hpLabel.y = 446;
        hpLabel.color = '#FFF';
        core.rootScene.addChild(hpLabel);
        
        var mpLabel = new Label(MP);
        mpLabel.font = "18px 'Consolas', 'Monaco', 'ＭＳ ゴシック'";
        mpLabel.x = 40;
        mpLabel.y = 463;
        mpLabel.color = '#FFF';
        core.rootScene.addChild(mpLabel);

        ///////////////////////////
        // デバッグ用ラベルの追加
        var debug = new Label('');
        debug.font = "12px 'Consolas', 'Monaco', 'ＭＳ ゴシック'";

        debug.x = 20;
        debug.y = 320;
        core.rootScene.addChild(debug);
        
         var posLabel = new Label('');
         posLabel.font = "12px 'Consolas', 'Monaco', 'ＭＳ ゴシック'";

          posLabel.x = 20;
          posLabel.y = 250;
          core.rootScene.addChild(posLabel);
        
        if (DEBUG) { 
            // 足あと用エリアの追加
            var area = new Sprite(WIDTH, HEIGHT);
            var surf = new Surface(WIDTH, HEIGHT);
            
            core.rootScene.addChild(area);
        }
               
		chara = new Avatar("1:10:3:2062:21554:22460");
		core.rootScene.addChild(chara);
		chara.scaleX=-1;
		chara.scaleY=1;
		chara.x=5;
		chara.y=5;
        
        ///////////////////////////////////////////////
        // 汎用関数
        function rand(num)
        {
            return Math.floor(Math.random()*num);
        }
        
        // ダメージカラー
        isDamageColor = function(myHP, maxHP) {
           var color = null;
          
          if (myHP <= maxHP/8) {
              color = '#ff6600';
          } else if (myHP <= maxHP/4) {
              color = '#ff9900';
          }
           return color;
       };
        
        var dx = 16;
        var dy = 5;
        var tick = 1;
        
        ////////////////////////////////////////////////////
        // ルートイベントハンドラ
        //
        
        ///////////////////////
        //タッチ開始時に呼ばれる
        core.rootScene.addEventListener(Event.TOUCH_START, function(e){
            // バトルデバッグ用
            // core.pushScene(createEnemyScene());
            chara.action = "attack";
            if(!(backgroundMap.hitTest(chara.x + 32, chara.y + 48))){
                chara.toX = e.x - TIP;
                chara.toY = e.y - TIP;
             }
             debug.text = "x:" + chara.x +  " y:" +chara.y + " bx:" + backgroundMap.x + " by:" + backgroundMap.y + " toX:" + chara.toX + " toY:" + chara.toY;
        });
          
        ///////////////////////        
        //タッチ移動時に呼ばれる
        core.rootScene.addEventListener(Event.TOUCH_MOVE, function(e){
            chara.toX = e.x - TIP;
            chara.toY = e.y - TIP;
        });

        ///////////////////////
        // 加速度センサー
        // デバイスモーションイベントリスナを登録
        window.addEventListener("devicemotion", function(e) {
            if (!chara) return ;
                var ag = e.accelerationIncludingGravity;
                dx =  ag.x;
                dy = -ag.y;
                debug.text = dx;
            });
       

       ///////////////////////       
       // フレーム処理
       chara.addEventListener('enterframe', function(e) {
           core.time = timeLabel.time;

           hpLabel.text = HP;
           hpLabel.color = isDamageColor(HP, MAX_HP);
           if (hpLabel.color === null) hpLabel.color = '#fff';
           mpLabel.text = MP;
           
           if(tick % 50 === 0) {
               if ((rand(100) > 60) && (tick > 100)) {
                core.pushScene(createEnemyScene());
                tick = 0;
               }
            }

           // 加速度移動モード
           if (mode === 0) {
               chara.x += dx;
               chara.y += dy;
           
               // x > 0 の時右、 x < 0 の時左
               if(dx > 0) {
                   if(backgroundMap.hitTest(chara.x + CHARA_WIDTH + 8 , chara.y + CHARA_HEIGHT)) {
                   chara.right();
                   chara.x -= dx; tick++;
                   }
               } else {
                   chara.left();
                   if (backgroundMap.hitTest(chara.x + CHARA_WIDTH - 8, chara.y + CHARA_HEIGHT)){
                       chara.x -= dx; tick++;
                   }
              }
          
                // y > 0 の時上、 y < 0 の時下
                if(dy > 0) {
                    if(backgroundMap.hitTest(chara.x + CHARA_WIDTH, chara.y + CHARA_HEIGHT + 8)) {
                       chara.y -= dy; tick++;
                   }
               } else if (backgroundMap.hitTest(chara.x + CHARA_WIDTH, chara.y + CHARA_HEIGHT - 8)){
                   chara.y -= dy; tick++;
               }
           }

           if (mode >= 2) {
            if (core.input.left) {
                chara.action = "run";
                chara.left();
                chara.x -= 8;
                debug.text = "x:" + chara.x +  " y:" +chara.y + " bx:" + backgroundMap.x + " by:" + backgroundMap.y;
                    if(backgroundMap.hitTest(chara.x + CHARA_WIDTH, chara.y + CHARA_HEIGHT)) chara.x += 16;
            }
           
			if (core.input.right){ 
                chara.action = "run";
                chara.right();
                chara.x += 8;
                                debug.text = "x:" + chara.x +  " y:" +chara.y + " bx:" + backgroundMap.x + " by:" + backgroundMap.y;
                if(chara.x > 320) {
                    backgroundMap.x -= 320;
                }

                if(backgroundMap.hitTest(chara.x + CHARA_WIDTH, chara.y + CHARA_HEIGHT)) chara.x -= 16;

            }
           
			if (core.input.up) {
                chara.action = "run";
                                debug.text = "x:" + chara.x +  " y:" +chara.y + " bx:" + backgroundMap.x + " by:" + backgroundMap.y;
                chara.y -= 5;
                                if(backgroundMap.hitTest(chara.x + CHARA_WIDTH, chara.y + CHARA_HEIGHT)) chara.y += 5;
            }
           
			if (core.input.down){ 
                chara.action = "run";
                                debug.text = "x:" + chara.x +  " y:" +chara.y + " bx:" + backgroundMap.x + " by:" + backgroundMap.y;
                chara.y += 5;
                                if(backgroundMap.hitTest(chara.x + CHARA_WIDTH, chara.y + CHARA_HEIGHT)) chara.y -= 5;
            }
        
            //上へ移動
            if (chara.y > chara.toY) {
                chara.action = "run";
                if (Math.abs(chara.y - chara.toY) < 3) {
                    chara.y=chara.toY - 8; // offset
                } else {
                    chara.y -= 3;
                }                
                  if(backgroundMap.hitTest(chara.x + CHARA_WIDTH, chara.y + CHARA_HEIGHT)) chara.y += 5;
            }
            //下へ移動
            else if (chara.y < chara.toY) {
                chara.action = "run";
                if (Math.abs(chara.y - chara.toY) < 3) {
                    chara.y = chara.toY;
                } else {
                    chara.y += 3;
                }
                 if(backgroundMap.hitTest(chara.x + CHARA_WIDTH, chara.y + CHARA_HEIGHT)) chara.y -= 5;
            } 
            //左へ移動
            if (chara.x > chara.toX) {
                chara.action = "run";
                chara.left();
                if (Math.abs(chara.x - chara.toX) < 3) {
                    chara.x = chara.toX;
                } else {
                    chara.x -= 3;
                }                
                 if(backgroundMap.hitTest(chara.x + CHARA_WIDTH, chara.y + CHARA_HEIGHT)) chara.x += 5;
            }
            //右へ移動
            else if (chara.x < chara.toX) {
                chara.action = "run";
                chara.right();
                if (Math.abs(chara.x- chara.toX) < 3) {
                    chara.x = chara.toX;
                } else {
                    chara.x += 3;
                }
                   if(backgroundMap.hitTest(chara.x + CHARA_WIDTH, chara.y + CHARA_HEIGHT)) chara.x -= 5;
            } 
            if (chara.x == chara.toX && chara.y == chara.toY) chara.action = "stop";
               
           }
           
           // ゴール地点
           var markX = Math.floor((chara.x + CHARA_WIDTH)/ TIP);
           var markY = Math.floor((chara.y + CHARA_HEIGHT)/ TIP);

    //       if ((chara.x >= TIP && chara.x < 2 * TIP) && (chara.y >= 8*TIP && chara.y < 9* TIP))  {
           if ((chara.x >= (17*TIP - CHARA_WIDTH) && chara.x < (18 * TIP - CHARA_WIDTH)) && (chara.y >= (20*TIP - CHARA_HEIGHT) && chara.y < (21* TIP - CHARA_HEIGHT)))  {                         
               posLabel.text = '[[[HIT!]]] x:' + chara.x + ' y:' + chara.y;

               core.pushScene(createClearScene());

       //        core.pushScene(core.field(chara.x, chara.y, core.createMap()));
              // core.end('');
           } else {
               posLabel.text = ' x:' + chara.x + ' y:' + chara.y + '<br>' + ' x: ' + markX + ' y:' + markY;
           }

        
        // 当たり判定チェック
        if (DEBUG){
            surf.context.beginPath();
            surf.context.fillStyle = 'rgba(0, 0, 255, 0.1)';
            surf.context.fillRect(markX * TIP, markY * TIP, markX + 8, markY + 8);
            ashi_surf.draw(core.assets[IMAGE_STATUS], 0, 84, 16, 16, markX * TIP, markY * TIP, 16, 16);
                        // context.drawImage(image, sx, sy, sw, sh, dx, dy, dw, dh)
            // imageの(sx,sy)地点からsw分の幅,sh分の高さの画像を(dx,dy）地点のdw幅,dh高さの領域へコピー。
           // ashi_surf.draw(core.assets[IMAGE_MAP], 4*16, 5*16, 16, 16, markX * TIP, markY * TIP, 16, 16);
           ashi_surf.draw(core.assets[IMAGE_MAP], 12*16, 0*16, 16, 16, 15 * TIP, 2*TIP, 16, 16 );
            area.image = surf;
          //  core.rootScene.addChild(area);

        }
           
        });
        
        // マップ生成
        core.createMap = function () {
            var map = new Map(TIP, TIP);
            
            map.image = core.assets['http://enchantjs.com/images/materials/map1.png'];
            map.loadData([
                [7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7],
                [7,36,36,36,36,36,36,36,36,36,7,36,36,36,36,36,36,36,36,7],
                [7,36,36,36,36,36,36,36,36,36,7,36,36,36,36,36,36,36,36,7],
                [7,7,7,7,7,7,7,7,36,36,7,36,36,7,7,7,7,36,36,7],
                [7,36,36,36,36,36,36,36,36,36,7,36,36,7,36,36,36,36,36,7],
                [7,36,36,36,36,36,36,36,36,36,7,36,36,7,36,36,36,36,36,7],
                [7,36,36,7,7,7,7,7,7,7,7,36,36,7,36,36,7,7,7,7],
                [7,36,36,36,36,36,36,36,36,36,36,36,36,7,36,36,36,36,36,7],
                [7,36,36,36,36,36,36,36,36,36,36,36,36,7,36,36,36,36,36,7],
                [7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,36,36,7],
                [7,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,7],
                [7,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,7],
                [7,36,36,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7],
                [7,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,7],
                [7,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,7],
                [7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,36,36,7],
                [7,36,36,36,36,36,36,36,7,36,36,36,36,36,36,36,7,36,36,7],
                [7,36,36,7,7,7,36,36,7,36,36,36,36,36,36,36,7,36,36,7],
                [7,36,36,36,36,7,36,36,7,36,36,7,7,7,36,36,7,36,36,7],
                [7,7,7,36,36,7,36,36,7,36,36,36,36,7,36,36,7,36,36,7],
                [7,36,36,36,36,7,36,36,7,36,36,36,36,7,36,36,7,36,36,7],
                [7,36,36,36,36,7,36,36,7,7,7,36,36,7,36,36,7,36,36,7],
                [7,36,36,36,36,7,36,36,36,36,36,36,36,7,36,36,36,36,36,7],
                [7,36,36,36,36,7,36,36,36,36,36,36,36,7,36,36,36,36,36,7],
                [7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7]
        ],[
                [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,27,27,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,27,27,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1],
    [-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1]
]);
map.collisionData = [
    [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
    [1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1],
    [1,1,1,1,1,1,1,1,0,0,1,0,0,1,1,1,1,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1],
    [1,0,0,1,1,1,1,1,1,1,1,0,0,1,0,0,1,1,1,1],
    [1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1],
    [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
    [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
    [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1],
    [1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1],
    [1,0,0,1,1,1,0,0,1,0,0,0,0,0,0,0,1,0,0,1],
    [1,0,0,0,0,1,0,0,1,0,0,1,1,1,0,0,1,0,0,1],
    [1,1,1,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,1],
    [1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,1],
    [1,0,0,0,0,1,0,0,1,1,1,0,0,1,0,0,1,0,0,1],
    [1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1],
    [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]
];
            return map;
    };
        
        // フィールド作成用関数
        // プレイヤー座標とマップを食わせる
        core.field = function(px, py, map) {
            var scene = new Scene();  
            
            scene.addChild(map);
            
            var chara = new Avatar("1:10:3:2062:21554:22460");
            
            scene.addChild(chara);
            
            scene.addEventListener('enterframe', function(e) {
                // なんかあれば
            });
            
            return scene;
        };
        
        var timeLabel = new TimeLabel(70, 20);
        timeLabel.time = core.time;
        timeLabel.scale(1.8);

        core.rootScene.addChild(timeLabel);
        
        ////////////////////////////////////////////
        // ここからシーン 
        //
        //
        
        /////////////////////////
        // 
        // ステージクリアシーン
        // 
        createClearScene = function() {
            var scene = new Scene();  
            STAGE_NUM++;
            
            var label = new Label('ステージクリア！');
            label.font = "32px 'Consolas', 'Monaco', 'ＭＳ ゴシック'";
            label.x = 20;
            label.y = 180;
            scene.addChild(label);
            label.tl.fadeIn(10).rotateBy(720, 10);

            var subLabel = new Label('');
            subLabel.font = "20px 'Consolas', 'Monaco', 'ＭＳ ゴシック'";
            subLabel.x = 20;
            subLabel.y = 220;
            if (STAGE_NUM == MAX_STAGE) {
                subLabel.text = 'ステージクリアおめでとう！<br>クリア時間：' + core.time + '秒<br>倒したモンスター：' + ENEMY_NUM + '匹'; 
                gameClear = new Sprite(267, 48);
                gameClear.image = core.assets[IMG_CLEAR];
                gameClear.x = 30;
                gameClear.y = 68;
                scene.addChild(gameClear);
            } else {
            subLabel.text = 'ステージクリアおめでとう！' + '<br>' + 'タップしたらつぎのステージへいくよ！'  + '<br>' + 'クリア時間：' + core.time + '秒';
           subLabel.tl.delay(30).fadeIn(30);
            }
                       //タッチ開始時に呼ばれる
            scene.addEventListener(Event.TOUCH_START, function(e){
                            if (STAGE_NUM == MAX_STAGE) { 
                                core.end();
                            } else {
                          core.pushScene(core.field(chara.x, chara.y, core.createMap()));
                            }
                                
            });
                            scene.addChild(subLabel);
          
            scene.backgroundColor = 'rgba(255, 255, 255, 0.7)';

            return scene;
        };
        
 
        /////////////////////////
        // 
        // バトルシーン
        // 
        createEnemyScene = function() {
            var scene = new Scene();  
            scene.backgroundColor = 'rgba(255, 255, 255, 0.7)';
            
            var chara = new Avatar("1:10:3:2062:21554:22460");
            chara.x = 40;
            chara.y = 180;
            chara.scaleX=-2;
            chara.scaleY=2;
            scene.addChild(chara);
            
            var monster = new AvatarMonster(core.assets[IMAGE_MONSTER]);
            monster.x=200;
            monster.y=160;
            monster.scaleX=1.5;
            monster.scaleY=1.5;
            scene.addChild(monster);
            
            var label = new Label('敵があらわれた！！');
            label.font = "32px 'Consolas', 'Monaco', 'ＭＳ ゴシック'";
            label.x = 20;
            label.y = 20;
            scene.addChild(label);
            label.tl.fadeIn(10).rotateBy(720, 10);

            var subLabel = new Label('');
            subLabel.font = "16px 'Consolas', 'Monaco', 'ＭＳ ゴシック'";
            subLabel.x = 20;
            subLabel.y = 80;
            subLabel.text = '画面タップしてダメージを与えろ！';
            subLabel.tl.delay(30).fadeIn(30);

            scene.addChild(subLabel);
            
            var damageLabel = new Label('');
            damageLabel.font = "40px 'Consolas', 'Monaco', 'ＭＳ ゴシック'";
            damageLabel.x = 40;
            damageLabel.y = 270;

            scene.addChild(damageLabel);
            
            var hpBtLabel = new Label('');
            hpBtLabel.font = "40px 'Consolas', 'Monaco', 'ＭＳ ゴシック'";
            hpBtLabel.x = 40;
            hpBtLabel.y = 320;

            scene.addChild(hpBtLabel);
            
            var winLabel = new Label('かち！');
            winLabel.font = "80px 'Consolas', 'Monaco', 'ＭＳ ゴシック'";
            winLabel.x = 90;
            winLabel.y = 180;
            winLabel.color = '#f00';

            var eHP = 20;
            eHP = rand(70);
            if (eHP < 20) eHP = 40;
            
            if (eHP < 0) eHP = 0;
            if (HP < 0) HP = 0;
            damageLabel.text = 'てき：' + eHP;
            hpBtLabel.text = '自分：' + HP;
            
            var count = 0;
            var tick = 0;
            
            var up = 0;
            var right = 0;
            var left = 0;
            var down = 0;
            
           chara.addEventListener('enterframe', function(e) {
               scene.backgroundColor = 'rgba(255, 255, 255, 0.7)';
               


               
               if(chara.frame % 3000 === 0) {
                     if ((rand(100) > 90) && ((eHP - count) > 0)) { 
                                   if(dx > 4 && ! right) {
                         right = 1;
                            alert('右手に力を込めた');
                                } 
                         
                               monster.action = "attack";
                               chara.action = "damage";
                               HP--;

                               scene.backgroundColor = 'rgba(255, 127, 0, 0.7)';
                                              
                     
                   
                  if (up && right){
                      if (MP < 5) { 
                          alert('しかしMPがたりない!'); } else {
                       up = 0;
                       alert('必殺技アイススパーク!！');
                       //scene.backgroundColor = 'rgba(0, 0, 0, 0.9)';
                      chara.action = "special";
                           //   chara.tl.delay(10).then(function () {chara.right();chara.action = "special";}
                     //  chara.tl.scaleTo(3, 10). then(function () {chara.right();chara.action = "special";}.scaleTo(2,10));
                             MP -= 5;
                       right = 0;
                      count += 10;
                          } }
                     }

                }
                 hpLabel.color = isDamageColor(HP, MAX_HP);
                 damageLabel.color = isDamageColor(eHP -count, eHP);
               
                 hpBtLabel.text = '自分：' + HP;
                         if(dy < -4  && up < 1) {
                         up = 1;
                                                  count++;
                         alert('間合いをとった');

                                } 
                                           damageLabel.text = 'てき：' + (eHP - count) ;
               if (HP < 0) {
                   // 死んだ時
                   scene.removeChild(label);
                   scene.removeChild(subLabel);
                   chara.action = "dead";
                   chara.tl.rotateBy(1080, 15).moveBy(-200,-150,5).delay(30).then(function() {core.end();});                       

                  // core.end();
               }
           });
            
           //タッチ開始時に呼ばれる
            scene.addEventListener(Event.TOUCH_START, function(e){
                
                if (count > eHP) {
                    monster.tl.rotateBy(1080, 15).moveBy(150,-150,5).then(function() {scene.addChild(winLabel);ENEMY_NUM++;}).delay(50).then(function() { core.popScene();});                       
                } else {
                       //     damageLabel.text = 'てき：' + (eHP - count) ;

                chara.action = "attack";
             //   chara.tl.moveBy(1,0,1);
                count++;


                }
 

            });

            return scene;
        };
         
    };
    
     //独自のロード画面作成
    core.loadingScene = new enchant.Scene();
    core.loadingScene.backgroundColor = '#FFF'; //白背景
  //  var load_sprite = new Sprite(64, 64); 
    //load_sprite.image = core.assets[IMG_LOGO];
//    core.loadingScene.addChild(load_sprite);
/*    var label = new enchant.Label(); //読み込み量表示ラベル
            label.font = "20px 'Consolas', 'Monaco', 'ＭＳ ゴシック'";
    label.moveTo(20, 220);
    label.color = "black";
    core.addEventListener('progress', function(e) {
      label.text = 'Loading：' +  e.loaded + '/' + e.total;
      console.log(label.text)
    });
    core.loadingScene.addChild(label);*/
 
    //その他、いろんな処理…
    core.start(); //読込開始されます

};
