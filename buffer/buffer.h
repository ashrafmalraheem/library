/******************************************************************************
 * Copyright (C) 2018 by Ashraf Abdalraheem
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Ashraf Abdalraheem are not liable for any
 * misuse of this material.
 *****************************************************************************/
/**
 * @file buffer.h
 * @brief Different buffers types
 *
 * This interface buffer type such as FIFO and LIFO circular buffer to handle
 * the data in slow peripherals. The implementation files contain the functions
 * that access these buffers.
 *
 * @author Ashraf Abdalraheem
 * @date April 18 2019
 *
 */
#ifndef __BUFFER_H__
#define __BUFFER_H__
#include "stdint.h"
//      Define your max buffer size here, take care about your available memory    //
#define BUFFER_MAX_SIZE    20
/***************************************************************************************
                          Buffer Status Enums
***************************************************************************************/
typedef enum {
	B_FULL,
	B_NOT_FULL,
	B_EMPTY,
	B_NOT_EMPTY,
	B_ERROR,
	B_NO_ERROR,
	B_ENOUGH_SPACE,
	B_NO_ENOUGH_SPACE,
	B_NULL
}B_status_e;

/***************************************************************************************
Generic buffer the type of it push or pop depends on how it is been accessed.
The implementation will determine if it is a FIFO or a LIFO.
***************************************************************************************/
typedef struct {
uint8_t     data[BUFFER_MAX_SIZE];  // data buffer
uint16_t    head;                          // index of the first item, initial is zero
uint16_t    tail;                          // index of the last item, initial is at the circular buffer tail
volatile B_status_e  is_empty;             // if the buffer is empty, initially is empty
volatile B_status_e  is_full;              // if the buffer is full, initially is not
}buffer_t;

//struct buffer_s;  // Struct declartion

/*
 * @brief push one byte data into a FIFO circular buffer
 *
 * This function will push one byte data into a circular FIFO buffer. Therefore, the newest
 * data will be stored at the tail of the current data stored in the buffer.
 * it aslo check whether the buffer is full or not or the buffer points to NULL
 * in the buffer and it returns the result accordingly
 *
 * @param buffer pointer
 * @param data
 * @return status of the push
 */
B_status_e fifo_buffer_push(buffer_t *buffer,uint8_t item);


/*
 * @brief pop one byte data from a FIFO circular buffer
 * @warning you should check if the buffer is empty or not before the pop or you get false data.
 *
 * This function will pop one byte data from a circular FIFO buffer. Therefore, the oldest
 * data will be returned. The buffer will point to the next oldest data item
 * it aslo check whether the buffer is empty or not or the buffer points to NULL
 * in the buffer and it returns the result accordingly
 *
 * @param buffer pointer
 * @return pop data or the status
 */
uint8_t fifo_buffer_pop(buffer_t *buffer);


/*
 * @brief Check if the buffer is full
 *
 * This function will return the status of the buffer whether it is full or not
 *
 * @param buffer pointer
 * @return fullness status of the buffer
 */
B_status_e fifo_buffer_full(buffer_t *buffer);


/*
 * @brief Check if the buffer is empty
 *
 * This function will return the status of the buffer whether it is empty or not
 * This function should be called before any pop request.
 *
 * @param buffer pointer
 * @return emptyness status of the buffer
 */
B_status_e fifo_buffer_empty(buffer_t *buffer);


/*
 * @brief initilize empty buffer
 *
 * This function will initialize an empty buffer and returns its address
 * if it fails on inilialize it will return NULL
 * It assigns the initial value of the head which is 0
 * It assigns the initial value of the tail which is BUFFER_MAX_SIZE
 * Buffer status flags (is_empty and is_full) are initialized also
 *
 * @param buffer pointer
 * @return address of the buffer
 */
buffer_t* fifo_buffer_init(buffer_t *buffer);

/*
 * @brief push a array of data into the FIFO buffer
 *
 * This function push an array of data to the buffer after it checks if the
 * available space is sufficient or not. It returns the result of the push
 *
 * @param buffer pointer
 * @param data arry pointer
 * @param length of data
 * @return status of the push
 */
B_status_e fifo_buffer_push_array(buffer_t *buffer,uint8_t *data,uint16_t length);

/*
 * @brief Check the available free space in the buffer
 *
 * This function will check the available space in the buffer and it
 * it returns the number of empty spaces in the specified buffer.
 *
 * @param buffer pointer
 * @return available free space
 */
uint16_t fifo_available_space(buffer_t *buffer);
#endif /*__BUFFER_H__*/
