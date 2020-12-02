# OBS Flip and Sum Filter

## Introduction

This is a very simple audio filter plugin for OBS Studio which reduces noise by
downmixing a stereo channel to a mono channel via difference. Noise which occurs
on both channels (e.g. due to mains loops or inadequate shielding of the cables)
will be cancelled.

## Build

This is largely cargo-culted, so I make no guarantees that it will work for you.

### Linux

    sudo apt-get install libobs-dev

    git clone https://github.com/pjt33/obs-flip-sum-filter.git
    mkdir obs-flip-sum-filter/build
    cd obs-flip-sum-filter/build
    cmake ..
    make
    mkdir -p ~/.config/obs-studio/plugins/obs-flip-sum-filter/bin/64bit/
    cp obs-flip-sum-filter.so ~/.config/obs-studio/plugins/obs-flip-sum-filter/bin/64bit/
