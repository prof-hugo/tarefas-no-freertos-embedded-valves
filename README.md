# tarefas-no-freertos-embedded-valves
tarefas-no-freertos-embedded-valves created by GitHub Classroom


Implementação do exercício 3 da aula FreeRTOS parte 3.

Uso do programa base semphr_FreeRTOS_qemu como base para fazer uma fila (queue) para a troca de informações entre as tarefas, mantendo as funcionalidades do arquivo base original.

Projeto finalizado.

Questões teóricas:

1a)

1b) Quando ambas as tarefas são periódicas o buffer irá determinar quantos dados poderão ficar armazenados sem serem consumidos. Logo, se a tarefa produtora produzir dados mais rapidamente do que a tarefa consumidora consome os dados, essa diferença irá preenchendo o buffer. Quanto maior o tamanho do buffer mais dados serão armazenados. Caso a tarefa consumidora tenha um período menor que a tarefa produtora o buffer não terá tanta utilidade, pois assim que o dado for produzido ele será imediatamente consumido.

1c)

2a) 

2b)

3b) A implementação das queues é mais simples de modo que não é necessário a indexação da fila, tornando o programa mais fácil do ponto de vista do programador e também mais confiável pois é o próprio RTOS que faz o arranjo de índices. Também há facilidade e otimização de memória com o uso de somente uma queue, quando no caso do semáforo é necessária a criação de um consumidor e um produtor.
