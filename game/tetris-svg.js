"use strict";
window.addEventListener("load", function (ev) {
    // SVG UI for Tetris
    var opt = {
        svgid: "view",
        stageid: "stage",
        svgns: "http://www.w3.org/2000/svg",
        scale: 24,
        width: 10,
        height: 20,
        cursor: 50,
        input: 200,
        fall: 3,
    };
    
    var newBlock = function () {
        return Tetris.Block(
            0|(opt.width / 2) - 2, 0, 0, 
            Tetris.shapes[0|(Math.random() * Tetris.shapes.length)]);
    };
    
    var render = function () {
        while (view.hasChildNodes()) view.removeChild(view.lastChild);
        stage.eachStone(function (x, y, color) {
            view.appendChild(stone(x, y, color));
        });
        block.eachStone(function (x, y, color) {
            view.appendChild(stone(x, y, color));
        });
    };
    
    var stone = function (x, y, color) {
        var rect = document.createElementNS(opt.svgns, "rect");
        rect.setAttribute("x", opt.scale * x);
        rect.setAttribute("y", opt.scale * y);
        rect.setAttribute("width", opt.scale);
        rect.setAttribute("height", opt.scale);
        rect.setAttribute("fill", color);
        rect.setAttribute("stroke", "black");
        return rect;
    };
    
    var tryLeft = function () {
        var next = block.left();
        if (!next.ok(stage)) return;
        block = next;
        render();
    };
    var tryRight = function () {
        var next = block.right();
        if (!next.ok(stage)) return;
        block = next;
        render();
    };
    var tryRotate = function () {
        var next = block.rotate();
        if (!next.ok(stage)) return;
        block = next;
        render();
    };
    var tryFall = function () {
        var next = block.fall();
        if (next.ok(stage)) {
            block = next;
            return render();
        } else {
            block.put(stage);
            render();
            setTimeout(function () {
                stage.shrink();
                block = newBlock();
                if (!block.ok(stage)) {
                    // gameover
                    stage.reset();
                }
                render();
            }, 10);
        }
    };
    
    // init
    var svg = document.getElementById(opt.svgid);
    svg.setAttribute("width", opt.scale * opt.width);
    svg.setAttribute("height", opt.scale * opt.height);
    svg.style.backgroundColor = "grey";
    var view = document.getElementById(opt.stageid);

    var stage = Tetris.Stage(opt.width, opt.height);
    var block = newBlock();

    //document.body.addEventListener("keydown", keyHandler, false);
    render();
    var cursor = SVGCursor(svg, opt.cursor);
    var count = 0;
    var loop = window.setInterval(function () {
        count = (count + 1) % opt.fall;
        if (cursor.move.y < -0.5) tryRotate();
        if (cursor.move.x < -0.5) tryLeft();
        if (cursor.move.x > 0.5) tryRight();
        if (cursor.move.y > 0.5) tryFall();
        if (count === 0) tryFall(); 
    }, opt.input);
}, false);
