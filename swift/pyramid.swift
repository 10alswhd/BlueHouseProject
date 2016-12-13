import UIKit

class Pyramid: Printable {
    var levels :[[Int]]

    init (levelCount :Int = 5) {
        var levels = [[Int]]()
        for i in 0..<levelCount {
            var level = [Int]()
            for j in 0..<i + 1 {
                level.append(Int(arc4random()) % 100)
            }
            levels.append(level)
        }
        self.levels = levels
    }

    var description: String {
        get {
            var s = ""
            for level in self.levels {
                var line = ""
                for num in level {
                    line += "\(num) "
                }
                s += "\(line)\n"
            }
            return s
        }
    }
}

class PathFinder {
    var pyramid: Pyramid
    var stack = [Int]()
    var paths = [[Int]]()
    var sortedPaths = [[Int]]()

    init(_ pyramid: Pyramid) {
        self.pyramid = pyramid
        self.travel(0, 0)
        self.sortedPaths = sorted(self.paths, { $0.reduce(0,+) > $1.reduce(0,+) })
    }

    func travel(depth: Int, _ index: Int) {
        stack.append(pyramid.levels[depth][index])
        if depth + 1 < pyramid.levels.count {
            for i in index...index+1 {
                travel(depth + 1, i)
            }
        } else {
            var copy = self.stack
            self.paths.append(copy)
        }
        stack.removeLast()
    }
}

var p = Pyramid(levelCount: 5)
p.description
p.levels

var f = PathFinder(p)
f.sortedPaths
