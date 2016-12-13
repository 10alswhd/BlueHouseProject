
let ax = ["a", "b", "c", "d", "e", "f"]


// prefer
for i in ax.indices {
    print("\(i): \(ax[i])")
}

// vs
var ii: Int
ii = 0
for e in ax {
    print("\(ii): \(e)")
    ii++
}

// vs
var ii: Int
for (var i = 0; i < ax.count; i++) {
    print("\(ii): \(ax[i])")
    ii++
}
