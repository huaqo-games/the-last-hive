#ifndef ARRAY_H
#define ARRAY_H

typedef struct {
    void** elements;
    unsigned int count;
    unsigned int capacity;
} Array;

Array* CreateArray(unsigned int initCapacity){
    Array* array = malloc(sizeof(Array));
    if (!array) return NULL;

    array->elements = malloc(sizeof(void* ) * initCapacity);
    if (!array->elements) {
        free(array);
        return NULL;
    }

    array->count = 0;
    array->capacity = initCapacity;
    return array;
}

int AddElementToArray(Array* array, void* element){
    if(array->count >= array->capacity) {
        unsigned int newCapacity = array->capacity * 2;
        void** newElements = realloc(array->elements, sizeof(void*) * newCapacity);
        if (!newElements) return 0;

        array->elements = newElements;
        array->capacity = newCapacity;
    }
    array->elements[array->count++] = element;
    return 1;
}

// NORMAL REMOVE
// int RemoveElementFromArray(Array* array, unsigned int index){
//     if (index >= array->count) return 0;

//     for (unsigned int i = index; i < array->count - 1; i++) {
//         array->elements[i] = array->elements[i + 1];
//     }

//     array->count--;
//     return 1;
// }

// SWAP AND POP REMOVE
int RemoveElementFromArray(Array* array, unsigned int index) {
    if (index >= array->count) return 0;

    array->elements[index] = array->elements[array->count - 1];

    array->count--;

    return 1;
}

void* GetRandomElementFromArray(Array* array){
    if (array == NULL || array->elements == NULL || array->count == 0) {
        return NULL;
    }
    int randomIndex = GetRandomValue(0, (int)array->count-1);
    return &array->elements[randomIndex];
}

void UpdateArray(Array* array, void (*updateFunc)(void*))
{
    if (!array || !updateFunc) return;
    for (unsigned int i = 0; i < array->count; i++) {
        updateFunc(array->elements[i]);
    }
}

void RenderArray(Array* array, void (*renderFunc)(void*))
{
    if (!array || !renderFunc) return;
    for (unsigned int i = 0; i < array->count; i++) {
        renderFunc(array->elements[i]);
    }
}

void FreeArray(Array** array) {
    if (!array || !*array) return;

    free((*array)->elements);
    (*array)->elements = NULL;

    free(*array);
    *array = NULL;
}


#endif // ARRAY_H
