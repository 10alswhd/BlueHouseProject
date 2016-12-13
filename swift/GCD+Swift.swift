//
//  GCD+Swift.swift
//
//  Created by Marcel Dierkes on 01.06.15.
//  Copyright (c) 2015 Marcel Dierkes. All rights reserved.
//
import Dispatch

/**
A Swift-compatible abstraction for libDispatch.
*/
public struct GCD {
    
    /**
    Submits a block for asynchronous execution on a dispatch queue.
    */
    @inline(__always) public static func async(queue: dispatch_queue_t, block: () -> Void) {
        dispatch_async(queue, block)
    }
    
    /**
    Submits a block for synchronous execution on a dispatch queue.
    */
    @inline(__always) public static func sync(queue: dispatch_queue_t, block: () -> Void) {
        dispatch_sync(queue, block)
    }

    /**
    Schedule a block for execution on a given queue at a specified time. The given delay is in seconds.
    */
    @inline(__always) public static func after(delay: Double, queue: dispatch_queue_t, block: () -> Void) {
        let time = dispatch_time(DISPATCH_TIME_NOW, Int64(delay * Double(NSEC_PER_SEC)))
        dispatch_after(time, queue, block)
    }
    
    /**
    Execute a block once and only once.
    */
    @inline(__always) public static func once(inout predicate: dispatch_once_t, block: () -> Void) {
        dispatch_once(&predicate, block)
    }
    
    // MARK: Queues
    public enum QueueType {
        case Serial, Concurrent
        
        public func toQueueAttributes() -> dispatch_queue_attr_t! {
            switch self {
            case .Serial: return DISPATCH_QUEUE_SERIAL
            case .Concurrent: return DISPATCH_QUEUE_CONCURRENT
            }
        }
    }
    
    /**
    Returns the default queue that is bound to the main thread.
    
    - returns: Returns the main queue.
    */
    @inline(__always) public static func mainQueue() -> dispatch_queue_t {
        return dispatch_get_main_queue()
    }
    
    /**
    Returns a global queue with a specific QOS class
    
    - returns: Returns a global queue.
    */
    @inline(__always) public static func globalQueue(QOSClass: qos_class_t, flags: UInt = 0) -> dispatch_queue_t {
        return dispatch_get_global_queue(QOSClass, flags)
    }
    
    /**
    Creates a new dispatch queue to which blocks may be submitted.
    
    - returns: The newly created dispatch queue.
    */
    @inline(__always) public static func createQueue(label: String, queueType: QueueType = .Serial) -> dispatch_queue_t {
        return dispatch_queue_create(label, queueType.toQueueAttributes())
    }
}
