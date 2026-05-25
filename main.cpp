#include <xenon/xenon.h>
#include <input/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Constantes de Deadzone (5% do valor maximo)
const int ANALOG_DEADZONE = 1638; 
const int TRIGGER_DEADZONE = 13;   

int main() {
    // Inicializa o video e os componentes do Xbox 360
    xenos_init();
    console_init();
    usb_init();

    printf("Lendo controle do Xbox 360 (Nuvem Float + 5%% Deadzone)...\n");

    while (1) {
        // Atualiza o estado dos perifericos/controles
        usb_do_poll();

        struct controller_data_s ctrl;
        if (get_controller_data(&ctrl, 0)) { // Le o primeiro controle
            
            // --- BOTOES LS E RS ---
            if (ctrl.buttons & BUTTON_LOGO) { // Exemplo de botao (LibXenon usa mapeamentos proprios)
                printf("Botao do Controle Pressionado!\n");
            }

            // --- GATILHOS (Normalizados para Float) ---
            float leftTrigger = 0.0f;
            float rightTrigger = 0.0f;

            if (ctrl.lt > TRIGGER_DEADZONE) {
                leftTrigger = (float)(ctrl.lt - TRIGGER_DEADZONE) / (255.0f - TRIGGER_DEADZONE);
            }
            if (ctrl.rt > TRIGGER_DEADZONE) {
                rightTrigger = (float)(ctrl.rt - TRIGGER_DEADZONE) / (255.0f - TRIGGER_DEADZONE);
            }

            if (leftTrigger > 0.0f)  printf("LT Float: %f\n", leftTrigger);
            if (rightTrigger > 0.0f) printf("RT Float: %f\n", rightTrigger);

            // --- ANALOGICOS (-1.0f ate 1.0f com Deadzone de 5%) ---
            float thumbLX = 0.0f;
            float thumbLY = 0.0f;

            if (abs(ctrl.s1x) > ANALOG_DEADZONE) {
                thumbLX = (ctrl.s1x > 0) ? (float)(ctrl.s1x - ANALOG_DEADZONE) / (32767.0f - ANALOG_DEADZONE)
                                         : (float)(ctrl.s1x + ANALOG_DEADZONE) / (32768.0f - ANALOG_DEADZONE);
            }
            if (abs(ctrl.s1y) > ANALOG_DEADZONE) {
                thumbLY = (ctrl.s1y > 0) ? (float)(ctrl.s1y - ANALOG_DEADZONE) / (32767.0f - ANALOG_DEADZONE)
                                         : (float)(ctrl.s1y + ANALOG_DEADZONE) / (32768.0f - ANALOG_DEADZONE);
            }

            if (thumbLX != 0.0f || thumbLY != 0.0f) {
                printf("Analogico Esquerdo -> X: %f Y: %f\n", thumbLX, thumbLY);
            }
        }
        
        delay(10); // Evita superaquecimento
    }
    return 0;
}
