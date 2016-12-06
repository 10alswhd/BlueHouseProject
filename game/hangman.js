var prompt = require('prompt');

prompt.start();
var word = '';
var guessStatus = [];
var isGuessedCounter = 0;
var lives = 7;

function getWordToGuess () {
  prompt.get([
  {
    name: 'word'
  }], function (err, result) {
    word = result.word;
    isGuessedCounter = word.length;
    composeGuessStatus(word);
    guessALetter();
  });
}

function guessALetter(){
    console.log("Lives left: " + lives)
 prompt.get([
  {
      name: 'ch'
    }], function (err, result) {
        if(word.toLowerCase().indexOf(result.ch) != -1 && result.ch != ''){
            for(var i = 0; i < word.length; i++){
                if(word[i].toLowerCase() === result.ch){
                    guessStatus[i] = word[i];
                    isGuessedCounter--;
                }
            }
            if(isGuessedCounter == 0){
                console.log(guessStatus.join(''));
                console.log("Congrats!")
            } else {
                console.log(guessStatus.join(''));
                guessALetter();
            }
        } else {
            lives--;
            if(lives <= 0) {
                console.log("Game over!")
            } else {
                console.log(guessStatus.join(''));
                guessALetter();
            }
        }
  });
}

function composeGuessStatus(word) {
    for(var i = 0; i < word.length; i++){
        guessStatus[i] = '_';
    }
}
console.log('Enter a word to guess:');
getWordToGuess();
