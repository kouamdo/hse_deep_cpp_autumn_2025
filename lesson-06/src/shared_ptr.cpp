#include <iostream>

namespace my
{

class shared_ptr
{
public:
    using value_type = int32_t;

    shared_ptr() = default;

    shared_ptr(value_type* data) : object_(new object(data, 1))
    {
        std::cout << "shared_ptr(value_type*)" << std::endl;
    }

    shared_ptr(const shared_ptr& rhs) : object_(rhs.object_)
    {
        std::cout << "shared_ptr(const shared_ptr&)" << std::endl;
        if (object_ != nullptr)
        {
            object_->counter_ += 1;
        }
    }

    shared_ptr(shared_ptr&& rhs) : object_(rhs.object_)
    {
        rhs.object_ = nullptr;
    }

    shared_ptr& operator=(const shared_ptr& rhs)
    {
        if (this != &rhs)
        {
            decrement();
            object_ = rhs.object_;
            if (object_)
            {
                object_->counter_ += 1;
            }
        }
        return *this;
    }

    shared_ptr& operator=(shared_ptr&& rhs)
    {
        if (this != &rhs)
        {
            decrement();
            object_ = rhs.object_;
            rhs.object_ = nullptr;
        }
        return *this;
    }

    value_type* get() const
    {
        return object_->data_;
    }

    void reset(value_type* ptr)
    {
        decrement();
        object_ = new object(ptr, 1);
    }

    ~shared_ptr()
    {
        std::cout << "~shared_ptr()" << std::endl;
        decrement();
    }
private:
    struct object
    {
        value_type* data_{nullptr};
        size_t counter_{0};
    };

    void decrement()
    {
        if (object_ != nullptr && object_->counter_ != 0 && --object_->counter_ == 0)
        {
            std::cout << "destroy" << std::endl;
            delete object_->data_;
            delete object_;
            object_ = nullptr;
        }
    }

private:
    object* object_{nullptr};
};

} // namespace my

int main()
{
    my::shared_ptr ptr1(new my::shared_ptr::value_type{10});
    my::shared_ptr ptr2 = ptr1;
    {
        my::shared_ptr ptr3(new my::shared_ptr::value_type{-10});
        //ptr3 = ptr1;
        ptr3 = ptr3;
        std::cout << *ptr3.get() << std::endl;
    }
    ptr2.reset(new my::shared_ptr::value_type{100500});

    my::shared_ptr ptr4 = std::move(ptr1);
    ptr1 = std::move(ptr1);
    ptr1 = std::move(ptr4);
    ptr4.reset(new my::shared_ptr::value_type{500});
}
