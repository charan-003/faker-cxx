#include "faker-cxx/color.h"

#include <span>
#include <string>
#include <string_view>

#include "color_data.h"
#include "common/format_helper.h"
#include "faker-cxx/helper.h"
#include "faker-cxx/number.h"
#include "faker-cxx/types/hex.h"
#include "faker-cxx/types/locale.h"

namespace faker::color
{
namespace
{
std::span<const std::string_view> getColors(Locale locale)
{
    switch (locale)
    {
    case Locale::pl_PL:
        return polishColors;
    default:
        return englishColors;
    }
}
}

const std::array<std::string_view, 20> colorSpaces = {
    "sRGB", "Adobe RGB", "ProPhoto RGB", "DCI-P3",       "Rec. 709",        "Rec. 2020",       "CMYK",
    "XYZ",  "Lab",       "ACES",         "CIE 1931 XYZ", "CIE 1976 L*a*b*", "CIE 1976 L*u*v*", "CIEUVW",
    "Y'UV", "Y'IQ",      "Y'DbDr",       "YCC",          "YPbPr",           "YPbPr601"};

std::string_view name(Locale locale)
{
    const auto& colors = getColors(locale);

    return helper::randomElement(colors);
}

std::string space()
{
    return std::string(helper::randomElement(colorSpaces));
}

std::string rgb(bool includeAlpha)
{
    const std::integral auto red = number::integer(255);
    const std::integral auto green = number::integer(255);
    const std::integral auto blue = number::integer(255);

    if (!includeAlpha)
    {
        return common::format("rgb({}, {}, {})", red, green, blue);
    }

    std::floating_point auto alpha = number::decimal(1.0);

    return common::format("rgba({}, {}, {}, {:.2f})", red, green, blue, alpha);
}

std::string hex(HexCasing casing, HexPrefix prefix, bool includeAlpha)
{
    return number::hexadecimal(includeAlpha ? 8 : 6, casing, prefix);
}

std::string hsl(bool includeAlpha)
{
    std::integral auto hue = number::integer(360);
    std::integral auto saturation = number::integer(100);
    std::integral auto lightness = number::integer(100);

    if (!includeAlpha)
    {
        return common::format("hsl({}, {}, {})", hue, saturation, lightness);
    }

    std::floating_point auto alpha = number::decimal(1.0);

    return common::format("hsla({}, {}, {}, {:.2f})", hue, saturation, lightness, alpha);
}

std::string lch(bool includeAlpha)
{
    std::integral auto luminance = number::integer(100);
    std::integral auto chroma = number::integer(100);
    std::integral auto hue = number::integer(360);

    if (!includeAlpha)
    {
        return common::format("lch({}, {}, {})", luminance, chroma, hue);
    }

    std::floating_point auto alpha = number::decimal(1.0);

    return common::format("lcha({}, {}, {}, {:.2f})", luminance, chroma, hue, alpha);
}

std::string cmyk()
{
    std::floating_point auto cyan = number::decimal(1.);
    std::floating_point auto magenta = number::decimal(1.);
    std::floating_point auto yellow = number::decimal(1.);
    std::floating_point auto key = number::decimal(1.);

    return common::format("cmyk({:.2f}, {:.2f}, {:.2f}, {:.2f})", cyan, magenta, yellow, key);
}

std::string lab()
{
    std::floating_point auto lightness = number::decimal(100.0);
    std::floating_point auto red_green = number::decimal(-128.0, 128.0);
    std::floating_point auto blue_yellow = number::decimal(-128.0, 128.0);

    return common::format("lab({:.2f}, {:.2f}, {:.2f})", lightness, red_green, blue_yellow);
}

std::string hsb()
{
    std::integral auto hue = number::integer(360);
    std::integral auto saturation = number::integer(100);
    std::integral auto brightness = number::integer(100);

    return common::format("hsb({}, {}, {})", hue, saturation, brightness);
}

std::string hsv()
{
    std::integral auto hue = number::integer(360);
    std::integral auto saturation = number::integer(100);
    std::integral auto value = number::integer(100);

    return common::format("hsv({}, {}, {})", hue, saturation, value);
}

std::string hwb()
{
    std::integral auto hue = number::integer(360);
    std::integral auto whiteness = number::integer(100);
    std::integral auto blackness = number::integer(100);

    return common::format("hwb({}, {}, {})", hue, whiteness, blackness);
}

std::string yuv()
{
    std::integral auto luminance = number::integer(255);
    std::integral auto chrominance_blue = number::integer(255);
    std::integral auto chrominance_red = number::integer(255);

    return common::format("yuv({}, {}, {})", luminance, chrominance_blue, chrominance_red);
}

}
