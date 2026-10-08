#pragma once

#ifdef PLATSERV_EXPORTS
#define PLATSERV_API __declspec(dllexport)
#else
#define PLATSERV_API __declspec(dllimport)
#endif

#include <random>
#include <iterator>
#include <d2d1.h>

#pragma comment(lib, "d2d1.lib")

constexpr int BAD_PTR{ 5001 };
constexpr int BAD_INDEX{ 5002 };
constexpr int BAD_PARAM{ 5003 };
constexpr int BAD_ERR{ 5004 };

constexpr float scr_width{ 1000.0f };
constexpr float scr_height{ 750.0f };

constexpr float sky{ 50.0f };
constexpr float ground{ 750.0f };

constexpr D2D1_RECT_F FULL_SCREEN{ 0, 0, scr_width, scr_height };
constexpr D2D1_RECT_F GAME_SCREEN{ 0, sky, scr_width, ground };

namespace indll
{
	class PLATSERV_API EXCEPTION
	{
	private:
		int what{ 0 };

	public:
		EXCEPTION(int what_happened);

		const wchar_t* eGet() const;
	};

	class PLATSERV_API RANDIT
	{
	private:
		std::mt19937* twister{ nullptr };

	public:

		RANDIT();

		~RANDIT();

		int operator()(int min, int max);

		float operator()(float min, float max);
	};

	template<typename T> class BAG
	{
	private:
		T* mPtr{ nullptr };
		size_t max_size{ 1 };
		size_t next_pos{ 0 };

	public:
		BAG()
		{
			mPtr = reinterpret_cast<T*>(calloc(max_size, sizeof(T)));
		}
		BAG(size_t lenght)
		{
			max_size = lenght;

			mPtr = reinterpret_cast<T*>(calloc(max_size, sizeof(T)));
		}
		BAG(BAG& other)
		{
			if (!other.mPtr)
			{
				max_size = 1;
				next_pos = 0;

				mPtr = reinterpret_cast<T*>(calloc(max_size, sizeof(T)));
			}
			else if (other.mPtr == mPtr)throw EXCEPTION(BAD_PARAM);
			else
			{
				max_size = other.max_size;
				next_pos = other.next_pos;

				mPtr = reinterpret_cast<T*>(calloc(max_size, sizeof(T)));

				if (!mPtr)throw EXCEPTION(BAD_PTR);
				else
				{
					for (size_t index = 0; index < next_pos; ++index)mPtr[index] = other.mPtr[index];
				}
			}
		}
		BAG(BAG&& other)
		{
			if (!other.mPtr)
			{
				max_size = 1;
				next_pos = 0;

				mPtr = reinterpret_cast<T*>(calloc(max_size, sizeof(T)));
			}
			else if (other.mPtr == mPtr)throw EXCEPTION(BAD_PARAM);
			else
			{
				max_size = other.max_size;
				next_pos = other.next_pos;

				mPtr = other.mPtr;

				other.mPtr = nullptr;
			}
		}

		~BAG()
		{
			free(mPtr);
		}

		BAG& operator = (BAG& other)
		{
			if (!other.mPtr)
			{
				max_size = 1;
				next_pos = 0;

				free(mPtr);

				mPtr = reinterpret_cast<T*>(calloc(max_size, sizeof(T)));
			}
			else if (other.mPtr == mPtr)throw EXCEPTION(BAD_PARAM);
			else
			{
				max_size = other.max_size;
				next_pos = other.next_pos;

				free(mPtr);

				mPtr = reinterpret_cast<T*>(calloc(max_size, sizeof(T)));

				if (!mPtr)throw EXCEPTION(BAD_PTR);
				else
				{
					for (size_t index = 0; index < next_pos; ++index)mPtr[index] = other.mPtr[index];
				}
			}

			return(*this);
		}
		BAG& operator = (BAG&& other)
		{
			free(mPtr);

			if (!other.mPtr)
			{
				max_size = 1;
				next_pos = 0;

				mPtr = reinterpret_cast<T*>(calloc(max_size, sizeof(T)));
			}
			else if (other.mPtr == mPtr)throw EXCEPTION(BAD_PARAM);
			else
			{
				max_size = other.max_size;
				next_pos = other.next_pos;

				mPtr = other.mPtr;

				other.mPtr = nullptr;
			}

			return (*this);
		}

		T& operator[] (size_t index)
		{
			if (index >= next_pos)throw EXCEPTION(BAD_PARAM);

			if (!mPtr)throw EXCEPTION(BAD_PTR);
			
			return mPtr[index];
		}

		bool empty() const
		{
			return (next_pos == 0);
		}
		size_t size() const
		{
			return next_pos;
		}
		size_t capacity() const
		{
			return max_size;
		}

		void clear()
		{
			free(mPtr);

			max_size = 1;
			next_pos = 0;

			mPtr = reinterpret_cast<T*>(calloc(max_size, sizeof(T)));
		}

		T& front()
		{
			if (!mPtr) throw EXCEPTION(BAD_PTR);

			return *mPtr;
		}
		T& back()
		{
			if (!mPtr) throw EXCEPTION(BAD_PTR);

			return mPtr[next_pos - 1];
		}

		void push_back(T element)
		{
			if (!mPtr)throw EXCEPTION(BAD_PTR);
			else
			{
				if (next_pos + 1 <= max_size)
				{
					mPtr[next_pos] = element;
					++next_pos;
				}
				else
				{
					++max_size;

					T* temp{ reinterpret_cast<T*>(realloc(mPtr, max_size * sizeof(T))) };
					
					if (!temp)throw EXCEPTION(BAD_PTR);
					else
					{
						mPtr = temp;

						mPtr[next_pos] = element;
						++next_pos;
					}
				}
			}
		}
		void push_back(T* element)
		{
			if (!mPtr)throw EXCEPTION(BAD_PTR);
			else
			{
				if (next_pos + 1 <= max_size)
				{
					mPtr[next_pos] = *element;
					++next_pos;
				}
				else
				{
					++max_size;

					T* temp{ reinterpret_cast<T*>(realloc(mPtr, max_size * sizeof(T))) };

					if (!temp)throw EXCEPTION(BAD_PTR);
					else
					{
						mPtr = temp;

						mPtr[next_pos] = *element;
						++next_pos;
					}
				}
			}
		}

		void push_front(T element)
		{
			if (!mPtr)throw EXCEPTION(BAD_PTR);
			else if (empty())
			{
				*mPtr = element;
				++next_pos;
			}
			else
			{
				if (next_pos + 1 <= max_size)
				{
					for (size_t count = next_pos; count > 0; --count)mPtr[count] = mPtr[count - 1];
					*mPtr = element;
					++next_pos;
				}
				else
				{
					++max_size;

					T* temp{ reinterpret_cast<T*>(realloc(mPtr,max_size * sizeof(T))) };

					if(!temp)throw EXCEPTION(BAD_PTR);
					else
					{
						mPtr = temp;

						for (size_t count = next_pos; count > 0; --count)mPtr[count] = mPtr[count - 1];
						*mPtr = element;
						++next_pos;
					}
				}
			}
		}
		void push_front(T* element)
		{
			if (!mPtr)throw EXCEPTION(BAD_PTR);
			else if (empty())
			{
				*mPtr = *element;
				++next_pos;
			}
			else
			{
				if (next_pos + 1 <= max_size)
				{
					for (size_t count = next_pos; count > 0; --count)mPtr[count] = mPtr[count - 1];
					*mPtr = *element;
					++next_pos;
				}
				else
				{
					++max_size;

					T* temp{ reinterpret_cast<T*>(realloc(mPtr,max_size * sizeof(T))) };

					if (!temp)throw EXCEPTION(BAD_PTR);
					else
					{
						mPtr = temp;

						for (size_t count = next_pos; count > 0; --count)mPtr[count] = mPtr[count - 1];
						*mPtr = *element;
						++next_pos;
					}
				}
			}
		}

		void insert(T* element, size_t index)
		{
			if (!mPtr)throw EXCEPTION(BAD_PTR);
			else
			{
				if (index > next_pos)throw EXCEPTION(BAD_PARAM);
				else if (empty())
				{
					*mPtr = element;
					++next_pos;
				}
				else
				{
					if (next_pos + 1 <= max_size)
					{
						for (size_t count = next_pos; count > index; --index)mPtr[index] = mPtr[index - 1];

						mPtr[index] = element;
						++next_pos;
					}
					else
					{
						++max_size;

						T* temp{ reinterpret_cast<T*>(realloc(mPtr,max_size * sizeof(T))) };

						if (!temp)throw EXCEPTION(BAD_PTR);
						else
						{
							mPtr = temp;
							
							for (size_t count = next_pos; count > index; --index)mPtr[index] = mPtr[index - 1];

							mPtr[index] = element;
							++next_pos;
						}
					}
				}

			}
		}

	};





}