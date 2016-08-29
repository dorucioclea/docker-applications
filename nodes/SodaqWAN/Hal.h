#ifndef _Hal_h
#define _Hal_h

#ifdef DEBUG
#define debugPrintLn(...) { if (this->diagStream) this->diagStream->println(__VA_ARGS__); }
#define debugPrint(...) { if (this->diagStream) this->diagStream->print(__VA_ARGS__); }
#warning "Debug mode is ON"
#else
#define debugPrintLn(...)
#define debugPrint(...)
#endif

#include "Utils.h"

class Hal
{
public:
  // Creates a new Sodaq_RN2483 instance.
  Hal();

  // Initialize the Hal and all the stuff in it
  bool initHal();

  // Give the Hal time to do his work and check all the stuff
  bool Update();

  bool CheckAndAct();

  bool sendMessage(const uint8_t* payload, uint8_t size);

  // Sets the optional "Diagnostics and Debug" stream.
  void setDiag(Stream& stream) { diagStream = &stream; };

  inline void setAckOn() { isAckActive=true; };
  inline void setAckOff() { isAckActive=false; };
  inline bool getAcknowledge() { return isAckActive; };
  inline bool isInitialized() { return isHalInitialized; };
  
private:
  void init();
  
  // initialize the Lora stack
  bool initLora();
  // initialize the Switch stack
  bool initSwitch();
  // initialize the Temperature stack
  bool initTemperature();

  // The (optional) stream to show debug information.
  Stream* diagStream;
  // Is the HAL initialized
  bool isHalInitialized=false;
  // Send message with Acknowledgement
  bool isAckActive=false;
  int switchState = 0;
  int switchOldState = 0;
};

extern Hal HalImpl;
#endif _Hal_h
