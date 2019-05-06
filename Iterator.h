//---------------------------------------------------------------------------
#ifndef IteratorH
#define IteratorH
//---------------------------------------------------------------------------
template <class Type>
class Iterator
{
protected:
	Iterator() {}
public:
	virtual ~Iterator(){}
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() const = 0;
	virtual Type GetCurrent() = 0;
	virtual void GetCurrent(Type *outBuffer) = 0;
};
#endif
