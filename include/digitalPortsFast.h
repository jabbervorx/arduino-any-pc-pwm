#ifndef __DIGITAL_PORTS_FAST_H
#define __DIGITAL_PORTS_FAST_H

#include <avr/io.h>

#define portWrite(set,mask,port) do {\
		byte state = port;\
		state &= ~mask;\
		state |= set;\
		port = state;\
	} while(0)

#define _digitalWriteFast(P, V) \
	do {\
		if((P) < 8)\
			portWrite((V) << (P),_BV(P), PORTD);\
		else if((P) < 14)\
			portWrite((V) << ((P)-8),_BV((P)-8), PORTB);\
		else\
			portWrite((V) << ((P)-14),_BV((P)-14), PORTC);\
	} while(0)

#define portRead(bit,pin,ret) do {\
		ret = pin;\
		ret >>= bit;\
		ret &= 1;\
	} while(0)

#define _digitalReadFast(P, ret) do {\
	if((P) < 8)\
		portRead((P), PIND, ret);\
	else if((P) < 14)\
		portRead((P)-8, PINB, ret);\
	else\
		portRead((P)-14, PINC, ret);\
	} while(0)


#define _pinModeFast(P, V) \
	do {\
		if((P) < 8)\
			portWrite((V) << (P),_BV(P), DDRD);\
		else if((P) < 14)\
			portWrite((V) << ((P)-8),_BV((P)-8), DDRB);\
		else\
			portWrite((V) << ((P)-14),_BV((P)-14), DDRC);\
	} while(0)

static inline byte digitalReadFast(byte pin) {
	byte ret;
	_digitalReadFast(pin, ret);
	return ret;
}

static inline void digitalWriteFast(byte pin, byte value) {
	_digitalWriteFast(pin, value);
}

static inline void pinModeFast(byte pin, byte value) {
	_pinModeFast(pin, value);
}

#endif /* __DIGITAL_PORTS_FAST_H */
