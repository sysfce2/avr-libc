#include <stdlib.h>
#include <avr/pgmspace.h>

#if __SIZEOF_LONG_LONG__ != 8
/* With -mint8 we don't have 64-bit int. */
int main (void)
{
  return 0;
}
#else

#define VAL 0x0102030405060708

PROGMEM_FAR
const uint64_t data[] = { VAL, 2 * VAL, 7 * VAL };

uint64_t get_val (uint8_t i)
{
  uint64_t v = VAL;
  if (i == 1) v *= 2;
  if (i == 2) v *= 7;
  return v;
}

__attribute__((noinline,noclone))
void test (uint8_t i)
{
  if (pgm_read_u64_far (pgm_get_far_address (data[0])) != get_val (0))
    exit (__LINE__);

  uint_farptr_t pf = pgm_get_far_address (data[0]) + i * sizeof (uint64_t);
  if (pgm_read_u64_far (pf) != get_val (i))
    exit (__LINE__);
}

int main (void)
{
  test (1);
  test (2);
  return 0;
}
#endif /* long long = 8 bytes */
