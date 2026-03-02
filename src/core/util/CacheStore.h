#ifndef GAME_ENGINE_CACHESTORE_H
#define GAME_ENGINE_CACHESTORE_H

#include <map>

template <typename T>
struct CacheStore {
  std::map<std::uint32_t, T> cache;
  std::uint32_t nextId = 0;

  std::uint32_t add(T item) {
    cache[nextId] = item;
    return nextId++;
  }

  void remove(std::uint32_t id) {
    cache.erase(id);
  }
};

#endif