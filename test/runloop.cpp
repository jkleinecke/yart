#include "gtest/gtest.h"

#include "runloop/runloop_mgr.h"

using namespace yart ;

TEST(RunLoop, OneWorker)
{
	RunLoop* loop = new RunLoop() ;

	int i = 0;

	// add a simple worker that increments i
	loop->AddWorker([&]{	++i; }) ;

	// now let the loop execute
	loop->Execute() ;

	ASSERT_TRUE(i == 1) ;

	loop->Release() ;
}

TEST(RunLoop, TwoWorkers)
{
	RunLoop* loop = new RunLoop() ;

	int i = 0;

	// add a simple worker that increments i
	loop->AddWorker([&]{	++i; }) ;
	loop->AddWorker([&]{	++i; }) ;

	// now let the loop execute
	loop->Execute() ;

	ASSERT_TRUE(i == 2) ;

	loop->Release() ;
}

TEST(RunLoop, Manager)
{
	RunLoopManager mgr ;

	ASSERT_TRUE(mgr.GetCurrentRunLoop() == nullptr) ;
	ASSERT_TRUE(mgr.CreateRunLoop()) ;
	ASSERT_TRUE(mgr.GetCurrentRunLoop() != nullptr) ;
	ASSERT_FALSE(mgr.CreateRunLoop()) ;					// make sure only one is allowed per thread
}