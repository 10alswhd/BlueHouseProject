var matrix = [[1,0,0], [0,0,0]]

function bomber(i, j) {
	var selectedCell = matrix[i][j]
	if (selectedCell != 1) return
	matrix.forEach((elem, idx, array) => {
		console.log(elem)
		elem.splice(j, 1, 1)
	})
	var arrayLength = matrix[i].length
	matrix[i] = matrix[i].fill(1)
	console.log(matrix)
}

bomber(0, 0)

//////////////
// Attempt #2 - Unrefactored
//////////////

'use strict'

const matrix = [[0,1,0], [0,0,0], [0,0,0]]
let newMatrix = matrix
let rowsWithOnes = new Array(matrix.length).fill(false)
let columnsWithOnes = new Array(matrix[0].length).fill(false)
const numberYouAreLookingFor = 1

function findAllOnes(matrix) {
	for (var rowIndex in matrix) {
		for(var colIndex in matrix[rowIndex]) {
			if (matrix[rowIndex][colIndex] == numberYouAreLookingFor) {
				rowsWithOnes[rowIndex] = true
				columnsWithOnes[colIndex] = true
			}
		}
	}
}

function bomber() {
	findAllOnes(matrix)
	rowsWithOnes.forEach((containsOne, rowIdx) => {
		if (containsOne) {
			newMatrix[rowIdx] = newMatrix[rowIdx].fill(1)
		} else {
			newMatrix[rowIdx].forEach((elem, colIdx) => {
				if (columnsWithOnes[colIdx]) {
					newMatrix[rowIdx].splice(colIdx, 1, numberYouAreLookingFor)
				}
			})
		}
	})
	return newMatrix
}

bomber()
