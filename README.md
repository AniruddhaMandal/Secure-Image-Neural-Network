<img src="net.webp">

# Secure Neural Network for Images

Train neural network with the encrypted data. This repository is supposed to contain a Deep Neural Network architecture and an Encryption library. This Encryption library takes the image and produces a meshed up image/array, which cannot be recovered. Train the Neural Network with this encrypted image. DNN would still be able to learn under these images and it would successfully classify the images. As the images cannot be recovered this algorithm is supposed to be privacy-preserving. [Note: This project is a part of my ongoing research on privacy-preserving Deep Learning Models under the supervision of **Prof. Avishek Adhikari**, Presidency University, Dept. of Mathematics, Kolkata.]

## Building The Project
This package is fairly easy to compile and run. As you follow the steps it would only take couple of minutes to setup and compile the project. Currently the project only supports linux so please use a linux system to compile and run the project.
### Dependencies: 
Download the following packages with the commands. Open up a terminal and past those commands. For Ubuntu use debian based commands, and for Manjaro use arch based commands. For any other package manager serch the following apckages.

1. Linux Build Essentials:
```bash
# for debian based systems
$ sudo apt-get install build-essential cmake
# for arch based systems 
$ sudo pacman -S base-devel camke
```
2. `CMAKE`:
```bash
# for debian based systems
$ sudo apt-get install cmake
# for arch based systems
$ sudo pacman -Ss cmake
```
3. `OpenMP`: 
```bash 
# for debian based systems
$ sudo apt-get isntall libopenmp-dev
# for arch based systems 
$ sudo pacman -S openmp
```
4. Create Directories:
```bash
# Go to the root folder of the project and
# create folders with names `DEBUG` and 
# `build` and `MNIST`.
$ mkdir DEBUG build MNIST
```
5. Download Data:

Download four files from <a hrf="http://yann.lecun.com/exdb/mnist/">MNIST website</a>. After download paste those files into the MNIST folder and unzip with following command.
```bash
# goto the MNIST folder and paste in your terminal
$ gz **
# that would unzip every file inside MNIST
```
6. Building Project:

```bash
# go to the build folder and use command.
$ cmake ..
$ make 
```
Then a executabel file called `Main` will be created along with some dynamically linked libraries. 

7. Runing Project:

To run the program use command:
```bash
$ ./Main
```

### Note: 
Include MathCal.h in the main file as it contains the initial seeds. Otherwise generated random numbers inside the random matrix would have same sign for all. Due to this reason the model would not learn.

## To Do:
1. Identify why it is not learning. :heavy_check_mark: 
2. Fix the learning issue. :heavy_check_mark:
3. Complete the encryption algorithm.:star2:
4. (Possibly ) add a network visualization tool.
5. Verify whether the _Accuracy function is working as expected. :heavy_check_mark:
6. Verify whether Matrix operations are working as expected. :heavy_check_mark: 
7. Verify whether BackPropagation is working properly. (Confirm any calculation or overflow error) :heavy_check_mark:
8. Parallelize NeuralNetwork (possibily with pthread or fork).
9. Solve any memory issues. :heavy_check_mark:
10. Change Random Number Generator. :heavy_check_mark:
11. Investigate why learning is being stoped after some steps. :heavy_check_mark:

## Problems:
1. Sometimes learning sometimes it is not learning. :heavy_check_mark:
2. Learning stoped after some steps. :heavy_check_mark:
3. Computation is extreamly slow. Use GPU parallelization.