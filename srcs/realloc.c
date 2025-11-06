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
    if (ptr == NULL)
        return (malloc(size));
    if (size == 0U)
    {
        free(ptr);
        return (NULL);
    }
    size_t   old_size = size;
    size = align8(size);
    if (((t_data*)(ptr - META_DATA))->size > size + META_DATA) // Smaller -> going for a split.
        {
            t_data*   new;
            new = ptr + size; // new points on the split block
    
            new->next = ((t_data*)(ptr - META_DATA))->next;
            if (new->next)
                new->next->prev = new;
            ((t_data*)(ptr - META_DATA))->next = new;
            new->prev = ((t_data*)(ptr - META_DATA));
            new->free = true;
            new->head = false;
            new->size = ((t_data*)(ptr - META_DATA))->size - size - META_DATA;
            ((t_data*)(ptr - META_DATA))->size = size;

            free((void*)(new + META_DATA)); // Since it became unused, it must be free.
        }
    else if (((t_data*)(ptr - META_DATA))->size < size)// Larger
    {
        TYPE type = (size <= TINY_SIZE) ? TINY : (size <= SMALL_SIZE) ? SMALL : LARGE;
        if (type != LARGE)
        {
            if ((((t_data*)(ptr - META_DATA))->next) && (((t_data*)(ptr - META_DATA))->next->free) &&
                (((t_data*)(ptr - META_DATA))->size + META_DATA + ((t_data*)(ptr - META_DATA))->next->size >= size)) // Fusion current chunk with the next
            {
                fusion_blocks(((t_data*)(ptr - META_DATA)));

                if ((((t_data*)(ptr - META_DATA))->size - size) > META_DATA) // Split if the new block is big enough
                    split_blocks(((t_data*)(ptr - META_DATA)), size);
                return (ptr);
            }
        }

        void* new_ptr = malloc(size);
        if (!new_ptr)
            return (NULL);

        memmove(new_ptr, ptr, old_size);
        free(ptr);
    }
    else
        ((t_data*)(ptr - META_DATA))->size = size; // Cannot change size but update metadata size.
    return (ptr);
}

// Split the block into two, the first one being of the requested size, the second one being free.
// void*   smaller_realloc(void* meta_ptr, size_t size)
// {
//     // (void)meta_ptr;
//     (void)size;
//     return (NULL);
    // ft_printf("%s--> smaller_realloc called on ptr: %p with size: %u%s\n", BYEL, (meta_ptr + META_DATA), size, END);
    // t_data*   new;
    // new = meta_ptr + META_DATA + size; // new points on the split block
    
    // new->next = meta_ptr->next;
    // ft_printf("%s--> smaller_realloc new block at: %p%s\n", BYEL, new + META_DATA, END);
    // if (new->next)
    //     new->next->prev = new;
    // meta_ptr->next = new;
    // ft_printf("%s--> smaller_realloc adjusted meta_ptr->next to: %p%s\n", BYEL, meta_ptr->next + META_DATA, END);
    // new->prev = meta_ptr;
    // ft_printf("%s--> smaller_realloc adjusted new->prev to: %p%s\n", BYEL, new->prev + META_DATA, END);
    // new->free = true;
    // new->head = false;
    // new->size = meta_ptr->size - size - META_DATA;
    // ft_printf("%s--> smaller_realloc new block size: %u%s\n", BYEL, new->size, END);
    // meta_ptr->size = size;
    // ft_printf("%s--> smaller_realloc adjusted meta_ptr size to: %u%s\n", BYEL, meta_ptr->size, END);

    // // split_blocks(meta_ptr, size);

    // free(new + META_DATA); // Since it became unused, it must be free.

    // return (meta_ptr + META_DATA);
// }

// Try to fuse with the next block if it's free and of the same type. 
// If not possible, malloc a new block, copy the data and free the old one.
// void*   larger_realloc(void* ptr, t_data* meta_ptr, size_t size)
// {
//     ft_printf("%s--> larger_realloc called on ptr: %p with size: %u%s\n", BYEL, ptr, size, END);
//     void*   new_ptr = NULL;
//     (void)meta_ptr;


//     // Large or no next tiny/small available (malloc will either find a corresponding free block or allocate a new zone)
//     new_ptr = malloc(size);

//     if (!new_ptr)
//         return (NULL);
//     free(ptr);

//     return (new_ptr);
// }
