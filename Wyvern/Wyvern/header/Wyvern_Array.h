// Wvvern_Array.h

#ifndef __WYVERN_ARRAY__
#define __WYVERN_ARRAY__

//Just use STD::VECTOR!!

template <typename T>
struct Wyvern_Array
{
	Wyvern_Array()
		: arr_(nullptr)
		, size_(0)
	{

	}
	~Wyvern_Array()
	{
		if (arr_)
			delete[] arr_;
		arr_ = nullptr;
	}

	int Length()
	{
		return size_;
	}
	
	void Push_Back(const T &obj)
	{
		Expand();
		arr_[size_ - 1] = obj;
	}

private:
	T* arr_;
	int size_;

	void Expand()
	{
		T* temp = arr_;
		arr_ = new T[size_ + 1];

		for (int i = 0; i < size_; i++)
			arr_[i] = temp[i];
		size_++;

		delete[] temp;
	}
};


#endif // !__WYVERN_ARRAY__
