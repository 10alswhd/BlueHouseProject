// http://en.wikipedia.org/wiki/Perlin_noise
var perlinTerrain = require('voxel-perlin-terrain')

var game = require('voxel-hello-world')({
  // we will be giving the engine our own terrain data
  // so we should tell it not to generate its own
  generateChunks: false,
  // how much terrain should be loaded at a time:
  chunkDistance: 3,
  playerSkin: 'substack.png'
})

var chunkSize = 32
var seed = 'abc123'
var floor = 0
var ceiling = 5
var terrainGenerator = perlinTerrain(seed, floor, ceiling)

game.voxels.on('missingChunk', function(chunkPosition) {
  var voxels = terrainGenerator(chunkPosition, chunkSize)
  var chunk = {
    position: chunkPosition,
    dims: [chunkSize, chunkSize, chunkSize],
    voxels: voxels
  }
  game.showChunk(chunk)
})

// start game without waiting for user to click
game.paused = false

// for debugging
window.game = game
