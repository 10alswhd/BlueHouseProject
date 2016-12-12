enum Bit: UInt8 {
    case Zero = 0
    case One = 1
}
let five: "\(Bit.One)\(Bit.Zero)\(Bit.One)" // "OneZeroOne"
