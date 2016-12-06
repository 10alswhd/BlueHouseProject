// game board
var board = $('<div></div>').attr('id','board').attr('class','board');
var score = $('<div></div>').attr('id','score').attr('class','score');
$('body').append(board).append(score);

// board css
$('body').css('background-image','url("http://www.snwvalves.com/image/table/rect_959595_620_20_1-3.jpg")');
board.css({'position':'absolute',
           'top':'60px','left':'20px',
           'width':'200px','height':'400px',
           'background-color':'#cc9',
           'opacity':0.9});
score.css({'background-color':'#fc6',
           'font-size':'13px',
           'padding':'5px'});

// init
if (!window.console) console = {debug: function() {}};

// define tetromino
var shapes = ['L','O','J','T','S','I','Z'];
var tetromino = {};
tetromino.L = {};
tetromino.L.shape = {};
tetromino.L.shape.r0 = new Array('fill','fill','n','empty','fill','n','empty','fill');
tetromino.L.shape.r90  = new Array('empty','empty','fill','n','fill','fill','fill');
tetromino.L.shape.r180 = new Array('fill','empty','n','fill','empty','n','fill','fill');
tetromino.L.shape.r270 = new Array('fill','fill','fill','n','fill','empty','empty');
tetromino.L.color = '#c99';
tetromino.O = {};
tetromino.O.shape = {};
tetromino.O.shape.r0 = new Array('fill','fill','n','fill','fill');
tetromino.O.shape.r90 = new Array('fill','fill','n','fill','fill');
tetromino.O.shape.r180 = new Array('fill','fill','n','fill','fill');
tetromino.O.shape.r270 = new Array('fill','fill','n','fill','fill');
tetromino.O.color = '#598982';
tetromino.J = {};
tetromino.J.shape = {};
tetromino.J.shape.r0 = new Array('fill','fill','n','fill','empty','n','fill','empty');
tetromino.J.shape.r90  = new Array('fill','fill','fill','n','empty','empty','fill');
tetromino.J.shape.r180 = new Array('empty','fill','n','empty','fill','n','fill','fill');
tetromino.J.shape.r270 = new Array('fill','empty','empty','n','fill','fill','fill');
tetromino.J.color = '#8152CE';
tetromino.T = {};
tetromino.T.shape = {};
tetromino.T.shape.r0 = new Array('fill','empty','n','fill','fill','n','fill','empty');
tetromino.T.shape.r90  = new Array('fill','fill','fill','n','empty','fill','empty');
tetromino.T.shape.r180 = new Array('empty','fill','n','fill','fill','n','empty','fill');
tetromino.T.shape.r270 = new Array('empty','fill','empty','n','fill','fill','fill');
tetromino.T.color = '#E70909';
tetromino.S = {};
tetromino.S.shape = {};
tetromino.S.shape.r0 = new Array('fill','empty','n','fill','fill','n','empty','fill');
tetromino.S.shape.r90  = new Array('empty','fill','fill','n','fill','fill','empty');
tetromino.S.shape.r180 = new Array('fill','empty','n','fill','fill','n','empty','fill');
tetromino.S.shape.r270  = new Array('empty','fill','fill','n','fill','fill','empty');
tetromino.S.color = '#8989FF';
tetromino.I = {};
tetromino.I.shape = {};
tetromino.I.shape.r0 = new Array('fill','fill','fill','fill');
tetromino.I.shape.r90  = new Array('fill','n','fill','n','fill','n','fill');
tetromino.I.shape.r180 = new Array('fill','fill','fill','fill');
tetromino.I.shape.r270  = new Array('fill','n','fill','n','fill','n','fill');
tetromino.I.color = '#ff9';
tetromino.Z = {};
tetromino.Z.shape = {};
tetromino.Z.shape.r0 = new Array('empty','fill','n','fill','fill','n','fill','empty');
tetromino.Z.shape.r90  = new Array('fill','fill','empty','n','empty','fill','fill');
tetromino.Z.shape.r180 = new Array('empty','fill','n','fill','fill','n','fill','empty');
tetromino.Z.shape.r270  = new Array('fill','fill','empty','n','empty','fill','fill');
tetromino.Z.color = '#569458';
 
 
var COLUMN_SIZE = 10;
var ROW_SIZE = 20;
var SQUARE_SIZE = 20;
 
var help = "방향키:j, l, 회전:k, 드롭:SpaceBar"
var score = 0;
var speed = 1000;
 
//util
function getValue(element, attr) {
    try {
        return parseInt(element.getFrame().css(attr)); 
    } catch(e) {
        return parseInt(element.css(attr));
    }
}
 
//Square object
var Square = function() {
 
    this.getSquare = function() {
        return $('<div/>', {
            'class': 'square'
        }).css({'position':'absolute', 'width':SQUARE_SIZE, 'height':SQUARE_SIZE, 'border-right':'1px solid gray', 'border-bottom':'1px solid gray', 'z-index':3})
    }
};
 
var activeFrame;
 
var Frame = function(type) { 
    this.type = type; 
 
    _self = this;
    this.rotateDegree = 0;
 
    this.frame = $('<div/>', {
        'class': 'frame',
    }).css({'position':'absolute', 'left':'80px', 'top':'0px','border':'0px solid black', 'z-index':2});
 
    this.drawSquares = function(type) {
        var r = 'r' + this.rotateDegree;
        var left = 0, top = 0;
 
        $.each(tetromino[type]['shape'][r], function(index, value) {
 
            if(value=='fill') {
                var square = (new Square()).getSquare();
                square.css({'left':left ,'top':top});
                left += 20; 
            }
 
            if(value=='empty') {
                left += 20;
            }
            
            if(value=='n') {
                left = 0;
                top += 20;
            }
 
            _self.frame.append(square); 
            
        });
 
        _self.frame.css({'width':left,'height':top+SQUARE_SIZE});
    }
 
    this.drawFrame = function() {
        this.frame.empty();
        this.drawSquares(type);
        this.frame.children('.square').css({'background-color':tetromino[type]['color']});
        var frameRight = getValue(this.frame, 'width')+getValue(this.frame, 'left');
        if(frameRight > COLUMN_SIZE*SQUARE_SIZE) {
            this.frame.css('left', getValue(this.frame, 'left')-frameRight+COLUMN_SIZE*SQUARE_SIZE);
        }
        return this.frame; 
    }
 
 
    this.getFrame = function() {
        return this.frame;
    }; 
 
    this.getSquares = function() {
        return this.frame.children('.square');
    };
 
};
 
function rotate(frame) {
 
    if(!frame) {return;}
 
    frame.rotateDegree += 90;
    frame.rotateDegree = frame.rotateDegree % 360;
    frame.drawFrame(); 
}
 
 
function drop(frame) {
    if(!frame) {return;}
 
    while(canMoveDown(frame)) {
        move(frame, 'down');
    }
    afterDrop();
}
 
function move(frame, direction) {
    if(!frame) {return;}
    
    var left = getValue(frame, 'left');
    var top = getValue(frame, 'top');
 
    if(direction == 'left') {
        if(!getValue(frame,'left')) {
            return;
        }
        
        frame.getFrame().css({'left':left-SQUARE_SIZE});
    }
    if(direction == 'right') {
        var boardWidth = SQUARE_SIZE * COLUMN_SIZE;
        var boardRight = getValue($("#board"), 'left') + boardWidth;
        var frameRight = getValue($("#board"), 'left') + getValue(frame, 'left') + getValue(frame, 'width');
 
        if(!(boardRight-frameRight)) {
            return;
        }
        
        frame.getFrame().css({'left':left+SQUARE_SIZE});
    }
    if(direction == 'down') {
        frame.getFrame().css({'top':top+SQUARE_SIZE});
    }
}
 
 
function canMoveDown(frame) {
 
    var boardHeight = getValue($("#board"), 'height');
    var boardLeft = getValue($("#board"), 'left');
    var boardTop = getValue($("#board"), 'top');
 
    var frameLeft = getValue(frame, 'left');
    var frameTop = getValue(frame, 'top');
 
    var squares = frame.getSquares();
    for(var i=0; i<squares.length; i++) {
        // board area check
        var squareLeft = getValue($(squares[i]),'left');
        var squareTop = getValue($(squares[i]),'top');
        var x = boardLeft + frameLeft + squareLeft;
        var y = boardTop + frameTop + squareTop + SQUARE_SIZE;
    
        if(boardHeight + boardTop == y) {
            return false;
        }
 
        // checking frame stopped
        var atPoint = document.elementFromPoint(x+10, y+10);
        if($(atPoint).attr('status')) {
            return false;
        }
 
    }
 
 
    return true;
}
 
function afterDrop() {
    $(activeFrame.getSquares()).attr('status', 'unactive');
 
    //strip frame
    var squares = activeFrame.getSquares();
    $.each(squares, function(index, square) {
        $(square).css({
            'left': getValue($(square), 'left') + getValue(activeFrame, 'left'),
            'top' : getValue($(square), 'top')  + getValue(activeFrame, 'top')
        });
 
    });
 
 
 
    activeFrame.getFrame().parent().append(squares);
    activeFrame.getFrame().remove();
 
    checkGameOver(activeFrame);
 
 
    console.debug('activeFrame set to null');
    activeFrame = null;
 
}
 
function clearLines() {
    var boardLeft = getValue($("#board"), 'left');
    var boardTop = getValue($("#board"), 'top');
 
    for(var j=1; j<=ROW_SIZE; j++) {
        var squareArray = new Array();
        for(var i=COLUMN_SIZE; i>0; i--) {
            var x = boardLeft + (SQUARE_SIZE*i) - 10;
            var y = boardTop + (SQUARE_SIZE*j) - 10;
            
            var atPoint = $(document.elementFromPoint(x,y));
 
            if(atPoint.attr('class') != 'square') {
                break;
            } else {
                squareArray.push(atPoint);
            }
 
            if(squareArray.length==COLUMN_SIZE) {
                console.debug('success...');
                score += 100;
                $.each($('.square'), function(index, square) {
                    if(getValue($(square), 'top') < y-boardTop) {
                        $(square).css('top', getValue($(square), 'top')+SQUARE_SIZE);
                    }
                    
                })
                while(s=squareArray.pop()) {
                    s.remove();
                }
            }
        }
    }
 
}
 
//interval control
var createFrameInterval;
var moveDownInterval;
 
function checkGameOver(activeFrame) {
    if(getValue(activeFrame, 'top') <= 0) {
        clearInterval(createFrameInterval);
        alert("Game Over.. SCORE : " + score);
 
        $('#board').empty();
        startGame();
 
    }
}
 
function levelup() {
    speed = 1000 - parseInt(score / 400)*100;
 
    if(speed < 300) {speed=300}
 
    clearInterval(moveDownInterval);
    moveDown(speed);
 
}
 
function startGame() {
    score = 0;
    
    // create frame
    createFrameInterval = setInterval(function() {
        if(activeFrame) {return;} 
 
        clearLines();
        levelup();
 
        $('#score').html('score: ' + score + ' | level: ' + (1000-speed)/100 + ' | ' + help);
 
        var frame = new Frame(getNextTetromino());
        frame.drawFrame();
        console.debug('new frame was given');
        $("#board").append(frame.getFrame()); 
        activeFrame = frame;
    }, 100); 
 
}
 
// move frame down 
function moveDown(speed) {
    moveDownInterval = setInterval(function() {
        if(!activeFrame) {return;}
 
        console.debug(speed);
        if(!canMoveDown(activeFrame)) {
            afterDrop();
            return;
        }
 
        move(activeFrame, 'down');
 
    }, speed);
 
}
 
$(function() {
 
    startGame();
    moveDown(speed);
 
 
    $("body").keypress(function(event) {
        
        if(event.which == 105 || event.which == 107) {
            rotate(activeFrame);
        }
        if(event.which == 32) {
            drop(activeFrame);
        }
        if(event.which == 106 || event.which == 104) {
            move(activeFrame, 'left');
        }
        if(event.which == 108) {
            move(activeFrame, 'right');
        }
    });
 
});
 
 
function getNextTetromino() {
    return shapes[Math.floor(Math.random() * shapes.length)]
}
