int get_numero_teclado (void);
int creaArrayFrecuencias (int inicial, int final);
  
void
configModo2 ()
{
  int inicial = get_numero_teclado();
  int final = get_numero_teclado();
  creaArrayFrecuencias (inicial, final);
  creaArrayFrecuencias (inicial, final);
}
