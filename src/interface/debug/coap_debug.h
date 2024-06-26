/*******************************************************************************
 * Copyright (c)  2015  Dipl.-Ing. Tobias Rohde, http://www.lobaro.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *******************************************************************************/
#ifndef COM_DEBUG_H
#define COM_DEBUG_H

#define DEBUG_BUF_SIZE (500)
extern char dbgBuf[DEBUG_BUF_SIZE];

#define UART_PUTS hal_debug_puts
#define UART_PUT_ARRAY hal_debug_array


#define PUTS(...) \
	do { \
		UART_PUTS(__VA_ARGS__); \
	} while(0)

#define PRINTF(...) \
	do { \
		coap_sprintf(dbgBuf,__VA_ARGS__);\
		PUTS(dbgBuf); \
	} while(0)


#if defined(COAP_LL_ERROR) || defined(COAP_LL_INFO) || defined(COAP_LL_DEBUG)
	#define ERROR(...) \
	do { \
                PRINTF("[ERROR] "); \
                PRINTF(__VA_ARGS__); \
	} while(0)
#else
	#define ERROR(...) do{}while(0)
#endif

#if defined(COAP_LL_INFO) || defined(COAP_LL_DEBUG)
	#define INFO(...) \
	do { \
	        PRINTF(__VA_ARGS__); \
	} while(0)
#else
	#define INFO(...) do{}while(0)
#endif

#if defined(COAP_LL_DEBUG)
	#define DEBUG(...) \
	do { \
                PRINTF(__VA_ARGS__); \
	} while(0)

        #define DEBUG_ARRAY(msg, array, size) \
        do { \
                    UART_PUT_ARRAY(msg, array, size); \
        } while(0)

#else
	#define DEBUG(...) do{}while(0)
        #define DEBUG_ARRAY(msg, array, size) do{}while(0)
#endif

#define assert_coap(VAL) \
do { \
			if(!(VAL)) { PRINTF("!!! ASSERT FAILED [line: %d at %s]!!!\r\n", __LINE__, __FILE__); } \
} while(0)


#define PRINT_IPV6(IP) \
do { \
	PRINTF("%02x%02x:%02x%02x:%02x%02x"      \
		":%02x%02x:%02x%02x:%02x%02x"     \
		":%02x%02x:%02x%02x",               \
		( IP ) . u8 [  0 ], ( IP ) . u8 [  1 ], \
		( IP ) . u8 [  2 ], ( IP ) . u8 [  3 ], \
		( IP ) . u8 [  4 ], ( IP ) . u8 [  5 ], \
		( IP ) . u8 [  6 ], ( IP ) . u8 [  7 ], \
		( IP ) . u8 [  8 ], ( IP ) . u8 [  9 ], \
		( IP ) . u8 [ 10 ], ( IP ) . u8 [ 11 ], \
		( IP ) . u8 [ 12 ], ( IP ) . u8 [ 13 ], \
		( IP ) . u8 [ 14 ], ( IP ) . u8 [ 15 ] ); \
} while(0)

#define LOG_INFO(...) 	INFO(__VA_ARGS__)
#define LOG_ERROR(...) 	ERROR(__VA_ARGS__)
#define LOG_DEBUG(...) 	DEBUG(__VA_ARGS__)
#define LOG_DEBUG_ARRAY(msg, array, size) DEBUG_ARRAY(msg, array, size)

#endif
