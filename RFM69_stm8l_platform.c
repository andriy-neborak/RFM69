#include <stm8l15x.h>
#include <stm8l15x_gpio.h>
#include <stm8l15x_spi.h>


volatile uint16_t RFM69_ms_timer = 0;
// function to disable interrupts
void noInterrupts(){
  disableInterrupts();
}

// function to enable interrupts
void interrupts(){
  enableInterrupts();
}

// function to control the GPIO tied to RFM69 chip select (parameter HIGH or LOW)
void RFM69_SetCSPin(bool state){
  if(state){
    GPIO_SetBits(GPIOB, GPIO_Pin_3);
  }
  else{
    GPIO_ResetBits(GPIOB, GPIO_Pin_3);
  }
}          

// function to read GPIO connected to RFM69 DIO0 (RFM69 interrupt signalling)
bool RFM69_ReadDIO0Pin(void){
  return (bool)GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0);
}

// function to transfer 1byte on SPI with readback
uint8_t SPI_transfer8(uint8_t data){
  uint8_t retvalue = 0;
  
  while(SPI_GetFlagStatus(SPI1, SPI_FLAG_TXE) == RESET);
  SPI_SendData(SPI1, data);
  while(SPI_GetFlagStatus(SPI1, SPI_FLAG_BSY) == SET);
  while(SPI_GetFlagStatus(SPI1, SPI_FLAG_RXNE) == RESET);
  
  retvalue = SPI_ReceiveData(SPI1);
  
  return retvalue;
}       

 // function for timeout handling, checks if previously set timeout expired
bool RFM69_IsTimeout(void){
  return (bool)(RFM69_ms_timer == 0);
}

// function for timeout handling, set timeout value
void RFM69_SetTimeout(uint16_t ms){
  RFM69_ms_timer = ms;
}

// function supply timeout variable decrement
void RFM69_TimerTick(void){
  if(RFM69_ms_timer){
    RFM69_ms_timer--;
  }
}
