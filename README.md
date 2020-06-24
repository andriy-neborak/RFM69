# RFM69
RFM69 C library port attempt from this arduino library: https://github.com/LowPowerLab/RFM69
Supports RFM69W, RFM69HW, RFM69CW, RFM69HCW (semtech SX1231, SX1231H)

### How to use this library

#### Configure pins

- `MOSI/CLK` - output
- `MISO` - input
- `NSS` - output
- `RESET/DIO1` - input

#### External interrupt line
`DIO1` line configure as external interrupt line on rising edge and use `RFM69_interruptHandler()` as callback. 

#### SPI module
- set SPI CPOL= 0 and CPHA = 0, MSB first
- maximum 10MHz SCK clock according to RFM69 datasheet
 

#### Please define in your project these platform specific functions defined as extern in RFM69.h:
- `extern void noInterrupts();`             function to disable interrupts
- `extern void interrupts();`               function to enable interrupts  
- `extern void RFM69_SetCSPin(bool);`       function to control the GPIO connected to RFM69 chip select (HIGH or LOW)
- `extern bool RFM69_ReadDIO0Pin(void);`    function to read GPIO connected to RFM69 DIO0 (RFM69 interrupt signalling)
- `extern uint8_t SPI_transfer8(uint8_t);`  function to transfer 1byte on SPI with readback
- `extern bool RFM69_IsTimeout(void);`   function for timeout handling, checks if previously set timeout expired
- `extern void RFM69_SetTimeout(uint16_t);` function for timeout handling, sets a timeout, parameter is in milliseconds (ms)

