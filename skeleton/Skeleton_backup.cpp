#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/ValueSymbolTable.h"
#include "llvm/IR/ValueMap.h"
#include <iostream>
using namespace llvm;

namespace {
  struct SkeletonPass : public FunctionPass {
    static char ID;
    SkeletonPass() : FunctionPass(ID) {}

    virtual bool runOnFunction(Function &F) {
      // Get the function to call from our runtime library.
      LLVMContext &Ctx = F.getContext();
      Constant *logFunc = F.getParent()->getOrInsertFunction(
        "logop", Type::getVoidTy(Ctx), Type::getInt32Ty(Ctx), NULL
      );
      Constant *initialFunc = F.getParent()->getOrInsertFunction(
        "LogInitial", Type::getVoidTy(Ctx), Type::getInt32Ty(Ctx),  NULL
      );
      Constant *assignedFunc = F.getParent()->getOrInsertFunction(
        "LogAssigned", Type::getVoidTy(Ctx), Type::getInt32Ty(Ctx), NULL
      );
      ValueSymbolTable* prev_table = new ValueSymbolTable();
      for (auto &B : F) {
       
        for (auto &I : B) {
         
          if (I.getOpcode() == Instruction::Store) {
            // Insert at the point where the instruction `op` appears.
            llvm::StoreInst *op = dyn_cast<llvm::StoreInst>(&I);
//             op->dump();
            IRBuilder<> builder(op);
            IRBuilder<> builder2(op);
            IRBuilder<> builder3(op);
            builder.SetInsertPoint(&B, --builder.GetInsertPoint());
            builder.SetInsertPoint(&B, --builder.GetInsertPoint());
            builder3.SetInsertPoint(&B, ++builder3.GetInsertPoint());
            // Insert a call to our function.
            Value *value = op->getValueOperand();
            Value *pointer = op->getPointerOperand();
            
//             symbolTable->dump();
//             ValueMap::iterator = symbolTable->begin();
             ValueSymbolTable* symbolTable = B.getValueSymbolTable();
            if(pointer->hasName() && pointer->getName().str() == "num") {
             Value* start_name = builder.CreateGlobalString(pointer->getName());
             
             Value* args[] = {start_name, pointer};
//              builder.CreateCall(initialFunc, args);
             std::vector<Value*> arguements;
            for(StringMapIterator<Value *> iter=symbolTable->begin(); iter != 
                symbolTable->end(); iter++) {
//               iter->first->dump();
              Value* iter_value = iter->second;
              if(iter_value->hasName()) {
                  iter_value->dump();
                  if(!prev_table->empty()) {
                  Value* last_value = prev_table->lookup(iter_value->getName());
                  if(iter_value->getName().str() != "argc" &&
                     iter_value->getName().str() != "argv"
                  ) {
                  Value* name = 
                      builder.CreateGlobalString(iter_value->getName());
//                       arguements.push_back(name);
//                   builder.SetInsertPoint(&B, ++builder.GetInsertPoint());
//                   builder.SetInsertPoint(&B, ++builder.GetInsertPoint());
//                   builder.SetInsertPoint(&B, ++builder.GetInsertPoint());
//                       arguements.push_back(iter_value);
//                    Value* args2[] = {name, iter_value};
//                    builder3.CreateCall(assignedFunc, args2);
//                   builder.SetInsertPoint(&B, ++builder.GetInsertPoint());
                  }
                  }
              }
            }
              
//               Value* size = ConstantInt::get(Type::getInt32Ty(Ctx), arguements.size() / 2);
//               arguements.insert(arguements.begin(), size);
//               ArrayRef<Value*>*  args2 = new ArrayRef<Value*>(arguements);
//               builder3.CreateCall(assignedFunc, *args2);
              prev_table = symbolTable;
             }
             

           
//             builder2.CreateCall(logFunc, rhs);
//             return true;
          }
//            std::cout << "loop" << std::endl;
        }
        
      }

      return false;
    }
  };
}

char SkeletonPass::ID = 0;

// Automatically enable the pass.
// http://adriansampson.net/blog/clangpass.html
static void registerSkeletonPass(const PassManagerBuilder &,
                         legacy::PassManagerBase &PM) {
  PM.add(new SkeletonPass());
}
static RegisterStandardPasses
  RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                 registerSkeletonPass);
