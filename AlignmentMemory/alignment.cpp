#include "alignment.h"


ptr_i calculatePadding_degree_2(ptr_i pointer, ptr_i align) {

    return -pointer & (align - 1);
}

ptr_i calculateAlignment_degree_2(ptr_i pointer, ptr_i align) {

    return (pointer + (align - 1)) & -align;
}

ptr_u calculatePadding_degree_2(ptr_u pointer, ptr_u align) {

    return -pointer & (align - 1);
}

ptr_u calculateAlignment_degree_2(ptr_u pointer, ptr_u align) {

    return (pointer + (align - 1)) & -align;
}

ptr_i calculatePadding(ptr_i pointer, ptr_i align) {
    return (align - (pointer % align)) % align;
}

ptr_i calculateAlignment(ptr_i pointer, ptr_i align) {

    return pointer + ((align - (pointer % align)) % align);
}

ptr_u calculatePadding(ptr_u pointer, ptr_u align) {
    return (align - (pointer % align)) % align;
}

ptr_u calculateAlignment(ptr_u pointer, ptr_u align) {
    return pointer + ((align - (pointer % align)) % align);
}
