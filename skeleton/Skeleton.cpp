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

bool RelevantUsers(Value* value, std::string relevance) {
  bool relevant = false;
//   std::cout << "NumUsers2: " << value->getNumUses() <<  std::endl;
  for(auto U : value->users()){  // U is of type User*
    if (auto J= dyn_cast<Instruction>(U)){

      if (!J->isIdenticalTo((dyn_cast<Instruction>(value)))) {

        if (J->getOpcode() == Instruction::Store) {
          llvm::StoreInst *user = dyn_cast<llvm::StoreInst>(J);
          Value *pointer = user->getPointerOperand();
          if(pointer->hasName() && pointer->getName().str() == relevance) {
            return true;
          }
          if (pointer != value) {
          if (RelevantUsers(pointer, relevance)) {
            return true;
          }
          }
        }
        if (RelevantUsers(J, relevance)) {
          return true;
        }
      }
    }
  }
  return false;
}

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
      int x = 0;
      for (auto &B : F) {

        for (auto &I : B) {
          std::cout << "Instruction" << std::endl;
//           I.dump();
          bool relevant = false;
          if (I.getOpcode() == Instruction::Store) {
            // Insert at the point where the instruction `op` appears.
            llvm::StoreInst *op = dyn_cast<llvm::StoreInst>(&I);
            Value *pointer = op->getPointerOperand();
            relevant = RelevantUsers(pointer, "output");
            }
            I.dump();
            std::cout << "RELEVANCE: " <<  relevant << std::endl;
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
