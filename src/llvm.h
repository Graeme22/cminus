#ifndef _LLVM_H_
#define _LLVM_H_

#include <map>
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"

// LLVM related
extern std::unique_ptr<llvm::LLVMContext> context;
extern std::unique_ptr<llvm::Module> llvmModule;
extern std::unique_ptr<llvm::IRBuilder<>> builder;
extern std::map<std::string, llvm::AllocaInst *> namedValues;

#endif