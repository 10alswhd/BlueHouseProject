import Foundation

import CoreTelephony

class OperatorInfo {
    func id() -> String {
        let networkInfo =  CTTelephonyNetworkInfo()
        let carrier = networkInfo.subscriberCellularProvider
        let mcc = carrier!.mobileCountryCode
        let mnc = carrier!.mobileNetworkCode
        
        return NSString(format: "%@%@", mcc!, mnc!) as String
    }
}
