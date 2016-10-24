#include <cstdlib>
using std::size_t;

#include <cassert>
#include <cstring>
using ::memmove;

#include <new>
using std::bad_alloc;
using std::nothrow;

#include <random>
using std::default_random_engine;
using std::uniform_int_distribution;

#include <array>
using std::array;

#include <limits>
using std::numeric_limits;

#include <algorithm>

template <typename ElemType>
struct Queue
{
	// Types
	typedef size_t                  size_type;
	typedef ElemType               value_type;
	typedef value_type*               pointer;
	typedef value_type&             reference;
	typedef const value_type& const_reference;
	typedef value_type*              iterator;
	typedef const value_type*  const_iterator;

	// --------------------------------------------------------------------
	// SYNOPSYS
	// --------------------------------------------------------------------
	#if -0

	// Constructors
	Queue();                                // Default
	Queue(const Queue&);                    // Copy constructor

	// Operators
	Queue& operator=(const Queue&);         // Copy assignment operator

	// Methodes
	void              push(const reference);// Adds elem to back of queue
	void              pop(void);            // Removes front elem from queue
	reference       front(void);            // Returns ref to the front element
	const_reference front(void) const;      // Returns const reference to the front element
	bool            empty(void) const;      // Returns whether the queue is empty
	size_t           size(void) const;      // Returns the # of elements
	const_iterator  begin(void) const;      // Returns a const iterator to the beginning 
	iterator        begin(void);            // Returns an iterator to the beginning
	const_iterator    end(void) const;      // Returns a const iterator to the end 
	iterator          end(void);            // Returns an iterator to the end 

	#endif

	// --------------------------------------------------------------------
	// IMPLEMENTATION
	// --------------------------------------------------------------------

	Queue()
		: size_(0),
		  v_(nullptr)
	{}

	Queue(const Queue& source)
		: size_(source.size_),
		  v_( allocate(sizeof(value_type) * source.size_) )
	{
		if (v_)
		{
                        std::copy(source.begin(), source.end(), begin());
		}
		else
		{
			size_ = 0;
		}
	}

	// Operators
	Queue& operator=(const Queue& source)
	{
		const auto size = sizeof(value_type) * source.size_;
		auto       ptr  = allocate(size);

		if (ptr)
		{
			v_ = ptr;
			size_ = source.size();
                        std::copy(source.begin(), source.end(), begin());
		}
	}

	// Methodes
	iterator begin()
	{
		return iterator(&v_[0]);
	}

	const_iterator begin() const
	{
		return const_iterator(&v_[0]);
	}

	iterator end()
	{
		return iterator(&v_[size_]);
	}

	const_iterator end() const
	{
		return const_iterator(&v_[size_]);
	}

	void push(const reference value)
	{
		auto ptr = allocate( sizeof(value_type) * (size_ + 1) );

		if (ptr)
		{
			memmove(ptr, v_, sizeof(value_type) * size_);
			delete v_;
			v_ = ptr;
			v_[size_++] = value;
		}
	}

	void pop()
	{
		auto ptr = allocate( sizeof(value_type) * (size_ - 1) );

		if (ptr)
		{
			memmove(ptr, v_ + 1, sizeof(value_type) * --size_ );
			delete v_;
			v_ = ptr;
		}
	}

	reference front()
	{
		return v_[0];
	}

	const reference front() const
	{
		return v_[0];
	}

	inline bool empty() const
	{
		return size_ == 0;
	}

	inline size_t size() const
	{
		return size_;
	}

	~Queue()
	{
		delete v_;
	}

	struct tests
	{
		static const auto RANGE = 2;

		static void constructors(void)
		{
			// default constructor
			Queue queue;

			// copy constructor
			const Queue source = populate<RANGE>(queue);

			const Queue copy(queue);

                        assert(copy.size() == source.size());
			for (auto i = 0; i < RANGE; ++i)
                        {
                                assert(copy.v_[i] == source.v_[i]);
                        }
		}


		static void operator_equal()
		{
			const Queue source = populate<RANGE>();
			Queue         copy;

			copy = source;

                        assert(copy.size() == source.size());
			for (auto i = 0; i < RANGE; ++i)
                        {
                                assert(copy.v_[i] == source.v_[i]);
                        }
		}

		static void push()
		{
			// Init
			default_random_engine generator;
			uniform_int_distribution<value_type> distribution(numeric_limits<value_type>::lowest(), numeric_limits<value_type>::max());

			Queue queue;

			value_type values[] =
			{
				distribution(generator),
				distribution(generator)
			};

			// Test
			queue.push(values[0]);
			assert(queue.v_[0] == values[0]);
			assert(queue.size() == 1);

			queue.push(values[1]);
			assert(queue.v_[1] == values[1]);
			assert(queue.size() == 2);
		}

		static void pop()
		{
			// Init
			default_random_engine generator;
			uniform_int_distribution<value_type> distribution(numeric_limits<value_type>::lowest(), numeric_limits<value_type>::max());

			Queue queue;

			value_type values[] =
			{
				distribution(generator),
				distribution(generator)
			};

			queue.push(values[0]);
			queue.push(values[1]);

			// Test
			queue.pop();
			assert(queue.size() == 1);

			queue.pop();
			assert(queue.size() == 0);
		}

		static void front()
		{
			Queue queue; populate<RANGE>(queue);

			assert(&(++queue.front()) == &queue.v_[0]);
		}

		static void front_const()
		{
	// Constructors
			const Queue queue = populate<RANGE>();

			assert(&queue.front() == &queue.v_[0]);
		}

                static void empty()
		{
			const Queue empty;
			assert(empty.empty() == true);

			const Queue populated = populate<RANGE>();
			assert(populated.empty() == false);
		}

                template <size_type N>
                static void size()
                {
                        Queue queue = populate<N>();

                        assert(queue.size() == N);
                        assert(static_cast<const Queue>(queue).size() == N);
                }

		static void size()
		{
			size<0>();
			size<1>();
			size<2>();
		}

		// Tools
		template <size_type N>
		static Queue& populate(Queue& queue)
		{
			static default_random_engine                generator;
			static uniform_int_distribution<value_type> distribution(numeric_limits<value_type>::lowest(), numeric_limits<value_type>::max());
			static array<value_type, N>                 values;

			for (auto i = 0; i < N; ++i)
			{
				values[i] = distribution(generator);
				queue.push(values[i]);
			}
                        return queue;
		}

		template <size_type N>
		static Queue populate(void)
		{
			static default_random_engine                generator;
			static uniform_int_distribution<value_type> distribution(numeric_limits<value_type>::lowest(), numeric_limits<value_type>::max());
			static array<value_type, N>                 values;

			Queue queue;

			for (auto i = 0; i < N; ++i)
			{
				values[i] = distribution(generator);
				queue.push(values[i]);
			}
			return queue;
		}
	};

	private:
	static pointer allocate(size_t request)
	{
		return static_cast<pointer>(::operator new (request, nothrow));
	}

	size_type size_;			// Buffer size
	pointer v_;				// Buffer

	friend struct tests;
};

int main()
{
	Queue<short>::tests::constructors();
	Queue<short>::tests::operator_equal();
	Queue<short>::tests::push();
	Queue<short>::tests::pop();
	Queue<short>::tests::front();
	Queue<short>::tests::front_const();
	Queue<short>::tests::empty();
	Queue<short>::tests::size();
}
