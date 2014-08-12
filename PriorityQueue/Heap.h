#ifndef Heap_h
#define Heap_h

#include "PriorityQueue.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T, typename K>
class Heap : public PriorityQueue<T,K>
{
public:
	// Heap
	class Element : public PriorityQueue<T,K>::Element
	{
	public:
		// Element
		virtual ~Element();
		virtual T& Value() override;
		virtual const K& Key() override;
	
	protected:
		Element();
		Element(const T& t, const K& key, const size_t kuIndex);
		Element(const Element& element);

		void UpdateKey(const K& key);

		size_t Index() const;
		void UpdateIndex(const size_t kuIndex);

		friend Heap;

		T m_t;
		K m_key;
		size_t m_uIndex;
	};

	virtual ~Heap() override;
	virtual std::shared_ptr<typename PriorityQueue<T,K>::Element> InsertElementWithKey(const T& t, const K& key) override;
	virtual std::shared_ptr<typename PriorityQueue<T,K>::Element> MaximumElement() const override;
	virtual std::shared_ptr<typename PriorityQueue<T,K>::Element> ExtractMaximumElement() override;
	virtual void IncreaseElementKey(typename PriorityQueue<T,K>::Element* pElement, const K& key) override;

private:
	size_t ParentIndexForChildIndex(const size_t kuChildIndex) const;
	size_t LeftChildIndexForParentIndex(const size_t kuParentIndex) const;
	size_t RightChildIndexForParentIndex(const size_t kuParentIndex) const;

	std::vector<std::shared_ptr<Element>> m_aHeap;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T, typename K>
Heap<T,K>::Element::~Element()
{
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T, typename K>
T&
Heap<T,K>::Element::Value()
{
	return m_t;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T, typename K>
const K&
Heap<T,K>::Element::Key()
{
	return m_key;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T, typename K>
Heap<T,K>::Element::Element()
{
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T, typename K>
Heap<T,K>::Element::Element(const T& t, const K& key, const size_t kuIndex) :
	m_t(t),
	m_key(key),
	m_uIndex(kuIndex)
{
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T, typename K>
void
Heap<T,K>::Element::UpdateKey(const K& key)
{
	m_key = key;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T, typename K>
size_t
Heap<T,K>::Element::Index() const
{
	return m_uIndex;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T, typename K>
void 
Heap<T,K>::Element::UpdateIndex(const size_t kuIndex)
{
	m_uIndex = kuIndex;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T, typename K>
Heap<T,K>::~Heap()
{
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T, typename K>
std::shared_ptr<typename PriorityQueue<T,K>::Element>
Heap<T,K>::InsertElementWithKey(const T& t, const K& key)
{
	size_t uIndex = m_aHeap.size();
	assert( uIndex < std::numeric_limits<size_t>::max() );

	std::shared_ptr<Element> pElement(new Element(t, key, uIndex));
	m_aHeap.push_back(pElement);

	IncreaseElementKey(pElement.get(), key);

	return pElement;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T, typename K>
std::shared_ptr<typename PriorityQueue<T,K>::Element>
Heap<T,K>::MaximumElement() const
{
	if ( m_aHeap.size() == 0 )
		return nullptr;

	return m_aHeap[0];
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T, typename K>
std::shared_ptr<typename PriorityQueue<T,K>::Element>
Heap<T,K>::ExtractMaximumElement()
{
	size_t kuHeapSize = m_aHeap.size();
	if ( kuHeapSize == 0 )
		return nullptr;

	std::shared_ptr<Element> pElement(m_aHeap[0]);

	size_t uIndex = 0;
	const size_t kuLastElementIndex = kuHeapSize - 1;
	
	m_aHeap[uIndex] = m_aHeap[kuLastElementIndex];
	m_aHeap[uIndex]->UpdateIndex(uIndex);

	m_aHeap.pop_back();
	kuHeapSize--;

	if ( kuHeapSize > 0 )
	{
		while ( uIndex < (kuHeapSize - 1) )
		{
			size_t uLargestKeyIndex = uIndex;
			size_t uLeftChildIndex = LeftChildIndexForParentIndex(uIndex);
			size_t uRightChildIndex = RightChildIndexForParentIndex(uIndex);

			if ( uLeftChildIndex < kuHeapSize && 
			     m_aHeap[uLeftChildIndex]->Key() > m_aHeap[uLargestKeyIndex]->Key() )
				uLargestKeyIndex = uLeftChildIndex;

			if ( uRightChildIndex < kuHeapSize && 
			     m_aHeap[uRightChildIndex]->Key() > m_aHeap[uLargestKeyIndex]->Key() )
				uLargestKeyIndex = uRightChildIndex;

			if ( uLargestKeyIndex == uIndex )
				break;

			std::shared_ptr<Element> pTempElement(m_aHeap[uIndex]);
			
			m_aHeap[uIndex] = m_aHeap[uLargestKeyIndex];
			m_aHeap[uIndex]->UpdateIndex(uIndex);

			m_aHeap[uLargestKeyIndex] = pTempElement;
			pTempElement->UpdateIndex(uLargestKeyIndex);

			uIndex = uLargestKeyIndex;
		}
	}

	pElement->UpdateIndex(std::numeric_limits<size_t>::max());
	return pElement;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T, typename K>
void
Heap<T,K>::IncreaseElementKey(typename PriorityQueue<T,K>::Element* pElement, const K& key)
{
	assert( dynamic_cast<const Element*>(pElement) != nullptr );
	Element* pTempElement = static_cast<Element*>(pElement);
	size_t uIndex = pTempElement->Index();

	if ( uIndex == std::numeric_limits<size_t>::max() || pElement->Key() > key )
		return;

	std::shared_ptr<Element> pHeapElement = m_aHeap[uIndex];
	pHeapElement->UpdateKey(key);

	while ( uIndex > 0 )
	{
		size_t uParentIndex = ParentIndexForChildIndex(uIndex);
	
		if ( m_aHeap[uParentIndex]->Key() >= pElement->Key() )
			break;

		m_aHeap[uIndex] = m_aHeap[uParentIndex];
		m_aHeap[uIndex]->UpdateIndex(uIndex);

		uIndex = uParentIndex;
	}

	m_aHeap[uIndex] = pHeapElement;
	pHeapElement->UpdateIndex(uIndex);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T, typename K>
size_t 
Heap<T,K>::ParentIndexForChildIndex(const size_t kuChildIndex) const
{
	assert( kuChildIndex > 0 );

	return ((kuChildIndex + 1) / 2) - 1;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T, typename K>
size_t 
Heap<T,K>::LeftChildIndexForParentIndex(const size_t kuParentIndex) const
{
	return ((kuParentIndex + 1) * 2) - 1;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T, typename K>
size_t 
Heap<T,K>::RightChildIndexForParentIndex(const size_t kuParentIndex) const
{
	return (kuParentIndex + 1) * 2;
}

#endif

