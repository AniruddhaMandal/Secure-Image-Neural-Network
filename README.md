# Secure Neural Network for Images

Train neural network with the encrypted data. This repository is supposed to contain a Deep Neural Network architecture and an Encryption library. This Encryption library takes the image and produces a meshed up image/array, which cannot be recovered. Train the Neural Network with this encrypted image. DNN would still be able to learn under these images and it would successfully classify the images. As the images cannot be recovered this algorithm is supposed to be privacy-preserving. [Note: This project is a part of my ongoing research on privacy-preserving Deep Learning Models under the supervision of **Prof. Avishek Adhikari**, Presidency University, Dept. of Mathematics, Kolkata.]

## Building The Project
Please use **cmake** to compile the project. It would create a bunch of dynamically linkable libraries along with the main file (which is for testing purposes). 

## To Do:
1. Identify why it is not learning.
2. Fix the learning issue.
3. Complete the encryption algorithm.
4. (Possibly ) add a network visualization tool.
5. Why sometimes the gradient of the weights of the first layer is zero (completely zero :raised_eyebrow:)