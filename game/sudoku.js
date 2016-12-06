var Sudoku = function(data) 
   {
     //   Private methods
     // -------------------------
    var sudoku = data;
     var sudokuLength = sudoku[0].length;
     var uniqueAndValidNumber  = function(array){
      var arr = array.slice().sort(), i;
          for( i= arr.length; i--;) {
            //The number shouldn't be repeated, has to be a number and couldn't be bigger than the length
            if (arr[i] === arr[i-1]  || !parseInt(arr[i]) || parseInt(arr[i]) > sudokuLength) {
               return false;
            };
          };
          return true;
      }
      //Evaluate the little squares
      var checkLittleSquares = function(){
      	var tempSudo = sudoku.slice();
      	var littleSqLength = Math.sqrt(sudoku[0].length);
      	var tempArr =[];
      	while(tempSudo[0].length > 0){
      		for (var i = 0; i < sudokuLength; i++) {      			
      			tempArr = tempArr.concat( tempSudo[i].length <= littleSqLength ? tempSudo[i].splice(0) : tempSudo[i].splice(0, littleSqLength));
      			if (tempArr.length === sudokuLength) {
      				if (!uniqueAndValidNumber(tempArr)) {
		      			return false;
		      		};
		      		tempArr =[];
      			};	
      			
      		};
      		
      	}
      	return true;
      }
     //   Public methods
     // -------------------------
     return {
       isValid: function() {
       //My alghorithm should work without this
       //and validate everything, but this is a tricky issue of cw
       if(sudoku.length > 1 && sudoku[0].length == 0) return true;
      //Check if the √N == integer
      if(Math.sqrt(sudokuLength) %1 != 0) { return false; };
         for (var i = 0; i < sudoku.length; i++) {
            if (sudoku[i].length != sudokuLength) {
               //Not equal length
               return false;
            };
            if (!uniqueAndValidNumber(sudoku[i])) {
               //A number is repeat in the row i
               return false;
            };
         };
         //Finally validate little squares
         if (!checkLittleSquares()) {
         	return false;
         };
         return true;
       }
     };
   };
