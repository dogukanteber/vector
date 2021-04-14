#ifndef __MY_VECTOR__
#define __MY_VECTOR__

#include <algorithm>


template <typename T> 
class Vector {
	public:
	using value_type        = T;
        using reference         = T&;
        using const_reference   = T const&;
        using pointer           = T*;
        using const_pointer     = T const*;
        using iterator          = T*;
        using const_iterator    = T const*;
        using riterator         = std::reverse_iterator<iterator>;
        using const_riterator   = std::reverse_iterator<const_iterator>;
        using difference_type   = std::ptrdiff_t;
	using size_type 	= std::size_t;
		
	const size_type DEFAULT_SIZE = 4;

	private:
		size_type m_size;
		size_type m_capacity;
		T* m_data;

	public:
		// CONSTRUCTORS
		Vector() 
			: m_size(0)
			, m_capacity(DEFAULT_SIZE)
			, m_data(new T[m_capacity])
		{ }
		Vector(size_type size)
			: m_size(0)
			, m_capacity(size)
			, m_data(new T[m_capacity])
		{ }
		Vector(const size_type count, const T &data)
			: m_size(count)
			, m_capacity(count)
			, m_data(new T[m_capacity])
		{
			std::fill(m_data, m_data + count, data);
		}
		Vector(const Vector &other)
		: m_size(other.m_size)
		, m_capacity(other.m_capacity)
		, m_data(new T[other.m_capacity])
		{
			std::copy(other.m_data, other.m_data + other.m_capacity, m_data);
		}
		~Vector()
		{
			delete[] m_data;
		}

		Vector<T>& operator=(const Vector<T> &other) {

			// check assigning itself
			if ( this == &other )
				return *this;

			m_size = other.m_size;
			m_capacity = other.m_capacity;
			m_data = new T[other.m_capacity];

			std::copy(other.begin(), other.end(), m_data);
			
			return *this;
		}

		// ITERATORS
		iterator begin() 			{ return m_data; }
		riterator rbegin() 			{ return riterator(end()); }
		const_iterator begin() const  		{ return m_data; }
		const_riterator rbegin() const 		{ return riterator(end()); }

		iterator end() 				{ return m_data + m_size; }
		riterator rend() 			{ return riterator(begin()); }
		const_iterator end() const 		{ return m_data + m_size; }
		const_riterator rend() const 		{ return riterator(begin()); }

		const_iterator cbegin() const 		{ return begin(); }
		const_riterator crbegin() 		{ return rbegin(); }

		const_iterator cend() const 		{ return end(); }
		const_riterator crend() 		{ return rend(); }

		// NON-MUTATING FUNCTIONS
		size_type size() const 			{ return m_size; }
		size_type capacity() const  		{ return m_capacity; }
		bool empty() const 			{ return m_size == 0; };

		// MUTATING FUNCTIONS
		void push(const T &data) {
			if ( m_capacity == m_size ) {
			T* new_data = new T[m_capacity*2];

			std::move(m_data, m_data + m_capacity, new_data);

			delete[] m_data;

			m_data = new_data;
			m_capacity = m_capacity * 2;
			}

			m_data[m_size] = data;
			m_size++;
		}

		void pop() {
			if ( m_size != 0 ) {
				--m_size;
				m_data[m_size].~T();
			}
		}

		// VALIDATED ACCESS
		T& at(int n) 				 { validateIndex(n); return m_data[n]; }
		const T& at(int n) const 		 { validateIndex(n); return m_data[n]; }

		// NON-VALIDATED ACCESS
		T& front() 				 { return m_data[0]; }
		const T& front() const 			 { return m_data[0]; }
		T& back() 				 { return m_data[m_size-1]; }
		const T& back() const 			 { return m_data[m_size-1]; }
		T& operator[](int i) 			 { return m_data[i]; }
		const T& operator[](int i) const 	 { return m_data[i]; }
		
		// COMPARISON
		bool operator!=(const Vector &other) const { return *this == other; }
		bool operator==(const Vector &other) const { return ( size() == other.size() && std::equal(begin(), end(), other.begin()) ); }

		void print() const {
			std::for_each(begin(), end(), [](const_reference i) { std::cout << i << " "; });
			std::cout << "\n";
		}

	private:
		void validateIndex(size_type size) const {
			if ( size >= m_capacity )
				throw std::out_of_range("Out of range");
		}
};



#endif // __MY_VECTOR__
