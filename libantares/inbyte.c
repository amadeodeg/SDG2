char
inbyte (void)
{
  char ch;
  asm volatile( "movel #0x10, %%d0\n\t" "trap #15\n\t" "movel %%d1,%0\n\t"
		: "=d" (ch) :
		: "d0", "d1");
  return ch;
}
