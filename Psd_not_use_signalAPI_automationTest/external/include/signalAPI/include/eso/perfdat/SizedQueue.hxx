#ifndef PERFDAT_SIZEDQUEUE_HXX_
#define PERFDAT_SIZEDQUEUE_HXX_

/*
    Copyright esolutions GmbH
    All rights reserved
    Authors:
		Stefan Bittner
*/

#include <common/types/deque.hxx>
#include <osal/Mutex.hxx>
#include <osal/Condition.hxx>
#include <util/MutexGuard.hxx>


namespace perfdat {
	/**
	 *  \brief
	 *      A queue of limited size.
	 *      If the queue is full no new entries van be made.
	 **/
	template <typename S>
		class SizedQueue {
			public:
				// Constructor with capacity
				SizedQueue(size_t capacity);

				~SizedQueue();

				// Puts sample to the end. Returns false in case of success.
				bool put(const S& sample);

				// Gets and removes the oldest sample, blocks if the queue is empty
				// returns false if a sample was read, returns true if woken up - sample is not
				// touched then.
				bool get(S& sample);

				//! wakes a potential blocking caller in get.
				void wakeup();

				//! returns the queue capacity
				size_t capacity() const { return m_capacity; }

				//! returns the current queue size
				size_t size() const;

				//! returns the number of items that were retrieved from the queue
				size_t passed() const;
			private:
				typedef ipl::deque< S > Queue;
				size_t			m_capacity;
				Queue			m_q;
				osal::Mutex		m_lock;
				osal::Condition	m_condvar;
				bool			m_woken;
				size_t			m_passed;
		};

	template <typename S>
		SizedQueue<S>::SizedQueue(size_t capacity)
		: m_capacity(capacity)
		, m_woken(false)
		, m_passed(0)
	{
	}

	template <typename S>
	SizedQueue<S>::~SizedQueue() {
	}

	template <typename S>
	bool SizedQueue<S>::put(const S& sample) {
		util::MutexGuard guard(m_lock);
		if ( m_q.size() == m_capacity ) {
			return true;
		}
		m_q.push_back(sample);
		m_condvar.signal();
		return false;
	}

	template <typename S>
	bool SizedQueue<S>::get(S& sample) {
		util::MutexGuard guard(m_lock);
		while( m_q.empty() && !m_woken ) {
			m_condvar.wait(m_lock);
		}
		if ( m_woken ) {
			m_woken = false;
			return true;
		}
		sample = m_q.front();
		m_q.pop_front();
		m_passed++;
		return false;
	}

	template <typename S>
	void SizedQueue<S>::wakeup() {
		util::MutexGuard guard(m_lock);
		m_woken = true;
		m_condvar.signal();
	}

	template <typename S>
	size_t SizedQueue<S>::size() const {
		util::MutexGuard guard(m_lock);
		return m_q.size();
	}

	template <typename S>
	size_t SizedQueue<S>::passed() const {
		util::MutexGuard guard(m_lock);
		return m_passed;
	}
}

#endif // PERFDAT_SIZEDQUEUE_HXX_

