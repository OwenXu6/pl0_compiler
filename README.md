
编译程序:
> g++ -std=c++11 -O3 main.cpp -o pl0

运行代码:
> ./pl0 -exec filename

生成的中间代码文件:
code.txt

其中，pl.h是综合的头文件，pl_lex是词法分析部分，pl_ast是生成抽象语法树的一部分，pl_parse是语法分析部分，pl_code是中间代码生成部分。

