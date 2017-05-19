#include "gtest/gtest.h"

#include "refcounted.h"

class TestRefCount 
	: public yart::RefCounted
{
public:
	TestRefCount() {}
	~TestRefCount() { *m_TestValue = 0; }

	int* m_TestValue ;
} ;

TEST(RefCount, TestRelease)
{
	TestRefCount* pRef = new TestRefCount() ;

	int nValue = 1 ;
	pRef->m_TestValue = &nValue ;

	pRef->Release() ;

	ASSERT_TRUE(nValue == 0) ;
}