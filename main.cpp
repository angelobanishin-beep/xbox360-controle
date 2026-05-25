#include <xtl.h>
#include <stdio.h>

// Constantes de Deadzone (5% do valor maximo)
#define ANALOG_DEADZONE 1638
#define TRIGGER_DEADZONE 13

int main() {
    XINPUT_STATE state;
    DWORD controllerId = 0;

    printf("Mapeamento Xbox 360 Inicializado!\n");

    while (true) {
        // Limpa a estrutura e le o controle fisico do Xbox 360
        ZeroMemory(&state, sizeof(XINPUT_STATE));
        DWORD result = XInputGetState(controllerId, &state);

        if (result == ERROR_SUCCESS) {
            // --- GATILHOS (0.0f ate 1.0f - Deadzone 5%) ---
            float leftTrigger = 0.0f;
            float rightTrigger = 0.0f;

            if (state.Gamepad.bLeftTrigger > TRIGGER_DEADZONE) {
                leftTrigger = (float)(state.Gamepad.bLeftTrigger - TRIGGER_DEADZONE) / (255.0f - TRIGGER_DEADZONE);
            }
            if (state.Gamepad.bRightTrigger > TRIGGER_DEADZONE) {
                rightTrigger = (float)(state.Gamepad.bRightTrigger - TRIGGER_DEADZONE) / (255.0f - TRIGGER_DEADZONE);
            }

            // --- ANALOGICOS (-1.0f ate 1.0f - Deadzone 5%) ---
            float thumbLX = 0.0f;
            float thumbLY = 0.0f;

            SHORT rawLX = state.Gamepad.sThumbLX;
            SHORT rawLY = state.Gamepad.sThumbLY;

            // Tratamento absoluto manual para evitar erros de biblioteca
            int abs_x = (rawLX < 0) ? -rawLX : rawLX;
            int abs_y = (rawLY < 0) ? -rawLY : rawLY;

            if (abs_x > ANALOG_DEADZONE) {
                thumbLX = (rawLX > 0) ? (float)(rawLX - ANALOG_DEADZONE) / (32767.0f - ANALOG_DEADZONE)
                                      : (float)(rawLX + ANALOG_DEADZONE) / (32768.0f - ANALOG_DEADZONE);
            }
            if (abs_y > ANALOG_DEADZONE) {
                thumbLY = (rawLY > 0) ? (float)(rawLY - ANALOG_DEADZONE) / (32767.0f - ANALOG_DEADZONE)
                                      : (float)(rawLY + ANALOG_DEADZONE) / (32768.0f - ANALOG_DEADZONE);
            }

            // Imprime na tela do console se houver movimento
            if (thumbLX != 0.0f || thumbLY != 0.0f || leftTrigger > 0.0f || rightTrigger > 0.0f) {
                printf("LX: %.2f | LY: %.2f | LT: %.2f | RT: %.2f\n", thumbLX, thumbLY, leftTrigger, rightTrigger);
            }
        }
        Sleep(10);
    }
    return 0;
}
