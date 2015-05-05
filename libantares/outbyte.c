int
outbyte (char ch)
{
  asm volatile( "moveb %0,%%d1\n\t" "movel #0x13, %%d0\n\t" "trap #15\n\t"
		: : "d" (ch)
		: "d0", "d1");
  return 0;
}
