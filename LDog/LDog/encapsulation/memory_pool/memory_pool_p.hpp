#ifndef MEMORY_POOL_P_H
#define MEMORY_POLL_P_H

//#define MEMORY_POOL_TEST

#define TEST(message) std::cout<<message<<std::endl;

/**
* 
* 内存池,每次申请相对于申请类型来说数倍的内存空间,优化频繁申请与释放操作
* 
*/
template<typename T,size_t BlockSize = 4096>
class MemoryPoolP {
public:
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef const T* const_pointer;
	typedef const T& const_reference;
public:
	MemoryPoolP()noexcept;
	MemoryPoolP(const MemoryPoolP&) = delete;
	~MemoryPoolP()noexcept;
	pointer allocate()noexcept;
	void deallocate(pointer)noexcept;
private:

	/**
	* Responsible for storing data and block indexes
	*/
	union Slot_ {
		value_type element;
		Slot_* next_data_block;
	};

	typedef char* data_pointer;
	typedef Slot_ slot_type;
	typedef Slot_* slot_pointer;

	size_t padSize(data_pointer p, size_t align)const noexcept;
	void allocateBlock()noexcept;


	slot_pointer current_block;
	slot_pointer current_slot;
	slot_pointer last_slot;
	slot_pointer free_slot;

};

#endif // !MEMORY_POOL_P_H

/**
*
* 
*
*/
template<typename T, size_t BlockSize>
inline MemoryPoolP<T, BlockSize>::MemoryPoolP()noexcept
{
	this->current_block = nullptr;
	this->current_slot = nullptr;
	this->last_slot = nullptr;
	this->free_slot = nullptr;
}
/**
*
*
*
*/
template<typename T, size_t BlockSize>inline MemoryPoolP<T, BlockSize>::~MemoryPoolP() noexcept
{
	while (current_block != nullptr) {
#ifdef MEMORY_POOL_TEST
		std::cout << "deallocate block" << std::endl;
#endif // MEMORY_POOL_TEST
		slot_pointer prev = current_block->next_data_block;
		operator delete(reinterpret_cast<void*>(current_block));
		current_block = prev;
	}
}
/**
*
*
*
*/
template<typename T, size_t BlockSize>
inline MemoryPoolP<T,BlockSize>::pointer MemoryPoolP<T, BlockSize>::allocate() noexcept
{
	if (this->free_slot!= nullptr) {
		slot_pointer source = free_slot;
		free_slot = source->next_data_block;
		return reinterpret_cast<pointer>(source);
	}
	if (current_slot >= last_slot) {
		allocateBlock();
	}

	return reinterpret_cast<pointer>(current_slot++);
}
/**
*
*
*
*/
template<typename T, size_t BlockSize>
inline void MemoryPoolP<T, BlockSize>::deallocate(pointer p)noexcept
{
	reinterpret_cast<slot_pointer>(p)->next_data_block = this->free_slot;
	free_slot = reinterpret_cast<slot_pointer>(p);
}

/**
*
*
*
*/
template<typename T, size_t BlockSize>
inline size_t MemoryPoolP<T, BlockSize>::padSize(data_pointer p, size_t align)const noexcept
{
	size_t addr = reinterpret_cast<size_t>(p);
	return (addr % align);
}
/**
*
*
*
*/
template<typename T, size_t BlockSize>
inline void MemoryPoolP<T, BlockSize>::allocateBlock()noexcept
{
#ifdef MEMORY_POOL_TEST
	std::cout << "allocate block" << std::endl;
#endif // MEMORY_POOL_TEST

	//Allocate a new block
	data_pointer new_block = reinterpret_cast<data_pointer>(operator new(BlockSize));
	//create block index
	reinterpret_cast<slot_pointer>(new_block)->next_data_block = current_block;
	//update current block
	current_block = reinterpret_cast<slot_pointer>(new_block);
	//align
	data_pointer original_slot_addr = new_block + sizeof(slot_pointer);
	size_t offset = padSize(original_slot_addr, alignof(slot_type));
	current_slot = reinterpret_cast<slot_pointer>(original_slot_addr + offset);
	last_slot = reinterpret_cast<slot_pointer> (new_block + BlockSize - sizeof(slot_type) + 1);
}
