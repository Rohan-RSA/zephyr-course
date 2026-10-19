
#ifdef __cplusplus
extern "C" {
#endif

typedef struct our_struct_t {
    int mutable_int;
} our_struct_t;

int my_extension_api_func(our_struct_t *our_struct);

#ifdef __cplusplus
}
#endif


// #ifndef OUR_DRIVER_H
// #define OUR_DRIVER_H

// int my_extension_api_func(int count);

// #endif /* OUR_DRIVER_H__ */