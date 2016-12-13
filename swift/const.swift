func const<A, B>(a: A) -> B -> A {
  return { _ in a }
}
