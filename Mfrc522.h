/*
	File: Mfrc522.h
	Mfrc522 - Library for communicating with MFRC522 based NFC Reader/Writers
	Created by Eelco Rouw - Mainly based on code from Grant Gibson (www.grantgibson.co.uk) and Dr.Leong ( WWW.B2CQSHOP.COM )
	Lightly modified by Frank Milburn
	Released into the public domain
*/
#ifndef Mfrc522_h
#define Mfrc522_h

#include "Energia.h"

/*
	MFRC522 and Card specific defines. For the role of each define, please consult the datasheet.
*/

#define MAX_LEN	16

//MF522 - Commands
#define PCD_IDLE              0x00               
#define PCD_AUTHENT           0x0E               
#define PCD_RECEIVE           0x08               
#define PCD_TRANSMIT          0x04               
#define PCD_TRANSCEIVE        0x0C               
#define PCD_RESETPHASE        0x0F               
#define PCD_CALCCRC           0x03               

//Mifare_One - Commands
#define PICC_REQIDL           0x26
#define PICC_REQALL           0x52
#define PICC_ANTICOLL         0x93
#define PICC_SElECTTAG        0x93
#define PICC_AUTHENT1A        0x60
#define PICC_AUTHENT1B        0x61
#define PICC_READ             0x30
#define PICC_WRITE            0xA0
#define PICC_DECREMENT        0xC0
#define PICC_INCREMENT        0xC1
#define PICC_RESTORE          0xC2
#define PICC_TRANSFER         0xB0
#define PICC_HALT             0x50

//MF522 - Status
#define MI_OK                 0
#define MI_NOTAGERR           1
#define MI_ERR                2

//MF522 - Registers
//Page 0:Command and Status
#define     Reserved00            0x00    
#define     CommandReg            0x01    
#define     CommIEnReg            0x02    
#define     DivlEnReg             0x03    
#define     CommIrqReg            0x04    
#define     DivIrqReg             0x05
#define     ErrorReg              0x06    
#define     Status1Reg            0x07    
#define     Status2Reg            0x08    
#define     FIFODataReg           0x09
#define     FIFOLevelReg          0x0A
#define     WaterLevelReg         0x0B
#define     ControlReg            0x0C
#define     BitFramingReg         0x0D
#define     CollReg               0x0E
#define     Reserved01            0x0F

//Page 1:Command     
#define     Reserved10            0x10
#define     ModeReg               0x11
#define     TxModeReg             0x12
#define     RxModeReg             0x13
#define     TxControlReg          0x14
#define     TxAutoReg             0x15
#define     TxSelReg              0x16
#define     RxSelReg              0x17
#define     RxThresholdReg        0x18
#define     DemodReg              0x19
#define     Reserved11            0x1A
#define     Reserved12            0x1B
#define     MifareReg             0x1C
#define     Reserved13            0x1D
#define     Reserved14            0x1E
#define     SerialSpeedReg        0x1F

//Page 2:CFG    
#define     Reserved20            0x20  
#define     CRCResultRegM         0x21
#define     CRCResultRegL         0x22
#define     Reserved21            0x23
#define     ModWidthReg           0x24
#define     Reserved22            0x25
#define     RFCfgReg              0x26
#define     GsNReg                0x27
#define     CWGsPReg	          0x28
#define     ModGsPReg             0x29
#define     TModeReg              0x2A
#define     TPrescalerReg         0x2B
#define     TReloadRegH           0x2C
#define     TReloadRegL           0x2D
#define     TCounterValueRegH     0x2E
#define     TCounterValueRegL     0x2F

//Page 3:TestRegister     
#define     Reserved30            0x30
#define     TestSel1Reg           0x31
#define     TestSel2Reg           0x32
#define     TestPinEnReg          0x33
#define     TestPinValueReg       0x34
#define     TestBusReg            0x35
#define     AutoTestReg           0x36
#define     VersionReg            0x37
#define     AnalogTestReg         0x38
#define     TestDAC1Reg           0x39  
#define     TestDAC2Reg           0x3A   
#define     TestADCReg            0x3B   
#define     Reserved31            0x3C   
#define     Reserved32            0x3D   
#define     Reserved33            0x3E   
#define     Reserved34			  0x3F


class Mfrc522
{
	public:
		Mfrc522(int chipSelectPin, int NRSTPD);
		void WriteReg(unsigned char addr, unsigned char val);
		unsigned char ReadReg(unsigned char addr);
		void SetBitMask(unsigned char reg, unsigned char mask);
		void ClearBitMask(unsigned char reg, unsigned char mask);
		void AntennaOn(void);
		void AntennaOff(void);
		void Reset(void);
		void Init(void);
		unsigned char Request(unsigned char reqMode, unsigned char *TagType);
		unsigned char ToCard(unsigned char command, unsigned char *sendData, unsigned char sendLen, unsigned char *backData, unsigned int *backLen);
		unsigned char Anticoll(unsigned char *serNum);
		void CalulateCRC(unsigned char *pIndata, unsigned char len, unsigned char *pOutData);
		unsigned char SelectTag(unsigned char *serNum);
		unsigned char Auth(unsigned char authMode, unsigned char BlockAddr, unsigned char *Sectorkey, unsigned char *serNum);
		unsigned char ReadBlock(unsigned char blockAddr, unsigned char *recvData);
		unsigned char WriteBlock(unsigned char blockAddr, unsigned char *writeData);
		void Halt(void);
	private:
		int _chipSelectPin;
		int _NRSTPD;
};

#endif
