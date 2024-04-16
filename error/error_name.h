#ifndef ERROR_NAME_H
#define ERROR_NAME_H

DEF_ERR("ptr is null")

DEF_ERR("NaN value received")

DEF_ERR("memory allocation error")

DEF_ERR("an error occurred while opening the file")

DEF_ERR("an error occurred while closing the file")

DEF_ERR("an error occurred while reading text from the file")

DEF_ERR("error when executing system command")

DEF_ERR("division by zero")

DEF_ERR("root of a negative number")

DEF_ERR("the number under the logarithm is less than 0")

DEF_ERR("null pointer to list")

DEF_ERR("incorrect list size")

DEF_ERR("invalid pointer to the head of the list")

DEF_ERR("invalid pointer to the tail of the list")

DEF_ERR("invalid pointer to the first free cell in the list")

DEF_ERR("invalid pointer to data array")

DEF_ERR("the connection between the list nodes is broken")

DEF_ERR("the connection between free nodes of the list is broken")

DEF_ERR("the number of nodes is incorrect")

DEF_ERR("pointer to the next element in data, pointing to itself")

DEF_ERR("pointer to the next element in free, pointing to itself")

DEF_ERR("your list is full of shit, call init")

DEF_ERR("error when inserting element into list")

DEF_ERR("error when deleting list item")

DEF_ERR("error when resizing list")

DEF_ERR("null pointer to hash table")

DEF_ERR("your hash table is full of shit, call init")

DEF_ERR("incorrect hash table size")

DEF_ERR("invalid pointer to array of data")

DEF_ERR("invalid pointer to hash function")

DEF_ERR("error when resizing hash table")

#endif //ERROR_NAME_H
