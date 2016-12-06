/**
 * @param {string} secret
 * @param {string} guess
 * @return {string}
 */
var getHint = function(secret, guess) {
    
    var numA = 0;
    var numB = 0;

    var i, j, jl;
    var strLength = secret.length;
    var secretHash = {};
    
    for (i = 0; i < strLength; i++) {
        
        var secretChar = secret[i];
        
        secretHash[secretChar] = secretHash[secretChar] || [];
        
        secretHash[secretChar].push(i);
    }
    
    for (i = 0; i < strLength; i++) {
        
        var guessChar = guess[i];
        
        if (secretHash[guessChar]) {
            
            var secretIndexes = secretHash[guessChar];
            
            // Checking for Bulls
            if (secretIndexes.indexOf(i) !== -1) {
                
                numA++;
                
            } else {
                
                // Checking for Cows
                
                for (j = 0, jl = secretIndexes.length; j < jl; j++) {
                    
                    var secretIndex = secretIndexes[j];
                    
                    if (guess[secretIndex] !== secret[secretIndex]) {
                        
                        numB++;
                        secretIndexes[j] = -1;
                        break;
                    }
                }
            }
        }
    }
    
    return '' + numA + 'A' + numB + 'B';
};

/**
 * @param {string} secret
 * @param {string} guess
 * @return {string}
 */
var _getHint = function(secret, guess) {
    
    var numA = 0;
    var numB = 0;
    var usedIndexes = [];
    
    var strLength = secret.length;
    var i, j;
    
    for (i = 0; i < strLength; i++) {
        
        if (guess[i] === secret[i]) {
            
            numA++;
            usedIndexes.push(i);
            
        } else {
            
            for (j = 0; j < strLength; j++) {
                
                if (guess[i] === secret[j] && usedIndexes.indexOf(j) === -1 && guess[j] !== secret[j]) {
                    
                    numB++;
                    usedIndexes.push(j);
                    break;
                }
            }
        }
    }
    
    return '' + numA + 'A' + numB + 'B';
};
