const block_offsets = {
	"I": [
		[ {x: 0, y: 0}, {x: -1, y: 0}, {x: -2, y: 0}, {x: 1, y: 0} ],
		[ {x: 0, y: 0}, {x: 0, y: -1}, {x: 0, y: 1}, {x: 0, y: 2} ],
		[ {x: 0, y: 0}, {x: -1, y: 0}, {x: -2, y: 0}, {x: 1, y: 0} ],
		[ {x: -1, y: 0}, {x: -1, y: -1}, {x: -1, y: 1}, {x: -1, y: 2} ],
	],
	"J": [
		[ {x: 0, y: 0}, {x: -1, y: 0}, {x: 1, y: 0}, {x: -1, y: -1} ],
		[ {x: 0, y: -1}, {x: 1, y: -2}, {x: 0, y: -2}, {x: 0, y: 0} ],
		[ {x: 0, y: -1}, {x: -1, y: -1}, {x: 1, y: -1}, {x: 1, y: 0} ],
		[ {x: 0, y: -1}, {x: 0, y: -2}, {x: 0, y: 0}, {x: -1, y: 0} ],
	],
	"L": [
		[ {x: 0, y: 0}, {x: -1, y: 0}, {x: 1, y: 0}, {x: 1, y: -1} ],
		[ {x: 0, y: -2}, {x: 0, y: -1}, {x: 1, y: 0}, {x: 0, y: 0} ], 
		[ {x: 0, y: -1}, {x: -1, y: -1}, {x: 1, y: -1}, {x: -1, y: 0} ],
		[ {x: 0, y: -1}, {x: -1, y: -2}, {x: 0, y: -2}, {x: 0, y: 0} ],
	],
	"O": [
		[ {x: 0, y: 0}, {x: -1, y: 0}, {x: -1, y: -1}, {x: 0, y: -1} ],
		[ {x: 0, y: 0}, {x: -1, y: 0}, {x: -1, y: -1}, {x: 0, y: -1} ],
		[ {x: 0, y: 0}, {x: -1, y: 0}, {x: -1, y: -1}, {x: 0, y: -1} ],
		[ {x: 0, y: 0}, {x: -1, y: 0}, {x: -1, y: -1}, {x: 0, y: -1} ],
	],
	"S": [
		[ {x: 1, y: -1}, {x: 0, y: -1}, {x: 0, y: 0}, {x: -1, y: 0} ],
		[ {x: -1, y: -2}, {x: -1, y: -1}, {x: 0, y: -1}, {x: 0, y: 0} ],
		[ {x: 1, y: -1}, {x: 0, y: -1}, {x: 0, y: 0}, {x: -1, y: 0} ],
		[ {x: -1, y: -2}, {x: -1, y: -1}, {x: 0, y: -1}, {x: 0, y: 0} ],
	],
	"T": [
		[ {x: 0, y: 0}, {x: -1, y: 0}, {x: 1, y: 0}, {x: 0, y: -1} ],
		[ {x: 0, y: -1}, {x: 0, y: 0}, {x: 1, y: -1}, {x: 0, y: -2} ],
		[ {x: 0, y: -1}, {x: -1, y: -1}, {x: 1, y: -1}, {x: 0, y: 0} ],
		[ {x: 0, y: -1}, {x: 0, y: 0}, {x: -1, y: -1}, {x: 0, y: -2} ],
	],
	"Z": [
		[ {x: 0, y: -1}, {x: -1, y: -1}, {x: 1, y: 0}, {x: 0, y: 0} ],
		[ {x: 0, y: -1}, {x: 0, y: 0}, {x: 1, y: -2}, {x: 1, y: -1} ],
		[ {x: 0, y: -1}, {x: -1, y: -1}, {x: 1, y: 0}, {x: 0, y: 0} ], 		
		[ {x: 0, y: -1}, {x: 0, y: 0}, {x: 1, y: -2}, {x: 1, y: -1} ],
	]
};