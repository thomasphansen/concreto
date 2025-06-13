# Concreto

Programa em C para calcular os materiais de um traço de concreto.

## Compilação e testes

Primeiro execute o script `configure` para definir o prefixo de instalação (padrão `/usr/local`):

```bash
./configure
```

Em seguida compile e rode os testes:

```bash
make
make test
```

## Instalação

Para instalar o binário no sistema utilize:

```bash
sudo make install
```

O executável será copiado para `$(PREFIX)/bin`.
Os binários compilados ficam disponíveis em `build/concreto` (CLI) e
`build/concreto-gui` (interface gráfica Qt).

Para instalar a página de manual utilize:

```bash
sudo make manpage
```

## Criação do pacote Debian

É possível gerar um pacote `.deb` executando:

```bash
make deb
```

O arquivo `build/Concreto.deb` será criado e pode ser instalado com:

```bash
sudo dpkg -i build/Concreto.deb
```

O pacote já inclui a página de manual em `man1/concreto.1.gz`.

## Uso

Execute passando o traço no formato `a-b-c`, a granulometria do agregado graúdo em milímetros e o volume desejado em metros cúbicos:

```bash
./build/concreto 1-2-3 20 1.0
```

O programa exibirá as quantidades de cimento, água, areia e brita necessárias para produzir o volume informado. Os volumes são mostrados em litros.

Também é possível utilizar a interface gráfica executando `concreto-gui` após a instalação ou abrindo o atalho criado pelo pacote.

