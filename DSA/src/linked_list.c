#include "linked_list.h"
#include "utilities.h"

/**
 * @brief Create a new `list_node_t`
 *
 * @param data The data to store in the node
 * @return list_node_t*
 */
static list_node_t * list_node_new(void * data);

// Covers 4.1.9: A function pointer
comp_rtns_t custom_compare(void * value_to_find, void * node)
{
    comp_rtns_t result      = ERROR;
    int         search_data = 0;
    int         node_data   = 0;

    if ((NULL == value_to_find) || (NULL == node))
    {
        print_error("NULL argument passed.");
        goto END;
    }

    if (NULL == ((list_node_t *)node)->data)
    {
        print_error("NULL node data.");
        goto END;
    }

    search_data = *(int *)value_to_find;
    node_data   = *(int *)((list_node_t *)node)->data;

    printf("Checking for: %d, found: %d\n", search_data, node_data);

    if (search_data == node_data)
    {
        result = EQUAL;
        goto END;
    }

END:
    return result;
}

comp_rtns_t default_compare(void * value_to_find, void * node)
{
    comp_rtns_t result      = ERROR;
    int         search_data = 0;
    int         node_data   = 0;

    if ((NULL == value_to_find) || (NULL == node))
    {
        print_error("NULL argument passed.");
        goto END;
    }

    if (NULL == ((list_node_t *)node)->data)
    {
        print_error("NULL node data.");
        goto END;
    }

    search_data = *(int *)value_to_find;
    node_data   = *(int *)((list_node_t *)node)->data;

    if (search_data == node_data)
    {
        result = EQUAL;
        goto END;
    }

END:
    return result;
}

// Covers 4.3.2: Creating a circularly linked list a n number of items
list_t * list_new(FREE_F free_f, CMP_F cmp_f)
{
    list_t * new_list = NULL;

    new_list = calloc(1, sizeof(list_t));
    if (NULL == new_list)
    {
        print_error("CMR failure.");
        goto END;
    }

    new_list->size       = 0;
    new_list->head       = NULL;
    new_list->tail       = NULL;
    new_list->customfree = (NULL == free_f) ? free : custom_free;
    new_list->compare_function =
        (NULL == cmp_f) ? default_compare : custom_compare;

END:
    return new_list;
}

int list_push_head(list_t * list, void * data)
{
    int           exit_code = E_FAILURE;
    list_node_t * new_node  = NULL;
    list_node_t * current   = NULL;

    if ((NULL == list) || (NULL == data))
    {
        print_error("NULL argument passed.");
        goto END;
    }

    new_node = list_node_new(data);
    if (NULL == new_node)
    {
        print_error("Unable to create new node.");
        goto END;
    }

    if (NULL == list->head)
    { // Establish 'new_node' as the first node of an empty list
        list->head       = new_node;
        list->tail       = new_node;
        list->tail->next = list->head;
        list->head->prev = list->tail;

        // Update the position of the new node
        new_node->position = 1;
    }
    else
    { // Insert 'new_node' at the front of a populated list
        new_node->next   = list->head;
        new_node->prev   = list->tail;
        list->head->prev = new_node;
        list->tail->next = new_node;
        list->head       = new_node;

        current = new_node;

        // Update the positions of each node
        for (size_t idx = 0; idx <= list->size; idx++)
        {
            current->position += 1;
            current = current->next;
        }
    }

    list->size += 1;

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

int list_push_tail(list_t * list, void * data)
{
    int           exit_code = E_FAILURE;
    list_node_t * new_node  = NULL;
    // list_node_t *current = NULL;

    if ((NULL == list) || (NULL == data))
    {
        print_error("NULL argument passed.");
        goto END;
    }

    new_node = list_node_new(data);
    if (NULL == new_node)
    {
        print_error("Unable to create new node.");
        goto END;
    }

    if (NULL == list->head)
    { // Establish 'new_node' as the first node of an empty list
        list->head       = new_node;
        list->tail       = new_node;
        list->tail->next = list->head;
        list->head->prev = list->tail;

        // Update the position of the new node
        new_node->position = 1;
    }
    else
    { // Insert 'new_node' at the rear of a populated list
        new_node->position = list->tail->position + 1;
        new_node->prev     = list->tail;
        new_node->next     = list->head;
        list->tail->next   = new_node;
        list->head->prev   = new_node;
        list->tail         = new_node;
    }

    list->size += 1;

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

int list_emptycheck(list_t * list)
{
    int exit_code = E_FAILURE;

    if (NULL == list)
    {
        print_error("NULL argument passed.");
        goto END;
    }

    if (0 == list->size)
    {
        exit_code = E_SUCCESS;
    }

END:
    return exit_code;
}

list_node_t * list_pop_head(list_t * list)
{
    list_node_t * head_node = NULL;
    list_node_t * current   = NULL;

    if ((NULL == list) || (NULL == list->head))
    {
        print_error("List is empty.");
        goto END;
    }

    head_node = list->head;

    if (list->head == list->tail)
    {
        list->head = NULL;
        list->tail = NULL;
    }
    else
    {
        list->head       = list->head->next;
        list->head->prev = list->tail;
        list->tail->next = list->head;

        current = list->head;

        // Update the positions of each node
        for (size_t idx = 0; idx < list->size; idx++)
        {
            current->position -= 1;
            current = current->next;
        }
    }

    list->size--;

END:
    return head_node;
}

list_node_t * list_pop_tail(list_t * list)
{
    list_node_t * tail_node = NULL;

    if ((NULL == list) || (NULL == list->tail))
    {
        print_error("List is empty.");
        goto END;
    }

    tail_node = list->tail;

    if (list->head == list->tail)
    {
        list->head = NULL;
        list->tail = NULL;
    }
    else
    {
        list->tail       = list->tail->prev;
        list->tail->next = list->head;
        list->head->prev = list->tail;
    }

    list->size--;

END:
    return tail_node;
}

list_node_t * list_peek_head(list_t * list)
{
    list_node_t * node = NULL;

    if (NULL == list)
    {
        print_error("NULL argument passed.");
        goto END;
    }

    node = list->head;

END:
    return node;
}

list_node_t * list_peek_tail(list_t * list)
{
    list_node_t * node = NULL;

    if (NULL == list)
    {
        print_error("NULL argument passed.");
        goto END;
    }

    node = list->tail;

END:
    return node;
}

// Covers 4.3.2 Removing selected items from the circularly linked list
int list_remove(list_t * list, void ** item_to_remove)
{
    int           exit_code    = E_FAILURE;
    list_node_t * current_node = NULL;
    list_node_t * temp         = NULL;

    if (NULL == list)
    {
        print_error("NULL argument passed.");
        goto END;
    }

    current_node = list->head;

    for (size_t idx = 0; idx < list->size; idx++)
    {
        if (ERROR != (list->compare_function(item_to_remove, current_node)))
        {
            current_node->prev->next = current_node->next;
            current_node->next->prev = current_node->prev;

            temp = current_node->next; // Save off the next node

/***********************************************************************
 * NOTE: Typically, you would free the data for each node before
 *freeing the node itself.
 ***********************************************************************/
#if 0
            list->customfree(current_node->data);
            current_node->data = NULL;
#endif
            free(current_node);
            current_node = NULL;

            list->size--;

            current_node = temp;

            // Update the positions of each node
            for (uint32_t idx = current_node->position; idx < list->size; idx++)
            {
                current_node->position -= 1;
                current_node = current_node->next;
            }

            exit_code = E_SUCCESS;
            break;
        }

        current_node = current_node->next;
    }

END:
    return exit_code;
}

// Covers 4.3.2: Navigating through a circularly linked list
int list_foreach_call(list_t * list, ACT_F action_function)
{
    int           exit_code    = E_FAILURE;
    list_node_t * current_node = NULL;

    if ((NULL == list) || (NULL == action_function))
    {
        print_error("NULL argument passed.");
        goto END;
    }

    current_node = list->head;

    for (size_t idx = 0; idx < list->size; idx++)
    {
        action_function(current_node);
        current_node = current_node->next;
    }

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

// Covers 4.3.2 Finding the first occurence of an item in a circularly linked
// list
list_node_t * list_find_first_occurrence(list_t * list, void ** search_data)
{
    list_node_t * current_node = NULL;

    if (NULL == list)
    {
        print_error("NULL argument passed.");
        goto END;
    }

    current_node = list->head;

    for (size_t idx = 0; idx < list->size; idx++)
    {
        if (ERROR != (list->compare_function(search_data, current_node)))
        {
            goto END;
        }

        current_node = current_node->next;
    }

    current_node = NULL; // Set back to NULL if no match was found
END:
    return current_node;
}

list_t * list_find_all_occurrences(list_t * list, void ** search_data)
{
    list_t *      new_list     = NULL;
    list_node_t * current_node = NULL;
    int           check        = E_FAILURE;

    if (NULL == list)
    {
        print_error("NULL argument passed.");
        goto END;
    }

    if (0 == list->size)
    {
        print_error("Empty list.");
        goto END;
    }

    new_list = list_new(custom_free, custom_compare);
    if (NULL == new_list)
    {
        print_error("Unable to create new list.");
        goto END;
    }

    current_node = list->head;

    // Iterate over the whole list and store any matches in 'new_list'
    for (size_t idx = 0; idx < list->size; idx++)
    {
        if (ERROR != (list->compare_function(search_data, current_node)))
        {
            check = list_push_head(new_list, current_node->data);
            if (E_SUCCESS != check)
            {
                print_error("Unable to push node into list.");
                list_delete(&new_list);
                goto END;
            }
        }
    }

END:
    return new_list;
}

int list_sort(list_t * list)
{
    int           exit_code = E_FAILURE;
    list_node_t * temp_head = NULL;
    list_t *      temp_list = NULL;
    uint32_t      size      = 0;

    if (list == NULL)
    {
        print_error("NULL argument passed.");
        goto END;
    }

    temp_list = list_new(list->customfree, list->compare_function);
    if (NULL == temp_list)
    {
        print_error("Unable to create new list.");
        goto END;
    }

    /***********************************************************************
     * NOTE: Setting 'size' to 'list->size' because using 'list->size' here
     *       will have the side effect of updating each iteration.
     ***********************************************************************/
    size = list->size;

    // Remove the the contents of the old list and store them temporarily
    for (uint32_t idx = 0; idx < size; idx++)
    {
        temp_head = list_pop_tail(list);
        exit_code = list_push_tail(temp_list, temp_head->data);
        if (E_SUCCESS != exit_code)
        {
            print_error("Push tail failed.");
            goto END;
        }

        free(temp_head);
        temp_head = NULL;
    }

    // Add the contents back to the list in reverse order
    for (uint32_t idx = 0; idx < size; idx++)
    {
        temp_head = list_pop_head(temp_list);
        exit_code = list_push_tail(list, temp_head->data);
        if (E_SUCCESS != exit_code)
        {
            print_error("Push tail failed.");
            goto END;
        }

        free(temp_head);
        temp_head = NULL;
    }

    exit_code = E_SUCCESS;
END:
    list_delete(&temp_list);
    free(temp_list);
    return exit_code;
}

// Covers 4.3.2 Removing all items from the circularly linked list
int list_clear(list_t * list)
{
    int           exit_code    = E_FAILURE;
    list_node_t * current_node = NULL;
    list_node_t * next_node    = NULL;

    if (NULL == list)
    {
        print_error("NULL argument passed.");
        goto END;
    }

    current_node = list->head;
    if (NULL == current_node)
    {
        print_error("Empty list.");
        goto END;
    }

    for (size_t idx = 0; idx < list->size; idx++)
    {
        next_node = current_node->next;
/***********************************************************************
 * NOTE: Typically, you would free the data for each node before freeing
 * the node itself.
 ***********************************************************************/
#if 0
        list->customfree(current_node->data);
        current_node->data = NULL;
#endif
        free(current_node);
        current_node = NULL;
        current_node = next_node;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

// Covers 4.3.2: Destroying a circularly linked list
int list_delete(list_t ** list_address)
{
    int exit_code = E_FAILURE;

    if (NULL == *list_address)
    {
        print_error("NULL argument passed.");
        goto END;
    }

    exit_code = list_clear(*list_address);
    if (E_SUCCESS != exit_code)
    {
        print_error("Unable to clear list.");
        goto END;
    }

    free(*list_address);
    *list_address = NULL;

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

void custom_free(void * mem_addr)
{
    free(mem_addr);
    mem_addr = NULL;
}

/***********************************************************************
 * NOTE: STATIC FUNCTIONS LISTED BELOW
 ***********************************************************************/

static list_node_t * list_node_new(void * data)
{
    list_node_t * new_node = NULL;

    if (NULL == data)
    {
        print_error("NULL argument passed.");
        goto END;
    }

    new_node = calloc(1, sizeof(list_node_t));
    if (NULL == new_node)
    {
        print_error("CMR failure.");
        goto END;
    }

    new_node->data     = data;
    new_node->prev     = NULL;
    new_node->next     = NULL;
    new_node->position = 0;

END:
    return new_node;
}

/*** end of file ***/
