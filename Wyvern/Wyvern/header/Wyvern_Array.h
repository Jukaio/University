// Wvvern_Array.h

#ifndef __WYVERN_ARRAY__
#define __WYVERN_ARRAY__

template <typename T>
struct Wyvern_Array
{
	Wyvern_Array()
		: arr_(nullptr)
		, size_(0)
	{

	}

	T* arr_;
	int Length()
	{
		return size_;
	}
	
	void Push_Back()
	{
		Expand();
		//arr_[size_ - 1] = obj;
	}

private:
	int size_;

	void Expand()
	{
		size_++;
		Wyvern_Array<T> temp = arr_; // Fix this
		arr_ = new Wyvern_Array<T>[size_]; // Fix this
		for (int i = 0; i < size_; i++)
			arr_[i] = temp[i];
	}

};


#endif // !__WYVERN_ARRAY__
