#ifndef NONBLOCKINGIOINTERFACE_H
#define NONBLOCKINGIOINTERFACE_H

namespace cgdg
{
	namespace common
	{

class NonblockingIOInterface
{
public:
	enum {
		ERRORCODE_OTHER = -1,
		ERRORCODE_BLOCK = -2
	};
	virtual int read(void* pBuffer, unsigned nLength) = 0;
	virtual int write(const void* pBuffer, unsigned nLength) = 0;
};

	}
}

#endif
