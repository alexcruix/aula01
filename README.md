PIC16F876A + LCD 16x2 (HD44780) — Demo para Proteus

Resumo
- MCU: PIC16F876A
- Compilador: MPLAB XC8 v2 (xc8-cc)
- Mensagem: "aqui funciona" na 1ª linha, "tudo" na 2ª, seguido de contador 00–99

Arquivos
- src/main.c — código-fonte XC8
- Makefile — build simples via linha de comando
- firmware.hex — gerado após o build

Como compilar (Linux)
1) Instale MPLAB XC8 v2 e garanta o comando `xc8-cc` no PATH.
2) No diretório do projeto, execute:
   make
3) Resultado: `firmware.hex` no diretório raiz do projeto.

Pinos (PORTC → LCD)
- RC0 → RS
- RC1 → EN
- RC2 → D4
- RC3 → D5
- RC4 → D6
- RC5 → D7
- RW → GND, VSS → GND, VDD → +5V, VO (contraste) via trimpot 10 k

Configurações relevantes
- _XTAL_FREQ = 4 MHz (ajuste se usar outro clock)
- #pragma config FOSC = XT (para cristal até 4 MHz)
- ADCON1=0x06 para tornar I/O digitais

Como simular no Proteus
1) Abra o Proteus e crie um novo projeto esquemático.
2) Adicione um PIC16F876A e um LCD 16x2 (HD44780)
3) Faça as ligações conforme a seção de pinos acima; ligue MCLR ao VDD via resistor de 10 k.
4) No PIC, carregue o arquivo `firmware.hex` (gerado pelo make).
5) Rode a simulação. A mensagem deve aparecer e o contador avançará de 00 a 99.

Solução de problemas
- Se nada aparecer, ajuste o contraste (VO) e confirme RW no GND.
- Verifique o clock e `#pragma config` condizentes com seu projeto.
- Aumente `__delay_ms(20)` para 40 ms em `lcd_init()` em LCDs mais lentos.

# Aula01
 Aprendendo js
