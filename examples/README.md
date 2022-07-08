# OFFLOADING

### Generate executable
```
export MYCLANG='/home/randreshg/soft/llvm-offloading/bin/clang'
export MYCLANG='/home/randreshg/soft/llvm-offloading-test/bin/clang'
$MYCLANG -fopenmp -fopenmp-targets=nvptx64 code.c -o code
$MYCLANG -fopenmp -fopenmp-targets=nvptx64-nvidia-cuda -Xopenmp-target -march=sm_80 
simple.c -o simple
clang -fopenmp -fopenmp-targets=nvptx64-nvidia-cuda -Xopenmp-target -march=sm_70 simple1.c -o simple1
LIBOMPTARGET_DEBUG=1 ./code //To get debug information
```
### To get device info
- Print all data arguments upon entering an OpenMP device kernel: ``0x01``
- Indicate when a mapped address already exists in the device mapping table: ``0x02``
- Dump the contents of the device pointer map at kernel exit: ``0x04``
- Indicate when an entry is changed in the device mapping table: ``0x08``
- Print OpenMP kernel information from device plugins: ``0x10``
- Indicate when data is copied to and from the device: ``0x20``
```
$MYCLANG -fopenmp -fopenmp-targets=nvptx64 code.c -o code
LIBOMPTARGET_INFO=1 ./code
```

### For debugging

```
$MYCLANG -fopenmp -fopenmp-targets=nvptx64 -fopenmp-target-new-runtime -fopenmp-target-debug=3 code.c -o code
LIBOMPTARGET_DEVICE_RTL_DEBUG=3 ./code
``

### Generate LLVM IR
```
clang simple.c -fopenmp -fopenmp-targets=nvptx64 -S -emit-llvm -O0
```
### Profiler
```
nsys nvprof --print-gpu-trace ./simple

```

### Debugger
```
add -g
gdb ./simple
run > Execute code
bt -> Backtrace
b -> breakpoint (break /Full/path/to/service.cpp:45)
c -> Execute until breakpoint
next
```

### Compiler explorer
```
Compiler: x86-64 clang (trunk)
-O0 -fopenmp -fopenmp-targets=nvptx64 -emit-llvm
```

### Rebuild compiler
```
cmake ../llvm  -DCMAKE_INSTALL_PREFIX=../../../soft/llvm-offloading -DCMAKE_BUILD_TYPE=Release -G Ninja  -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DLLVM_ENABLE_PROJECTS='clang;openmp;lld;lldb;compiler-rt' -DLLVM_APPEND_VC_REV=OFF -DLLVM_ENABLE_ASSERTIONS=ON -DLLVM_USE_LINKER=lld  -DBUILD_SHARED_LIBS=ON -DLLVM_OPTIMIZED_TABLEGEN=ON -DLLVM_CCACHE_BUILD=ON -DCLANG_ENABLE_STATIC_ANALYZER=ON  -DLIBOMPTARGET_NVPTX_COMPUTE_CAPABILITIES=60,70,75,80 -DOPENMP_ENABLE_LIBOMPTARGET=ON -DCLANG_OPENMP_NVPTX_DEFAULT_ARCH=sm_80 -DLIBOMPTARGET_NVPTX_DEBUG=1 -DLIBOMPTARGET_ENABLE_DEBUG=1

sudo ninja

sudo ninja install

cmake -Bbuild -H. -DMODEL=omp -DCMAKE_CXX_COMPILER=clang++ -DOFFLOAD=ON -DOFFLOAD_FLAGS='-fopenmp -fopenmp-targets=nvptx64-nvidia-cuda -Xopenmp-target -march=sm_80'
cmake --build build
./build/omp-stream
```