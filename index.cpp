#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include "llvm/IR/IRBuilder.h"
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>

#include "LLVMController.h"

int main() {
    // create context and other llvm stuff
    LLVMController controller;

    /* printf */
    {
    llvm::Type* voidType = llvm::Type::getVoidTy(controller.ctx);
    llvm::Type* arrayRef = llvm::PointerType::get(llvm::Type::getInt8Ty(controller.ctx), 0);
    llvm::FunctionType* funcType = llvm::FunctionType::get(voidType, arrayRef, false);
    llvm::Function* fn = controller.declareFunction("printf", funcType);
    }

    /* declare main function */
    {
    llvm::Type* voidType = llvm::Type::getVoidTy(controller.ctx);
    llvm::FunctionType* funcType = llvm::FunctionType::get(voidType, false);
    llvm::Function* main = controller.declareFunction("main", funcType);
    }

    /* define main function */
    {
        llvm::BasicBlock* entry = controller.defineFunction("main");
    }

    /* call printf w hello world */
    {
        llvm::Value* helloWorld = controller.builder->CreateGlobalStringPtr("Hello, World!\n");
        llvm::Value* args[] = {helloWorld};
        controller.callFunction(controller.module->getFunction("printf"), std::vector<llvm::Value*>(args, args + 1));
    }

    

    /* return  */
    {
        controller.builder->CreateRetVoid();
    }

    // output IR to out.ll file
    std::error_code EC;
    llvm::raw_fd_ostream file("out.ll", EC);
    controller.module->print(file, nullptr);
}