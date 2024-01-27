# The Embroidermodder Project Website

This repository contains most of the broader documentation and automation to
stop minor changes flooding each of Embroidermodder's sub-projects. Including
the documentation as webpages for the
[site itself](https://www.libembroidery.org), each subproject's user manual but
not the reference manual.

This frees the other repositories of the minor-commit heavy mundane tasks of
bundling software and separating a "user" build from a "production" build. It
also means that those projects aren't tasked with keeping production history.

For in-depth information about the software please read some of the PDF manual
included in the top level of the repository. Finishing the manual is the current
top priority in order to fascilitate new developers joining the project.

## Style

Inspired by https://github.com/clayh53/tufte-jekyll and uses
https://github.com/edwardtufte/tufte-css. Both under the MIT License.

## Ideas

A testing site that is maintained under testing.libembroidery.org so builds
don't go straight to the main landing page.

If this reaches the cap of storage offered by a github repository then we'll
have to think of something else since the version history of the binaries could
quickly become important if we have any regressions.

## Build

    sphinx-build -M html . _build

