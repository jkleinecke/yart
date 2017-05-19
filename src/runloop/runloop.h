/**
 * runloop.h - Header file for run loops
 */
#pragma once

#include <vector>
#include <functional>

#include "../refcounted.h"

namespace yart {

	class RunLoop
	: public RefCounted
	{
	public:
		RunLoop() ;
	private:
		~RunLoop() ;

	public:
		void Execute() ;

		void AddWorker(std::function<void()> worker) ;
	private:

		std::vector< std::function<void()> > m_aWorkers ;
	} ;

}