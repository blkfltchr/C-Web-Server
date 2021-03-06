#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "cache.h"

/**
 * Allocate a cache entry
 */
struct cache_entry *alloc_entry(char *path, char *content_type, void *content, int content_length)
{
    ///////////////////
    // IMPLEMENT ME! //
    ///////////////////
    struct cache_entry *entry = malloc(sizeof(*entry));
    entry->path = strdup(path);
    entry->content_type = strdup(content_type);
    entry->content = strdup(content);
    entry->content_length = content_length;
    entry->prev = NULL;
    entry->next = NULL;

    return entry;
}

/**
 * Deallocate a cache entry
 */
void free_entry(struct cache_entry *entry)
{
    ///////////////////
    // IMPLEMENT ME! //
    ///////////////////
    
}

/**
 * Insert a cache entry at the head of the linked list
 */
void dllist_insert_head(struct cache *cache, struct cache_entry *ce)
{
    // Insert at the head of the list
    if (cache->head == NULL) {
        cache->head = cache->tail = ce;
        ce->prev = ce->next = NULL;
    } else {
        cache->head->prev = ce;
        ce->next = cache->head;
        ce->prev = NULL;
        cache->head = ce;
    }
}

/**
 * Move a cache entry to the head of the list
 */
void dllist_move_to_head(struct cache *cache, struct cache_entry *ce)
{
    if (ce != cache->head) {
        if (ce == cache->tail) {
            // We're the tail
            cache->tail = ce->prev;
            cache->tail->next = NULL;

        } else {
            // We're neither the head nor the tail
            ce->prev->next = ce->next;
            ce->next->prev = ce->prev;
        }

        ce->next = cache->head;
        cache->head->prev = ce;
        ce->prev = NULL;
        cache->head = ce;
    }
}


/**
 * Removes the tail from the list and returns it
 * 
 * NOTE: does not deallocate the tail
 */
struct cache_entry *dllist_remove_tail(struct cache *cache)
{
    struct cache_entry *oldtail = cache->tail;

    cache->tail = oldtail->prev;
    cache->tail->next = NULL;

    cache->cur_size--;

    return oldtail;
}

/**
 * Create a new cache
 * 
 * max_size: maximum number of entries in the cache
 * hashsize: hashtable size (0 for default)
 */
struct cache *cache_create(int max_size, int hashsize)
{
    ///////////////////
    // IMPLEMENT ME! //
    ///////////////////
    struct cache *cache = malloc(sizeof(*cache));
    cache->head = NULL;
    cache->tail = NULL;
    cache->cur_size = 0;
    cache->max_size = max_size;
    cache->index = hashtable_create(hashsize, NULL);
    return cache;
}

/**
 * Store an entry in the cache
 *
 * This will also remove the least-recently-used items as necessary.
 * 
 * NOTE: doesn't check for duplicate cache entries
 */
void cache_put(struct cache *cache, char *path, char *content_type, void *content, int content_length)
{
    ///////////////////
    // IMPLEMENT ME! //
    ///////////////////

    struct cache_entry *entry = alloc_entry(path, content_type, content, content_length); // Allocate a new cache entry with the passed parameters.
    dllist_insert_head(cache, entry); // Insert the entry at the head of the doubly-linked list.
    hashtable_put(cache->index, entry->path, entry); // Store the entry in the hashtable as well, indexed by the entry's `path`.
    cache->cur_size++; // Increment the current size of the cache.
    while (cache->cur_size > cache->max_size) // If the cache size is greater than the max size:
    {
        hashtable_delete(cache->index, cache->tail->path); // Remove the entry from the hashtable, using the entry's `path` and the `hashtable_delete` function.
        entry = dllist_remove_tail(cache); // Remove the cache entry at the tail of the linked list.
        free_entry(entry); // Free the cache entry.
        // Ensure the size counter for the number of entries in the cache is correct.
    }
}

/**
 * Retrieve an entry from the cache
 */
struct cache_entry *cache_get(struct cache *cache, char *path)
{
    ///////////////////
    // IMPLEMENT ME! //
    ///////////////////

    // Attempt to find the cache entry pointer by `path` in the hash table.
    // If not found, return `NULL`.
    // Move the cache entry to the head of the doubly-linked list.
    // Return the cache entry pointer.

}