# Trabalho de Sistemas Operacionais

## Execução
Para abrir esse projeto é necessário as bibliotecas **pthread**, **allegro5**.

### Opção 1 (Usando Make)

Após instalado essas dependências, execute o comando abaixo:
```bash
make build run
```

### Opção 2 (Usando CMD) Windows

```bash
g++ src\\main.cpp src\\physics\\physics.cpp src\\cannonLogic\\cannon.cpp src\\bombLogic\bomb.cpp src\\heliLogic\heli.cpp -o executable.exe -Wall -Wextra -Wshadow -Wconversion -lallegro -lallegro_font -lallegro_primitives -lallegro_image -pthread -lallegro_ttf
```

### Opção 3 (Usando CMD) Linux

```bash
g++ src/main.cpp src/physics/physics.cpp src/cannonLogic/cannon.cpp src/bombLogic/bomb.cpp src/heliLogic/heli.cpp -o executable.exe -Wall -Wextra -Wshadow -Wconversion -lallegro -lallegro_font -lallegro_primitives -lallegro_image -pthread -lallegro_ttf
```