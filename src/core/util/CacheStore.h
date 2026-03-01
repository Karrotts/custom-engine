#ifndef GAME_ENGINE_CACHESTORE_H
#define GAME_ENGINE_CACHESTORE_H

#include <map>

template <typename T>
struct CacheStore {
  std::map<uint32_t, T> cache;
  uint32_t nextId = 0;

  uint32_t add(T item) {
    cache[nextId] = item;
    return nextId++;
  }

  void remove(uint32_t id) {
    cache.erase(id);
  }
};

#endif