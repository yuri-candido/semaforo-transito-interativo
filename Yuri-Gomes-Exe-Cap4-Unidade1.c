#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define LED_VERDE 11
#define LED_VERMELHO 13
#define BOTAO 5
#define BUZZERPINO 10

const uint16_t PERIOD = 7812;
uint16_t dutycycle = 1000;
const float DIVIDER_PWM = 16.0;

alarm_id_t alarm_id_verde;

void setup_pwm() { // configuração do pwm
    uint slice;
    gpio_set_function(BUZZERPINO, GPIO_FUNC_PWM);
    slice = pwm_gpio_to_slice_num(BUZZERPINO);
    pwm_set_clkdiv(slice, DIVIDER_PWM);
    pwm_set_wrap(slice, PERIOD);
    pwm_set_gpio_level(BUZZERPINO, dutycycle);
    pwm_set_enabled(slice, true);
}

int64_t callback_vermelho(alarm_id_t id, void *user_data);
void isr_botoes(uint gpio, uint32_t events);

// Callback para acionar o led amarelo
int64_t callback_amarelo(alarm_id_t id, void *user_data) {
    gpio_set_irq_enabled_with_callback(BOTAO, GPIO_IRQ_EDGE_FALL, false, &isr_botoes);
    add_alarm_in_ms(3000, callback_vermelho, NULL, false); // alarme que aciona a função de callback "callback_vermelho" depois de 3s
    printf("Sinal: Amarelo\n");
    gpio_put(LED_VERMELHO, 1);
    return 0;
}

// Callback para acionar o led verde
int64_t callback_verde(alarm_id_t id, void *user_data) {
    gpio_set_irq_enabled_with_callback(BOTAO, GPIO_IRQ_EDGE_FALL, true, &isr_botoes);
    dutycycle = 0;
    pwm_set_gpio_level(BUZZERPINO, dutycycle);
    alarm_id_verde = add_alarm_in_ms(10000, callback_amarelo, NULL, false); // alarme que aciona a função de callback "callback_amarelo" depois de 10s
    printf("Sinal: Verde\n");
    gpio_put(LED_VERMELHO, 0);
    gpio_put(LED_VERDE, 1);
    return 0;
}

// Callback para acionar o led vermelho
int64_t callback_vermelho(alarm_id_t id, void *user_data) {
    gpio_set_irq_enabled_with_callback(BOTAO, GPIO_IRQ_EDGE_FALL, false, &isr_botoes);
    add_alarm_in_ms(10000, callback_verde, NULL, false); // alarme que aciona a função de callback "callback_verde" depois de 10s
    printf("Sinal: Vermelho\n");
    gpio_put(LED_VERDE, 0);
    gpio_put(LED_VERMELHO, 1);
    dutycycle = 1000;
    pwm_set_gpio_level(BUZZERPINO, dutycycle);
    return 0;
}

// função que é acionada ao apertar o botão, o qual liga o led amarelo e, após 3s, desliga-o e liga o vermelho.
void isr_botoes(uint gpio, uint32_t events) { 
  cancel_alarm(alarm_id_verde); // cancela o evento de alarme que é definido dentro da função de "callback_verde"
  printf("Botão de pedestres acionado\n");
  gpio_put(LED_VERDE, 1);
  gpio_put(LED_VERMELHO, 1);
  add_alarm_in_ms(3000, callback_vermelho, NULL, false); // alarme que aciona a função de callback "callback_vermelho" depois de 3s
}

int main()
{
    stdio_init_all();

    // Inicializa os leds 
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_put(LED_VERMELHO, 1);
    pwm_set_gpio_level(BUZZERPINO, dutycycle);

    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_put(LED_VERDE, 0);

    // Inicializa botão como pull_up
    gpio_init(BOTAO);
    gpio_set_dir(BOTAO, GPIO_IN);
    gpio_pull_up(BOTAO);

    setup_pwm(); // inicializa pwm do buzzer
      
    printf("Sinal: Vermelho\n");

    add_alarm_in_ms(10000, callback_verde, NULL, false); // alarme que aciona a função de callback "callback_verde" depois de 10s

    while (true) {
        sleep_ms(1000);
    }
}
