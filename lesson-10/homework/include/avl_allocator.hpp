#pragma once

namespace avl {
    template<typename T, typename BaseAllocator = std::allocator<T>>
    class CustomAllocator {
    public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        
        template<typename U>
        struct rebind {
            using other = CustomAllocator<U, BaseAllocator>;
        };
        
        CustomAllocator() noexcept = default;
        template<typename U>
        CustomAllocator(const CustomAllocator<U>&) noexcept {}
        
        pointer allocate(size_type n);
        void deallocate(pointer p, size_type n);
        
        template<typename U, typename... Args>
        void construct(U* p, Args&&... args);
        
        template<typename U>
        void destroy(U* p);
    };
    
    // Comparaison d'allocateurs
    template<typename T1, typename T2>
    bool operator==(const CustomAllocator<T1>&, const CustomAllocator<T2>&) noexcept;
    
    template<typename T1, typename T2>
    bool operator!=(const CustomAllocator<T1>&, const CustomAllocator<T2>&) noexcept;
}