# KSS16-P329 # KSS16-P330 # KSS16-P766
### Algorithms

Based on [RELIC cryptographic toolkit](https://github.com/relic-toolkit/relic) we implemented a new method about membership testing for $\mathbb{G}_2$ on three KSS16 curves: KSS16-329, KSS16-330 and KSS16-766. 

### Requirements

The build process requires the [CMake](https://cmake.org/) cross-platform build system. The [GMP](https://gmplib.org/) library is also needed in our benchmarks.

### Build instructions

Instructions for building the library can be found in the [Wiki](https://github.com/relic-toolkit/relic/wiki/Building).


### Source code
  
The main source codes of our algorithm about the new method are distributed in different folders. The main functions are:
* ep4_tau(ep4_t r, const ep4_t p): given $p\in \mathbb{G}_2$, computing tau(p). (in \src\epx\relic_ep4_frb.c)
* g2_is_valid_kss16(const g2_t a): checking whether $a$ is a point in $\mathbb{G}_2$ or not. (in \src\pc\relic_pc_util.c)

### Testings, benckmarks and comparisons
* Testings and benckmarks: Function testings and benckmarking can be done by performing the following commands：

    1. mkdir build && cd build 
    2. ../preset/x64-pbc-kss16-329.sh ../
    3. make
    4. cd bin 
    5. ./test_kss16_g2
    6. ./bench_kss16_g2
    
* 'kss16-329' in step 2 can be replaced by 'kss16-330' and 'kss16-766' to apply our new method on these curves. 
  
* step 5 is to check that our implementation is corrret:
Testing if validity test with new method (for KSS16 curves)
Testing if blinding with new method (for KSS16 curves) is consistent. 

* step 6 is to obtain clock cycles of the new method about membership testing for $\mathbb{G}_2$ on KSS16-P329 (or KSS16-P330, KSS16-P766):
BENCH: g2_is_valid_kss16
 
* Comparisons: After executing "./bench_pc" , BENCH: g2_is_valid and BENCH: g2_is_valid_kss16 are shown with their clock cycles respectively, which can be compared to conclude that our new method is about 24.0%, 33.3% and 29.2% faster than the previous method(https://doi.org/10.1007/s10623-023-01223-7) on KSS16-P329, KSS16-P330 and KSS16-P766, respectively. 
