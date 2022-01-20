<img src="net.webp">

# Secure Neural Network for Images

Train neural network with the encrypted data. This repository is supposed to contain a Deep Neural Network architecture and an Encryption library. This Encryption library takes the image and produces a meshed up image/array, which cannot be recovered. Train the Neural Network with this encrypted image. DNN would still be able to learn under these images and it would successfully classify the images. As the images cannot be recovered this algorithm is supposed to be privacy-preserving. [Note: This project is a part of my ongoing research on privacy-preserving Deep Learning Models under the supervision of **Prof. Avishek Adhikari**, Presidency University, Dept. of Mathematics, Kolkata.]

## Building The Project
Please use **cmake** to compile the project. It would create a bunch of dynamically linkable libraries along with the main file (which is for testing purposes). 
Download `gcc` and `cmake`. 
```bash
    # for debian based systems
    sudo apt-get install build-essential cmake
    # for arch based systems 
    sudo pacman -S base-devel camke
```
Another dependency is `OpenMP`.
```bash 
    # for debian based systems
    sudo apt-get isntall libopenmp-dev
    # for arch based systems 
    sudo pacman -S openmp
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