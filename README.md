# 🌿 Projeto Reflorestamento

Sistema de gerenciamento de projetos de reflorestamento desenvolvido em C, permitindo cadastrar projetos com suas respectivas espécies de árvores, quantidades e origens.

## 📋 Sobre o Projeto

Projeto desenvolvido como trabalho final da disciplina de **Algoritmos e Estrutura de Dados I**.

O sistema permite gerenciar projetos de reflorestamento de forma organizada, armazenando informações sobre cada projeto (nome, data de início, descrição) e as espécies de árvores associadas (nome científico, origem e quantidade de representantes).

A estrutura de dados utilizada é uma **lista duplamente encadeada aninhada com nó descritor**, aplicada tanto para projetos quanto para árvores. O sistema é dividido em quatro módulos principais:

```
sistema.h
├── ferramentas.h
└── projeto.h
    └── arvore.h
```

## 🚀 Como Compilar e Executar

```bash
gcc main.c -o reflorestamento
./reflorestamento
```

## 🗂️ Estrutura dos Módulos

| Módulo | Responsabilidade |
|---|---|
| `arvore.h` | Definição e manipulação do TAD Árvore e da lista de árvores |
| `projeto.h` | Definição e manipulação do TAD Projeto e da lista de projetos |
| `ferramentas.h` | Funções auxiliares (leitura de strings, limpeza de buffer, etc.) |
| `sistema.h` | Funcionalidades principais, menu e manipulação de arquivos |

## 🖥️ Menu do Sistema

```
+---------------------------------------+
|                 MENU                  |
+---------------------------------------+
| PROJETOS
| [1] Cadastrar projeto(s)
| [2] Remover projeto por nome
| [3] Listar projeto(s)
| [4] Pesquisar projeto por nome

| ARVORES
| [5] Cadastrar arvore em projeto
| [6] Remover especie de arvore em projeto
| [7] Listar arvores de um projeto
| [8] Contar arvores de um projeto
| [9] Total de arvores plantadas

| ARQUIVOS E RELATORIOS
| [10] Ler arquivo de projetos
| [11] Gerar relatorio dos projetos

| [0] Sair
_________________________________________
```

## 📁 Arquivos de Entrada

O sistema suporta leitura de projetos a partir de arquivos `.txt`. A pasta `Entradas/` contém três arquivos de exemplo:

- `entrada10Projetos.txt`
- `entrada20Projetos.txt`
- `entrada50Projetos.txt`

### Formato do arquivo

```
Nome do Projeto
DD/MM/AAAA
0               ← Sem descrição
N               ← Número de espécies
Especie 1
Origem Quantidade

Nome do Projeto 2
DD/MM/AAAA
1               ← Com descrição
Descricao do projeto.
N
Especie 1
Origem Quantidade
```

**Origem:** `1` = Nativa &nbsp;|&nbsp; `2` = Exótica

### Exemplo

```
Projeto Verde Bahia
05/01/2023
1
Iniciativa de reflorestamento para protecao de nascentes e cursos dagua.
3
Araucaria angustifolia
1 29
Pinus elliottii
2 13
Copaifera langsdorffii
1 12
```

Para carregar um arquivo, selecione a opção `[10]` no menu e informe o caminho:

```
Digite o caminho do arquivo: Entradas/entrada10Projetos.txt
Arquivo carregado com sucesso!
```

## 📄 Geração de Relatório

A opção `[11]` gera um relatório `.txt` no formato compatível com a leitura do sistema, podendo ser reutilizado como arquivo de entrada.

```
Digite o caminho onde deseja salvar o arquivo: 
Digite o nome do arquivo: relatorio
Relatorio gerado com sucesso!
```

## 🔧 Principais Funções

### Árvores
- `criarListaArvores()` — Aloca e inicializa uma lista de árvores
- `adicionarArvoreOrdenada()` — Insere uma árvore em ordem alfabética
- `removerArvores()` — Remove uma espécie da lista
- `buscarArvorePorNome()` — Busca uma árvore pelo nome científico
- `contarArvores()` — Conta o total de representantes na lista

### Projetos
- `criarListaProjetos()` — Aloca e inicializa uma lista de projetos
- `adicionarProjetoOrdenado()` — Insere um projeto em ordem alfabética
- `removerProjeto()` — Remove um projeto da lista
- `buscarProjetoPorNome()` — Busca um projeto pelo nome
- `contarArvoresProjetos()` — Conta o total de árvores em todos os projetos

## 📦 Estruturas de Dados

```c
typedef struct arvore {
    char nomeCientifico[60];
    int origem; // 1 = Nativa, 2 = Exótica
} Arvore;

typedef struct projeto {
    char nomeProjeto[60];
    char descricao[100];
    char dataDeInicio[12];
    ListaArvores arvores;
} Projeto;
```

## 🔗 Repositório

[github.com/pedrotavol/projeto-reflorestamento](https://github.com/pedrotavol/projeto-reflorestamento)
