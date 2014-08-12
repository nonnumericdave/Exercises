#ifndef PriorityQueue_h
#define PriorityQueue_h

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T, typename K>
class PriorityQueue
{
public:
	// PriorityQueue
	class Element 
	{
	public:
		// Element
		virtual ~Element() { }
		virtual T& Value() = 0;
		virtual const K& Key() = 0;
	
	protected:
		Element() { };
		Element(const Element& element);
	};

	virtual ~PriorityQueue() { };
	virtual std::shared_ptr<Element> InsertElementWithKey(const T& t, const K& key) = 0;
	virtual std::shared_ptr<Element> MaximumElement() const = 0;
	virtual std::shared_ptr<Element> ExtractMaximumElement() = 0;
	virtual void IncreaseElementKey(Element* pElement, const K& key) = 0;
};

#endif

