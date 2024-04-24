# g++ -std=c++17 *.cpp -o index -I/usr/local/include/antlr4-runtime -L. -lantlr4-runtime
g++ *.cpp -o codegen  -std=c++17 -g  `llvm-config --cflags --libs`
sudo cp ./codegen /usr/local/bin