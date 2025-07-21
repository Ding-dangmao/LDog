#ifndef THREAD_POOL_UTIL_H
#define THREAD_POOL_UTIL_H

#ifdef PROIRITY_ON

#include<functional>

class PriorityTask {
public:

	PriorityTask() = delete;
	//PriorityTask(std::function<void()>&& f)noexcept;
	PriorityTask(std::function<void()>&& f, int prio_level)noexcept;
	PriorityTask(std::function<void()> f, int prio_level)noexcept;

	//PriorityTask operator=(const PriorityTask& task)noexcept;
	//PriorityTask(const PriorityTask& task)noexcept;
	//PriorityTask(PriorityTask&& prio_task)noexcept;

	bool operator<(const PriorityTask&)const;
	void operator()();

	std::function<void()> f;
	int priority_level;
};


//PriorityTask::PriorityTask(std::function<void()>&& f)noexcept :PriorityTask(std::move(f), 0) {}
//
inline PriorityTask::PriorityTask(std::function<void()>&& f, int prio_level)noexcept :
	f(std::move(f)), priority_level(prio_level) {}

inline PriorityTask::PriorityTask(std::function<void()> f, int prio_level) noexcept:
	f(f),priority_level(prio_level){}

//PriorityTask PriorityTask::operator=(const PriorityTask& prio_task)noexcept
//{
//	return PriorityTask(prio_task.f, prio_task.priority_level);
//}
//
//inline PriorityTask::PriorityTask(const PriorityTask& task) noexcept
//{
//	this->f = task.f;
//	this->priority_level = task.priority_level;
//}

//PriorityTask::PriorityTask(PriorityTask&& prio_task)noexcept
//{
//	this->f = std::move(prio_task.f);
//	this->priority_level = prio_task.priority_level;
//}

inline bool PriorityTask::operator<(const PriorityTask& task) const
{
	return this->priority_level < task.priority_level;
}

inline void PriorityTask::operator()() {
	f();
}

#endif //PROIRITY_ON

#endif //THREAD_POOL_UTIL_H