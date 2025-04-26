#ifndef INC_3DGAME_ALIGNMENT_H
#define INC_3DGAME_ALIGNMENT_H

#include <cstdlib>
#include <iostream>
#include <stdexcept>


typedef intptr_t ptr_i;
typedef uintptr_t ptr_u;

ptr_i calculatePadding_degree_2(ptr_i pointer, ptr_i align);

ptr_i calculateAlignment_degree_2(ptr_i pointer, ptr_i align);

ptr_u calculatePadding_degree_2(ptr_u pointer, ptr_u align);

ptr_u calculateAlignment_degree_2(ptr_u pointer, ptr_u align);

ptr_i calculatePadding(ptr_i pointer, ptr_i align);

ptr_i calculateAlignment(ptr_i pointer, ptr_i align);

ptr_u calculatePadding(ptr_u pointer, ptr_u align);

ptr_u calculateAlignment(ptr_u pointer, ptr_u align);

template<typename T>
ptr_u getPadding_degree_2(T* pointer, ptr_u align){

    return (-1 * ((ptr_u)pointer) & (align - 1));
}

template<typename T>
T* alignedPointer_degree_2(T* pointer, ptr_u align){

    ptr_u padding = (-1 * ((ptr_u)pointer) & ((ptr_u)align - 1));
    return reinterpret_cast<T *>((ptr_u)pointer + padding);
}

template<typename T>
ptr_u getPadding(T* pointer, ptr_u align){

    return (align - ((ptr_u)pointer % align)) % align;
}

template<typename T>
T* alignedPointer(T* pointer, ptr_u align){

    ptr_u padding = (align - ((ptr_u)pointer % align)) % align;
    return reinterpret_cast<T *>((ptr_u)pointer + padding);
}

template<typename T>
inline T* getAlignedPointer_degree_2(const size_t size, const size_t align){

    const ptr_u VOID_SIZE = sizeof(void **);
    const ptr_u VOID_ALIGN = alignof(void **);

    auto pointer = malloc(size + align + VOID_SIZE + VOID_ALIGN);

    auto offset = (ptr_u)pointer + VOID_SIZE + VOID_ALIGN;

    ptr_u align_ptr = (offset + (align - 1)) & -align;
    auto void_ptr = align_ptr - (align_ptr % VOID_ALIGN) - VOID_SIZE;
    auto void_pointer = (void **)(void_ptr);
    *void_pointer = pointer;
    return reinterpret_cast<T *>(align_ptr);
}

template<typename T>
inline void removeAlignedPointer_degree_2(T* pointer){

    auto void_ptr = (ptr_u)pointer - ((ptr_u)pointer % alignof(void **)) - sizeof(void **);
    free(*((void **)void_ptr));
}

template<typename T>
inline T* getAlignedPointer(const size_t size, const size_t align){

    const ptr_u VOID_SIZE = sizeof(void **);
    const ptr_u VOID_ALIGN = alignof(void **);

    auto pointer = malloc(size + align + VOID_SIZE + VOID_ALIGN);

    auto offset = (ptr_u)pointer + VOID_SIZE + VOID_ALIGN;

    ptr_u align_ptr = (offset + ((align - (offset % align)) % align));
    auto void_ptr = align_ptr - (align_ptr % VOID_ALIGN) - VOID_SIZE;
    auto void_pointer = (void **)(void_ptr);
    *void_pointer = pointer;
    return reinterpret_cast<T *>(align_ptr);
}

template<typename T>
inline void removeAlignedPointer(T* pointer){

    auto void_ptr = (ptr_u)pointer - ((ptr_u)pointer % alignof(void **)) - sizeof(void **);
    free(*((void **)void_ptr));
}

template<typename T>
class AlignedPointer{

public:

    AlignedPointer(void *originalPointer, T *alignmentPointer) :
    originalPointer(originalPointer),
    alignmentPointer(alignmentPointer) {}

    AlignedPointer(const AlignedPointer<T>& other){

        originalPointer = other.originalPointer;
        alignmentPointer = other.alignmentPointer;
    }

    AlignedPointer<T>& operator = (const AlignedPointer<T>& other){

        originalPointer = other.originalPointer;
        alignmentPointer = other.alignmentPointer;

        return reinterpret_cast<AlignedPointer<T *> &>(*this);
    }

    AlignedPointer(AlignedPointer<T>&& other){

        originalPointer = other.originalPointer;
        other.originalPointer = nullptr;
        alignmentPointer = other.alignmentPointer;
        other.alignmentPointer = nullptr;
    }

    AlignedPointer<T>& operator = (AlignedPointer<T>&& other){

        originalPointer = other.originalPointer;
        other.originalPointer = nullptr;
        alignmentPointer = other.alignmentPointer;
        other.alignmentPointer = nullptr;

        return reinterpret_cast<AlignedPointer<T *> &>(*this);
    }

    void* originalPointer;
    T* alignmentPointer;

};

template<typename T>
bool operator == (AlignedPointer<T>& first, AlignedPointer<T>& second){

    return (first.originalPointer == second.originalPointer && first.alignmentPointer == second.alignmentPointer);
}

template<typename T>
bool operator != (AlignedPointer<T>& first, AlignedPointer<T>& second){

    return (first.originalPointer != second.originalPointer && first.alignmentPointer != second.alignmentPointer);
}

template<typename T>
AlignedPointer<T> allocAlignedPointer(size_t size, size_t align){

    auto pointer = malloc(size + align);
    auto offset = reinterpret_cast<ptr_u>(pointer);
    auto padding = (align - (offset % align)) % align;
    auto alig_ptr = reinterpret_cast<T *>(offset + padding);
    auto alignedPointer = AlignedPointer(pointer, alig_ptr);
    return alignedPointer;
}

template<typename T>
void freeAlignedPointer(AlignedPointer<T>& alignedPointer){

    free(alignedPointer.originalPointer);
}

template<typename T>
AlignedPointer<T> allocAlignedPointer_degree_2(size_t size, size_t align){

    auto pointer = malloc(size + align);
    auto offset = reinterpret_cast<ptr_u>(pointer);
    auto padding = -offset & (align - 1);
    auto alig_ptr = reinterpret_cast<T *>(offset + padding);
    auto alignedPointer = AlignedPointer(pointer, alig_ptr);
    return alignedPointer;
}

template<typename T>
void freeAlignedPointer_degree_2(AlignedPointer<T>& alignedPointer){

    free(alignedPointer.originalPointer);
}















#endif //INC_3DGAME_ALIGNMENT_H
