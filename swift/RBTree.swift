import Foundation

class RBNode {
	var key :Int?
	var isRed :Bool = false
	var left :RBNode?
	var right :RBNode?
	var parent: RBNode?

	init(_ inKey :Int?) {
		self.key = inKey
	}
}

extension RBNode :Printable {
	var description :String {
	get {
		return "\(self.key)"
	}
	}
}

class RBTree {
	var _nil :RBNode!
	var _root :RBNode!

	init() {
		self._nil = RBNode(nil)
		self._root = _nil
	}

	func search(inKey :Int, _ inX :RBNode?=nil) -> RBNode {
		var x :RBNode = self._root
		if inX != nil {
			x = inX!
		}
		while x !== self._nil &&
			inKey != x.key {
				if inKey < x.key {
					x = x.left!
				} else {
					x = x.right!
				}
		}
		return x
	}

	func minimum(_ inX:RBNode?=nil) -> RBNode {
		var x :RBNode = self._root
		if inX != nil {
			x = inX!
		}
		while x.left !== self._nil {
			x = x.left!
		}
		return x
	}

	func maximum(_ inX:RBNode?=nil) -> RBNode {
		var x :RBNode = self._root!
		if inX != nil {
			x = inX!
		}
		while x.right !== self._nil {
			x = x.right!
		}
		return x
	}

	func insertKey(key:Int) {
		var node = RBNode(key)
		self.insertNode(node)
	}

	func insertNode(inZ:RBNode) {
		var z = inZ
		var y = self._nil
		var x = self._root
		while x !== self._nil {
			y = x
			if z.key < x.key {
				x = x.left!
			} else {
				x = x.right!
			}
		}
		z.parent = y
		if y === self._nil {
			self._root = z
		} else if z.key < y.key {
			y.left = z
		} else {
			y.right = z
		}
		z.left = self._nil
		z.right = self._nil
		z.isRed = true
		self.insertFixUp(z)
	}

	func insertFixUp(inZ:RBNode) {
		var z = inZ
		while z.parent!.isRed == true {
			if z.parent === z.parent!.parent!.left! {
				var y = z.parent!.parent!.right!
				if y.isRed {
					z.parent!.isRed = false
					y.isRed = false
					z.parent!.parent!.isRed = true
					z = z.parent!.parent!
				} else {
					if z === z.parent!.right! {
						z = z.parent!
						// left rotate
					}
					z.parent!.isRed = false
					z.parent!.parent!.isRed = false
					// right rotate
				}
			} else {
				var y = z.parent!.parent!.left!
				if y.isRed {
					z.parent!.isRed = false
					y.isRed = false
					z.parent!.parent!.isRed = true
					z = z.parent!.parent!
				} else {
					if z === z.parent!.left! {
						z = z.parent!
						// right rotate
					}
					z.parent!.isRed = false
					z.parent!.parent!.isRed = false
					// left rotate
				}
			}
		}
		self._root.isRed = false
	}

	func _left_rotate(inX:RBNode) {
		var x = inX
		var y = x.right!
		x.right = y.left
		if x.left !== self._nil {
			y.left!.parent	= x
		}
		y.parent = x.parent
		if x.parent === self._nil {
			self._root = y
		} else if x === x.parent!.left! {
			x.parent!.left = y
		} else {
			x.parent!.right = y
		}
		y.left = x
		x.parent = y
	}

	func _right_rotate(inY:RBNode) {
		var y = inY
		var x = y.left!
		y.left = x.right
		if x.right !== self._nil {
			x.right!.parent = y
		}
		x.parent = y.parent
		if y.parent === self._nil {
			self._root = x
		} else if y === y.parent!.right! {
			y.parent!.right = x
		} else {
			y.parent!.left = x
		}
		x.right = y
		y.parent = x
	}

	func checkInvariants() -> Bool {
		func isRedBlackNode(node:RBNode) -> (Int, Bool) {
			if (node.left != nil && node.right == nil) ||
				(node.left == nil && node.right != nil) {
					return (0, false)
			}
			if node.left == nil && node.right == nil && node.isRed == true {
				return (0, false)
			}
			if	node.isRed == true && node.left != nil && node.right != nil {
				if node.left!.isRed == true && node.right!.isRed == true {
					return (0, false)
				}
			}
			if node.left != nil && node.right != nil {
				if self._nil !== node.left && node !== node.left!.parent! {
					return (0, false)
				}
				if self._nil !== node.right && node !== node.right!.parent! {
					return (0, false)
				}
				var (leftCounts, leftOK) = isRedBlackNode(node.left!)
				if leftOK == false {
					return (0, false)
				}
				var (rightCounts, rightOK) = isRedBlackNode(node.right!)
				if rightOK == false {
					return (0, false)
				}
				if leftCounts != rightCounts {
					return (0, false)
				}
				return (leftCounts, true)
			}
			return (0, true)
		}
		var (numBlack, isOK) = isRedBlackNode(self._root)
		return isOK && self._root.isRed == false
	}
}

func writeTreeAsDot(t :RBTree) {
	func nodeID(node :RBNode) -> String {
		return NSString(format:"%p", [node] as CVarArg)
	}

	func nodeColor(node :RBNode) -> String {
		return node.isRed ? "red" : "black"
	}

	func visitNode(node :RBNode) {
		println("  \(nodeID(node)) [label=\"\(node.key)\", color=\"\(nodeColor(node))\"];")
		if node.left {
			var left = node.left!
			if left !== t._nil {
				visitNode(left)
				println("  \(nodeID(node)) -> \(nodeID(left));")
			}
		}
		if node.right {
			var right = node.right!
			if right !== t._nil {
				visitNode(right)
				println("  \(nodeID(node)) -> \(nodeID(right));")
			}
		}
	}
	println("digraph red_black_tree {")
	visitNode(t._root)
	println("}")
}

var t = RBTree()

for i in 0...100 {
	t.insertKey(i)
}
writeTreeAsDot(t)
