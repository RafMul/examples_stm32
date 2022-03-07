/*
 * BUFFER_RING.h
 *
 *  Created on: Feb 26, 2022
 *      Author: root
 */

#ifndef INC_BUFFER_RING_H_
#define INC_BUFFER_RING_H_

#define BUFFER_RING_SIZE   					30

//Status
//Object Buffer Ring
typedef enum {
	RB_STATE_OK = 0,
	BR_STATE_ERROR = 1
} BR_Status;

typedef struct {
	uint16_t Head;
	uint16_t Tail;
	uint8_t Buffer[BUFFER_RING_SIZE];

} BufferRing_t;

//Functions

//Write
BR_Status BR_Read (BufferRing_t *Buf, uint8_t *Value );
//Read
BR_Status BR_Write (BufferRing_t *Buf, uint8_t Value );
// Flush
void BR_Flush(BufferRing_t *Buf);

#endif /* INC_BUFFER_RING_H_ */
