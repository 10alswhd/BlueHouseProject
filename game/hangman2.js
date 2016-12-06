const gameIsWon = ({word, correctGuesses, wrongGuesses}) => wordIsGuessed(word, correctGuesses)
const gameIsLost = ({word, correctGuesses, wrongGuesses}) => listGTE10(wrongGuesses)
const wordIsGuessed = (word, guesses) => word.split('').every(c => guesses.includes(c))
const letterInWord = (letter, word) => word.split('').includes(letter)
const listGTE10 = (list) => Array.isArray(list) && list.length >= 10

function playHangman({word, correctGuesses, wrongGuesses}){
  const letter = prompt('Guess a letter')
  const goodGuess = letterInWord(letter, word)
  const gameState = goodGuess? {word, correctGuesses: [letter, ...correctGuesses], wrongGuesses } : {word, correctGuesses, wrongGuesses: [letter, ...wrongGuesses]}
  const maskedWord = word.split('').reduce((ac,x)=> ac + (gameState.correctGuesses.includes(x)? x : '_'), "")
  const msg = goodGuess? 'Right!' : 'Sorry!'
  alert(msg + ' ' + maskedWord)
  if(gameIsWon(gameState)){
    alert("You win! The word was "+word)
  } else if(gameIsLost(gameState)){
    alert("You lose, the word was "+ word)
  } else {
    return playHangman(gameState)
  }
  return gameState
}

function start(word){
 return playHangman({word, correctGuesses:[], wrongGuesses:[]})
}
