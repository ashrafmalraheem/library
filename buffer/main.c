#include "stdio.h"
#include "stdint.h"
#include "buffer.h"
#include "stdlib.h"
void main(){

char status_c [9][20] =	{
	"B_FULL",
	"B_NOT_FULL",
	"B_EMPTY",
	"B_NOT_EMPTY",
	"B_ERROR",
	"B_NO_ERROR",
	"B_ENOUGH_SPACE",
	"B_NO_ENOUGH_SPACE",
	"B_NULL"
	};
	buffer_t my = {{0},0,BUFFER_MAX_SIZE,B_EMPTY,B_NOT_FULL};
	buffer_t *my_buffer= (buffer_t*) malloc(sizeof(buffer_t));
	//printf("1- Head = %d  Tail = %d\n",my_buffer->head,my_buffer->tail);
	fifo_buffer_init(my_buffer);
	/* printf("2- Head = %d  Tail = %d\n",my_buffer->head,my_buffer->tail);
	//printf("Push:  %s\n",status_c + fifo_buffer_push(my_buffer,3));
	//printf("3- Head = %d  Tail = %d\n",my_buffer->head,my_buffer->tail);
	//fifo_buffer_push(my_buffer,4);
	//fifo_buffer_push(my_buffer,5);
	//printf("Tail = %d  , Data on Tail = %d\n",my_buffer->tail,my_buffer->data[my_buffer->tail]);
        printf("4- Head = %d  Tail = %d\n",my_buffer->head,my_buffer->tail);
	fifo_buffer_push(my_buffer,6);
	printf("5- Head = %d  Tail = %d\n",my_buffer->head,my_buffer->tail);
	printf("first:  %d    %s\n",fifo_buffer_pop(my_buffer),status_c + fifo_buffer_pop(my_buffer));
	printf("Tail = %d  , Data on Tail = %d\n",my_buffer->tail,my_buffer->data[my_buffer->tail]);*/
	for(uint8_t i = 1;i<2*BUFFER_MAX_SIZE;i++){
		fifo_buffer_push(my_buffer,i);
		printf("Push:  %d\n",i);
		if(0){
			fifo_buffer_pop(my_buffer);
		}
		
	}
	printf("\n1-Head: %d \n",my_buffer->head);
	printf("\n1-Tail: %d \n",my_buffer->tail);
	fifo_buffer_pop(my_buffer);
	printf("\n2-Head: %d \n",my_buffer->head);
	printf("\n2-Tail: %d \n",my_buffer->tail);
	fifo_buffer_push(my_buffer,80);
	fifo_buffer_pop(my_buffer);
	printf("\n3-Head: %d \n",my_buffer->head);
	printf("\n3-Tail: %d \n",my_buffer->tail);	
	fifo_buffer_push(my_buffer,90);
	printf("\n4-Head: %d \n",my_buffer->head);
	printf("\n4-Tail: %d \n",my_buffer->tail);
	for(uint8_t i=0;i<BUFFER_MAX_SIZE;i++){
		printf("Pop:  %d\n",fifo_buffer_pop(my_buffer));
				
		//printf("index: %d  value: %d\n",i,my_buffer->data[i]);
	}
	for(uint8_t i=0;i<BUFFER_MAX_SIZE;i++){
		printf("Pop:  %d\n",fifo_buffer_pop(my_buffer));		
		//printf("index: %d  value: %d\n",i,my_buffer->data[i]);
	}
	printf("\n\nHead: %d \n",my_buffer->head);
	return ;
}

