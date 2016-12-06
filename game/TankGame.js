/**
 * Created with JetBrains WebStorm.
 * User: Big mac
 * Date: 13-7-26
 * Time: 下午6:00
 * To change this template use File | Settings | File Templates.
 */
var herocolor = new Array("#BA9658", "#FFD972");
var enemycolor = new Array("#00A2B5", "#00FEFE");

function tank(x, y, direct, color) {
    this.x = x;
    this.y = y;
    this.speed = 2;
    this.live = true;
    this.direct = direct;
    this.color = color;
    this.moveUp = function () {
        this.y -= this.speed;
        this.direct = 0;
    }
    this.moveRight = function () {
        this.x += this.speed;
        this.direct = 1;
    }
    this.moveDown = function () {
        this.y += this.speed;
        this.direct = 2;
    }
    this.moveLeft = function () {
        this.x -= this.speed;
        this.direct = 3;
    }

}
function hero(x, y, direct, color) {
    this.mytank = tank;
    this.mytank(x, y, direct, color);
    this.shotEnemy = function () {

        switch (this.direct) {
            case 0:
                HeroMissile = new Missile(this.x + 9, this.y, this.direct, 3, "good", this);
                break;
            case 1:
                HeroMissile = new Missile(this.x + 30, this.y + 9, this.direct, 3, "good", this);
                break;
            case 2:
                HeroMissile = new Missile(this.x + 9, this.y + 30, this.direct, 3, "good", this);
                break;
            case 3:
                HeroMissile = new Missile(this.x, this.y + 9, this.direct, 3, "good", this);
                break;
        }
        HeroMissiles.push(HeroMissile);
//        var timer= window.setInterval("HeroMissile.run()",50);
        var timer = window.setInterval("HeroMissiles[" + (HeroMissiles.length - 1) + "].run()", 50);
//        HeroMissile.timer=timer;
        HeroMissiles[HeroMissiles.length - 1].timer = timer;
    }
}
function enemyTank(x, y, direct, color) {
    this.enemy = tank;
    this.step = 0;
    this.missilelive = true;
    this.enemy(x, y, direct, color);
    this.run = function () {
        switch (this.direct) {
            case 0:
                if (this.y > 0) {
                    this.y -= this.speed;
                }
                break;
            case 1:
                if (this.x + 30 < 400) {
                    this.x += this.speed;
                }
                break;
            case 2:
                if (this.y + 30 < 300) {
                    this.y += this.speed;
                }
                break;
            case 3:
                if (this.x > 0) {
                    this.x = this.speed;
                }
                break;
        }
        if (this.step > 30) {
            this.direct = Math.round(Math.random() * 3);
            this.step = 0;
        }
        this.step++;
        if (this.missilelive != false) {
        } else {
            switch (this.direct) {
                case 0:
                    EnemyMissile = new Missile(this.x + 9, this.y , this.direct, 3, "enemy", this);
                    break;
                case 1:
                    EnemyMissile = new Missile(this.x + 30, this.y + 9, this.direct, 3, "enemy", this);
                    break;
                case 2:
                    EnemyMissile = new Missile(this.x + 9, this.y + 30, this.direct, 3, "enemy", this);
                    break;
                case 3:
                    EnemyMissile = new Missile(this.x, this.y + 9, this.direct, 3, "enemy", this);
                    break;
            }
            enemyMissiles.push(EnemyMissile);
            var EnemyTimer = window.setInterval("enemyMissile[" + (enemyMissiles.length - 1) + "].run()", 50);
            enemyMissiles[enemyMissiles.length - 1].timer = EnemyTimer;
            this.missilelive=true;
        }
    }
}
function draw(tank) {     //tank is an object
    if (tank.live) {
        switch (tank.direct) {
            case 0:
            case 2:
                cxt.fillStyle = tank.color[0];
                cxt.fillRect(tank.x, tank.y, 5, 30);
                cxt.fillRect(tank.x + 15, tank.y, 5, 30);
                cxt.fillRect(tank.x + 6, tank.y + 5, 8, 20);

                cxt.fillStyle = tank.color[1];
                cxt.beginPath();
                cxt.arc(tank.x + 10, tank.y + 15, 4, 0, 360, true);
                cxt.closePath();
                cxt.fill();

                cxt.strokeStyle = tank.color[1];
                cxt.lineWidth = 2;
                cxt.beginPath();
                cxt.moveTo(tank.x + 10, tank.y + 15);
                if (tank.direct == 0) {
                    cxt.lineTo(tank.x + 10, tank.y);
                } else if (tank.direct == 2) {
                    cxt.lineTo(tank.x + 10, tank.y + 30);
                }
                cxt.closePath();
                cxt.stroke();
                break;
            case 1:
            case 3:
                cxt.fillStyle = tank.color[0];
                cxt.fillRect(tank.x, tank.y, 30, 5);
                cxt.fillRect(tank.x, tank.y + 15, 30, 5);
                cxt.fillRect(tank.x + 5, tank.y + 6, 20, 8);

                cxt.fillStyle = tank.color[1];
                cxt.beginPath();
                cxt.arc(tank.x + 15, tank.y + 10, 4, 0, 360, true);
                cxt.closePath();
                cxt.fill();

                cxt.strokeStyle = tank.color[1];
                cxt.lineWidth = 2;
                cxt.beginPath();
                cxt.moveTo(tank.x + 15, tank.y + 10);
                if (tank.direct == 1) {
                    cxt.lineTo(tank.x + 30, tank.y + 10);
                } else if (tank.direct == 3) {
                    cxt.lineTo(tank.x, tank.y + 10);
                }
                cxt.closePath();
                cxt.stroke();
                break;

        }
    }
}
function drawEnemyMissile(){
   for( var i=0;i<enemyMissiles.length;i++){
       var EnemyMissile= enemyMissiles[i];
       if(EnemyMissile.live){
           cxt.fillStyle="#00FEFE";
           cxt.fillRect(EnemyMissile.x,EnemyMissile.y,2,2);
       }
   }
}
function Missile(x, y, direct, speed, type, tank) {
    this.x = x;
    this.y = y;
    this.speed = speed;
    this.direct = direct;
    this.timer = null;
    this.live = true;
    this.type = type;
    this.tank = tank;
    this.run = function () {
        if (this.x <= 0 || this.x >= 400 || this.y <= 0 || this.y >= 300 && this.live == false) {
            window.clearInterval(this.timer);
            this.live = false;
            if (this.type == "enemy") {
                this.tank.missilelive = false;
            }
        }
        switch (this.direct) {
            case 0:
                this.y -= this.speed;
                break;
            case 1:
                this.x += this.speed;
                break;
            case 2:
                this.y += this.speed;
                break;
            case 3:
                this.x -= this.speed;
                break;
        }
        document.getElementById("aa").innerText = " missile x =" + this.x + " missile y= " + this.y;
    }
}
function drawMissile() {
    for (var i = 0; i < HeroMissiles.length; i++) {
//        alert(i);
        var HeroMissile = HeroMissiles[i];
        if (HeroMissile != null && HeroMissile.live) {
            cxt.fillStyle = "#FEF26E";
            cxt.fillRect(HeroMissile.x, HeroMissile.y, 2, 2);
        }
    }
}
function hitTanks() {
    for (var i = 0; i < HeroMissiles.length; i++) {
        var HeroMissile = HeroMissiles[i];
        if (HeroMissile.live) {
            for (var j = 0; j < enemies.length; j++) {
                var enemyTank = enemies[j];
                if (enemyTank.live) {
                    switch (enemyTank.direct) {
                        case 0:
                        case 2:
                            if (HeroMissile.x > enemyTank.x && HeroMissile.x < enemyTank.x + 20
                                && HeroMissile.y > enemyTank.y && HeroMissile.y < enemyTank.y + 30) {
                                enemyTank.live = false;
                                HeroMissile.live = false;
                            }
                            break;
                        case 1:
                        case 3:
                            if (HeroMissile.x > enemyTank.x && HeroMissile.x < enemyTank.x + 30
                                && HeroMissile.y > enemyTank.y && HeroMissile.y < enemyTank.y + 20) {
                                enemyTank.live = false;
                                HeroMissile.live = false;
                            }
                            break;
                    }
                }
            }
        }
    }
}
