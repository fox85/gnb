#ifndef gnb_hash32_h
#define gnb_hash32_h


#include <stdint.h>
#include <sys/types.h>

#ifndef __u_char_defined
typedef unsigned char	u_char;
#define __u_char_defined
#endif

#include "gnb_alloc.h"
#include "gnb_block.h"


typedef struct _gnb_kv32_t gnb_kv32_t;

typedef struct _gnb_kv32_t{
    gnb_block32_t *key;
    gnb_block32_t *value;
    gnb_kv32_t *nex;
}gnb_kv32_t;

typedef struct _gnb_hash32_bucket_t gnb_hash32_bucket_t;

typedef struct _gnb_hash32_map_t{
    
    gnb_heap_t *heap;

    uint32_t bucket_num;

    uint32_t kv_num;
    
    gnb_hash32_bucket_t **buckets;
    
} gnb_hash32_map_t;


gnb_hash32_map_t *gnb_hash32_create(gnb_heap_t *heap, uint32_t bucket_num,uint32_t kv_num);

void gnb_hash32_release(gnb_hash32_map_t *hash32_map);

gnb_kv32_t* gnb_hash32_put(gnb_hash32_map_t *hash32_map, u_char *key, uint32_t key_len, void *value, uint32_t value_len);

int gnb_hash32_store(gnb_hash32_map_t *hash32_map, u_char *key, uint32_t key_len, void *value, uint32_t value_len);

gnb_kv32_t* gnb_hash32_get(gnb_hash32_map_t *hash32_map, u_char *key, uint32_t key_len);

gnb_kv32_t* gnb_hash32_del(gnb_hash32_map_t *hash32_map, u_char *key, uint32_t key_len);

void gnb_kv32_release(gnb_hash32_map_t *hash_map, gnb_kv32_t *kv);

gnb_kv32_t** gnb_hash32_array(gnb_hash32_map_t *hash32_map, uint32_t *num);


#define GNB_HASH32_UINT32_SET(hash32_map,uint32key,value) gnb_hash32_put(hash32_map,(u_char *)&uint32key,sizeof(uint32_t),value,0)
#define GNB_HASH32_UINT32_STORE(hash32_map,uint32key,value,value_len) gnb_hash32_store(hash32_map,(u_char *)&uint32key,sizeof(uint32_t),value,value_len)
#define GNB_HASH32_UINT32_GET(hash32_map,uint32key) gnb_hash32_get(hash32_map,(u_char *)&uint32key,sizeof(uint32_t))

#define GNB_HASH32_UINT32_GET_PTR(hash32_map,uint32key) GNB_HASH32_VALUE_PTR(gnb_hash32_get(hash32_map,(u_char *)&uint32key,sizeof(uint32_t)))
#define GNB_HASH32_UINT32_DEL(hash32_map,uint32key) gnb_hash32_del(hash32_map,(u_char *)&uint32key,sizeof(uint32_t))
uint32_t* gnb_hash32_uint32_keys(gnb_hash32_map_t *hash32_map, uint32_t *num);


#define GNB_HASH32_UINT64_SET(hash32_map,uint64key,value) gnb_hash32_put(hash32_map,(u_char *)&uint64key,sizeof(uint64_t),value,0)
#define GNB_HASH32_UINT64_STORE(hash32_map,uint64key,value,value_len) gnb_hash32_store(hash32_map,(u_char *)&uint64key,sizeof(uint64_t),value,value_len)
#define GNB_HASH32_UINT64_GET(hash32_map,uint64key) gnb_hash32_get(hash32_map,(u_char *)&uint64key,sizeof(uint64_t))
#define GNB_HASH32_UINT64_GET_PTR(hash32_map,uint64key) GNB_HASH32_VALUE_PTR(gnb_hash32_get(hash32_map,(u_char *)&uint64key,sizeof(uint64_t)))
#define GNB_HASH32_UINT64_DEL(hash32_map,uint64key) gnb_hash32_del(hash32_map,(u_char *)&uint64key,sizeof(uint64_t))
uint64_t* gnb_hash32_uint64_keys(gnb_hash32_map_t *hash32_map, uint32_t *num);


#define GNB_HASH32_SET(hash32_map,string,string_len,value) gnb_hash_put(hash32_map, string, (uint32_t)string_len, value, 0)
#define GNB_HASH32_STORE(hash32_map,string,string_len,value,value_len) gnb_hash32_store(hash32_map,string,(uint32_t)string_len,value,(uint32_t)value_len)
#define GNB_HASH32_GET(hash32_map,key_string,key_string_len) gnb_hash32_get(hash32_map,key_string,(uint32_t)key_string_len)
#define GNB_HASH32_GET_PTR(hash32_map,key_string,key_string_len) GNB_HASH32_VALUE_PTR(gnb_hash32_get(hash32_map,key_string,(uint32_t)key_string_len))
#define GNB_HASH32_DEL(hash32_map,string,string_len) gnb_hash32_del(hash32_map,string,(uint32_t)string_len)
u_char** gnb_hash32_string_keys(gnb_hash32_map_t *hash32_map, uint32_t *num);


#define GNB_HASH32_UINT32_KEY(kv32)   (*(uint32_t *)kv32->key->data)
#define GNB_HASH32_UINT32_VALUE(kv32) (*(uint32_t *)kv32->value->data)

#define GNB_HASH32_UINT64_KEY(kv32)   (*(uint64_t *)kv32->key->data)
#define GNB_HASH32_UINT64_VALUE(kv32) (*(uint64_t *)kv32->key->data)

#define GNB_HASH32_STRING_KEY(kv32)   ((unsigned char *)kv32->key->data)
#define GNB_HASH32_STRING_VALUE(kv32) ((unsigned char *)kv32->value->data)

#define GNB_HASH32_KEY_SIZE(kv32)     (kv32->key->size)
#define GNB_HASH32_VALUE_SIZE(kv32)   (kv32->value->size)

#define GNB_HASH32_KEY_PTR(kv32)      kv32!=NULL?(*(void **)&kv32->key->data):NULL
#define GNB_HASH32_VALUE_PTR(kv32)    kv32!=NULL?(*(void **)&kv32->value->data):NULL

#define GNB_HASH32_VALUE(kv32)       kv32!=NULL?kv32->value:NULL

#define GNB_HASH32_GET_VALUE(hash32_map,key,key_len)  GNB_HASH32_VALUE( gnb_hash32_get(hash32_map,key,key_len) )

#endif
