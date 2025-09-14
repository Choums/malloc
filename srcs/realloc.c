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

#include "../includes/ft_malloc.h"

void*   realloc(void* ptr, size_t size)
{
    t_data* meta_ptr;

    if (ptr == NULL)
        return (malloc(size));
    
    size = align8(size);
    meta_ptr = (t_data*)ptr - META_DATA;

    if (meta_ptr->size > size + META_DATA) // Smaller
        ptr = smaller_realloc(meta_ptr, size);
    else // Larger
        ptr = larger_realloc(ptr, meta_ptr, size);
    return (ptr);
}

void*   smaller_realloc(t_data* meta_ptr, size_t size)
{
    void*   new;

    new = meta_ptr + META_DATA + size; // new point on the split block

    new->next = meta_ptr->next;
    if (new->next)
        new->next->prev = new;
    meta_ptr->next = new;
    new->prev = meta_ptr;

    new->free = true;
    new->head = false;
    new->size = meta_ptr->size - size - META_DATA;
    meta_ptr->size = size;

    ft_free(new + META_DATA); // Since it became unused, it must be free.

    return (meta_ptr + META_DATA);
}

void*   larger_realloc(t_data* ptr, t_data* meta_ptr, size_t size)
{
    void*   new_ptr = NULL;

    TYPE type = (size <= TINY_SIZE) ? TINY : (size <= SMALL_SIZE) ? SMALL : LARGE;

    if (type == TINY) // Tiny
    {
        if ((ptr->next) && (ptr->next->free) && (ptr->next->size <= TINY_SIZE)) // Fusion current chunk with the next
        {
            fusion_blocks(ptr);
            return (ptr);
        }
    }
    else if (type == SMALL) // Small
    {
        if ((ptr->next) && (ptr->next->free) && (ptr->next->size <= SMALL_SIZE)) // Fusion current chunk with the next
        {
            fusion_blocks(ptr);
            return (ptr);
        }
    }

    // Large or no next  tiny/small available (malloc will either find a corresponding free block or allocate a new zone)
    new_ptr = malloc(size);

    if (!new_ptr)
        return (NULL);
    ft_memmove(new_ptr, meta_ptr, meta_ptr->size);

    free(meta_ptr);

    return (new_ptr);
}
