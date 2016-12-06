// TETRIS
var TETRIS = {
    BLOCKS: [[],[],[],[],[]],
    render: function render () {
        console.log('render called!');
    },
    renderLoop: function renderLoop () {
        window.requestAnimationFrame(TETRIS.renderLoop);
        if ((TETRIS.offsetRecorder.value % TETRIS.offsetRecorder.offsetMargin) === 0)
            TETRIS.render();
        TETRIS.offsetRecorder.value++;
    },
    // 60ms * offsetMargin will be time offset for each render loop
    offsetRecorder: {offsetMargin: 60, value: 0}
};
// RenderLoop
TETRIS.renderLoop();
