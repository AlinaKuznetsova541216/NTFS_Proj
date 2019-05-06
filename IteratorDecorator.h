//---------------------------------------------------------------------------

#ifndef IteratorDecoratorH
#define IteratorDecoratorH
#include "Iterator.h"
#include <string>
#include <windows.h>
//---------------------------------------------------------------------------
class IteratorDecorator : public Iterator<BYTE *>
{
protected:
	Iterator<BYTE> * Iterat;
	IteratorDecorator() {}
public:
	IteratorDecorator(Iterator<BYTE> * it) {Iterat = it;}
	virtual ~IteratorDecorator(){delete Iterat;}
	virtual void First(){Iterat->First();}
	virtual void Next(){Iterat->Next();}
	virtual bool IsDone(){return Iterat->IsDone();}
	virtual BYTE * GetCurrent(){return (unsigned char *)Iterat->GetCurrent();}
	virtual void GetCurrent(BYTE **dataBuffer){Iterat->GetCurrent(*dataBuffer);}
};
#endif
