import Foundation

class Log{
    enum LogLevel: Int {
        case None = 0
        case Debug
        case Info
        case Warn
        case Error
        case Fatal
    }
    static var logLevel:LogLevel = .None
    
    class func debug(message: String, fileName: String = __FILE__, funcName: String = __FUNCTION__, line: Int = __LINE__) {
            self.__log__(message, "[debug]", fileName, funcName, line, .Debug)
    }
    
    class func info(message: String, fileName: String = __FILE__, funcName: String = __FUNCTION__, line: Int = __LINE__) {
        self.__log__(message, "[info]", fileName, funcName, line, .Info)
    }
    
    class func warn(message: String, fileName: String = __FILE__, funcName: String = __FUNCTION__, line: Int = __LINE__) {
        self.__log__(message, "[warn]", fileName, funcName, line, .Warn)
    }
    
    class func error(message: String, fileName: String = __FILE__, funcName: String = __FUNCTION__, line: Int = __LINE__) {
        self.__log__(message, "[error]", fileName, funcName, line, .Error)
    }
    
    class func fatal(message: String, fileName: String = __FILE__, funcName: String = __FUNCTION__, line: Int = __LINE__) {
        self.__log__(message, "[fatal]", fileName, funcName, line, .Fatal)
    }
    
    private class func __log__(message: String, _ header:String, _ fileName: String, _ funcName: String , _ line: Int, _ logLevel: LogLevel) {
        if(self.logLevel.rawValue>LogLevel.None.rawValue && self.logLevel.rawValue <= logLevel.rawValue){
            NSLog("\(header) [\(fileName.lastPathComponent.stringByDeletingPathExtension).\(funcName):\(line)] "+message)
        }
    }
}
