#include "pin.h"

#include <Arduino.h>

template <typename input, typename output>
class BoardIO
{
public:
    using in = input;
    using out = output;
};

class Board
{
public:
    using D0 = BoardIO<InputDigitalPin<0>, OutputDigitalPin<0>>;
    using D1 = BoardIO<InputDigitalPin<1>, OutputDigitalPin<1>>;
    using D2 = BoardIO<InputDigitalPin<2>, OutputDigitalPin<2>>;
    using D3 = BoardIO<InputDigitalPin<3>, OutputAnalogPin<3>>;
    using D4 = BoardIO<InputDigitalPin<4>, OutputDigitalPin<4>>;
    using A0 = BoardIO<InputAnalogPin<::A0>, OutputAnalogPin<::A0>>;
    using A1 = BoardIO<InputAnalogPin<::A1>, OutputAnalogPin<::A1>>;
    using A2 = BoardIO<InputAnalogPin<::A2>, OutputAnalogPin<::A2>>;
    using A3 = BoardIO<InputAnalogPin<::A3>, OutputAnalogPin<::A3>>;
    using A4 = BoardIO<InputAnalogPin<::A4>, OutputAnalogPin<::A4>>;
    using A5 = BoardIO<InputAnalogPin<::A5>, OutputAnalogPin<::A5>>;
};