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
 * @file buffer.c
 * @brief Different buffers types
 *
 * This implement buffer type such as FIFO and LIFO circular buffer to handle 
 * the data in slow peripherals. The implementation files contain the functions
 * that access these buffers.
 *
 * @author Ashraf Abdalraheem
 * @date April 18 2019
 *
 */
 
////////////////////////////////////////////////////////////////////////////////////////
                   /* enter necessary header files for visibility */
////////////////////////////////////////////////////////////////////////////////////////

#include "buffer.h"
#include "stdint.h"



buffer_t* fifo_buffer_init(buffer_t buffer){
	buffer->head = 0;
	buffer->tail = BUFFER_MAX_SIZE;
	buffer->is_empty = B_EMPTY;
	buffer->is_full  = B_NOT_FULL;
	return buffer;
}
///////==================================================================///////////////////
/******************************************************************************************/
///////==================================================================///////////////////
B_status_e fifo_buffer_push(buffer_t buffer,uint8_t item){
	B_status_e status = fifo_buffer_full(buffer);
	//**************** Check if the pointer is valid and the buffer is not full **********//
	if(status == B_NOT_FULL){
		
		//   if the tail in the last position of the array move it to the first one
		if(buffer->tail == BUFFER_MAX_SIZE){
			buffer->tail = 0;
		}else{
			buffer->tail++;
		}
		buffer->data[buffer->tail]=item;
		buffer->is_empty = B_NOT_EMPTY;
		return B_NO_ERROR;
	}
	else{
	    return status;
	}
}
///////==================================================================///////////////////
/******************************************************************************************/
///////==================================================================///////////////////
B_status_e fifo_buffer_full(buffer_t buffer){
	if(buffer == NULL){
		return B_NULL;
	} // ******* if the head is at 0 position and tail at the end
	  // ******* it means it is full Or the tail is just before the head
	if(((buffer->tail - buffer->head) == (BUFFER_MAX_SIZE - 1)) 
		|| ((buffer->head - buffer->tail) == 1))
	{
		buffer->is_full = B_FULL;
		return B_FULL;
	}
	return B_NOT_FULL;
}
///////==================================================================///////////////////
/******************************************************************************************/
///////==================================================================///////////////////
uint16_t fifo_available_space(buffer_t buffer){
	uint16_t available_space = (BUFFER_MAX_SIZE-1-(buffer->tail-buffer->head));
	if(B_FULL == fifo_buffer_full(buffer))
	{
		return 0;
	}else if(B_EMPTY == fifo_buffer_empty(buffer)){
		return BUFFER_MAX_SIZE;
	}else{
		return (available_space<BUFFER_MAX_SIZE) ? available_space : (BUFFER_MAX_SIZE - available_space) ;
	}
	return B_NULL;
}
///////==================================================================///////////////////
/******************************************************************************************/
///////==================================================================///////////////////
B_status_e fifo_buffer_empty(buffer_t buffer){
	if(buffer == NULL){
		return B_NULL;
	}
	return buffer->is_empty;
}
///////==================================================================///////////////////
/******************************************************************************************/
///////==================================================================///////////////////
uint8_t fifo_buffer_pop(buffer_t buffer){
	uint8_t data = buffer->data[buffer->head];
	if(buffer_t == NULL){
		return B_NULL;
	}
	if (fifo_buffer_empty(buffer)){
		return B_EMPTY;
	}
	///***  If the head and tail points to the same location it means this is the last element in the buffer ***////
	if(buffer->head == buffer->tail){
		buffer->is_empty = B_EMPTY;    // Now the buffer is empty
	}else{
		buffer->is_empty = B_NOT_EMPTY;
		if(buffer->head == BUFFER_MAX_SIZE - 1){
			buffer->head = 0;
		}else{
			buffer->head++;
		}
	}
	return data;
}
///////==================================================================///////////////////
/******************************************************************************************/
///////==================================================================///////////////////
B_status_e fifo_buffer_push_array(buffer_t buffer,uint8_t *data,uint16_t length){
	if(buffer == NULL){
		return B_NULL;
	}
	if(length < fifo_available_space(buffer)){
		return B_NO_ENOUGH_SPACE;
	}
	for(uint16_t i=0;i<length;i++){
		fifo_buffer_push(buffer,*(data+i));
	}
	return B_NO_ERROR;
}
