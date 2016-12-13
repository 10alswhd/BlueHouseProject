class MyDependency {}

class MyClass
{
  private let dependency:MyDependency
  
  init(dependency:MyDependency)
  {
    self.dependency = dependency
  }
}
