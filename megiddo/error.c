
volatile int megiddo_error=0;

const char*
mensaje_error (int err)
{
  static const char* msg[] = {
    /*0*/ "Error desconocido",
    /*1*/ "Turno del jugador agotado",
  };
  if (err > 1) err = 0;
  return msg[err];
}
