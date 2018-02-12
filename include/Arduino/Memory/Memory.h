/*
Copyright 2013-2016 Ryan Fobel and Christian Fobel

This file is part of the Arduino Memory library.

The Arduino Memory Library is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

The Arduino Memory Library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with the Arduino Memory Library.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _MEMORY_H
#define _MEMORY_H

#include <stdint.h>
#include <stdlib.h>

#ifdef __AVR__
#include <avr/io.h> //RAMEND, SP
typedef uint16_t umemory_address_t;
typedef int16_t memory_address_t;

/*
 * Based on code from several sources:
 * http://www.arduino.cc/playground/Code/AvailableMemory
 * http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1213583720
 * http://forum.pololu.com/viewtopic.php?f=10&t=989&view=unread#p4218
 *
 * Reference figure of AVR memory areas .data, .bss, heap (all growing upwards),
 * then stack growing downward:
 * http://www.nongnu.org/avr-libc/user-manual/malloc.html
 */

extern umemory_address_t __data_start;
extern umemory_address_t __data_end;
extern umemory_address_t __bss_start;
extern umemory_address_t __bss_end;
extern umemory_address_t __heap_start;
extern void *__brkval;
#else
typedef uint32_t umemory_address_t;
typedef int32_t memory_address_t;

#define RAMEND 0
#define SP 0
#endif

#ifdef __AVR__
inline memory_address_t ram_size() {
  return (memory_address_t) RAMEND - (memory_address_t) &__data_start;
}
inline memory_address_t data_size() {
  return (memory_address_t) &__data_end - (memory_address_t) &__data_start;
}
inline memory_address_t bss_size() {
  return (memory_address_t) &__bss_end - (memory_address_t) &__bss_start;
}
inline memory_address_t heap_size() {
  if((memory_address_t)__brkval==0) { // no heap
    return 0;
  }
  return (memory_address_t) __brkval - (memory_address_t) &__heap_start;
}
inline memory_address_t stack_size() {
  return (memory_address_t) RAMEND - (memory_address_t) SP;
}
inline memory_address_t free_memory() {
  if((memory_address_t)__brkval==0) { // no heap
    return (memory_address_t) SP - (memory_address_t) &__bss_end;
  }
  return (memory_address_t) SP - (memory_address_t) __brkval;
}
#else
inline memory_address_t ram_size() { return 0; }
inline memory_address_t data_size() { return 0; }
inline memory_address_t bss_size() { return 0; }
inline memory_address_t heap_size() { return 0; }
inline memory_address_t stack_size() { return 0; }
inline memory_address_t free_memory() {
    /* Code from [Teensy 3 forum][1].
     *
     * [1]: https://forum.pjrc.com/threads/23256-Get-Free-Memory-for-Teensy-3-0?p=34242&viewfull=1#post34242 */
    uint32_t stackTop;
    uint32_t heapTop;

    // Current position of the stack.
    stackTop = (uint32_t) &stackTop;

    // Current position of heap.
    void* hTop = malloc(1);
    heapTop = (uint32_t) hTop;
    free(hTop);

    // The difference is the free, available ram.
    return stackTop - heapTop;
}
#endif

#endif
