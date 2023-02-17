/* Include the system headers we need */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Include our header */
#include "vector.h"

/* Define what our struct is */
struct vector_t
{
    size_t size;
    int *data;
};

/* Utility function to handle allocation failures. In this
   case we print a message and exit. */
static void allocation_failed()
{
    fprintf(stderr, "Out of memory.\n");
    exit(1);
}

/* Bad example of how to create a new vector */
vector_t *bad_vector_new()
{
    /* Create the vector and a pointer to it */
    vector_t *retval, v;
    retval = &v;

    /* Initialize attributes */
    retval->size = 1;
    retval->data = malloc(sizeof(int));
    if (retval->data == NULL)
    {
        allocation_failed();
    }

    retval->data[0] = 0;
    // Bad reason: retval points a local vector_t.
    return retval;
}

/* Another suboptimal way of creating a vector */
vector_t also_bad_vector_new()
{
    /* Create the vector */
    vector_t v;

    /* Initialize attributes */
    v.size = 1;
    v.data = malloc(sizeof(int));
    if (v.data == NULL)
    {
        allocation_failed();
    }
    v.data[0] = 0;
    // Bad reason: almost same as the previous one.
    return v;
}

/* Create a new vector with a size (length) of 1
   and set its single component to zero... the
   RIGHT WAY */
vector_t *vector_new()
{
    /* Declare what this function will return */
    vector_t *retval;

    /* First, we need to allocate memory on the heap for the struct */
    retval = (vector_t *)malloc(sizeof(struct vector_t));

    /* Check our return value to make sure we got memory */
    if (!retval)
    {
        allocation_failed();
    }

    /* Now we need to initialize our data.
       Since retval->data should be able to dynamically grow,
       what do you need to do? */
    retval->size = 1;
    retval->data = (int *)calloc(retval->size, sizeof(int));

    /* Check the data attribute of our vector to make sure we got memory */
    if (!retval->data)
    {
        free(retval); // Why is this line necessary?
        allocation_failed();
    }

    /* and return... */
    return retval;
}

/* Return the value at the specified location/component "loc" of the vector */
int vector_get(vector_t *v, size_t loc)
{

    /* If we are passed a NULL pointer for our vector, complain about it and exit. */
    if (v == NULL)
    {
        fprintf(stderr, "vector_get: passed a NULL vector.\n");
        abort();
    }

    /* If the requested location is higher than we have allocated, return 0.
     * Otherwise, return what is in the passed location.
     */
    if (loc < v->size)
    {
        return v->data[loc];
    }
    else
    {
        return 0;
    }
}

/* Free up the memory allocated for the passed vector.
   Remember, you need to free up ALL the memory that was allocated. */
void vector_delete(vector_t *v)
{
    /* YOUR SOLUTION HERE */
    free(v->data);
    v->data = NULL;
    free(v);
    v = NULL;
}

/* Set a value in the vector. If the extra memory allocation fails, call
   allocation_failed(). */
void vector_set(vector_t *v, size_t loc, int value)
{
    /* What do you need to do if the location is greater than the size we have
     * allocated?  Remember that unset locations should contain a value of 0.
     */

    /* YOUR SOLUTION HERE */
    if (loc >= v->size)
    {
        int *prevData = v->data;
        v->data = (int *)calloc(loc + 1, sizeof(int));
        if (!v->data)
        {
            vector_delete(v);
            allocation_failed();
        }
        memcpy(v->data, prevData, v->size * sizeof(int));
        free(prevData);
        v->size = loc + 1;
    }
    v->data[loc] = value;
}