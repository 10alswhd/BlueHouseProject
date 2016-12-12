let maxScore = [100, 10, 50]

var teamScore = 0 // set
for scores in maxScore {
  
    if scores > 51 {
      teamScore += 10
    } else {
      teamScore += 20
    }
}
teamScore
