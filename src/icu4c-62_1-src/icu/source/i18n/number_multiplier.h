// © 2018 and later: Unicode, Inc. and others.
// License & terms of use: http://www.unicode.org/copyright.html

#include "unicode/utypes.h"

#if !UCONFIG_NO_FORMATTING
#ifndef __SOURCE_NUMBER_MULTIPLIER_H__
#define __SOURCE_NUMBER_MULTIPLIER_H__

#include "numparse_types.h"
#include "number_decimfmtprops.h"

U_NAMESPACE_BEGIN namespace number {
namespace impl {


/**
 * Wraps a {@link Multiplier} for use in the number formatting pipeline.
 */
// Exported as U_I18N_API for tests
class U_I18N_API MultiplierFormatHandler : public MicroPropsGenerator, public UMemory {
  public:
    MultiplierFormatHandler() = default; // WARNING: Leaves object in an unusable state; call setAndChain()

    void setAndChain(const Scale& multiplier, const MicroPropsGenerator* parent);

    void processQuantity(DecimalQuantity& quantity, MicroProps& micros,
                         UErrorCode& status) const U_OVERRIDE;

  private:
    Scale multiplier;
    const MicroPropsGenerator *parent;
};


/** Gets a Scale from a DecimalFormatProperties. In Java, defined in RoundingUtils.java */
static inline Scale scaleFromProperties(const DecimalFormatProperties& properties) {
    int32_t magnitudeMultiplier = properties.magnitudeMultiplier + properties.multiplierScale;
    int32_t arbitraryMultiplier = properties.multiplier;
    if (magnitudeMultiplier != 0 && arbitraryMultiplier != 1) {
        return Scale::byDoubleAndPowerOfTen(arbitraryMultiplier, magnitudeMultiplier);
    } else if (magnitudeMultiplier != 0) {
        return Scale::powerOfTen(magnitudeMultiplier);
    } else if (arbitraryMultiplier != 1) {
        return Scale::byDouble(arbitraryMultiplier);
    } else {
        return Scale::none();
    }
}


} // namespace impl
} // namespace number
U_NAMESPACE_END

#endif //__SOURCE_NUMBER_MULTIPLIER_H__
#endif /* #if !UCONFIG_NO_FORMATTING */
