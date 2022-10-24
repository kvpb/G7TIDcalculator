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

#include <stdint.h> // int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t  https://www.ibm.com/docs/en/zos/2.4.0?topic=files-stdinth-integer-types https://opensource.apple.com/source/Libc/Libc-1158.50.2/include/stdint.h.auto.html
#include <limits.h> // USHRT_MAX, UINT_MAX  https://www.ibm.com/docs/en/zos/2.4.0?topic=files-limitsh-standard-values-limits-resources https://opensource.apple.com/source/xnu/xnu-344/EXTERNAL_HEADERS/machine/limits.h.auto.html
#include <stdlib.h> // NULL, STRTOL
#include <math.h> // pow, log2, log10, floor
#include <stdio.h> // PRINTF

uint8_t nbrlen( uint32_t number, int8_t base )
{
	if ( base != 2 && base != 10 )
		return 1;

	uint8_t length;

	length = 0;
	if ( base == 2 )
		length = (uint8_t) floor( log2( number ) + 1 );
	else if ( base == 10 )
		length = (uint8_t) floor( log10( number ) + 1 );

	return length;
}

int main( int count_argument, char* vector_argument[] )
{
	if ( count_argument != 3 )
		exit( 1 );

	int16_t integer_G7SID; // 0 < i_G7SID < 4294, i_G7SID = floor( n / 10^( l_max - 6 ) )
	int32_t integer_G7TID; // 0 < i_G7TID < 999999, i_G7TID = n mod 10^6
	uint32_t number_IDNo; // 0 < n_IDNo < 4294967295, n = i_TID + ( i_SID * 2^16 )
	uint16_t integer_SID; // 0 < i_SID < 65535, ( 2^32 - ( 65535 * 2^16 ) ) - 1 == max_SID
	uint16_t integer_TID; // 0 < i_TID < 65535, ( 2^32 - ( 65535 * 2^16 ) ) - 1 == max_TID
	uint16_t max_16bitunsigned; // 65535
	int32_t million; // 1000000
	uint32_t max_32bitunsigned; // 4294967295
	int8_t base /*radix*/; // positional numeral system: decimal system; radix: 10;
	uint8_t length_G7TID; // l_G7TID = 6 == l_max - l_G7SID
	uint8_t length_G7SID; // l_G7SID = l_max - l_G7TID == 4
	uint8_t length_maximum; // maximum value length: 10 == l_max = floor( b - log_b( i_max ) + 1 )

	integer_SID = (uint16_t) strtol(vector_argument[ 2 ], (char**) NULL, 10 ); /* SID */
	integer_TID = (uint16_t) strtol(vector_argument[ 1 ], (char**) NULL, 10 ); /* TID */
	max_16bitunsigned = (uint16_t) ( pow( 2, 16 ) - 1 ); // 65,535
	million = (int32_t) pow( 10, 6 ); // 1,000,000
	max_32bitunsigned = (uint32_t) ( pow( 2, 32 ) - 1 ); // 4,294,967,295
	base = (int8_t) 10; // decimal system
	length_G7TID = (uint8_t) 6; // G7TID length
	length_maximum = nbrlen( max_32bitunsigned, base ); //length_maximum = (uint8_t) ( floor( log10( max_32bitunsigned ) + 1 ) ); // maximum value length // Wait a second. My formula is wrong: log_10( 4294967295 ) == 9.6329598611, 10 - 9.6329598611 + 1 == 1.36; and so I later end up with 1 - 6. Why was I subtracting b from log_b( n ) + 1? I got it, I got it... Heh, I got shit.
	length_G7SID = (uint8_t) length_maximum - length_G7TID; // G7SID length
	number_IDNo = (uint32_t) ( integer_TID + ( integer_SID * pow( 2, 16 ) ) );
	integer_G7TID = (int32_t) ( number_IDNo % million );
	integer_G7SID = (int16_t) ( floor( (double) number_IDNo / pow( 10, ( length_maximum - length_G7SID ) ) ) );
	//printf("PRINTF:\tnumber_IDNo == %d\n", number_IDNo ); //	debug
	//printf("PRINTF:\tlength_maximum == %d\n", length_maximum ); //	debug
	//printf("PRINTF:\tnumber_IDNo / pow( 10, ( length_maximum - 6 ) ) == %f\n", number_IDNo / pow( 10, length_maximum - ( length_maximum - length_G7SID ) ) /*number_IDNo / pow( 10, ( length_maximum - 6 ) )*/ /* And I did not calculate this correctly too. */ ); //	debug
	//printf("PRINTF:\tinteger_G7SID == %d\n", integer_G7SID ); //	debug

	printf("TID:\t%s\nSID:\t%s\nG7TID:\t%i\nG7SID:\t%hi\n", vector_argument[ 1 ], vector_argument[ 2 ], integer_G7TID, integer_G7SID );

	return 0;
}

/*//	main.c
////	G8TID Calculator
////
////	Karl V. P. B. `kvpb` AKA Karl Thomas George West `ktgw`
////	+1 (DDD) DDD-DDDD
////	+33 A BB BB BB BB
////	local-part@domain
////	local-part@domain
////	https://www.linkedin.com/in//
////	https://twitter.com/ktgwkvpb
////	https://github.com/kvpb
*///	https://vm.tiktok.com/ZSwAmcFh/
