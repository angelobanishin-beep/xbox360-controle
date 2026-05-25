#include <iostream>
#include <cmath>

// Estrutura universal para simular os dados brutos do controle do Xbox 360
struct XboxControllerData {
    int s1x; // Analógico Esquerdo X (-32768 a 32767)
    int s1y; // Analógico Esquerdo Y (-32768 a 32767)
    int lt;  // Gatilho Esquerdo (0 a 255)
    int rt;  // Gatilho Direito (0 a 255)
};

// Constantes de Deadzone (5% do valor máximo)
const int ANALOG_DEADZONE = 1638; 
const int TRIGGER_DEADZONE = 13;   

// Função que processa os dados com a deadzone de 5% e converte para Float
void processarControle(const XboxControllerData& ctrl) {
    // --- GATILHOS (0.0f até 1.0f - Deadzone 5%) ---
    float leftTrigger = 0.0f;
    float rightTrigger = 0.0f;

    if (ctrl.lt > TRIGGER_DEADZONE) {
        leftTrigger = (float)(ctrl.lt - TRIGGER_DEADZONE) / (255.0f - TRIGGER_DEADZONE);
    }
    if (ctrl.rt > TRIGGER_DEADZONE) {
        rightTrigger = (float)(ctrl.rt - TRIGGER_DEADZONE) / (255.0f - TRIGGER_DEADZONE);
    }

    // --- ANALÓGICOS (-1.0f até 1.0f - Deadzone 5%) ---
    float thumbLX = 0.0f;
    float thumbLY = 0.0f;

    if (std::abs(ctrl.s1x) > ANALOG_DEADZONE) {
        thumbLX = (ctrl.s1x > 0) ? (float)(ctrl.s1x - ANALOG_DEADZONE) / (32767.0f - ANALOG_DEADZONE)
                                 : (float)(ctrl.s1x + ANALOG_DEADZONE) / (32768.0f - ANALOG_DEADZONE);
    }
    if (std::abs(ctrl.s1y) > ANALOG_DEADZONE) {
        thumbLY = (ctrl.s1y > 0) ? (float)(ctrl.s1y - ANALOG_DEADZONE) / (32767.0f - ANALOG_DEADZONE)
                                 : (float)(ctrl.s1y + ANALOG_DEADZONE) / (32768.0f - ANALOG_DEADZONE);
    }

    // Exibe os valores tratados na tela do terminal
    if (thumbLX != 0.0f || thumbLY != 0.0f || leftTrigger > 0.0f || rightTrigger > 0.0f) {
        std::cout << "LX: " << thumbLX << " | LY: " << thumbLY 
                  << " | LT: " << leftTrigger << " | RT: " << rightTrigger << "\n";
    }
}

int main() {
    std::cout << "Mapeamento do Controle Xbox 360 Inicializado (Float e Deadzone 5%)\n";
    
    // Teste simulando o analógico movido para a direita e gatilho pressionado pela metade
    XboxControllerData controleDeTeste = {10000, 0, 128, 0};
    processarControle(controleDeTeste);

    return 0;
}


