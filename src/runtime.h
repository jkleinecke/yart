/**
 * runtime.h - standard runtime includes
 */

#ifndef ASSERT

#ifdef DEBUG
	#include <assert.h>
	#define ASSERT(cond) assert(cond)
#else
	#define ASSERT
#endif

#endif

#ifndef BREAK
#define BREAK() ASSERT(false)
#endif

#ifndef VERIFY
#include <assert.h>
#define VERIFY(cond) assert(cond)
#endif
