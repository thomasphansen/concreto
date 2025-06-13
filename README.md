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

## Criação do pacote Debian

É possível gerar um pacote `.deb` executando:

```bash
make deb
```

O arquivo `Concreto.deb` será criado e pode ser instalado com:

```bash
sudo dpkg -i Concreto.deb
```

## Uso

Execute passando o traço no formato `a-b-c`, a granulometria do agregado graúdo em milímetros e o volume desejado em metros cúbicos:

```bash
./concreto 1-2-3 20 1.0
```

O programa exibirá as quantidades de cimento, água, areia e brita necessárias para produzir o volume informado. Os volumes são mostrados em litros.

