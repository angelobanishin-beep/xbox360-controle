#include <xenon/xenon.h>
#include <console/console.h>
#include <usb/usbmain.h>
#include <input/input.h>
#include <stdio.h>
#include <stdlib.h>

// Constantes de Deadzone (5% do valor maximo)
#define ANALOG_DEADZONE 1638
#define TRIGGER_DEADZONE 13

int main() {
    // Inicializacao minima do hardware
    xenos_init();
    console_init();
    usb_init();

    printf("Controle Xbox 360 Pronto (Float e Deadzone 5%%)\n");

    while (1) {
        usb_do_poll();

        struct controller_data_s ctrl;
        // Le o primeiro controle conectado
        if (get_controller_data(&ctrl, 0)) {
            
            // --- GATILHOS (0.0f ate 1.0f - Deadzone 5%) ---
            float leftTrigger = 0.0f;
            float rightTrigger = 0.0f;

            if (ctrl.lt > TRIGGER_DEADZONE) {
                leftTrigger = (float)(ctrl.lt - TRIGGER_DEADZONE) / (255.0f - TRIGGER_DEADZONE);
            }
            if (ctrl.rt > TRIGGER_DEADZONE) {
                rightTrigger = (float)(ctrl.rt - TRIGGER_DEADZONE) / (255.0f - TRIGGER_DEADZONE);
            }

            // --- ANALOGICOS (-1.0f ate 1.0f - Deadzone 5%) ---
            float thumbLX = 0.0f;
            float thumbLY = 0.0f;

            // Tratamento manual de sinal absoluto sem depender de <math.h>
            int abs_x = (ctrl.s1x < 0) ? -ctrl.s1x : ctrl.s1x;
            int abs_y = (ctrl.s1y < 0) ? -ctrl.s1y : ctrl.s1y;

            if (abs_x > ANALOG_DEADZONE) {
                thumbLX = (ctrl.s1x > 0) ? (float)(ctrl.s1x - ANALOG_DEADZONE) / (32767.0f - ANALOG_DEADZONE)
                                         : (float)(ctrl.s1x + ANALOG_DEADZONE) / (32768.0f - ANALOG_DEADZONE);
            }
            if (abs_y > ANALOG_DEADZONE) {
                thumbLY = (ctrl.s1y > 0) ? (float)(ctrl.s1y - ANALOG_DEADZONE) / (32767.0f - ANALOG_DEADZONE)
                                         : (float)(ctrl.s1y + ANALOG_DEADZONE) / (32768.0f - ANALOG_DEADZONE);
            }

            // Imprime apenas se houver alguma mudanca significativa
            if (thumbLX != 0.0f || thumbLY != 0.0f || leftTrigger > 0.0f || rightTrigger > 0.0f) {
                printf("LX: %.2f | LY: %.2f | LT: %.2f | RT: %.2f\n", thumbLX, thumbLY, leftTrigger, rightTrigger);
            }
        }
    }
    return 0;
}

