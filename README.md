
<a id="readme-top"></a>
<div align="center">
<h2 align="center">Fast Random Pathfinder</h2>

  <p align="center">
    A fast pathfinder that traverses randomly and self-optimizes.
  </p>
</div>

<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about">About</a>
    </li>
    <li>
      <a href="#getting-started">Getting started</a>
      <ul>
        <li><a href="#automatic-installer">Prerequisites</a></li>
      </ul>
      <ul>
        <li><a href="#manual-installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li>
      <a href="#uninstallation">Installation</a>
      <ul>
        <li><a href="#automatic-uninstaller">Automatic Unnstaller</a></li>
      </ul>
      <ul>
        <li><a href="#manual-uninstallation">Manual Unnstallation</a></li>
      </ul>
    </li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT -->
## About
Read the in-depth analysis of how Fast Random Pathfinder operates [here](https://www.nthorn.com/articles/fast-random-pathfinder).

Fast Random Pathfinder is a pathfinding algorithm that, as the name implies, traverses randomly until reaching it's goal. Although random, it is comparibly faster than alternative random pathfinding solutions. Fast Random Pathfinder also iteratively optimizes itself, increasing the odds of finding an optimal path.

It should be said that there is little use for a pathfinder that relies solely on random chance when traversing. This project exists solely for curiosity's sake, and should not even be considered for actual use cases when alternatives like [A*](https://en.wikipedia.org/wiki/A*_search_algorithm) exist.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- INSTALLATION -->
## Getting started

### Prerequisites

Fast Random Pathfinder relies on `<windows.h>` for visualization, making compilation difficult on Linux/macOS systems without the use of a virtual environment.

### Installation

1. Clone/download the repo
   ```sh
   git clone https://github.com/nTh0rn/fast-random-pathfinder.git
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- USAGE -->
## Usage

1. Build to `.exe` using [CMake](https://cmake.org/)
   ```sh
   cmake build .
   ```

<p align="center">
<img src="https://nthorn.com/images/fast-random-pathfinder/optimizeandtraverse.webp" width="500">
</p>

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

Nikolas Thornton - [nthorn.com](https://nthorn.com) - contact@nthorn.com

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

* [C++ Clear Screen](https://stackoverflow.com/a/70131006)

<p align="right">(<a href="#readme-top">back to top</a>)</p>
