#include "PoolAllocator.hpp"

#include "HyperCore/Core.hpp"

namespace Hyperion
{
	PoolAllocator::PoolAllocator(size_t totalSize, size_t chunkSize)
		: m_TotalSize(totalSize), m_ChunkSize(chunkSize)
	{
		m_StartPtr = malloc(m_Size);
	}

	PoolAllocator::~PoolAllocator()
	{
		free(m_StartPtr);
	}

	void* PoolAllocator::Allocate(const size_t allocationSize, const size_t alignment)
	{
		HP_CORE_ASSERT(allocationSize == m_ChunkSize, "Allocation size must be equal to chunk size");

		FreeHeader freePosition = m_FreeList.peek();
		m_FreeList.pop();

		HP_CORE_ASSERT(freePosition.Ptr != nullptr, "The pool allocator is full");

		m_Size++;
		m_Capacity += m_ChunkSize;

		return (void*) freePosition.Ptr;
	}

	void PoolAllocator::Free(void* ptr)
	{
		m_Size -= 1;
		m_Capacity -= m_ChunkSize;

		FreeHeader header = { ptr };
		m_FreeList.push(header);
	}

	void PoolAllocator::Reset()
	{
		m_Size = 0;
		m_Capacity = 0;

		const size_t chunks = m_TotalSize / m_ChunkSize;
		for (size_t i = 0; i < chunks; i++)
		{
			size_t address = (size_t)m_StartPtr + i * m_ChunkSize;
			FreeHeader header = { (void*)address };
			m_FreeList.push(header);
		}
	}
}
