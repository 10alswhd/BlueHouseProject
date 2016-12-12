//
//  GetOrElse.swift
//
//  Requires Swift 2.0 for protocol extensions
//
import Foundation

protocol GetOrElse {
  func getOrElse<T>(block block: () -> T) -> T
  func getOrElse<T>(defaultValue: T) -> T
}

extension Optional : GetOrElse {
  func getOrElse<T>(block block: () -> T) -> T {
    switch self {
    case nil:
      return block()
    default:
      return self as! T
    }
  }

  func getOrElse<T>(defaultValue: T) -> T {
    switch self {
    case nil:
      return defaultValue
    default:
      return self as! T
    }
  }
}

// Usage
let string: String? = nil

print( "print default value:" )
print( string.getOrElse("default") )

print( "print default value from block:" )
print( string.getOrElse({
  return "default in block"
}))

let string2: String? = "woah..."

print( "Don't print 'default', and print 'woah' twice:" )

print( string2.getOrElse("default") )
print( string2.getOrElse({
  return "default in block"
}))
