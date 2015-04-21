void rutina_tout0 (void);
void rutina_tout1 (void);

void __attribute__((interrupt_handler)) _prep_TOUT0 (void)
{
  rutina_tout0 ();
}

void __attribute__((interrupt_handler)) _prep_TOUT1 (void)
{
  //rutina_tout1 ();
}

