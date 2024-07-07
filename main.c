#include <stdio.h>
#include "cJSON.h"
#include "memorypool.h"

#ifdef true
#undef true
#endif
#define true ((cJSON_bool)1)

#ifdef false
#undef false
#endif
#define false ((cJSON_bool)0)

#define MAX_MEM 10*1024
static MemoryPool *handle = NULL;

static void *memoryPoolMalloc(long unsigned int wantsize)
{
    return MemoryPoolAlloc(handle, wantsize);
}

static void memoryPoolFree(void *ptr)
{
    MemoryPoolFree(handle, ptr);
}

int main()
{
    handle = MemoryPoolInit(MAX_MEM, MAX_MEM);
    if (handle == NULL)
    {
        printf("MemoryPoolInit err\n");
    }

    cJSON_Hooks hooks = {
        .malloc_fn = memoryPoolMalloc,
        .free_fn = memoryPoolFree,
    };
    cJSON_InitHooks(&hooks);

    cJSON *json = cJSON_CreateObject();

    cJSON_AddStringToObject(json, "Name", "LiMing");
    cJSON_AddNumberToObject(json, "age", 15);
    
    int score[] = {81, 85, 83};
    cJSON *score_array = cJSON_CreateIntArray(score, sizeof(score)/sizeof(int));
    if (cJSON_AddItemToObject(json, "Score", score_array) == false)
    {
        cJSON_Delete(score_array);
    }

    char *str_json = cJSON_Print(json);
    printf("str_json = %s\n", str_json);

    cJSON_free(str_json);
    cJSON_Delete(json);

    printf("used:%llu, usage:%f\n", GetUsedMemory(handle), MemoryPoolGetUsage(handle));
    return 0;
}
