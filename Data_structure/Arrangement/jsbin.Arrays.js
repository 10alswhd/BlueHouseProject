function write(message) {     document.getElementById('message').innerHTML += message + '<br/>';
   }

function newParagraph() {
  write("");
}

write('type of 1 : '+typeof 1);
write('type of 3.14 : '+typeof 3.14);
newParagraph();

write("0.1+0.2 ="+0.1+0.2);
write("(0.1+0.2).toFixed(1) ="+(0.1+0.2).toFixed(1));

//for in
newParagraph();
//for in
var Person = {
  name : 'palani',
  age  : '21',
  city : 'Redmond'
};

for(var property in Person) {
  write(property + ' : ' + Person[property]);
}
newParagraph();

//array
var collection = ['a', 1, /3/,  {}];
write('collection[0]'+' : '+collection[0]);
write('collection.length'+' : '+collection.length);
for(var property in collection) {
  write('collection['+property + '] : ' + collection[property]);
}
newParagraph();

//Stack

var vowels = ['a', 'e', 'i', 'o'];
for(var char in vowels) {
  write(char + ' : ' + vowels[char]);
}
newParagraph();

vowels.push('u');

write("vowels.pop() : "+vowels.pop());
vowels.push('u');
write("vowels : "+vowels);
newParagraph();

//array methods
write("['a','b','c','d'].reverse() : "+['a','b','c','d'].reverse());

write("['a','d','c','a'].sort() : "+['a','d','c','a'].sort());

write("[1,3,21,9,11,2].sort() : "+ [1,3,21,9,11,2].sort());
write("[1,3,21,9,11,2].sort(function(first,second){ return first-second;}) : "+ [1,3,21,9,11,2].sort(function(first,second){
  return first-second;
}));
newParagraph();
write("['a','b','c','d'].slice(1,3) : "+['a','b','c','d'].slice(1,3));

var ch = ['a','b','c','d'];
write("ch : "+ch);
write("ch.splice(1,3) : "+ch.splice(1,3));
write("ch : "+ch);
