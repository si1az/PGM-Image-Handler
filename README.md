# PGM-Transformer
## A mini-project from 2021 that works with PGM files.
## I used XnView to view the PGM files. <img src="https://www.xnview.com/img/app-xnview-512.png" width="48" align="middle">
- The transformer's invent function uses the following formula:
  - array[i][j] = abs(255 - array[i][j])
  - where array is a matrix of grayscale pixels
- The PGM file to be transformed is able to be opened through the fstream C++ library since PGM is solely a collection of integers seperated by whitespace, where each integer is a pixel.
- Each pixel is represented by a value between 0 (black) and 255 (white), with the values in between representing different shades of gray.
- Average functions are able to simply calculate the following averages:
  - row pixel average
  - column pixel average
  - total matrix pixel average
- guyDude.pgm is the starter image to test with.
