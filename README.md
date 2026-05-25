# Modelagem Hierárquica em OpenGL Moderno

Exemplo prático de modelagem hierárquica utilizando OpenGL moderno (GLFW + GLAD + GLM).

O projeto demonstra como construir objetos complexos a partir da reutilização de uma geometria simples (cubo), aplicando transformações geométricas e relações hierárquicas entre objetos.

## Estrutura do exemplo

O braço robótico é composto por:

```text
Base
 └── Braço
      └── Antebraço
```

Cada componente utiliza a mesma geometria básica e difere apenas por transformações aplicadas à matriz `Model`.

## Conceitos abordados

- Transformações geométricas 3D
- Matrizes Model, View e Projection
- Reutilização de geometria
- Modelagem hierárquica
- Pivôs
- Herança de transformações
- Animação por teclado

## Hierarquia utilizada

```text
M_braco      = M_base × M_local
M_antebraco  = M_braco × M_local
```

Isso significa:

- se a base gira → todo o sistema acompanha;
- se o braço gira → o antebraço acompanha;
- se o antebraço gira → somente ele se move.

## Controles

| Tecla | Ação |
|--------|-------|
| A | Rotaciona a base para esquerda |
| D | Rotaciona a base para direita |
| W | Move o braço |
| S | Move o braço |
| Q | Move o antebraço |
| E | Move o antebraço |
| ESC | Fecha a aplicação |

## Dependências

- OpenGL 3.3+
- GLFW
- GLAD
- GLM

## Compilação (Linux)

```bash
g++ main.cpp glad.c -o app \
-lglfw -ldl -lGL
```

Executar:

```bash
./app
```

## Objetivo didático

Este exemplo foi desenvolvido para demonstrar que objetos complexos podem ser construídos reutilizando geometrias simples e organizando relações entre transformações.

A ideia central é:

```text
mesma geometria
+ transformações
+ hierarquia
=
objetos complexos
```
