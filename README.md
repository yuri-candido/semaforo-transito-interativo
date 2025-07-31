# semaforo-transito-interativo
Criação de um semáforo de trânsito com acionamento de travessia para pedestres e indicação de tempo restante.

### **Instruções:**    
**Descrição do sistema:**    
+ Ação 1 - descrição: O semáforo deve iniciar na cor vermelha e permanecer por 10(dez) segundos nesta cor;  
+ Ação 2 - descrição: Em seguida, deve acionar a cor verde e permanecer por 10 (dez) segundos;  
+ Ação 3 - descrição: Após isso, deve acionar a cor amarela e permanecer por (três) segundos. Neste experimento, utilize simultaneamente os LEDs Verde (GPIO 11) e Vermelho (GPIO 13) para obter o amarelo no LED RGB da BitDogLab;  
+ Ação 4 - descrição: Em seguida, deve repetir continuamente o ciclo acima descrito, a menos que um pedestre deseje atravessar a rua, quando então deverá acionar um Botão para que o semáforo acione a cor vermelha, permitindo sua passagem;  
+ Ação 5 - descrição: Ao acionar o Botão de passagem de pedestres, o semáforo deve acender amarelo e permanecer por 3 (três) segundos para, em seguida, comutar para o vermelho, reiniciando então todo o ciclo;  
+ Ação 6 - descrição: A cada cor acesa, o sistema deve imprimir no Monitor Serial o texto: “Sinal: nome da cor”. O mesmo deve ocorrer quando o Botão de pedestres for pressionado: “Botão de Pedestres acionado”;

**Materiais e Conceitos Envolvidos:**  
+ Botão (A ou B) – Simula a botoneira acionada pelo pedestre;  
+ LED RGB - Simula as cores do semáforo;  
+ Buzzer – Simula emissão de alerta sonoro para pedestres com
baixa visão ou cegos (acessibilidade);  
+ Monitor Serial: Simula o cronômetro regressivo para visualização
do tempo restante de travessia para o pedestre. Também pode ser
implementando com o Display OLED presente na plataforma
BitDogLab;  
+ Temporização de sistemas utilizando o Periférico Avançado
“Temporizador” do RP2040;  
+ Alarmes e Interrupções  

**Requisitos técnicos:**  
+ Usar a biblioteca “hardware/timer.h”;  
+ Utilizar as funções de alarme, temporização, interrupção e
Callback;  
+ Todo o processo deve ocorrer FORA do Loop Infinito, poupando
recursos da CPU para outras tarefas que requeiram maior poder de
processamento;  
+ Não deve ser utilizada a técnica de pooling com monitoramento
contínuo do(s) Botão(ões).  
