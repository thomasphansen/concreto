# concreto

Programa em C para calcular os materiais de um traço de concreto.

## Compilação

Use o `gcc` para compilar:

```bash
gcc -o concreto concreto.c
```

## Uso

Execute passando o traço no formato `a-b-c`, a granulometria do agregado graúdo em milímetros e o volume desejado em metros cúbicos:

```bash
./concreto 1-2-3 20 1.0
```

O programa exibirá as quantidades de cimento, água, areia e brita necessárias para produzir o volume informado.
