# 3d_triangles
Project that uses linear algebra to discover if two (or more) 
## How to launch:

1. Cloning project:
```
git clone https://github.com/2APetrin/3d_triangles.git
cd 3d_triangles
```

2. Creating directory for build + build itself
```
mkdir build
cd build/
cmake ..
```

3. Starting work
```
cd geometry/
make
cd ../tests/
make
```
So now you have two directories with executable files

4. Launch:
```
cd geometry/
./main_triag
```
or
```
cd tests/
./test_main
```

5. To launch other tests of main programm
```
./main_triag < *test_path*
```