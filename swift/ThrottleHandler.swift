import Foundation

class ThrottleHandler {
    let interval: NSTimeInterval
    let block: dispatch_block_t

    private var source: dispatch_source_t?

    init(interval: NSTimeInterval, block: dispatch_block_t) {
        self.interval = interval
        self.block = block
    }

    func fire() {
        if let source = source {
            dispatch_source_cancel(source)
        }

        source = nil

        let s = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, dispatch_get_main_queue())
        let time = dispatch_time(DISPATCH_TIME_NOW, Int64(interval) * Int64(NSEC_PER_SEC))
        dispatch_source_set_timer(s, time, DISPATCH_TIME_FOREVER, 0);

        dispatch_source_set_event_handler(s) { [weak self] in
            if let block = self?.block {
                block()
            }

            if let source = self?.source {
                dispatch_source_cancel(source)
            }
            
            self?.source = nil
        }

        dispatch_resume(s)
        source = s
    }
}
