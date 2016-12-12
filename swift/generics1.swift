class Person: NSObject {
	
	let name: String
	let surname: String
	var friends: [Person]?
	
	init(name: String,  surname: String) {
		self.name = name
		self.surname = surname
	}
}
