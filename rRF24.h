#pragma once
#include "B4RDefines.h"
#include "RF24.h"
//~dependson: <SPI.h>
//~version: 1.00
namespace B4R {
	//~shortname: RF24
	//~Event: NewData (Data() As Byte)
	class B4RRF24 {
		private:
			uint8_t beRF[sizeof(RF24)];
			RF24* rf;
			SubVoidArray newDataSub;
			PollerNode pnode;
			static void looper(void* b);
			ArrayByte arr;
			Byte buffer[32];
		public:
			/**
			*Initializes the object.
			*CEPin - Pin connected to the CE pin.
			*CSPin - Pin connected to the CSN pin.
			*NewDataSub - Sub that will handle the NewData event.
			*/
			void Initialize(Byte CEPin, Byte CSPin, SubVoidArray NewDataSub);
			//Opens the reading pipe and set its address.
			void OpenReadingPipe(Byte Address);
			//Opens the writing pipe and set its address. Data will be sent to this address.
			void OpenWritingPipe(Byte Address);
			//Writes data to the address set in OpenWritingPipe. Maximum length is 32 bit.
			//Returns true if the data was sent successfully.
			bool Write(ArrayByte* Data);
			
	};
}