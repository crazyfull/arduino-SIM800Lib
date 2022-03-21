#ifndef SIM800L_H
#define SIM800L_H
#include <Arduino.h>
//#include <math.h>
//#include <WString.h>

//#include <String.h>

#include <SoftwareSerial.h>
#include "clsUnicode.h"

/*
enum RequestCommand{

};
*/
struct SMSMessage{
    bool isNewSMS = false;
    String PhoneNumber;
    String Message;
    String Name;
};

class SIM800L {
private:
    bool isBusy;
    SoftwareSerial *m_pGSMSerial;
    String m_serialBuffer;
    clsUnicode m_Unicode;
    bool isRegisteredSim = false;
    int RegTimer = 0;
    

    void parsehCommands();
    void SetBusyON();
    void SetBusyOFF();
    String ReadSerial(uint32_t timeout = 1000);
    
public:
    
    SIM800L(uint32_t GSMSpeed, uint8_t rx, uint8_t tx);
    
    void CheckSerial();
    void SetEchoOFF();
    
    void SetEnableCallerID();
    void SetEnableCallTone();
    void SetTextFormatMode();
    void SetCharacterset(const char* name);
    void SetSMSDeleveryReportON();
    void SetEnableAutoNetworkTime();
    void SetNationalNumberType();
    void SendCallTone(uint8_t tonNum);
    void AddContanct(uint8_t index, const char* phoneNumber, const char* Name);
    void GetContactByIndex(uint8_t index);
    void GetCurrentTime();
    void SearchContanctByName(const char* Name);
    void SendCheckRegisterNetwork();
    bool isRegisteredNetwork();
    void RejectCall();
    void SendUSSD(const char* code);

    void SendSMS(const char* phoneNumber, const char* Message);
    void SendSMS(const char* phoneNumber, const String &Message);
    
    SMSMessage ReadSMSByIndex(int16_t index);
    void DeleteAllSMS();
    void DeleteReadsSMS();
    void DeleteSendsSMS();
    void DeleteSMSByIndex(int16_t index);
    void ReStartGSM();
    void GetOperatorName();
    void SaveSettings();
    void ResetSettings();
    void WriteToSerial(const char* ATcmd);
    
    //events
    virtual void OnReceiveSMSMessage(const SMSMessage &Message);
    virtual void OnReceiveUSSDMessage(const String &Message);
    virtual void OnReceiveCreaditMessage(const String &Message);
    virtual void OnReceiveSIMCardDeavtive();
    virtual void OnReceiveSIMCardAvtive();
    
    
    //AT+COPS?\r  //get operator tag name
};

#endif  // SIM800L_H
