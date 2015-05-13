int get_numero_teclado (void);
int creaArrayFrecuencias (int inicial, int final);
  
int
main (int argc, char const *argv[])
{
  int inicial = get_numero_teclado();
  int final = get_numero_teclado();
  creaArrayFrecuencias (inicial, final);
  creaArrayFrecuencias (inicial, final);
  return 0;
}
