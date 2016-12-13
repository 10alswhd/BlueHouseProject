import CoreLocation

let metersPerMile: CLLocationDistance = 1_609.344
let secondsPerHour = 60.0 * 60.0
let yardsPerMile = 1_760.0
let feetPerMile = yardsPerMile * 3.0

/// Provides appropriately formatted, localized descriptions of linear distances.
class DistanceFormatter: NSLengthFormatter {
    /// True to favor brevity over precision.
    var approximate: Bool
    /// True to insert hints for text-to-speech.
    var forVoiceUse: Bool
    let nonFractionalLengthFormatter = NSLengthFormatter()
    
    init(approximate: Bool = false, forVoiceUse: Bool = false) {
        self.approximate = approximate
        self.forVoiceUse = forVoiceUse
        super.init()
    }
    
    required init?(coder decoder: NSCoder) {
        approximate = decoder.decodeBoolForKey("approximate")
        forVoiceUse = decoder.decodeBoolForKey("forVoiceUse")
        super.init(coder: decoder)
    }
    
    override func encodeWithCoder(coder: NSCoder) {
        super.encodeWithCoder(coder)
        coder.encodeBool(approximate, forKey: "approximate")
        coder.encodeBool(forVoiceUse, forKey: "forVoiceUse")
    }
    
    func stringFromDistance(distance: CLLocationDistance) -> String {
        let miles = distance / metersPerMile
        let feet = miles * feetPerMile
        
        var unit: NSLengthFormatterUnit = .Millimeter
        unitStringFromMeters(distance, usedUnit: &unit)
        let replacesYardsWithMiles = unit == .Yard && miles > 0.2
        let showsMixedFraction = (unit == .Mile && miles < 10) || replacesYardsWithMiles
        
        // An elaborate hack to use vulgar fractions with miles regardless of
        // language.
        if showsMixedFraction {
            numberFormatter.positivePrefix = "|"
            numberFormatter.positiveSuffix = "|"
            numberFormatter.decimalSeparator = "!"
            numberFormatter.alwaysShowsDecimalSeparator = true
        } else {
            numberFormatter.positivePrefix = ""
            numberFormatter.positiveSuffix = ""
            numberFormatter.decimalSeparator = nonFractionalLengthFormatter.numberFormatter.decimalSeparator
            numberFormatter.alwaysShowsDecimalSeparator = nonFractionalLengthFormatter.numberFormatter.alwaysShowsDecimalSeparator
        }
        
        if approximate && !showsMixedFraction {
            numberFormatter.usesSignificantDigits = true
            numberFormatter.maximumSignificantDigits = 2
        } else {
            numberFormatter.usesSignificantDigits = false
            numberFormatter.maximumFractionDigits = showsMixedFraction ? 2 : 0
        }
        numberFormatter.roundingIncrement = 0.25
        
        var formattedDistance: String
        if unit == .Yard {
            if miles > 0.2 {
                unit = .Mile
                formattedDistance = stringFromValue(miles, unit: unit)
            } else {
                unit = .Foot
                numberFormatter.roundingIncrement = 50
                formattedDistance = stringFromValue(feet, unit: unit)
            }
        } else {
            formattedDistance = stringFromMeters(distance)
        }
        
        // Elaborate hack continued.
        if showsMixedFraction {
            var parts = formattedDistance.componentsSeparatedByString("|")
            assert(parts.count == 3, "Positive format should’ve inserted two pipe characters.")
            var numberParts = parts[1].componentsSeparatedByString("!")
            assert(numberParts.count == 2, "Decimal separator should be present.")
            let decimal = Int(numberParts[0])
            if let fraction = Double(".\(numberParts[1])0") {
                let fourths = Int(round(fraction * 4))
                if fourths == fourths % 4 {
                    if decimal == 0 && fourths != 0 {
                        numberParts[0] = ""
                    }
                    let vulgarFractions = ["", "¼", "½", "¾"]
                    numberParts[1] = vulgarFractions[fourths]
                    if forVoiceUse && !numberParts[0].isEmpty && !numberParts[1].isEmpty {
                        numberParts[0] += " & "
                    }
                    parts[1] = numberParts.joinWithSeparator("")
                } else {
                    parts[1] = numberParts.joinWithSeparator(nonFractionalLengthFormatter.numberFormatter.decimalSeparator)
                }
            } else {
                parts[1] = numberParts.joinWithSeparator(nonFractionalLengthFormatter.numberFormatter.decimalSeparator)
            }
            formattedDistance = parts.joinWithSeparator("")
        }
        
        return formattedDistance
    }
}
