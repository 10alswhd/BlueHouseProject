var fs = require('fs'),
    filename = 'wordlist.txt',
    anagramChecker;

function anagram(rawList){
  return function (word){
    var list = rawList.slice(),
        matched = [];

    while(wordFromList = list.shift()){
      if(wordFromList.length == word.length) {
        var sortedWordFromList = wordFromList.split('').sort().join(''),
            sortedWord = word.split('').sort().join('');

        if(sortedWordFromList == sortedWord){
          matched.push(wordFromList);
        }
      }
    }

    console.log("===========");
    console.log(matched);
  }
}

fs.readFile(filename, 'utf8', function(err, data) {
  if (err) throw err;

  anagramChecker = anagram(data.split('\n'));
  anagramChecker("abba");
  anagramChecker("horse");
  anagramChecker("apple");
  anagramChecker("carthorse");
});
