/*
 * buffer_ring.c
 *
 *  Created on: Feb 26, 2022
 *      Author: root
 */


#include "main.h"
#include "buffer_ring.h"

BR_Status BR_Read(BufferRing_t *Buf, uint8_t *Value) {
	if (Buf->Head == Buf->Tail) {
		return BR_STATE_ERROR;
	}

	*Value = Buf->Buffer[Buf->Tail];
	Buf->Tail = (Buf->Tail + 1) % BUFFER_RING_SIZE;
	return RB_STATE_OK;
}

BR_Status BR_Write(BufferRing_t *Buf, uint8_t Value) {
	uint8_t HeadTmp = (Buf->Head + 1) % BUFFER_RING_SIZE;

	if (HeadTmp == Buf->Tail) {
		return BR_STATE_ERROR;
	}
	Buf->Buffer[Buf->Head] = Value;
	Buf->Head = HeadTmp;
	return RB_STATE_OK;
}

void BR_Flush(BufferRing_t *Buf) {
	Buf->Head = 0;
	Buf->Tail = 0;
}
