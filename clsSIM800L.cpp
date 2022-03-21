#include "clsSIM800L.h"
#include <SoftwareSerial.h>

#define BUFFER_RESERVE_MEMORY 255
#define NOTFOUND -1
#define NETWORK_CHECK_TIME 30*1000


SIM800L::SIM800L(uint32_t GSMSpeed, uint8_t rx, uint8_t tx) {
    m_serialBuffer.reserve(BUFFER_RESERVE_MEMORY);
    m_pGSMSerial = new SoftwareSerial(rx, tx);
    m_pGSMSerial->begin(GSMSpeed);
    
    delay(1);
    
    //m_pGSMSerial->println(F("AT"));
    
    //age be shabake vasl shode bod tanzimat emal nashe
    if(isRegisteredNetwork() == true){
        //return;
    }
    
    //set echo off
    SetEchoOFF();
    
    //set sms format to text
    SetTextFormatMode();
    
    //set character set to unicode
    SetCharacterset("UCS2");
    
    //adame niaz be +98 moghe call ya sms
    SetNationalNumberType();
    
    //delete all sms
    DeleteAllSMS();
}

void SIM800L::SetBusyON() {
    isBusy = true;
}
void SIM800L::SetBusyOFF() {
    isBusy = false;
}

void SIM800L::SetEchoOFF() {
    m_pGSMSerial->println(F("ATE0"));
    //ReadSerial();
    delay(6);
}

void SIM800L::SetEnableCallerID() {
    m_pGSMSerial->println(F("AT+CLIP=1"));
    delay(3);
}

void SIM800L::SetTextFormatMode() {
    m_pGSMSerial->println(F("AT+CMGF=1"));
    delay(3);
}

void SIM800L::SetSMSDeleveryReportON() {
    //AT+CNMI=,,,,1   //5 jomi bayad 1 beshe
    m_pGSMSerial->println(F("AT+CNMI=2,1,0,1,0"));
    delay(10);
    //AT+CSMP=49,167,0,0  //49 delivery on
    m_pGSMSerial->println(F("AT+CSMP=49,167,,"));
    delay(3);
}

void SIM800L::SetEnableAutoNetworkTime() {
    m_pGSMSerial->println(F("AT+CLTS=1"));
    delay(3);
}

void SIM800L::SetNationalNumberType() {
    /*
  129 Unknown type
    161 National number type
    145 International number type
    177 Network specific number
  */
    m_pGSMSerial->println(F("AT+CSTA=161"));
    delay(3);
    //ReadSerial();
}

bool SIM800L::isRegisteredNetwork(){
    m_pGSMSerial->println(F("AT+CSMINS?"));
    String ret = ReadSerial();
    Serial.println(ret);
    
    int16_t x = ret.indexOf("+CSMINS: ", 1);
    if(x > 0){
        x = ret.indexOf(",", x)+1;
        int16_t endVal = ret.indexOf("\r\n", x);
        
        if(x > 0){
            uint8_t status = ret.substring(x, endVal).toInt();
            if(status == 1){
                isRegisteredSim = true;
                 Serial.println("network is registred");
            }
        }
    }
    /*
    //+CPIN: READY
    if(ret.indexOf("+CPIN: READY") != NOTFOUND){
      isRegisteredSim = true;
      Serial.println("network registred");
    }else{
      isRegisteredSim = false;
    }
    */
    return isRegisteredSim;
}

void SIM800L::GetCurrentTime() {
    m_pGSMSerial->println(F("AT+CCLK?"));
    delay(3);
}

void SIM800L::SetEnableCallTone() {
    m_pGSMSerial->println(F("AT+DDET=1"));
    delay(3);
}

void SIM800L::RejectCall(){
    m_pGSMSerial->println(F("ATH"));
    delay(3);
}

void SIM800L::SendCallTone(uint8_t tonNum) {
    m_pGSMSerial->print(F("AT+DDET="));
    m_pGSMSerial->print(tonNum);
    m_pGSMSerial->print(F("\r"));
    delay(3);
}

void SIM800L::ReStartGSM() {
    m_pGSMSerial->println(F("AT+CFUN=0"));
    delay(15);
    m_pGSMSerial->println(F("AT+CFUN=1"));
    delay(15);
}

void SIM800L::SendCheckRegisterNetwork(){
    m_pGSMSerial->println(F("AT+CSMINS?"));
    delay(3);
}

void SIM800L::SetCharacterset(const char* name) {
    //AT+CSCS="UCS2"
    m_pGSMSerial->print(F("AT+CSCS=\""));
    m_pGSMSerial->print(name);
    m_pGSMSerial->println(F("\""));
    delay(3);
    //ReadSerial();
    
    //AT+CSMP=,,,25
    //set sms Data Coding to UCS2
    m_pGSMSerial->println(F("AT+CSMP=,167,,25"));
    delay(3);
    //ReadSerial();
}

void SIM800L::AddContanct(uint8_t index, const char* phoneNumber, const char* Name) {
    //AT+CPBW=1,"+989194206610",145,"Mojtaba"	//save number to simcard
    //AT+CPBW=,"+989194206610",145,"Mojtaba"
    //AT+CPBW=,"09194206610",129,"Mojtaba"
    
    //129 National number type
    //145 International number type
    
    m_pGSMSerial->print(F("AT+CPBW="));
    if (index > 0)
        m_pGSMSerial->print(index);  //Write a phonebook entry to the next available location
    
    m_pGSMSerial->print(F(",\""));
    m_pGSMSerial->print(phoneNumber);
    m_pGSMSerial->print(F("\" ,129,\""));
    m_pGSMSerial->print(Name);
    m_pGSMSerial->println(F("\""));
    delay(500);
}

void SIM800L::GetContactByIndex(uint8_t index) {
    //AT+CPBR=5
}

void SIM800L::SearchContanctByName(const char* Name) {
    m_pGSMSerial->print(F("AT+CPBF=\""));
    m_pGSMSerial->print(Name);
    m_pGSMSerial->println(F("\""));
    delay(3);
    //bayad read beshe az serial
}

void SIM800L::SendUSSD(const char* code) {
    //AT+CUSD=1,"*1#"
    m_pGSMSerial->print(F("AT+CUSD=1,\""));
    m_pGSMSerial->print( m_Unicode.ToUCS2(code) );
    m_pGSMSerial->println(F("\",15"));
    delay(3);
    //bayad read beshe az serial
}

void SIM800L::SendSMS(const char* phoneNumber, const char* Message) {
    m_pGSMSerial->print(F("AT+CMGS=\""));
    m_pGSMSerial->print(m_Unicode.ToUCS2(phoneNumber));
    m_pGSMSerial->println(F("\""));
    //bayad read beshe az serial Ya delay
    String res = ReadSerial();
    if(res.indexOf(">") == NOTFOUND ){
        Serial.print("err: can not send sms!: ");
        Serial.println(res);
        return;
    }
    //delay(10);
    
    //m_pGSMSerial->print(Message);  //need convert unicode
    m_pGSMSerial->print(m_Unicode.ToUCS2(Message));
    delay(10);
    m_pGSMSerial->print((char)26);
    //bayad read beshe az serial Ya delay
}

void SIM800L::SendSMS(const char* phoneNumber, const String &Message){
    SendSMS(phoneNumber, Message.c_str());
}

void SIM800L::WriteToSerial(const char* ATcmd) {
    m_pGSMSerial->println(ATcmd);
}

SMSMessage SIM800L::ReadSMSByIndex(int16_t index) {
    
    // AT+CMGR=1
    SMSMessage ret;
    if(index < 1)
        return ret;
    
    //send ATCommand
    m_pGSMSerial->print(F("AT+CMGR="));
    m_pGSMSerial->print(index);
    m_pGSMSerial->println();
    
    /**/
    //uint64_t timeOld = millis();
    String Buff = ReadSerial();
    //Serial.println(millis() - timeOld);
    
    
    int s = Buff.indexOf("+CMGR: ", 1);
    if (s != NOTFOUND) {
        
        Serial.print("\rSMSBUffer:[");
        Serial.print(Buff);
        Serial.println("]\n");
        
        int16_t part, s, p = 0;
        while (s != NOTFOUND) {
            s = Buff.indexOf("\"", s + 1);
            
            //if(s == NOTFOUND)
            //    break;
            
            if (p > 0) {
                part += 1;
                
                switch (part) {
                case 1:
                    //status
                    if(Buff.substring(p, s).indexOf("UNREAD") > 0){
                        ret.isNewSMS = true;
                    }
                    //Serial.println(Buff.substring(p, s));
                    break;
                case 2:
                    //phone numver
                    ret.PhoneNumber = m_Unicode.FromUCS2(Buff.substring(p, s));
                    //Serial.println(ret.PhoneNumber);
                    break;
                case 3:
                    //name (if exist)
                    ret.Name = m_Unicode.FromUCS2(Buff.substring(p, s));
                    //Serial.println(ret.Name);
                    break;
                case 4:
                    //date time
                    //Serial.println(Buff.substring(p, s));
                    break;
                }
                
                p = 0;
                continue;
            }
            
            p = s + 1;
        }
        
        //find end part message
        int msgEnd = Buff.indexOf("\r\n\r\n", 70);
        
        //set message
        ret.Message = m_Unicode.FromUCS2(Buff.substring(Buff.indexOf("\r\n", 30) + 2, msgEnd));
        //ret.Message = Buff.substring(Buff.indexOf("\"\r\n", 75) + 3, msgEnd);
        
        //Serial.print("\rMsg:");
        //Serial.println(ret.Message);
    }
    
    return ret;
}

void SIM800L::GetOperatorName() {
    //AT+COPS?
    //m_pGSMSerial->println(F("AT+COPS?"));
    //ReadSerial();
}

void SIM800L::DeleteAllSMS() {
    //AT+CMGDA=?  ("DEL READ","DEL UNREAD","DEL SENT","DEL UNSENT","DEL INBOX","DEL ALL")
    m_pGSMSerial->println(F("AT+CMGDA=\"DEL ALL\""));
    delay(10);
    //ReadSerial();
}

void SIM800L::DeleteReadsSMS() {
    //AT+CMGD=,2  //delete all send sms and receive readed sms                //همه پیام های خوانده شده و تلفن همراه ارسال شده را حذف کنید
    //AT+CMGD=,3  //delete all send and unsend sms and receive readed sms    // حذف همه پیام های خوانده شده . ارسال شده و ارسال نشده
    
    m_pGSMSerial->println(F("AT+CMGDA=\"DEL READ\""));
    delay(5);
    //ReadSerial();
}

void SIM800L::DeleteSendsSMS() {
    m_pGSMSerial->println(F("AT+CMGDA=\"DEL SENT\""));
    delay(10);
    //ReadSerial();
}

void SIM800L::DeleteSMSByIndex(int16_t index) {
    //AT+CMGD=index
    m_pGSMSerial->print(F("AT+CMGD="));
    m_pGSMSerial->print(index);
    m_pGSMSerial->println();
    delay(10);
    //ReadSerial();
}

void SIM800L::SaveSettings() {
    m_pGSMSerial->println(F("AT&W"));
    delay(5);
    //ReadSerial();
}

void SIM800L::ResetSettings() {
    m_pGSMSerial->println(F("AT&F"));
    delay(5);
    //ReadSerial();
}

void SIM800L::parsehCommands() {
    //m_serialBuffer.c_str();
    
    //+CMGR: "REC UNREAD","00480041004D005200410048004100560041004C","","21/08/20,13:30:29+18",129,100,0,8,"002B0039003800390031003100300030003500300030",145,236
    int x = m_serialBuffer.indexOf("+CMTI: ", 1);
    if(x > 0){
        x = m_serialBuffer.indexOf(",", x)+1;
        int16_t endVal = m_serialBuffer.indexOf("\r\n", x);
        int16_t smsIndex = m_serialBuffer.substring(x, endVal).toInt();
        
        //
        OnReceiveSMSMessage(this->ReadSMSByIndex(smsIndex));
        
        //delete sms age sms to simcard save shode bod
        // "SM",
        //if(m_serialBuffer.indexOf(" \"SM\",", 1) != NOTFOUND){
        DeleteSMSByIndex(smsIndex);
        //}
        
        return;
    }
    
    //+CMT: "00380034003100340077003400320035003100340038003400310034003600350031003400700034","","21/08/21,10:10:19+18"
    x = m_serialBuffer.indexOf("+CMT: ", 1);
    if(x > 0){
        x = m_serialBuffer.indexOf("\"", x)+1;
        int16_t endVal = m_serialBuffer.indexOf("\"", x);
        String msg = m_Unicode.FromUCS2(m_serialBuffer.substring(x, endVal));
        
        //
        //OnReceiveSMSMessage(this->ReadSMSByIndex(smsIndex));
        //ret.Name = m_Unicode.FromUCS2(msg);
        Serial.println(msg);
        
        //delete sms
        //DeleteSMSByIndex(smsIndex);
        return;
    }
    
    //+CUSD: 0, "06A9062F0020064806270631062F00200634062F0647002006460627062F06310633062A002006270633062A002E", 72
    x = m_serialBuffer.indexOf("+CUSD: ", 1);
    if(x > 0){
        x = m_serialBuffer.indexOf("\"", x)+1;
        if(x > 0){
            int16_t endVal = m_serialBuffer.indexOf("\"", x);
            
            //m_Unicode.FromUCS2(
            String Message = m_Unicode.FromUCS2(m_serialBuffer.substring(x, endVal));
            OnReceiveUSSDMessage(Message);
        }
        return;
    }
    
    //+CPIN: NOT READY
    //+CPIN: READY
    //+CPIN: NOT INSERTED
    x = m_serialBuffer.indexOf("+CPIN: ", 1);
    if(x > 0){
        if(m_serialBuffer.indexOf("NOT READY", x) >= 0){
            OnReceiveSIMCardDeavtive();
            return;
        }
        
        //OnReceiveSIMCardAvtive
        if(m_serialBuffer.indexOf(": READY", 4) >= 0){
            OnReceiveSIMCardAvtive();
            return;
        }
    }
    
    //+CSMINS: 0,1
    x = m_serialBuffer.indexOf("+CSMINS: ", 1);
    if(x > 0){
        x = m_serialBuffer.indexOf(",", x)+1;
        int16_t endVal = m_serialBuffer.indexOf("\r\n", x);
        
        if(x > 0){
            uint8_t status = m_serialBuffer.substring(x, endVal).toInt();
            if(status == 0){
                if(isRegisteredSim == true)
                    OnReceiveSIMCardDeavtive();
            }
            
            if(status == 1){
                if(isRegisteredSim == false)
                    OnReceiveSIMCardAvtive();
            }
        }
        return;
    }

    //in coming call
    //+CLIP: "+989194206610",145,"",0,"004D006F006A0074006100620061",0
    x = m_serialBuffer.indexOf("+CLIP: ", 1);
    if(x > 0){
      RejectCall();
      return;
    }

    //get operator name
    //+CIEV: 10,"43211","IR-MCI","IR-MCI", 0, 0
    
}

void SIM800L::OnReceiveSIMCardDeavtive(){
    Serial.println("\nOnReceiveSIMCardDeavtive");
    isRegisteredSim = false;
}

void SIM800L::OnReceiveSIMCardAvtive(){
    Serial.println("\nOnReceiveSIMCardAvtive");
    isRegisteredSim = true;
}

void SIM800L::OnReceiveSMSMessage(const SMSMessage &Message){
    Serial.print("\r\nOnReceiveSMSMessage, From:");
    Serial.println(Message.PhoneNumber);
    
    Serial.print("Name: ");
    Serial.println(Message.Name);
    
    Serial.print("Message: ");
    Serial.println(Message.Message);
}


void SIM800L::OnReceiveUSSDMessage(const String &Message){
    //اعتبار شما
    if(Message.indexOf("اعتبار شما") != NOTFOUND)
        OnReceiveCreaditMessage(Message);
}

void SIM800L::OnReceiveCreaditMessage(const String &Message){
    Serial.println(Message);
    SendSMS("09194206610", Message);
}

void SIM800L::CheckSerial() {
    
    while (m_pGSMSerial->available()) {
        //Serial.println("CheckSerial");
        //delay(10);
        m_serialBuffer = m_pGSMSerial->readString();
        
        //debug
        Serial.print("Buffer[");
        Serial.println(m_serialBuffer);
        Serial.print("]");
        
        //
        parsehCommands();
        m_serialBuffer.clear();
        
        // منتظر بایت بعدی باشید ، اگر بعد از این چیزی نیامد به این معنی است که متن قسمتی از یک جریان وارد شده توسط کاربر نبوده است.
        delay(1);
    }
    
    RegTimer += 1;
    if(RegTimer > NETWORK_CHECK_TIME) //30 sec
    {
        
        if(isRegisteredSim == false){
            ReStartGSM();
        }else{
            SendCheckRegisterNetwork();
        }
        
        RegTimer = 0;
    }
}


String SIM800L::ReadSerial(uint32_t timeout) {
    uint64_t timeOld = millis() + timeout;
    while (!m_pGSMSerial->available() && !(millis() > timeOld)) {
        delay(1);
    }
    
    String str = m_pGSMSerial->readString();
    /*
        Serial.print("\nReadSerial[");
        Serial.println(str);
        Serial.print("]");
        */
    /*
    while (m_pGSMSerial->available()) {
        if (m_pGSMSerial->available() > 0) {
            str += m_pGSMSerial->readString();
        }
    }
    */
    
    return str;
}
