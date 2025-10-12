/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 19:33:27 by marvin            #+#    #+#             */
/*   Updated: 2025/06/08 19:33:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void*   realloc(void* ptr, size_t size)
{
    t_data* meta_ptr;

    if (ptr == NULL)
        return (malloc(size));
    if (size == 0U)
    {
        free(ptr);
        return (NULL);
    }

    size = align8(size);
    meta_ptr = (t_data*)(ptr - META_DATA);
    
    if (meta_ptr->size > size + META_DATA) // Smaller -> going for a split.
        ptr = smaller_realloc(meta_ptr, size);
    else // Larger
        ptr = larger_realloc(ptr, meta_ptr, size);
    return (ptr);
}

// Split the block into two, the first one being of the requested size, the second one being free.
void*   smaller_realloc(t_data* meta_ptr, size_t size)
{
    void*   new;

    new = meta_ptr + size + META_DATA; // new points on the split block

    ((t_data*)new)->next = meta_ptr->next;
    if (((t_data*)new)->next)
        ((t_data*)new)->next->prev = new;
    meta_ptr->next = new;
    ((t_data*)new)->prev = meta_ptr;

    ((t_data*)new)->free = true;
    ((t_data*)new)->head = false;
    ((t_data*)new)->size = meta_ptr->size - size - META_DATA;
    meta_ptr->size = size;

    free(new + META_DATA); // Since it became unused, it must be free.

    return (meta_ptr + META_DATA);
}

// Try to fuse with the next block if it's free and of the same type. 
// If not possible, malloc a new block, copy the data and free the old one.
void*   larger_realloc(t_data* ptr, t_data* meta_ptr, size_t size)
{
    void*   new_ptr = NULL;

    TYPE type = (size <= TINY_SIZE) ? TINY : (size <= SMALL_SIZE) ? SMALL : LARGE;

    if (type != LARGE)
    {
        if ((meta_ptr->next) && (meta_ptr->next->free) &&
            (meta_ptr->size + META_DATA + meta_ptr->next->size > size)) // Fusion current chunk with the next
        {
            fusion_blocks(meta_ptr);

            if ((meta_ptr->size - size) > META_DATA) // Split if the new block is big enough
                split_blocks(meta_ptr, size);
            return (meta_ptr + META_DATA);
        }
    }

    // Large or no next tiny/small available (malloc will either find a corresponding free block or allocate a new zone)
    new_ptr = malloc(size);

    if (!new_ptr)
        return (NULL);

    ft_memmove(new_ptr, meta_ptr, meta_ptr->size);

    // free(ptr);
    (void)ptr;

    return (new_ptr);
}
