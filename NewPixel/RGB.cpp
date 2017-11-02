// Include our header
#include "RGB.h"

// Constructor
RGB::RGB( uint8_t pin, uint16_t numPixels ) : pin( pin ), numPixels( numPixels ), numBytes( 3*numPixels )
{
  // Allocate the storage for the pixels and ...
  pixels = malloc( numBytes );

  // ... clear it.
  memset( pixels, 0, numBytes );

  // Set the output pin
  pinMode( pin, OUTPUT );
  digitalWrite( pin, LOW );

  // Set the port and pin mask
  port    = portOutputRegister( digitalPinToPort( pin ) );
  pinMask = digitalPinToBitMask( pin );
}

// Destructor
RGB::~RGB()
{
  if( pixels )
  {
    free( pixels );
  }
}

// Clear the array of pixels
void RGB::clear()
{
  memset( pixels, 0, numBytes );
}

// Set the color of a particular pixel
void RGB::setColor( uint16_t pixel, uint8_t red, uint8_t green, uint8_t blue )
{
  if( pixel <= numPixels )
  {
    uint8_t *p = &pixels[ pixel * 3 ];
    p[ rOffset ] = red;
    p[ gOffset ] = green;
    p[ bOffset ] = blue;
  }
}

// Show the colors in the array of pixels
void RGB::show()
{
  // Create the local variables
  volatile uint16_t  i   = numBytes;
  volatile uint8_t  *ptr = pixels;
  volatile uint8_t   b   = *ptr++;    // This is the "current" byte

  // The is the current value of the port with the output pin set high.
  volatile uint8_t  hi = *port |  pinMask;

  // This is the current value of the port with the output pin set low.
  volatile uint8_t  lo =  *port & ~pinMask;
      
  // This is the next value to be set
  volatile uint8_t next = lo;

  //  This the number of bits yet to be written
  volatile uint8_t bit = 8;

  // The timing below is critical, so turn off interrupts until it is complete.
  noInterrupts();

  // This is the work horse!
  asm volatile(
     "head20:"                   "\n\t" // Clk  Pseudocode    (T =  0)
      "st   %a[port],  %[hi]"    "\n\t" // 2    PORT = hi     (T =  2)
      "sbrc %[byte],  7"         "\n\t" // 1-2  if(b & 128)
       "mov  %[next], %[hi]"     "\n\t" // 0-1   next = hi    (T =  4)
      "dec  %[bit]"              "\n\t" // 1    bit--         (T =  5)
      "st   %a[port],  %[next]"  "\n\t" // 2    PORT = next   (T =  7)
      "mov  %[next] ,  %[lo]"    "\n\t" // 1    next = lo     (T =  8)
      "breq nextbyte20"          "\n\t" // 1-2  if(bit == 0) (from dec above)
      "rol  %[byte]"             "\n\t" // 1    b <<= 1       (T = 10)
      "rjmp .+0"                 "\n\t" // 2    nop nop       (T = 12)
      "nop"                      "\n\t" // 1    nop           (T = 13)
      "st   %a[port],  %[lo]"    "\n\t" // 2    PORT = lo     (T = 15)
      "nop"                      "\n\t" // 1    nop           (T = 16)
      "rjmp .+0"                 "\n\t" // 2    nop nop       (T = 18)
      "rjmp head20"              "\n\t" // 2    -> head20 (next bit out)
     "nextbyte20:"               "\n\t" //                    (T = 10)
      "ldi  %[bit]  ,  8"        "\n\t" // 1    bit = 8       (T = 11)
      "ld   %[byte] ,  %a[ptr]+" "\n\t" // 2    b = *ptr++    (T = 13)
      "st   %a[port], %[lo]"     "\n\t" // 2    PORT = lo     (T = 15)
      "nop"                      "\n\t" // 1    nop           (T = 16)
      "sbiw %[count], 1"         "\n\t" // 2    i--           (T = 18)
       "brne head20"             "\n"   // 2    if(i != 0) -> (next byte)
      : [port]  "+e" (port),
        [byte]  "+r" (b),
        [bit]   "+r" (bit),
        [next]  "+r" (next),
        [count] "+w" (i)
      : [ptr]    "e" (ptr),
        [hi]     "r" (hi),
        [lo]     "r" (lo));

  // The timing critical part is done so we can turn interrupts back on.
  interrupts();
  
  // Issue the "set" signal
  digitalWrite( pin, LOW );
  delayMicroseconds( 60 );
}
