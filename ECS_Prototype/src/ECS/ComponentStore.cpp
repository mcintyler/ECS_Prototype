#include "ComponentStore.h"

int ComponentStore::type_count = 0;
size_t* ComponentStore::offsets = nullptr;
size_t* ComponentStore::sizes = nullptr;
size_t ComponentStore::total_size = 0;