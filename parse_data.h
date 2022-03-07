/*
 * parse_data.h
 *
 *  Created on: Mar 6, 2022
 *      Author: root
 */

#ifndef INC_PARSE_DATA_H_
#define INC_PARSE_DATA_H_

#define ENDLINE  			'0'

void  Parse_SaveLine(BufferRing_t *Buf, uint8_t *LineData);
void Parse_Data(uint8_t *Data);

#endif /* INC_PARSE_DATA_H_ */
