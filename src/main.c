/*//	Copyright 2022 Karl Vincent Pierre Bertin
////
////	Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
////
////	1.	Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
////
////	2.	Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
////
////	3.	Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
////
*///	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "../include/header.h"

int main( int count_argument, char* vector_argument[] )
{
	if ( count_argument != 3 )
		exit( 1 );

	int16_t integer_G7SID; // G7SID: 0 < i_G7SID < 4294, i_G7SID = floor( n / 10^( l_max - 6 ) )
	int32_t integer_G7TID; // G7TID: 0 < i_G7TID < 999999, i_G7TID = n mod 10^6
	uint32_t integer_IDNo; // G7ID ('IDNo'): 0 < n_IDNo < 4294967295, n = i_TID + ( i_SID * 2^16 )
	uint16_t integer_TSV; // TSV: 0 < i_TSV < 2^16 - 1, i_TSV = ( i_TID XOR i_SID ) >> 4
	uint8_t integer_TRV; // TRV: 0 < i_TRV < 2^16 - 1, i_TRV = ( i_TID XOR i_SID ) & 0xF
	uint16_t integer_SID; // SID: 0 < i_SID < 65535, ( 2^32 - ( 65535 * 2^16 ) ) - 1 == max_SID
	uint16_t integer_TID; // TID: 0 < i_TID < 65535, ( 2^32 - ( 65535 * 2^16 ) ) - 1 == max_TID
	//uint16_t max_16bitunsigned; // 16-bit unsigned maximum value: 65535
	uint16_t result; // i_TID XOR i_SID
	int32_t million; // 'mask': 10^6 == 1000000
	uint32_t max_32bitunsigned; // 32-bit unsigned maximum value: 4294967295
	int8_t base /*radix*/; // positional numeral system: decimal system ( radix = 10 )
	uint8_t length_G7TID; // G7TID length: l_G7TID = 6 == l_max - l_G7SID
	uint8_t length_G7SID; // G7SID length: l_G7SID = l_max - l_G7TID == 4
	uint8_t length_maximum; // maximum value length: l_max = floor( b - log_b( i_max ) + 1 ) == 10

	integer_SID = (uint16_t) strtol(vector_argument[ 2 ], (char**) NULL, 10 );
	integer_TID = (uint16_t) strtol(vector_argument[ 1 ], (char**) NULL, 10 );
	//max_16bitunsigned = (uint16_t) ( pow( 2, 16 ) - 1 );
	result = integer_TID ^ integer_SID;
	integer_TSV = (uint16_t) ( ( result ) >> 4 );
	integer_TRV = (uint8_t) ( ( result ) & 0xF );
	million = (int32_t) pow( 10, 6 );
	max_32bitunsigned = (uint32_t) ( pow( 2, 32 ) - 1 );
	base = (int8_t) 10;
	length_G7TID = (uint8_t) 6;
	length_maximum = nbrlen( max_32bitunsigned, base );
	length_G7SID = (uint8_t) length_maximum - length_G7TID;
	integer_IDNo = (uint32_t) ( integer_TID + ( integer_SID * pow( 2, 16 ) ) );
	integer_G7TID = (int32_t) ( integer_IDNo % million );
	integer_G7SID = (int16_t) ( floor( (double) integer_IDNo / pow( 10, ( length_maximum - length_G7SID ) ) ) );

	printf("TID:\t%i\nSID:\t%i\nTSV:\t%i\nTRV:\t%i\nG7TID:\t%i\nG7SID:\t%hi\n", integer_TID, integer_SID, integer_TSV, integer_TRV, integer_G7TID, integer_G7SID );

	return 0;
}

/*//	main.c
////	CG7TID (G7TID Calculator)
////
////	Karl V. P. B. `kvpb`	AKA Karl Thomas George West `ktgw`
////	+33 A BB BB BB BB		+1 (DDD) DDD-DDDD
////	local-part@domain
////	https://twitter.com/ktgwkvpb
*///	https://github.com/kvpb
