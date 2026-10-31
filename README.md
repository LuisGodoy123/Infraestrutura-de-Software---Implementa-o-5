# Infraestrutura de Software - Implementação 5: Sincronização do Metrô

Sincronização entre vagões (threads) e passageiros (threads) de uma estação de metrô, usando um único mutex e variáveis de condição (pthreads).

## Arquivos

| Arquivo | Descrição |
|---|---|
| `sync_car.h` | Declaração da `struct station` e dos protótipos das funções |
| `sync_car.c` | Implementação de `station_init`, `station_load_car`, `station_wait_for_car` e `station_on_board` |
| `sync_car-runner.c` | Programa de teste fornecido pelo professor (contém o `main`) |
| `Makefile` | Compila o executável `sync_car` e limpa os arquivos gerados |
| `evidencias.log` | Registro dos comandos de teste executados e suas saídas |

## Sistema operacional

Desenvolvido e testado no Ubuntu 26.04 LTS (WSL), com gcc 15.2.0 e GNU Make 4.4.1. Deve funcionar em qualquer Linux, Unix ou macOS com gcc/clang e pthreads.

## Compilar

```
make
```

Gera o executável `sync_car` (junção de `sync_car-runner.c` com `sync_car.c`).

## Executar e testar

```
./sync_car
```

O teste é o próprio runner: ele cria 100 threads de passageiros, faz carros com número aleatório de assentos entrarem na estação e confere quantos passageiros embarcam em cada um. Em caso de sucesso imprime `Looks good!` e retorna 0; em caso de erro imprime a mensagem em stderr e retorna 1.

Como o teste usa números aleatórios, para exercitar mais cenários basta rodar várias vezes:

```
for i in $(seq 200); do ./sync_car > /dev/null 2>&1 || echo falhou; done
```

## Limpar

```
make clean
```

Remove o executável `sync_car`.

## Estratégia

- `free_seats`: assentos livres do carro presente (0 quando não há carro).
- `waiting`: passageiros esperando.
- `boarding`: passageiros que receberam assento e ainda não chamaram `station_on_board`.
- `car_arrived`: condição em que os passageiros dormem até haver carro com assento livre.
- `all_aboard`: condição em que o carro dorme até que todos tenham embarcado e o carro esteja cheio ou a fila vazia.

Não há busy-wait: toda espera é feita com `pthread_cond_wait`.
