#ifndef THREAD_POOL_P_HPP
#define THREAD_POLL_P_HPP

#include<iostream>
#include<thread>
#include<mutex>
#include<future>
#include<condition_variable>
#include<functional>
#include<new>
#include<memory>
#include<vector>
#include<queue>
#include<type_traits>

#define PROIRITY_ON
//#define THREAD_POOL_ENABLE_TEST
//#define THREAD_INFO

#ifdef PROIRITY_ON

#define PROIRITY_PARAMETERS_INPUT ,int priority
#define PROIRITY_PARAMETERS_OUTPUT ,priority

#else
	
#define PROIRITY_PARAMETERS_INPUT
#define PROIRITY_PARAMETERS_OUTPUT

#endif

#include "thread_pool_util.h"


#ifdef THREAD_POOL_ENABLE_TEST

#define TEST(value) std::cout<<value<<std::endl;
#define COUT(value)\
{\
std::scoped_lock lock{ this->output_mutex };\
std::cout << "(thread) id: " << std::this_thread::get_id() << std::endl;\
TEST(value)\
}
#endif // THREAD_POOL_ENABLE_TEST


#define AUTOINTERFACE(Name,Type)\
private:\
Type Name;\
public:\
Type\
 get##Name() { return Name; }\
void\
 set##Name(Type value){Name=value;}

#ifdef THREAD_POOL_ENABLE_TEST
int process_tasks;
#endif


class ThreadPoolP;
class ThreadInfo {
	friend ThreadPoolP;
public:
	int process_tasks{};
	std::thread::id thread_id;
};

class ThreadPoolInfo {
public:
	friend ThreadPoolP;
};


#ifdef THREAD_POOL_ENABLE_TEST
thread_local ThreadInfo thread_info;
thread_local ThreadPoolInfo thread_pool_info;
#endif

/**
* 
* 线程池
* 
* 先写一个简陋的框架,以后有需要再进行细节修饰
* 
*/
class [[nodiscard("may result in invalid create")]] ThreadPoolP {
	//thread nums
	using concurrency_t = std::invoke_result_t<decltype(std::thread::hardware_concurrency)>;
public:
	ThreadPoolP()noexcept;
	ThreadPoolP(concurrency_t thread_nums)noexcept;
	ThreadPoolP(std::function<void()>)noexcept;
	ThreadPoolP(concurrency_t thread_nums,std::function<void()>)noexcept;

	ThreadPoolP(ThreadPoolP&&) = delete;
	ThreadPoolP(const ThreadPoolP&) = delete;
	ThreadPoolP operator=(ThreadPoolP&&) = delete;
	ThreadPoolP operator=(const ThreadPoolP&) = delete;

	~ThreadPoolP()noexcept;

	template<typename F,typename R=std::invoke_result_t<F>>
	[[nodiscard("may result in invalid submissions")]] std::future<R> submit_task(F&& task PROIRITY_PARAMETERS_INPUT);

	void pause()noexcept;
	void unpause()noexcept;
	void wait()noexcept;
public:

private:
	void storage_task(std::function<void()> PROIRITY_PARAMETERS_INPUT);
	
	void createThreads(std::function<void()>&);

	void worker(std::function<void()> init_task);

	void init();

private:
	enum class Status:short{Stop,Running};
	//
	const concurrency_t max_threads = std::thread::hardware_concurrency();
	concurrency_t current_threads;
	//be accountable for the task
	std::mutex task_mutex;
	//be accountable for the thread status
	std::mutex status_mutex;
	//be accountable for the task
	std::condition_variable task_cv;
	//be accountable for the thread status
	std::condition_variable status_cv;

	int running_tasks;

	Status current_status = Status::Running;
	AUTOINTERFACE(IsPaused, bool);
	AUTOINTERFACE(Waiting, bool);

	
#ifdef PROIRITY_ON
	std::priority_queue<PriorityTask,std::vector<PriorityTask>,std::less<PriorityTask>> tasks;
#else
	//task queue
	std::queue<std::function<void()>> tasks;
#endif

	std::vector<std::thread> threads;
	
#ifdef THREAD_POOL_ENABLE_TEST
	std::mutex output_mutex;
#endif // THREAD_POOL_ENABLE_TEST 
#ifdef THREAD_INFO
	std::mutex thread_info_cout_mutex;
#endif
	
};

inline ThreadPoolP::ThreadPoolP()noexcept :ThreadPoolP(max_threads, [] {}) {}

inline ThreadPoolP::ThreadPoolP(concurrency_t thread_nums)noexcept : ThreadPoolP(thread_nums, [] {}) {}

inline ThreadPoolP::ThreadPoolP(std::function<void()> f) noexcept :ThreadPoolP(max_threads, f) {}

inline ThreadPoolP::ThreadPoolP(concurrency_t thread_nums, std::function<void()> f)noexcept
{
	thread_nums = std::min(thread_nums, this->max_threads);
	this->current_threads = thread_nums;
	init();
	createThreads(f);
}

inline ThreadPoolP::~ThreadPoolP() noexcept
{
	this->current_status = Status::Stop;
	this->task_cv.notify_all();
	for (int i = 0; i < threads.size(); i++)
		threads[i].join();
}

inline void ThreadPoolP::pause() noexcept
{
	std::scoped_lock lock{ this->task_mutex };
	setIsPaused(true);
}

inline void ThreadPoolP::unpause() noexcept
{
	{
		std::scoped_lock lock{ this->task_mutex };
		setIsPaused(false);
	}
	this->task_cv.notify_all();
}

inline void ThreadPoolP::wait() noexcept
{
	std::unique_lock lock(this->status_mutex);
	setWaiting(true);

	this->status_cv.wait(lock, [this]()->bool {
		std::cout << "this?" << std::endl;
#ifdef THREAD_POOL_ENABLE_TEST
		COUT((running_tasks == 0))
			COUT((running_tasks))
			COUT((getIsPaused() || tasks.empty()))
			COUT(((running_tasks == 0) && (getIsPaused() || tasks.empty())))
#endif // THREAD_POOL_ENABLE_TEST

			return (running_tasks == 0) && (getIsPaused() || tasks.empty());
		});

	setWaiting(false);
}


inline void ThreadPoolP::storage_task(std::function<void()> f PROIRITY_PARAMETERS_INPUT)
{	/**
	*
	*/
	//COUT("here is storage_task")
	{
		std::scoped_lock sc{ this->task_mutex };
#ifdef PROIRITY_ON
		//this->tasks.emplace(std::move(f) PROIRITY_PARAMETERS_OUTPUT);
		this->tasks.push(PriorityTask(f PROIRITY_PARAMETERS_OUTPUT));
#else
		this->tasks.push(std::move(f));
#endif

	}
	this->task_cv.notify_one();

}

inline void ThreadPoolP::createThreads(std::function<void()>& f)
{
	//std::scoped_lock lock( this->task_mutex,this->status_mutex);
	//this->running_tasks=this
	for (int i = 1; i <= this->current_threads; i++)
		threads.emplace_back(&ThreadPoolP::worker, this, f);
}

inline void ThreadPoolP::worker(std::function<void()> init_task)
{
	init_task();
	{
		std::unique_lock task_lock{ this->task_mutex };
#ifdef PROIRITY_ON
		//PriorityTask task([]{},1);
#endif
		while (true) {
			--this->running_tasks;
#ifdef THREAD_POOL_ENABLE_TEST
			thread_info.process_tasks++;
#endif
#ifdef THREAD_POOL_ENABLE_TEST
			{
				std::scoped_lock lock{ this->output_mutex };
				std::cout << "(thread) id: " << std::this_thread::get_id() << std::endl;
				TEST((getWaiting() && (running_tasks == 0) && (tasks.empty() || getIsPaused())))
			}
#endif // THREAD_POOL_ENABLE_TEST

			//status judge
			task_lock.unlock();
			if (getWaiting() && (running_tasks == 0) && (tasks.empty() || getIsPaused()))
				this->status_cv.notify_all();
			task_lock.lock();
			//task pulling or exit
			this->task_cv.wait(task_lock,
				// want  exit  or no paused and empty 
				[this]()->bool {
					return current_status == Status::Stop || !(tasks.empty() || getIsPaused());
				});
			if (this->current_status == Status::Stop)
				break;
#ifdef PROIRITY_ON
			//PriorityTask task = std::move(std::remove_const_t<PriorityTask&>(this->tasks.top()));
			//task = this->tasks.top();
#ifdef THREAD_POOL_ENABLE_TEST
			try
			{
#endif
				this->tasks.top().f();
#ifdef THREAD_POOL_ENABLE_TEST
			}
			catch (const std::exception& e)
			{
				COUT(e.what())
			}
#endif
#else 
			std::function<void()> task = std::move(this->tasks.front());
#endif
			++this->running_tasks;
			this->tasks.pop();
			task_lock.unlock();
#ifdef THREAD_POOL_ENABLE_TEST
			try {
#endif // THREAD_POOL_ENABLE_TEST
#ifdef PROIRITY_ON
				//task.f();
#else
				task();
#endif // PROIRITY_ON



#ifdef THREAD_POOL_ENABLE_TEST
			}
			catch (const std::exception& e) {
				COUT(e.what())
			}
#endif // THREAD_POOL_ENABLE_TEST
			//TEST("here?");

			task_lock.lock();
		}
	}

#ifdef THREAD_INFO
	{
		std::scoped_lock lock{ this->thread_info_cout_mutex };
		std::cout << "(thread exit) id: " << std::this_thread::get_id() << std::endl;
		std::cout << "process task nums: " << thread_info.process_tasks << std::endl;
		process_tasks += thread_info.process_tasks;
	}
#endif // THREAD_INFO
}

inline void ThreadPoolP::init()
{
	{
		std::scoped_lock lock(this->task_mutex);
		this->current_status = Status::Running;
		setIsPaused(false);
		setWaiting(false);
		this->running_tasks = this->current_threads;

	}
}

template<typename F, typename R>
inline std::future<R> ThreadPoolP::submit_task(F&& task PROIRITY_PARAMETERS_INPUT)
{
	//build future
	const std::shared_ptr<std::promise<R>> task_promise = std::make_shared<std::promise<R>>();
	//COUT("here is submit_task")
	//storage task
	storage_task([task = std::forward<F>(task), task_promise] {

		//constexpr is must
		if constexpr (std::is_void_v<R>) {
			task();
			task_promise->set_value();
		}
		else {
			task_promise->set_value(task());
		}
		} PROIRITY_PARAMETERS_OUTPUT);
	return task_promise->get_future();
}

#endif //THREAD_POOL_P_H




