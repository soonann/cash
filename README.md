# Crunchy 

Crunchy is a Linux Shell implemented in `C`.

![](./docs/demo.mp4)

This shell aims to meet the all the **9 lvls** of the [Kernel Development Pipeline](https://kdlp.underground.software/course/fall2023/assignments/P0.md) along with the bonus section.

## Dependencies

The project has the following dependencies:
- `make` (4.4.1)
- `gcc` (13.2.1)
- `docker` (optional)

## Building

A Dockerfile that builds a Fedora based image with Crunchy installed as the default shell can be found at `docker/Dockerfile`

To build and run the docker image, you can do the following:
```
# build the container image
make docker-build

# run the container image with an interactive shell
make docker-run
```


