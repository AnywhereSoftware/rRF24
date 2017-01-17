#include "B4RDefines.h"
namespace B4R {
	void B4RRF24::Initialize(Byte CEPin, Byte CSPin, SubVoidArray NewDataSub) {
		rf = new (beRF) RF24(CEPin, CSPin);
		this->newDataSub = NewDataSub;
		FunctionUnion fu;
		fu.PollerFunction = looper;
		pnode.functionUnion = fu;
		pnode.tag = this;
		arr.data = buffer;
		arr.length = 32;
		rf->begin();
	}
	void B4RRF24::OpenReadingPipe(Byte Address) {
		rf->openReadingPipe(1, 0xABCDABCD00LL | Address);
		if (pnode.next == NULL)
			pollers.add(&pnode);
		rf->startListening();
		
	}
	void B4RRF24::OpenWritingPipe(Byte Address) {
		rf->openWritingPipe(0xABCDABCD00LL | Address);
	}
	bool B4RRF24::Write(ArrayByte* Data) {
		rf->stopListening();
		bool b = rf->write(Data->data, Data->length);
		rf->startListening();
		return b;
	}
	void B4RRF24::looper(void* b) {
		B4RRF24* me = (B4RRF24*)b;
		if (me->rf->available()) {
			me->rf->read(me->arr.data, me->arr.length);
			me->newDataSub(&me->arr);
		}
	}
}