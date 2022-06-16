# OFFLOADING

###Generate executable
```
export MYCLANG='/home/randreshg/soft/llvm-offloading/bin/clang'
$MYCLANG -fopenmp -fopenmp-targets=nvptx64 code.c -o code
$MYCLANG -fopenmp -fopenmp-targets=nvptx64-nvidia-cuda -Xopenmp-target -march=sm_80 simple.c -o simple
LIBOMPTARGET_DEBUG=1 ./code
```
###Generate LLVM IR
```
clang simple.c -fopenmp -fopenmp-targets=nvptx64 -S -emit-llvm -O0
```

###Compiler explorer
```
Compiler: x86-64 clang (trunk)
-O0 -fopenmp -fopenmp-targets=nvptx64 -emit-llvm
```

###Rebuild compiler
```
cmake ../llvm  -DCMAKE_INSTALL_PREFIX=../../../soft/llvm-offloading -DCMAKE_BUILD_TYPE=Release -G Ninja  -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DLLVM_ENABLE_PROJECTS='clang;openmp;lld;lldb;compiler-rt' -DLLVM_APPEND_VC_REV=OFF -DLLVM_ENABLE_ASSERTIONS=ON -DLLVM_USE_LINKER=lld  -DBUILD_SHARED_LIBS=ON -DLLVM_OPTIMIZED_TABLEGEN=ON -DLLVM_CCACHE_BUILD=ON -DCLANG_ENABLE_STATIC_ANALYZER=ON  -DLIBOMPTARGET_NVPTX_COMPUTE_CAPABILITIES=60,70,75,80 -DOPENMP_ENABLE_LIBOMPTARGET=ON -DCLANG_OPENMP_NVPTX_DEFAULT_ARCH=sm_80 -DLIBOMPTARGET_NVPTX_DEBUG=1 -DLIBOMPTARGET_ENABLE_DEBUG=1

sudo ninja

sudo ninja install

```