import CoreData

@objc(Slot)
public class Slot: _Slot {
    static func request() -> NSFetchRequest {
        let request = NSFetchRequest(entityName: Slot.entityName())
        request.sortDescriptors = [NSSortDescriptor(key: "startTime", ascending: true)]

        return request
    }
}
