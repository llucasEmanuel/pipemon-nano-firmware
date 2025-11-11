#include "Sleep.h"

#include <avr/wdt.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

static volatile int remainingSeconds;

// Executado logo após voltar do sleep
ISR(WDT_vect) {
  if (remainingSeconds > 0) {
    remainingSeconds--;
  }
}

static void setupWatchdog() {
  // Limpa o flag de reset
  MCUSR &= ~(1 << WDRF);
  
  cli(); // Desabilita interrupções globais
  
  // Entra em modo de configuração do WDT (sequência de tempo crítica)
  WDTCSR |= (1 << WDCE) | (1 << WDE);
  
  // Define prescaler para 1s (WDTO_1S = 0b000110)
  // E ativa o modo de INTERRUPÇÃO (WDIE) em vez de reset
  WDTCSR = (1 << WDIE) | (0b000110); 
  
  sei(); // Habilita interrupções globais
}

void Sleep::sleep(int seconds) {
  remainingSeconds = seconds;

  while (remainingSeconds > 0) {
    // Configura o watchdog para acordar daqui 1s
    setupWatchdog()

    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();

    sleep_cpu();

    // CPU acorda quando a ISR termina

    sleep_disable();
  }

  cli();
  wdt_disable();
  sei();
}
